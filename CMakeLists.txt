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
# Project setup
########################################################################
cmake_minimum_required(VERSION 3.8)
project(gr-noaa CXX C)
enable_testing()

if(NOT CMAKE_MODULES_DIR)
  set(CMAKE_MODULES_DIR lib${LIB_SUFFIX}/cmake)
endif(NOT CMAKE_MODULES_DIR)

# Install to PyBOMBS target prefix if defined
if(DEFINED ENV{PYBOMBS_PREFIX})
    set(CMAKE_INSTALL_PREFIX $ENV{PYBOMBS_PREFIX})
    message(STATUS "PyBOMBS installed GNU Radio. Setting CMAKE_INSTALL_PREFIX to $ENV{PYBOMBS_PREFIX}")
endif()

########################################################################
# Setup dependencies
########################################################################
find_package(Gnuradio "3.8" COMPONENTS runtime blocks)
if(NOT Gnuradio_FOUND)
    find_package(Gnuradio "3.9" COMPONENTS runtime blocks)
	if(NOT Gnuradio_FOUND)
	    message(FATAL_ERROR "Unable to find GNURadio 3.8 or 3.9")
	ENDIF(NOT Gnuradio_FOUND)
ENDIF(NOT Gnuradio_FOUND)

include(GrVersion)
include(GrPlatform)
include(GrBoost)

########################################################################
# Register component
########################################################################

SET(GR_PKG_NOAA_EXAMPLES_DIR ${GR_PKG_DATA_DIR}/examples/noaa)

########################################################################
# Create uninstall target
########################################################################
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    )

########################################################################
# Add subdirectories
########################################################################
add_subdirectory(include/gnuradio/noaa)
add_subdirectory(lib)
if(ENABLE_PYTHON)
    add_subdirectory(swig)
    add_subdirectory(python/noaa)
    add_subdirectory(grc)
    add_subdirectory(examples)
endif(ENABLE_PYTHON)

include_directories(gr-noaa/include)

########################################################################
# Create Pkg Config File
########################################################################
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/gnuradio-noaa.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/gnuradio-noaa.pc
@ONLY)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/gnuradio-noaa.pc
    DESTINATION ${GR_LIBRARY_DIR}/pkgconfig
)
