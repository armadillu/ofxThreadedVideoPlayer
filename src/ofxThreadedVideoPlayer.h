//
//  ofxThreadedVideoPlayer.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 04/03/14.
//
//

#ifndef BaseApp_ofxThreadedVideoPlayer_h
#define BaseApp_ofxThreadedVideoPlayer_h

#include "ofMain.h"
#include "ofxAVFVideoPlayerExtension.h"

class ofxThreadedVideoPlayer;

struct ofxThreadedVideoPlayerStatus{
	ofxThreadedVideoPlayer* player;
	bool ready;
	string path;
	ofxThreadedVideoPlayerStatus(){ ready = true; player = NULL; }
};

class ofxThreadedVideoPlayer: public ofThread{

public:

	ofxThreadedVideoPlayer();
	~ofxThreadedVideoPlayer();

	void loadVideo(string path);
	void play();
	void stop();

	void setLoopMode(ofLoopType loop);
	bool hasFinished();

	void setPosition(float percent);
	float getPosition();
	float getDuration();

	bool isReadyForPlayback();

	void markForDeletion(); //call this before deletion
	bool isReadyToBeDeleted(); //then keep the pointer around, check fro this to be true and delete if it is

	ofTexture* getTexture();

	void draw(float x, float y, bool drawDebug = false);
	void draw(float x, float y, float w, float h);
	void drawDebug(float x, float y);
	void update();

	float getWidth();
	float getHeight();

	//public ofEvent api
	//call ofAddListener(v->videoIsReadyEvent, this, &testApp::videoIsReadyCallback);
	//to get notified when the video is ready for playback
	ofEvent<ofxThreadedVideoPlayerStatus>	videoIsReadyEvent;

private:

	void threadedFunction();

	string									videopPath;
	ofLoopType								loopMode;
	bool									loadNow;
	bool									playNow;
	bool									stopNow;
	bool									loaded;
	ofxAVFVideoPlayerExtension *			player;
	bool									readyForPlayback;

	bool									pendingDeletion; //if true, wait for thread to finish its pass
	bool									readyForDeletion; //if ture, object can be deleted by 3rd party

	bool									needToNotifyDelegate;
};

#endif