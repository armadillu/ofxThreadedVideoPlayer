//
//  ofxAVFVideoPlayerExtensions.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 06/03/14.
//
//

#ifndef BaseApp_ofxAVFVideoPlayerExtensions_h
#define BaseApp_ofxAVFVideoPlayerExtensions_h

#include "ofxAVFVideoPlayer.h"

class ofxAVFVideoPlayerExtension : public ofxAVFVideoPlayer{

public:

	virtual ~ofxAVFVideoPlayerExtension();
	bool isReallyLoaded();
	bool isTextureReady();

};


#endif
