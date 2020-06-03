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

#ifndef INCLUDED_HRPT_FENGYUN_DIFF_DECODER_H
#define INCLUDED_HRPT_FENGYUN_DIFF_DECODER_H

#include <hrpt/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace hrpt {

    /*!
     * \brief <+description of block+>
     * \ingroup hrpt
     *
     */
    class HRPT_API fengyun_diff_decoder : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<fengyun_diff_decoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of hrpt::fengyun_diff_decoder.
       *
       * To avoid accidental use of raw pointers, hrpt::fengyun_diff_decoder's
       * constructor is in a private implementation
       * class. hrpt::fengyun_diff_decoder::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace hrpt
} // namespace gr

#endif /* INCLUDED_HRPT_FENGYUN_DIFF_DECODER_H */

