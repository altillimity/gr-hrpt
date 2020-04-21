/* -*- c++ -*- */
/*
 * Copyright 2009 Free Software Foundation, Inc. 
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to 
 * the Free Software Foundation, Inc., 51 Franklin Street,  
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_POES_WEATHER_METOP_CADU_H
#define INCLUDED_POES_WEATHER_METOP_CADU_H

#define ASM1 	0x1A
#define ASM2 	0xCF
#define ASM3 	0xFC
#define ASM4 	0x1D

//ASM MARKER
#define ASM  	0x1ACFFC1DL

//negative ASM marker
#define NASM	0xE53003E2L

#define SYNC_WORDS        4    
#define BITS_PER_WORD     8



#endif /* INCLUDED_POES_WEATHER_METOP_CADU_H */
