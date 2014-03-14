//
//  ofxAVFVideoPlayerExtensions.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 06/03/14.
//
//


#include "ofxAVFVideoPlayerExtension.h"

bool ofxAVFVideoPlayerExtension::isReallyLoaded(){
	return [moviePlayer isLoaded];
}



bool ofxAVFVideoPlayerExtension::isTextureReady(){
	return moviePlayer.textureAllocated;
}