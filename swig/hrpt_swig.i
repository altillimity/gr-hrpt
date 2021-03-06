/* -*- c++ -*- */

#define HRPT_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "hrpt_swig_doc.i"

%{
    #include "hrpt/noaa_hrpt_pll_cf.h"
    #include "hrpt/noaa_hrpt_deframer.h"
    #include "hrpt/noaa_hrpt_decoder.h"
    #include "hrpt/viterbi_fengyun_decoder.h"
    #include "hrpt/viterbi_metop_decoder.h"
    #include "hrpt/metop_cadu_deframer.h"
    #include "hrpt/fengyun_diff_decoder.h"
%}

%include "hrpt/noaa_hrpt_pll_cf.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, noaa_hrpt_pll_cf);

%include "hrpt/noaa_hrpt_deframer.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, noaa_hrpt_deframer);

%include "hrpt/noaa_hrpt_decoder.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, noaa_hrpt_decoder);

%include "hrpt/viterbi_fengyun_decoder.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, viterbi_fengyun_decoder);

%include "hrpt/viterbi_metop_decoder.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, viterbi_metop_decoder);

%include "hrpt/metop_cadu_deframer.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, metop_cadu_deframer);

%include "hrpt/fengyun_diff_decoder.h"
GR_SWIG_BLOCK_MAGIC2(hrpt, fengyun_diff_decoder);