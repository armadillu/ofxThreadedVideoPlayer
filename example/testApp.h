#pragma once

#include "ofMain.h"
//#include "ofxTimeMeasurements.h"
#include "ofxThreadedVideoPlayer.h"

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	void addvideo();
	void videoIsReadyCallback(ofxThreadedVideoPlayerStatus&);


private:

	vector <ofxThreadedVideoPlayer*> videos;
	vector <ofxThreadedVideoPlayer*> videosPendingDeletion;

	int selectedVideo;
	int numPlayersCreated;
	int numPlayersDeleted;

	ofMutex mutex;

	bool autoPilot; //will add a video every now and then
					//and delete one too.
					//used to check for crashes / leaks
};
