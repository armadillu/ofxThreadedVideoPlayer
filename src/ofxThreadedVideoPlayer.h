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


class ofxThreadedVideoPlayer: public ofThread{

public:

	ofxThreadedVideoPlayer();

	void loadVideo(string path);
	void play();
	void stop();

	void setLoopMode(ofLoopType loop);
	bool hasFinished();

	void setPosition(float percent);
	float getPosition();
	float getDuration();

	ofTexture* getTexture();

	void draw(float x, float y, bool drawDebug = false);
	void draw(float x, float y, float w, float h);

	float getWidth();
	float getHeight();

	//use this to supply a method for ofxThreadedVideoPlayer to notify (from the main thread)
	//whoever you want that the video is ready
	void setVideoReadyCallback( void (*callBack)(ofxThreadedVideoPlayer*) );

private:

	void threadedFunction();

	string videopPath;
	ofLoopType loopMode;
	bool loadNow;
	bool playNow;
	bool stopNow;
	bool loaded;
	ofxAVFVideoPlayerExtension * player;

	void (*callBack)(ofxThreadedVideoPlayer*);
	bool needToNotifyDelegate;

};


#endif
