//
//  ofxThreadedVideoGC.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 13/05/14.
//
//

#ifndef __BaseApp__ofxThreadedVideoGC__
#define __BaseApp__ofxThreadedVideoGC__

#include "ofMain.h"
#include "ofxThreadedVideoPlayer.h"

class ofxThreadedVideoPlayer;

class ofxThreadedVideoGC: public ofThread{

public:

	static ofxThreadedVideoGC* instance();
	void addToGarbageQueue(ofxThreadedVideoPlayer*);


private:

	ofxThreadedVideoGC(){}; //use instance()!
	static ofxThreadedVideoGC*	singleton;

	vector<ofxThreadedVideoPlayer*> videosPendingDeletion;

	void threadedFunction();
};

#endif /* defined(__BaseApp__ofxThreadedVideoGC__) */
