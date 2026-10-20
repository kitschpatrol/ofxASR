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
* Permission is hereby granted, free of charge, to any person obtaining a 
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
