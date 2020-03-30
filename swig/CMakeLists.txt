# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup swig generation
########################################################################
find_package(SWIG)
find_package(PythonLibs)
if(NOT SWIG_FOUND OR NOT PYTHONLIBS_FOUND)
    return()
endif()
include(GrSwig)
include(GrPython)

set(GR_SWIG_INCLUDE_DIRS
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include> 
    $<TARGET_PROPERTY:gnuradio::runtime_swig,INTERFACE_INCLUDE_DIRECTORIES>
)

set(GR_SWIG_TARGET_DEPS gnuradio::runtime_swig)

if(ENABLE_GR_CTRLPORT)
  list(APPEND GR_SWIG_FLAGS "-DGR_CTRLPORT")
endif(ENABLE_GR_CTRLPORT)

set(GR_SWIG_DOC_FILE ${CMAKE_CURRENT_BINARY_DIR}/noaa_swig_doc.i)
set(GR_SWIG_DOC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include/gnuradio/noaa)
set(GR_SWIG_DOCS_TARGET_DEPS runtime_swig runtime_swig_swig_doc)

set(GR_SWIG_LIBRARIES gnuradio-noaa)

GR_SWIG_MAKE(noaa_swig noaa_swig.i)

GR_SWIG_INSTALL(
    TARGETS noaa_swig
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/noaa
)

install(
    FILES
    noaa_swig.i
    ${CMAKE_CURRENT_BINARY_DIR}/noaa_swig_doc.i
    DESTINATION ${GR_INCLUDE_DIR}/gnuradio/swig
)
