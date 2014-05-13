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
#include "ofxThreadedVideoGC.h"

class ofxThreadedVideoGC;
class ofxThreadedVideoPlayer;

struct ofxThreadedVideoPlayerStatus{
	ofxThreadedVideoPlayer* player;
	bool ready;
	string path;
	ofxThreadedVideoPlayerStatus(){ ready = true; player = NULL; }
};

class ofxThreadedVideoPlayer{

	friend class ofxThreadedVideoGC;

public:

	ofxThreadedVideoPlayer();

	static int getNumInstances();

	void loadVideo(string path);
	void play();
	void stop();

	void setLoopMode(ofLoopType loop);
	bool hasFinished();

	void setPosition(float percent);
	float getPosition();
	float getDuration();

	void setVolume(float v);

	bool isReadyForPlayback();

	ofTexture* getTexture();

	void draw(float x, float y, bool drawDebug = false);
	void draw(float x, float y, float w, float h);
	void drawDebug(float x, float y);
	void update();

	float getWidth();
	float getHeight();

	string getPath();

	void deleteMe(); //once you call this on yor object, dont access the
					//pointer to your object anymore, or you will get a crash.
					//ofxThreadedVideoGC will delete it in a bg thread
					//making sure the app doesnt stutter

	//public ofEvent api
	//call ofAddListener(v->videoIsReadyEvent, this, &testApp::videoIsReadyCallback);
	//to get notified when the video is ready for playback
	ofEvent<ofxThreadedVideoPlayerStatus>	videoIsReadyEvent;

private:

	~ofxThreadedVideoPlayer(); //dont destruct this object directly!
	void threadedFunction();

	string									videopPath;
	ofLoopType								loopMode;
	bool									loaded;
	ofxAVFVideoPlayerExtension *			player;
	bool									readyForPlayback;

	bool									needToNotifyDelegate;

};

#endif