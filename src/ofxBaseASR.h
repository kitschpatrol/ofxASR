/***************************************************************************
*
*  ofxBaseASR.h
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

#ifndef OFXBASEASR_H
#define OFXBASEASR_H

#include "ofMain.h"

// The return codes
#define OFXASR_SUCCESS                   0
#define OFXASR_FAIL_UNKNOWN             -1
#define OFXASR_FAIL_READ_FILES          -2
#define OFXASR_HAVE_NOT_INIT            -3
#define OFXASR_FAIL_WRITE_CONFIG        -4
#define OFXASR_INVALID_JSGF_GRAMMAR     -5
#define OFXASR_INVALID_CONFIG           -6
#define OFXASR_FAIL_INIT_FRONTEND       -7
#define OFXASR_FAIL_STARTENGINE         -8
#define OFXASR_FAIL_INIT_DECODER        -9
#define OFXASR_INVALID_AUDIO_FORMAT     -10
#define OFXASR_HAVE_NOT_START           -11

struct ofAsrEngineArgs
{    
    int samplerate;
    
    // Only for sphinx
    string sphinxmodel_am;
    string sphinxmodel_lm;
    string sphinxmodel_dict;
    string sphinxmodel_fdict;
    int sphinx_mode;
    vector<string> sphinx_candidate_sentences;

    // Only for some other recognition engine
    int other_engine_foo;
    int other_engine_bar;

    ofAsrEngineArgs()
    {
        samplerate = 16000;
        sphinx_mode = 0;
    }
};

class ofxASR
{
public:
    // Operation of the ASR engine
    virtual int engineInit(ofAsrEngineArgs *e) = 0;
    virtual int engineExit() = 0;
    virtual int engineOpen() = 0;
    virtual int engineClose() = 0;
    virtual int engineSentAudio(short *audioBuf, int audioSize) = 0;
    virtual char * engineGetText() = 0;
    virtual bool isEngineOpened() = 0;
};

#endif
