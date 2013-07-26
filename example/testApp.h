/***************************************************************************
*
*  testApp.h
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

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxASR.h"

class testApp : public ofBaseApp{

	public:
        void setup();     // set up ASR engines
        void exit();
        void draw();
        void mousePressed( int x, int y, int button );  // press mouse to record
        void mouseReleased();                    // release mouse to stop record
        void audioReceived( float * input, int bufferSize, int nChannels );

    private:
        ofTrueTypeFont	verdana;
        ofxASR *engine1_listenFromList;
        ofxASR *engine2_listenFromAnything;
        ofAsrEngineArgs *e;
        string result_from_engine1;
        string result_from_engine2;
};

#endif
