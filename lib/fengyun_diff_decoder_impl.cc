/* -*- c++ -*- */
/*
 * Copyright 2020 gr-hrpt author.
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
#include "fengyun_diff_decoder_impl.h"

namespace gr {
  namespace hrpt {

    fengyun_diff_decoder::sptr
    fengyun_diff_decoder::make()
    {
      return gnuradio::get_initial_sptr
        (new fengyun_diff_decoder_impl());
    }

    /*
     * The private constructor
     */
    fengyun_diff_decoder_impl::fengyun_diff_decoder_impl()
      : gr::block("fengyun_diff_decoder",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      set_history(2);	// need to look at two inputs
    }

    /*
     * Our virtual destructor.
     */
    fengyun_diff_decoder_impl::~fengyun_diff_decoder_impl()
    {
    }

    void
    fengyun_diff_decoder_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    fengyun_diff_decoder_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      int ninputs = ninput_items[0];
      const char *in = (const char *)input_items[0];
      unsigned char *out = (unsigned char *)output_items[0];

      in += 1;	// ensure that in[-1] is valid

      int i = 0, j = 0;
      unsigned char Xin_1, Yin_1, Xin, Yin, Xout, Yout;
      while(i < ninputs && j < noutput_items) {
        Xin_1 = in[i-1] & 0x02;
        Yin_1 = in[i-1] & 0x01;        
        Xin = in[i] & 0x02;
        Yin = in[i++] & 0x01;
        if(((Xin >> 1) ^ Yin) == 1){
            Xout = (Yin_1 ^ Yin);
	        Yout = (Xin_1 ^ Xin);
            out[j++] = (Xout << 1) + (Yout >> 1);
        }else{
            Xout = (Xin_1 ^ Xin);
            Yout = (Yin_1 ^ Yin);
            out[j++] = (Xout + Yout);
        }
       }

        consume_each(i);
        return j;
    }

  } /* namespace hrpt */
} /* namespace gr */

