/* -*- c++ -*- */
/*
 * Copyright 2020 Aang23 / mbsat.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "metop_cadu_deframer_impl.h"
#include <hrpt/metop_cadu.h>

namespace gr
{
namespace hrpt
{

#define ST_IDLE 0
#define ST_SYNCING 1
#define ST_SYNCED 2
#define ST_CHECK_SYNC 3

metop_cadu_deframer::sptr
metop_cadu_deframer::make(bool sync_check, int frame_length, int insync_after, int outsync_after)
{
  return gnuradio::get_initial_sptr(new metop_cadu_deframer_impl(sync_check, frame_length, insync_after, outsync_after));
}

/*
     * The private constructor
     */
metop_cadu_deframer_impl::metop_cadu_deframer_impl(bool sync_check, int frame_length, int insync_after, int outsync_after)
    : gr::block("metop_cadu_deframer",
                gr::io_signature::make(1, 1, sizeof(char)),
                gr::io_signature::make(1, 1, sizeof(char))),
      d_sync_check(sync_check),
      d_frame_length(frame_length),
      d_insync_after(insync_after),
      d_outsync_after(outsync_after)
{
  set_output_multiple(SYNC_WORDS); // room for writing full sync when received

  enter_idle();
}

/*
     * Our virtual destructor.
     */
metop_cadu_deframer_impl::~metop_cadu_deframer_impl()
{
}

void metop_cadu_deframer_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required)
{
  ninput_items_required[0] = noutput_items;
}

void metop_cadu_deframer_impl::enter_idle()
{
  d_state = ST_IDLE;
  d_item_count = 0;
  d_sync_marker_count = 0;
  d_negative = false;
  d_nosync_marker_count = 0;
}

void metop_cadu_deframer_impl::enter_syncing()
{
  d_state = ST_SYNCING;
  d_item_count = 0;
  d_shifter = 0;
}

void metop_cadu_deframer_impl::enter_synced()
{
  d_state = ST_SYNCED;
  d_bit_count = BITS_PER_WORD;
  d_word_count = d_frame_length - SYNC_WORDS;
  d_word = 0;
  d_item_count = 0;
}

void metop_cadu_deframer_impl::enter_staysynced()
{
  d_state = ST_SYNCED;
  d_bit_count = BITS_PER_WORD;
  d_word_count = d_frame_length - SYNC_WORDS;
  d_word = 0;
}

void metop_cadu_deframer_impl::enter_checksync()
{
  d_state = ST_CHECK_SYNC;
  d_item_count = 0;
}

int metop_cadu_deframer_impl::general_work(int noutput_items,
                                           gr_vector_int &ninput_items,
                                           gr_vector_const_void_star &input_items,
                                           gr_vector_void_star &output_items)
{
  int ninputs = ninput_items[0];
  const char *in = (const char *)input_items[0];
  unsigned char *out = (unsigned char *)output_items[0];
  char bit;
  int i = 0, j = 0;
  while (i < ninputs && j < noutput_items)
  {

    if (d_negative)
    {
      bit = (~in[i++]) & 1;
    }
    else
    {
      bit = in[i++];
    }

    switch (d_state)
    {
    case ST_IDLE:
      d_shifter = (d_shifter << 1) | bit;

      d_item_count++;

      if (d_shifter == ASM)
      {
        d_negative = false;
        printf("Deframer : BIT INVERSION ISN'T ACTIVE \n");
        d_sync_marker_count++;
        printf("Deframer : STATE %i , %i SYNC MARKER FOUND after %i bits \n",d_state, d_sync_marker_count,  d_item_count);
        if (d_sync_marker_count == d_insync_after)
        {
          enter_synced();
        }

        else
        {
          printf("Deframer : ENTER SYNCING STATE \n");
          enter_syncing();
        }
      }

      if (d_shifter == NASM)
      {
        d_negative = true;
        printf("Deframer : BIT INVERSION ACTIVE \n");
        d_sync_marker_count++;
        printf("Deframer : STATE %i , %i SYNC MARKER FOUND after %i bits \n",d_state, d_sync_marker_count,  d_item_count);
        if (d_sync_marker_count == d_insync_after)
        {
          enter_synced();
        }

        else
        {
          printf("Deframer : ENTER SYNCING STATE \n");
          enter_syncing();
        }
      }

      break;

    case ST_SYNCING:

      d_shifter = (d_shifter << 1) | bit;
      d_item_count++;
      if (d_item_count == d_frame_length * BITS_PER_WORD)
      {
        if (d_shifter == ASM)
        {
          d_sync_marker_count++;
          printf("Deframer : STATE %i , Sync marker nr %i found \n", d_state, d_sync_marker_count);
          d_item_count = 0;
          if (d_sync_marker_count == d_insync_after)
          {
            enter_synced();
            printf("Deframer : ENTER SYNCED STATE ofter %i valid sync ASM's \n", d_sync_marker_count);
            out[j++] = ASM1;
            out[j++] = ASM2;
            out[j++] = ASM3;
            out[j++] = ASM4;
          }
        }
        else
        {
          printf("Deframer : STATE %i , SYNC marker %i not present or invalid \n", d_state, d_sync_marker_count );
          printf("Deframer : ENTER IDLE STATE from syncing state \n");
          enter_idle();
        }
      }
      break;

    case ST_SYNCED:
      printf("bit count %i,   word count %i \n",d_bit_count, d_word_count);
      d_word = (d_word << 1) | bit;
      if (--d_bit_count == 0)
      {
        out[j++] = d_word;
        d_word = 0;
        d_bit_count = BITS_PER_WORD;
        if (--d_word_count == 0)
        {
          if (d_sync_check)
          {
            printf("Deframer : ST SYNCED , ENTER CHECK SYNC STATE \n");
            enter_checksync();
          }
          else
          {
            printf("Deframer : ST SYNCED , ENTER STAY SYNCED STATE \n");
            enter_staysynced();
            d_word_count = d_frame_length;
          }
        }
      }
      break;

    case ST_CHECK_SYNC:
      d_shifter = (d_shifter << 1) | bit;
      d_item_count++;
      if (d_item_count == SYNC_WORDS * BITS_PER_WORD)
      {
        d_item_count = 0;
        if (d_shifter == ASM)
        {
          printf("Deframer : STATE %i , CHECK SYNC, SYNC MARKER VALID\n", d_state);
          d_nosync_marker_count = 0;
          out[j++] = ASM1;
          out[j++] = ASM2;
          out[j++] = ASM3;
          out[j++] = ASM4;
          printf("Deframer : ST CHECK SYNC , ENTER STAY SYNCED STATE \n");
          enter_staysynced();
        }

        else
        {
          d_nosync_marker_count++;
          if (d_nosync_marker_count == d_outsync_after)
          {
            printf("Deframer : ENTER IDLE STATE from check sync state after %i invalid sync ASM's \n", d_nosync_marker_count);
            enter_idle();
          }
          else
          {
            out[j++] = ASM1;
            out[j++] = ASM2;
            out[j++] = ASM3;
            out[j++] = ASM4;
            enter_staysynced();
            printf("STATE %i , CHECK SYNC, SYNC MARKER %i from max %i is INVALID !!!!!!!\n", d_state, d_nosync_marker_count, d_outsync_after );
          }
        }
      }

      break;

    default:
      throw std::runtime_error("poesweather_metop_cadu_deframer: bad state\n");
    }
  }

  consume_each(i);
  return j;
}

} /* namespace hrpt */
} /* namespace gr */
