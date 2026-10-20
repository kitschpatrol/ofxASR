/***************************************************************************
*
*  ofxSphinxASR.h
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

#ifndef OFXSPHINXASR_H
#define OFXSPHINXASR_H

#include "ofxBaseASR.h"
#include "s3_decode.h"
#include "fsg_model.h"
#include "jsgf.h"

class ofxSphinxASR : public ofxASR
{
public:
    ofxSphinxASR();
    ~ofxSphinxASR();

    // Operation of the ASR Engine
    int engineInit(ofAsrEngineArgs *e);
    int engineExit();
    int engineOpen();
    int engineClose();
    int engineSentAudio(short *audioBuf, int audioSize);
    bool isEngineOpened();
    char * engineGetText();

private:
    // The Decoder
    s3_decode_t *decoder;
    fe_t *fe;

    // States
    bool bEngineInitialed;
    bool bEngineOpened;

    // Grammar
    fsg_model_t *get_fsg(jsgf_t *grammar, const char *name);

    // Utterance number
    int uttnum;
};

#endif
