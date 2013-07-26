/***************************************************************************
*
*  ofxSphinxASR.cpp
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
#ifdef WIN32
#include <io.h>
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include "ofxSphinxASR.h"
ofxSphinxASR::ofxSphinxASR()
{
    bEngineInitialed = false;
    bEngineOpened = false;
    decoder = NULL;
    fe = NULL;
    uttnum = 0;
}
ofxSphinxASR::~ofxSphinxASR() {}
int ofxSphinxASR::engineInit(ofAsrEngineArgs *e)
{
    
    cout << "Init engine: " << e->sphinxmodel_am.c_str() << endl;
    
#if defined TARGET_WIN32
    char cfg_filename[] = "sphinx.cfg";
    char grammarJSGF_filename[] = "grammar.jsgf";
    char grammarFSG_filename[] = "grammar.fsg";
#else
	char cfg_filename[] = "/tmp/sphinx.cfg";
    char grammarJSGF_filename[] = "/tmp/grammar.jsgf";
    char grammarFSG_filename[] = "/tmp/grammar.fsg";
#endif	
    FILE *cfg_fp = fopen(cfg_filename, "wt");
    if (cfg_fp==NULL)
        return OFXASR_FAIL_WRITE_CONFIG;
    if ( access(e->sphinxmodel_am.c_str(), 0) != 0 )
		return OFXASR_FAIL_READ_FILES;
	if ( access(e->sphinxmodel_lm.c_str(), 0) != 0 )
		return OFXASR_FAIL_READ_FILES;
	if ( access(e->sphinxmodel_dict.c_str(), 0) != 0 )
		return OFXASR_FAIL_READ_FILES;
	if ( access(e->sphinxmodel_fdict.c_str(), 0) != 0 )
		return OFXASR_FAIL_READ_FILES;
	
	char cur_path[1024];
	getcwd(cur_path, 1024);
    
    fprintf(cfg_fp, "-samprate %d\n", e->samplerate);
    fprintf(cfg_fp, "-hmm %s/%s\n", cur_path, e->sphinxmodel_am.c_str());
    fprintf(cfg_fp, "-dict %s/%s\n", cur_path, e->sphinxmodel_dict.c_str());
    fprintf(cfg_fp, "-fdict %s/%s\n", cur_path, e->sphinxmodel_fdict.c_str());
    fprintf(cfg_fp, "-lm %s/%s\n", cur_path, e->sphinxmodel_lm.c_str());

    //fprintf(cfg_fp, "-feat s2_4x\n");
    
    
    if (e->sphinx_mode == 2) {
        if(e->sphinx_candidate_sentences.size() < 1) {
            printf("Warning: The word list is empty! Use mode 4.\n");
            e->sphinx_mode = 4;
        }
        else {
            FILE *gram_fp = fopen(grammarJSGF_filename, "wt");
            if (gram_fp==NULL)
                return OFXASR_FAIL_WRITE_CONFIG;
            fprintf(gram_fp,
                "#JSGF V1.0;\n\ngrammar cca_gram;\n\npublic <cca_gram> = (\n");
            for (int i=0; i<e->sphinx_candidate_sentences.size()-1; i++) {
                fprintf(gram_fp, "%s |\n",
                 e->sphinx_candidate_sentences[i].c_str());
            }
            fprintf(gram_fp, "%s );\n\n",
                e->sphinx_candidate_sentences[e->sphinx_candidate_sentences.size()-1].c_str());
            fclose(gram_fp);
        }
        jsgf_t *jsgf = jsgf_parse_file(grammarJSGF_filename, NULL);
        if (jsgf == NULL) {
            printf("Bad jsgf file %s.\n", grammarJSGF_filename);
            return OFXASR_INVALID_JSGF_GRAMMAR;
        }
        fsg_model_t *fsg = get_fsg(jsgf, NULL);
        fsg_model_writefile(fsg, grammarFSG_filename);
        fsg_model_free(fsg);
        jsgf_grammar_free(jsgf);
        fprintf(cfg_fp, "-fsg %s\n", grammarFSG_filename);
    }
    
    fprintf(cfg_fp, "-op_mode %d\n", e->sphinx_mode);
    fclose(cfg_fp);
    
    cout << cfg_fp << endl;
    
    
    err_set_logfp(NULL); // disable logs
    
    cmd_ln_t *config = NULL;
    config = cmd_ln_parse_file_r(config, S3_DECODE_ARG_DEFS, cfg_filename, TRUE);
    if (config == NULL) {
        return OFXASR_INVALID_CONFIG;
    }
    decoder = new s3_decode_t;
    if (s3_decode_init(decoder, config) != S3_DECODE_SUCCESS) {
        return OFXASR_FAIL_INIT_DECODER;
    }
    
    //    cout << "Config: " << cfg_filename << endl;
    fe = fe_init_auto_r(config);
    if (fe == NULL) {
        return OFXASR_FAIL_INIT_FRONTEND;
    }
    bEngineInitialed = true;
    return OFXASR_SUCCESS;
}
int ofxSphinxASR::engineExit()
{
    s3_decode_close(decoder);
    if (decoder != NULL) {
        delete decoder;
        decoder = NULL;
    }
    if (fe != NULL) {
        fe_free(fe);
        fe = NULL;
    }
    return OFXASR_SUCCESS;
}
int ofxSphinxASR::engineOpen()
{
    if (! bEngineInitialed)
        return OFXASR_HAVE_NOT_INIT;
    char uttid[8];
    sprintf(uttid, "%d", uttnum);
    if (s3_decode_begin_utt(decoder, uttid) != S3_DECODE_SUCCESS)
    {
        return OFXASR_FAIL_STARTENGINE;
    }
    else {
        bEngineOpened = true;
        return OFXASR_SUCCESS;
    }
}
int ofxSphinxASR::engineClose()
{
    bEngineOpened = false;
    if (! bEngineInitialed)
        return OFXASR_SUCCESS;
    s3_decode_end_utt(decoder);
    return OFXASR_SUCCESS;
}
int ofxSphinxASR::engineSentAudio(short *audioBuf, int audioSize)
{
    float32 **frames;
    int n_frames;
    if (!bEngineInitialed)
        return OFXASR_HAVE_NOT_INIT;
    if (!bEngineOpened)
        return OFXASR_HAVE_NOT_START;
    fe_process_utt(fe, audioBuf, audioSize, &frames, &n_frames);
    if (frames != NULL) {
        s3_decode_process(decoder, frames, n_frames);
        ckd_free_2d((void **)frames);
    }
    return OFXASR_SUCCESS;
}
char * ofxSphinxASR::engineGetText()
{
    char * hypstr;
    if (s3_decode_hypothesis(decoder, NULL, &hypstr, NULL)
        == S3_DECODE_SUCCESS && decoder->phypdump) {
        return hypstr;
    }
    else {
        return NULL;
    }
}
bool ofxSphinxASR::isEngineOpened()
{
    return bEngineInitialed * bEngineOpened;
}
fsg_model_t* ofxSphinxASR::get_fsg(jsgf_t *grammar, const char *name)
{
    jsgf_rule_iter_t *itor;
    logmath_t *lmath = logmath_init(1.0001, 0, 0);
    fsg_model_t *fsg = NULL;
    for (itor = jsgf_rule_iter(grammar); itor;
        itor = jsgf_rule_iter_next(itor)) {
            jsgf_rule_t *rule = jsgf_rule_iter_rule(itor);
            char const *rule_name = jsgf_rule_name(rule);
            if ((name == NULL && jsgf_rule_public(rule))
                || (name && strlen(rule_name)-2 == strlen(name) &&
                0 == strncmp(rule_name + 1, name, strlen(rule_name) - 2))) {
                    fsg = jsgf_build_fsg_raw(grammar,
                                             rule, logmath_retain(lmath), 1.0);
                    jsgf_rule_iter_free(itor);
                    break;
            }
    }
    logmath_free(lmath);
    return fsg;
}