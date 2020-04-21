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

#ifndef INCLUDED_HRPT_METOP_CADU_DEFRAMER_IMPL_H
#define INCLUDED_HRPT_METOP_CADU_DEFRAMER_IMPL_H

#include <hrpt/metop_cadu_deframer.h>

namespace gr
{
namespace hrpt
{

class metop_cadu_deframer_impl : public metop_cadu_deframer
{
private:
  bool d_sync_check;
  int d_frame_length;
  int d_insync_after;
  int d_outsync_after;

  unsigned int d_state;
  unsigned int d_bit_count;
  unsigned int d_word_count;
  unsigned int d_sync_marker_count;
  unsigned int d_nosync_marker_count;
  unsigned long d_shifter;
  unsigned char d_word;
  unsigned int d_item_count;
  unsigned int d_framecount;
  bool d_negative;

  void enter_idle();
  void enter_syncing();
  void enter_synced();
  void enter_staysynced();
  void enter_checksync();

public:
  metop_cadu_deframer_impl(bool sync_check, int frame_length, int insync_after, int outsync_after);
  ~metop_cadu_deframer_impl();

  // Where all the action really happens
  void forecast(int noutput_items, gr_vector_int &ninput_items_required);

  int general_work(int noutput_items,
                   gr_vector_int &ninput_items,
                   gr_vector_const_void_star &input_items,
                   gr_vector_void_star &output_items);

  void set_sync_check(bool sync_check) { d_sync_check = sync_check; };
  void set_frame_length(int frame_length) { d_frame_length = frame_length; };
  void set_insync_after(int insync_after) { d_insync_after = insync_after; };
  void set_outsync_after(int outsync_after) { d_outsync_after = outsync_after; };
};

} // namespace hrpt
} // namespace gr

#endif /* INCLUDED_HRPT_METOP_CADU_DEFRAMER_IMPL_H */
