meta:
	ADDON_NAME = ofxASR
	ADDON_DESCRIPTION = An openFrameworks addon for speech recognition, using CMU Sphinx. Mirror of Jimbo Zhang's Google Code project.
	ADDON_AUTHOR = Jimbo Zhang
	ADDON_TAGS = "openframeworks" "ofx-addon" "speech-recognition" "sphinx" "asr"
	ADDON_URL = https://github.com/kitschpatrol/ofxASR

osx:
	ADDON_LIBS = libs/sphinx/lib/osx/libsphinxbase.dylib
	ADDON_LIBS += libs/sphinx/lib/osx/libs3decoder.dylib

linux:
	ADDON_LIBS = libs/sphinx/lib/linux/libsphinxbase.so.1
	ADDON_LIBS += libs/sphinx/lib/linux/libs3decoder.so.0

vs:
	ADDON_LIBS = libs/sphinx/lib/win32/s3decoder.lib
	ADDON_LIBS += libs/sphinx/lib/win32/sphinxbase.lib
	ADDON_DLLS_TO_COPY = libs/sphinx/lib/win32/s3decoder.dll
	ADDON_DLLS_TO_COPY += libs/sphinx/lib/win32/sphinxbase.dll
