/* -*- c++ -*- */

#define HRPT_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "hrpt_swig_doc.i"

%{
    #include "hrpt/noaa_hrpt_pll_cf.h"
    #include "hrpt/noaa_hrpt_deframer.h"
    #include "hrpt/noaa_hrpt_decoder.h"
%}

%include "hrpt/noaa_hrpt_pll_cf.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, noaa_hrpt_pll_cf);

%include "hrpt/noaa_hrpt_deframer.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, noaa_hrpt_deframer);

%include "hrpt/noaa_hrpt_decoder.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, noaa_hrpt_decoder);