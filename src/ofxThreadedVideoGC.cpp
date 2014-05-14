//
//  ofxThreadedVideoGC.cpp
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 13/05/14.
//
//

#include "ofxThreadedVideoGC.h"

ofxThreadedVideoGC* ofxThreadedVideoGC::singleton = NULL;

ofxThreadedVideoGC* ofxThreadedVideoGC::instance(){

	if (!singleton){   // Only allow one instance of class to be generated.
		singleton = new ofxThreadedVideoGC();
		singleton->startThread();
	}
	return singleton;
}


void ofxThreadedVideoGC::addToGarbageQueue(ofxThreadedVideoPlayer*p){
	lock();
		videosPendingDeletion.push_back(p);
	unlock();
}


void ofxThreadedVideoGC::threadedFunction(){

	while (isThreadRunning()) {
		sleep(1);
		lock();
		if(videosPendingDeletion.size()){
			cout << ">> about to delete"<< endl;
			delete videosPendingDeletion[0];
			cout << ">> deleted!"<< endl<< endl;
			videosPendingDeletion.erase(videosPendingDeletion.begin());
		}
		unlock();
	}
}