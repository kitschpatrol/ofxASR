# Archive

This folder mirrors content available on the [Google Code Archive](https://code.google.com/archive/p/ofxasr) page.

## Project

Via https://code.google.com/archive/p/ofxasr/.

> An openframeworks addon for speech recognition.

ofxASR is an openframeworks addon for speech recognition. It is for people to develop applications with speech recognition easily.

Currently it use CMU Sphinx3 as its Automatic Speech Recognition (ASR) engine, but it also designed allowing to use other ASR engine, such as Microsoft's SAPI or Mac OSX Speech API.

The developing of this project is a part of the project Community Core Audio (CCA), but ofxASR is standalone, it can be applied on any Openframeworks based program which need a speech recognition feature.

ofxASR is cross-platform.

The current release version is available to [download](#downloads). You can also check out from the svn Repo to get the newest version.

Before developing your own application with it, please read the [Frequently Asked Questions](#frequently-asked-questions).

ofxASR is distributed under the MIT License.

The author of this project, Jimbo Zhang, is a member of the [NUI Group](http://www.nuigroup.com) Community.

| Field   | Value                  |
| ------- | ---------------------- |
| Labels  | openframeworks, speech |
| License | MIT                    |
| Repo    | svn                    |
| Stars   | 15                     |

## Source

Via https://code.google.com/archive/p/ofxasr/source:

[source-archive.zip](./source-archive.zip)

## Wikis

Via https://code.google.com/archive/p/ofxasr/wikis:

### Frequently Asked Questions

#### Which languages will it be possible to use?

This addon is independent from language.

Which language an ASR engine support depends on the type of the acoustic model and the language model.

#### What components do I need to build an oF based application with speech-recognition?

First, of course you need download OpenFrameworks for your platform.

Then, you need download this addon. Download `ofxasr_x.xx.tar.gz`, where the "x.xx" is the newest version number.

In addition, you **MUST** have a sphinx-compatible resource package, which should contain an acoustics model, a language model, and dictionary. In our download page, a simple resource package is provide that can recognize English digits.

#### Why the resource package is required? What is it?

Most state-of-art speech recognition engine is based on Hidden Markov Model (HMM), and the resource package contains the resources that a HMM-based recognition engine need.

A resource package must contain:

- **Dictionary**: Any word that not in the dictionary can not be recognized.
- **Acoustics Model (AM)**: The acoustics statistical data.
- **Language Model (LM)**: The linguistics statistical data.

Although this addon wss designed as independent from the speech engine, it only support Sphinx in the current version. Therefore, the components (dictionary, AM, LM) in the resource package must be sphinx-compatible.

#### Is there documents about this addon?

In the `addons/ofxASR/example` folder, there is a example program that demonstrated how to develop a oF based application with ofxASR.

> **Note:** Don't forget to download a resource package.

#### Where can I get a resource package?

A resource package in fact is a folder that contains dictionary, AM and LM. To get a better resource package, you can download components from somewhere else. Here are some sites:

- https://www.keithv.com/software/sphinx/
- http://www.repository.voxforge1.org/downloads/Main/Trunk/AcousticModels/Sphinx/

And there are many other sites also provides sphinx resource.

You can also train AM and LM by yourself. To learn more about train a model, read sphinx's documents. But we do not suggest you training models by yourself, because it need huge audio data and it is not a very easy thing.

Our download page also provided two resource packages by now:

- [`typical_model.tar.gz`](./typical_model.tar.gz): a very simple resource package, it can only recognize English digits, that means even you speak something else, it still give the most similar English digits as the recognition result. We will provide more ready-to-use packages in future.
- [`sphinxmodel_voxforge-en-r0_1_3.tar.gz`](./sphinxmodel_voxforge-en-r0_1_3.tar.gz): a resource package from VoxForge, it provides complete resource for English recognition task.

#### Which path should I put the resource package?

Firstly, you should know which file is the Dictionary, which file is the AM and which file is the LM in the resource package.

Unzip the resource package to any location, and set the path of the Dictionary/AM/LM in your client applications like below:

```cpp
ofAsrEngineArgs *e = new ofAsrEngineArgs;
e->sphinxmodel_am = "sphinxmodel/digit.8gau";
e->sphinxmodel_lm = "sphinxmodel/digit.lm.DMP";
e->sphinxmodel_dict = "sphinxmodel/digit.dict";
e->sphinxmodel_fdict = "sphinxmodel/digit.fdict";
```

#### ofxASR supports two modes, what is the detail?

Currently ofxASR supports two modes:

- **Mode-4**: Any words in the dictionary can be recognized. The speaker is allowed to speak anything. In this mode, it is free to speak but not very accuracy.
- **Mode-2**: A list contains some sentences was required and the speaker must select one sentence to read. If she/he spoke something not in the list, the engine will return the most similar sentence from the list. This mode seems not very "free" but it is accuracy.

The mode numbers "4" and "2" are inherited from sphinx3's mode names.

#### I have built a application with ofxASR, but it always gave wrong recognizing result.

Please check:

- Is the audio sample rate correct? The sample rate of the AM and the audio input must be same.
- Do you use the correct mode? If you chose Mode-2, you must provide a list and only speak sentences in the list.

The recognizing accuracy is mainly depended on the AM and the LM. You may need to find better models.

#### I have a problem/question which is not on this FAQ.

Feel free to email me directly. :)

I'd glad to answer any questions and add this question into this FAQ if needed.

## Downloads

Via https://code.google.com/archive/p/ofxasr/downloads:

| File                                                                               | Summary                                                                                                   | Labels                           | Uploaded     |    Size |
| ---------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------- | -------------------------------- | ------------ | ------: |
| [`ofxasr_0.14.tar.gz`](./ofxasr_0.14.tar.gz)                                       | The newest version for OSX, Linux and Windows                                                             | Featured, Type-Source, OpSys-All | Aug 11, 2010 |  1.87MB |
| [`sphinxmodel_voxforge-en-r0_1_3.tar.gz`](./sphinxmodel_voxforge-en-r0_1_3.tar.gz) | A resource package from voxforge for CMU Sphinx. Provides complete resource for English recognition task. | Featured                         | Jul 22, 2010 | 11.86MB |
| [`ofxasr_xcode_106.zip`](./ofxasr_xcode_106.zip)                                   | An xcode project on OSX 10.6 (include openframeworks 0.61 and libresample)                                | OpSys-OSX                        | Jul 22, 2010 | 22.61MB |
| [`ofxasr_0.10.tar.gz`](./ofxasr_0.10.tar.gz)                                       | For Windows only.                                                                                         | Type-Source, OpSys-Windows       | Jun 25, 2010 |   600KB |
| [`typical_model.tar.gz`](./typical_model.tar.gz)                                   | A simple resource package for CMU Sphinx. Provides resource for digits recognition task only.             | Type-Archive                     | Jun 9, 2010  |  1.36MB |
