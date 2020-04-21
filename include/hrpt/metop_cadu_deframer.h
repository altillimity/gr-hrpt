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

#ifndef INCLUDED_HRPT_METOP_CADU_DEFRAMER_H
#define INCLUDED_HRPT_METOP_CADU_DEFRAMER_H

#include <hrpt/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace hrpt {

    /*!
     * \brief <+description of block+>
     * \ingroup hrpt
     *
     */
    class HRPT_API metop_cadu_deframer : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<metop_cadu_deframer> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of hrpt::metop_cadu_deframer.
       *
       * To avoid accidental use of raw pointers, hrpt::metop_cadu_deframer's
       * constructor is in a private implementation
       * class. hrpt::metop_cadu_deframer::make is the public interface for
       * creating new instances.
       */
      static sptr make(bool sync_check, int frame_length, int insync_after, int outsync_after);

      virtual void set_sync_check(bool sync_check) = 0;
      virtual void set_frame_length(int frame_length) = 0;
      virtual void set_insync_after(int insync_after) = 0;
      virtual void set_outsync_after(int outsync_after) = 0;
    };

  } // namespace hrpt
} // namespace gr

#endif /* INCLUDED_HRPT_METOP_CADU_DEFRAMER_H */

