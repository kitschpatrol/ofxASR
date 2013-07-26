/***************************************************************************
*
*  ofxASR.h
* 
*  Author: Jimbo Zhang <dr.jimbozhang@gmail.com>
*  Copyright 2010 Jimbo Zhang. All rights reserved.       
*
*
* This file is part of ofxASR, an openframeworks addon for speech
* recognition.
*
* ofxASR is free software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ofxASR is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with ofxASR. If not, see <http://www.gnu.org/licenses/>.
*
*
***************************************************************************/

#ifndef OFXASR_H
#define OFXASR_H

#define USE_SPHINX

#include "ofxBaseASR.h"

#ifdef USE_SPHINX
#include "ofxSphinxASR.h"
#endif

#endif
