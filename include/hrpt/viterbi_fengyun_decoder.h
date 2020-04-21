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

#ifndef INCLUDED_HRPT_VITERBI_FENGYUN_DECODER_H
#define INCLUDED_HRPT_VITERBI_FENGYUN_DECODER_H

#include <hrpt/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace hrpt {

    /*!
     * \brief <+description of block+>
     * \ingroup hrpt
     *
     */
    class HRPT_API viterbi_fengyun_decoder : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<viterbi_fengyun_decoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of hrpt::viterbi_fengyun_decoder.
       *
       * To avoid accidental use of raw pointers, hrpt::viterbi_fengyun_decoder's
       * constructor is in a private implementation
       * class. hrpt::viterbi_fengyun_decoder::make is the public interface for
       * creating new instances.
       */
      static sptr make(bool sync_check, float ber_threshold, int insync_after, int outsync_after, int reset_after);

      virtual void set_sync_check(bool sync_check) = 0;
      virtual void set_ber_threshold(float ber_threshold) = 0;
      virtual void set_insync_after(int insync_after) = 0;
      virtual void set_outsync_after(int outsync_after) = 0;
      virtual void set_reset_after(int reset_after) = 0;
    };

  } // namespace hrpt
} // namespace gr

#endif /* INCLUDED_HRPT_VITERBI_FENGYUN_DECODER_H */

