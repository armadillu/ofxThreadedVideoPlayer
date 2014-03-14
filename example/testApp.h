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

	int selectedVideo;
	bool debug;
};
