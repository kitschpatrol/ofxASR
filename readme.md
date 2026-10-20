<!-- title -->

# ofxASR

<!-- /title -->

<!-- badges -->

[![License: GPL-3.0-or-later](https://img.shields.io/badge/License-GPL--3.0--or--later-yellow.svg)](https://spdx.org/licenses/GPL-3.0-only)

<!-- /badges -->

<!-- short-description -->

**An openFrameworks addon for speech recognition, using CMU Sphinx. Mirror of Jimbo Zhang's Google Code project.**

<!-- /short-description -->

> [!IMPORTANT]
> This repo is just a mirror of ofxASR, which was created by Jimbo Zhang and originally hosted on [Google Code](https://code.google.com/archive/p/ofxasr).

## Overview

An [openFrameworks](https://openframeworks.cc/) [addon](https://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/) for speech recognition.

ofxASR uses [CMU Sphinx3](https://cmusphinx.github.io/) as its speech recognition engine. You open an utterance, send it 16-bit audio, close it, and ask for the recognized text. It can listen for any word in its dictionary, or for the closest match from a list of sentences you provide, which is more accurate.

## Getting started

### Dependencies

ofxASR was written for [openFrameworks 0.061](https://github.com/openframeworks/openFrameworks/tree/0061). The original project offered an Xcode project for Mac OS X 10.6 that bundled that version. The example uses APIs from that era and the bundled libraries are 32-bit, so the addon won't build with current openFrameworks releases without changes.

**Sphinx is included in the addon.** Headers for Sphinx3 and SphinxBase are in [`libs/sphinx/include`](libs/sphinx/include). Prebuilt 32-bit libraries are in [`libs/sphinx/lib`](libs/sphinx/lib): dynamic libraries for macOS (i386) and Linux (x86), and import libraries and DLLs for Windows (Win32).

You also need a Sphinx-compatible resource package with an acoustic model, a language model, and a dictionary. Words that aren't in the dictionary can't be recognized, and the languages ofxASR can recognize depend on the models you use. The original project's resource packages are still available from the Google Code archive:

- [`typical_model.tar.gz`](https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/ofxasr/typical_model.tar.gz): a small model from Sphinx3 that only recognizes English digits.
- [`sphinxmodel_voxforge-en-r0_1_3.tar.gz`](https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/ofxasr/sphinxmodel_voxforge-en-r0_1_3.tar.gz): a general English model from [VoxForge](https://www.voxforge.org/).

Please see the archived Google Code [FAQ](https://code.google.com/archive/p/ofxasr/wikis/FAQ.wiki) for more info on getting started. The FAQ, the original downloads, and a source snapshot are also kept in the [`archive`](archive) folder.

### Installation

Clone the repository into your openFrameworks `addons` folder:

```sh
cd openFrameworks/addons
git clone https://github.com/kitschpatrol/ofxASR.git
```

With openFrameworks 0.061, add the addon to your project by hand, as described in [`install.xml`](install.xml): add the files in [`src`](src), add `libs/sphinx/include/sphinxbase` and `libs/sphinx/include/sphinx3` to the header search paths, link the libraries for your platform from `libs/sphinx/lib`, and copy the dynamic libraries next to your app's executable. The macOS libraries have an `@executable_path` install name, so they won't load from anywhere else.

Newer openFrameworks versions read [`addon_config.mk`](addon_config.mk) instead, which lists the libraries to link on macOS, 32-bit Linux, and Visual Studio.

## Usage

Create an engine, describe the model with `ofAsrEngineArgs`, and initialize it. With `typical_model.tar.gz` unpacked in the working directory:

```cpp
#include "ofxASR.h"

ofxASR *engine = new ofxSphinxASR;
ofAsrEngineArgs *args = new ofAsrEngineArgs;
args->samplerate = 16000;
args->sphinx_mode = 2;
args->sphinxmodel_am = "res_digits/digit_8gau";
args->sphinxmodel_lm = "res_digits/digit.lm.DMP";
args->sphinxmodel_dict = "res_digits/dictionary";
args->sphinxmodel_fdict = "res_digits/fillerdict";
args->sphinx_candidate_sentences.push_back("one");
args->sphinx_candidate_sentences.push_back("two");
args->sphinx_candidate_sentences.push_back("three");

if (engine->engineInit(args) != OFXASR_SUCCESS) {
	printf("Check the model paths\n");
}
```

Then wrap each utterance in `engineOpen()` and `engineClose()`, and send audio from your sound input callback in between:

```cpp
engine->engineOpen();

// In the audio callback, for each buffer of 16-bit mono samples:
engine->engineSentAudio(samples, sampleCount);

engine->engineClose();
char *text = engine->engineGetText(); // NULL if nothing was recognized
```

## Other projects

- [ofxWhisper](https://github.com/roymacdonald/ofxWhisper) is an openFrameworks addon for [whisper.cpp](https://github.com/ggml-org/whisper.cpp).
- [ofxVosk](https://github.com/ryohajika/ofxVosk) is an openFrameworks addon for the [Vosk](https://alphacephei.com/vosk/) offline speech recognition toolkit.
- [ofxSpeech](https://github.com/latrokles/ofxSpeech) is a speech recognition and synthesis addon, now archived.

<!-- license -->

## License

[GPL-3.0-or-later](LICENSE) © Jimbo Zhang

<!-- /license -->
