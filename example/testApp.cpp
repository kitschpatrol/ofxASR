/***************************************************************************
*
*  testApp.cpp
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

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // For printing result
    verdana.loadFont("verdana.ttf", 8, false, true);

    /* 
     * ofxASR supports two modes:
     * Mode-4: Any words in the dictionary can be recognized. The 
     *         speaker is allowed to speak anything. In this mode,
     *         it is free to speak but not very accuracy.
     * Mode-2: A list contains some sentences was required and the
     *         speaker must select one sentence to read. If she/he
     *         spoke something not in the list, the engine will 
     *         return the most similar sentence from the list. This
     *         mode seems not very "free" but it is accuracy.
     * The usages of the both two modes are showed below, however, 
     * you only need choose one mode to use.
     */

    //////////////////////////////////////////////////////////////////////////
    // Create a Mode-4 engine
    //////////////////////////////////////////////////////////////////////////
    engine1_listenFromList = new ofxSphinxASR;
    e = new ofAsrEngineArgs;
	
	// set sample rate to 16000 Hz
    e->samplerate = 16000;
	
    // set mode code
    e->sphinx_mode = 4;	

#if defined TARGET_OSX    
    // set the folder of the acoustics model
    e->sphinxmodel_am = ".";

    // set the path of the language model
    e->sphinxmodel_lm = "digit.lm.DMP";

    // set the path of the dict and the filler dict
    e->sphinxmodel_dict = "dictionary";
    e->sphinxmodel_fdict = "fillerdict";
#else
    e->sphinxmodel_am = "sphinxmodel/digit.8gau";
    e->sphinxmodel_lm = "sphinxmodel/digit.lm.DMP";
    e->sphinxmodel_dict = "sphinxmodel/digit.dict";
    e->sphinxmodel_fdict = "sphinxmodel/digit.fdict";
#endif

    // Initial the engine
    int retval = engine1_listenFromList->engineInit(e);
    if (retval != OFXASR_SUCCESS) {
        printf("ASR Engine initial failed. Error Code: %d\n", retval);
		result_from_engine1 = "ASR Engine initial failed. Check sphinx resource path";
    }

    //////////////////////////////////////////////////////////////////////////
    // Create a Mode-2 engine
    //////////////////////////////////////////////////////////////////////////
    engine2_listenFromAnything = new ofxSphinxASR;
    e->sphinx_mode = 2;

    // Mode-2 need a list. Add sentences to the list
	e->sphinx_candidate_sentences.push_back("one");
	e->sphinx_candidate_sentences.push_back("two");
    e->sphinx_candidate_sentences.push_back("three");
	e->sphinx_candidate_sentences.push_back("four");
	e->sphinx_candidate_sentences.push_back("five");
	e->sphinx_candidate_sentences.push_back("six");
	e->sphinx_candidate_sentences.push_back("seven");
	e->sphinx_candidate_sentences.push_back("eight");
	e->sphinx_candidate_sentences.push_back("nine");
	e->sphinx_candidate_sentences.push_back("zero");
    
    retval = engine2_listenFromAnything->engineInit(e);
    if (retval != OFXASR_SUCCESS) {
        printf("ASR Engine initial failed. Error Code: %d\n", retval);
		result_from_engine1 = "ASR Engine initial failed. Check sphinx resource path";
    }
}

//--------------------------------------------------------------
void testApp::exit(){
    if (engine1_listenFromList != NULL) {
        engine1_listenFromList->engineExit();
        delete engine1_listenFromList;
        engine1_listenFromList = NULL;
    }
    if (engine2_listenFromAnything != NULL) {
        engine2_listenFromAnything->engineExit();
        delete engine2_listenFromAnything;
        engine2_listenFromAnything = NULL;
    }
    if (e != NULL) {
        delete e;
        e = NULL;
    }
}

//--------------------------------------------------------------
void testApp::mousePressed( int x, int y, int button )
{
    // Open the engines.
    int retval;
    retval = engine1_listenFromList->engineOpen();
    if (retval != OFXASR_SUCCESS) {
        printf("ASR Engine failed to open. Error Code: %d\n", retval);
    }    
    retval = engine2_listenFromAnything->engineOpen();
    if (retval != OFXASR_SUCCESS) {
        printf("ASR Engine failed to open. Error Code: %d\n", retval);
    }

    // Recording. Note that Mac OS do not support 16k sample rate
#if defined TARGET_OSX
	ofSoundStreamSetup(0, 1, this, 48000, 256, 2);
#else
    ofSoundStreamSetup(0, 1, this, 16000, 256, 2);
#endif
}

//--------------------------------------------------------------
void testApp::mouseReleased()
{
    // Stop recording
    ofSoundStreamClose(); 

    // Close the engines
    int retval;
    retval = engine1_listenFromList->engineClose();
    if (retval != OFXASR_SUCCESS) {
        printf("ASR Engine failed to close. Error Code: %d\n", retval);
    }


    retval = engine2_listenFromAnything->engineClose();
    if (retval != OFXASR_SUCCESS) {
        printf("ASR Engine failed to close. Error Code: %d\n", retval);
    }

    // Get result
	char *result_str;
	result_str = engine1_listenFromList->engineGetText();
	if (result_str) {
		string s1(result_str);
		result_from_engine1 = s1;
	}
	else {
		result_from_engine1 = "[No result.]";
	}

    result_str = engine2_listenFromAnything->engineGetText();
	if (result_str) {
		string s2(result_str);
		result_from_engine2 = s2;
	}
	else {
		result_from_engine2 = "[No result.]";
	}
};

void testApp::draw()
{
    ofSetColor(0x000000);
    verdana.drawString("result_from_engine1:", 10,10);
    verdana.drawString(result_from_engine1, 10,30);
    verdana.drawString("result_from_engine2:", 10,70);
    verdana.drawString(result_from_engine2, 10,90);
}

void testApp::audioReceived( float * input, int bufferSize, int nChannels )
{
    if (nChannels > 1) {
        printf("Only support 1-channel audio!\n");
        return;
    }

    // Convert sound from float to short    
#ifdef TARGET_OSX
	short *buf_16 = new short[bufferSize/3];
	for (int i=0; i<bufferSize/3; i++) {
        buf_16[i] = short(input[i*3] * 32767.5 - 0.5);
    }
#else
	short *buf_16 = new short[bufferSize];
    for (int i=0; i<bufferSize; i++) {
        buf_16[i] = short(input[i] * 32767.5 - 0.5);
    }
#endif
	
    // Sent sound to engines
    engine1_listenFromList->engineSentAudio(buf_16, bufferSize);
    engine2_listenFromAnything->engineSentAudio(buf_16, bufferSize);
}
