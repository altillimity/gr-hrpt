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

#ifndef INCLUDED_HRPT_VITERBI_METOP_DECODER_IMPL_H
#define INCLUDED_HRPT_VITERBI_METOP_DECODER_IMPL_H

#include <hrpt/viterbi_metop_decoder.h>

#define TestBitsLen 1024

extern "C"
{
#include <viterbi_lib/viterbi.h>
}

namespace gr
{
namespace hrpt
{

class viterbi_metop_decoder_impl : public viterbi_metop_decoder
{
private:
  bool d_sync_check;
  float d_ber_threshold;
  int d_insync_after;
  int d_outsync_after;
  int d_reset_after;

  float ber_calc1(struct viterbi_state *state0, struct viterbi_state *state1, unsigned int symsnr, unsigned char *insymbols_I, unsigned char *insymbols_Q);
  void phase_move_two(unsigned char phase_state, unsigned int symsnr, unsigned char *in_I, unsigned char *in_Q, unsigned char *out_I, unsigned char *out_Q);

  void do_reset();
  void enter_idle();
  void enter_syncing();
  void enter_synced();

  int d_mettab[2][256]; //metric table for continuous decoder

  struct viterbi_state d_state0[64]; //main viterbi decoder state 0 memory
  struct viterbi_state d_state1[64]; //main viterbi decoder state 1 memory

  unsigned char d_viterbi_in[4];
  bool d_viterbi_enable;
  unsigned int d_shift, d_shift_main_decoder;
  unsigned int d_phase;
  bool d_valid_ber_found;

  unsigned char d_bits, d_sym_count;
  bool d_even_symbol_last, d_curr_is_even, d_even_symbol;

  struct viterbi_state d_00_st0[64];
  struct viterbi_state d_00_st1[64];

  struct viterbi_state d_180_st0[64];
  struct viterbi_state d_180_st1[64];

  float d_ber[4][8];
  unsigned int d_chan_len;            //BER test input syms
  unsigned char d_valid_packet_count; //count packets with valid BER
  unsigned char d_invalid_packet_count;
  unsigned char d_state;

public:
  viterbi_metop_decoder_impl(bool sync_check, float ber_threshold, int insync_after, int outsync_after, int reset_after);
  ~viterbi_metop_decoder_impl();

  // Where all the action really happens
  void forecast(int noutput_items, gr_vector_int &ninput_items_required);

  int general_work(int noutput_items,
                   gr_vector_int &ninput_items,
                   gr_vector_const_void_star &input_items,
                   gr_vector_void_star &output_items);

  void set_sync_check(bool sync_check) { d_sync_check = sync_check; };
  void set_ber_threshold(float ber_threshold) { d_ber_threshold = ber_threshold; };
  void set_insync_after(int insync_after) { d_insync_after = insync_after; };
  void set_outsync_after(int outsync_after) { d_outsync_after = outsync_after; };
  void set_reset_after(int reset_after) { d_reset_after = reset_after; };
};

} // namespace hrpt
} // namespace gr

#endif /* INCLUDED_HRPT_VITERBI_METOP_DECODER_IMPL_H */
