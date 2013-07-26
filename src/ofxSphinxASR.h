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
