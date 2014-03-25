//
//  ofxThreadedVideoPlayer.cpp
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 04/03/14.
//
//

#include "ofxThreadedVideoPlayer.h"

ofxThreadedVideoPlayer::ofxThreadedVideoPlayer(){
	loadNow = playNow = stopNow = false;
	player = NULL;
	loaded = false;
	loopMode = OF_LOOP_NORMAL;
	needToNotifyDelegate = false;
	pendingDeletion = false;
	readyForPlayback = false;
	readyForDeletion = false;
	player = new ofxAVFVideoPlayerExtension();
}

ofxThreadedVideoPlayer::~ofxThreadedVideoPlayer(){
	cout << "~ofxThreadedVideoPlayer()" << endl;
	if ( player ){
		cout << "ofxThreadedVideoPlayer(): YOU NEED TO CALL markForDeletion() before deleting this object!" << endl;
	};
}

void ofxThreadedVideoPlayer::loadVideo(string path){
	videopPath = path;
	loadNow = true;
	if(!isThreadRunning()) startThread();
}

void ofxThreadedVideoPlayer::play(){
	playNow = true;
	if(!isThreadRunning()) startThread();
}

void ofxThreadedVideoPlayer::stop(){
	stopNow = true;
}

void ofxThreadedVideoPlayer::setLoopMode(ofLoopType loop){
	loopMode = loop;
	if(player){
		player->setLoopState(loop);
	}
}


bool ofxThreadedVideoPlayer::isReadyForPlayback(){
	return readyForPlayback;
}


void ofxThreadedVideoPlayer::threadedFunction(){

	readyForDeletion = false;

	#ifdef TARGET_OSX
	pthread_setname_np("ofxThreadedVideoPlayer");
	#endif

	while(isThreadRunning()){

		if (loadNow){	//////////////////////////// LOAD
			//lock();
				loaded = player->loadMovie(videopPath);
				needToNotifyDelegate = true;
				player->setLoopState(loopMode);
			//unlock();
			loadNow = false;
		}

		if (stopNow){	/////////////////////////// STOP
			if(loaded){
				lock();
				player->setPaused(true);
				unlock();
			}else{
				cout << "can't stop playing before we load a movie!" << endl;
			}
			stopNow = false;
			stopThread();
		}

		if (playNow){	///////////////////////////// PLAY
			if(loaded){
				lock();
				player->setPaused(false);
				player->play();
				unlock();
			}else{
				cout << "can't play before we load a movie!" << endl;
			}
			playNow = false;
		}

		if(player){
			if(player->isReallyLoaded()){
				lock();
				player->update();
				unlock();
			}
		}

		if (player && !pendingDeletion){
			if(player->getIsMovieDone() && loopMode == OF_LOOP_NONE){
				//lock();
				//player->stop();
				//unlock();
				stopThread();
			}
		}

		if (player && pendingDeletion){
			delete player;
			player = NULL;
			cout << "ofxThreadedVideoPlayer: deleting internal player!" << endl;
			stopThread();
		}

		ofSleepMillis(1); //mm todo!?
	}


	#if  defined(TARGET_OSX) || defined(TARGET_LINUX) /*I'm not 100% sure of linux*/
	pthread_detach( pthread_self() ); //this is a workaround for this issue https://github.com/openframeworks/openFrameworks/issues/2506
	#endif

	readyForDeletion = true;

}


bool ofxThreadedVideoPlayer::hasFinished(){
	bool ret = false;
	lock();
	ret = player->getIsMovieDone();
	unlock();
	return ret;
}


void ofxThreadedVideoPlayer::update(){

	lock();
	if(player){
		bool reallyLoaded = player->isReallyLoaded();
		ofTexture * tex = player->getTexture();

		if( reallyLoaded && tex){

			if(needToNotifyDelegate){ //notify our delegate from the main therad, just in case (draw() always called from main thread)
				ofxThreadedVideoPlayerStatus status;
				status.path = videopPath;
				status.player = this;
				ofNotifyEvent( videoIsReadyEvent, status, this );
				needToNotifyDelegate = false;
				readyForPlayback = true;
			}
		}
	}
	unlock();

}

void ofxThreadedVideoPlayer::draw(float x, float y, float w, float h){

	if(player && loaded){
		lock();
		bool reallyLoaded = player->isReallyLoaded();
		ofTexture * tex = player->getTexture();

		if( reallyLoaded && tex){
			tex->draw(x,y, w, h ); //doing this instead if drawing the player directly to avoid 2 textureUpdate calls (one to see if texture is there, one to draw)
		}
		unlock();
	}
}


void ofxThreadedVideoPlayer::draw(float x, float y, bool drawDebug){

	if(player && loaded){

		lock();
		bool reallyLoaded = player->isReallyLoaded();
		ofTexture * tex = player->getTexture();

		if( reallyLoaded && tex){
			tex->draw(x,y, player->getWidth(), player->getHeight() ); //doing this instead if drawing the player directly to avoid 2 textureUpdate calls (one to see if texture is there, one to draw)
		}
		unlock();
	}
}

void ofxThreadedVideoPlayer::drawDebug(float x, float y){
	string debug =	"isThreadRunning: " + ofToString(isThreadRunning()) + "\n" +
	"loadNow: " + ofToString(loadNow) + "\n" +
	"playNow: " + ofToString(playNow) + "\n" +
	"stopNow: " + ofToString(stopNow) + "\n" +
	"hasFinished: " + ofToString(hasFinished()) + "\n" +
	"position: " + ofToString(getPosition()) + "\n" +
	"loop: " + string(loopMode == OF_LOOP_NONE ? "NO" : "YES") + "\n";
	ofDrawBitmapString(debug, x + 25, y + 55);
}

float ofxThreadedVideoPlayer::getWidth(){
	if(player){
		return player->getWidth();
	}
	return 0;
}


float ofxThreadedVideoPlayer::getHeight(){
	if(player){
		return player->getHeight();
	}
	return 0;
}


void ofxThreadedVideoPlayer::setPosition(float percent){
	if(player){
		lock();
		player->stop();
		player->play();
		player->setPosition( ofClamp(percent,0.0f,1.0f) );
		unlock();
		if(!isThreadRunning()) startThread();
	}
}

float ofxThreadedVideoPlayer::getPosition(){
	if(player){
		lock();
		float p = player->getPosition();
		unlock();
		return p;
	}
	return 0;
}


float ofxThreadedVideoPlayer::getDuration(){
	if(player){
		lock();
		float d = player->getDuration();
		unlock();
		return d;
	}
	return 0;
}


void ofxThreadedVideoPlayer::markForDeletion(){


	stopNow = true;
	pendingDeletion = true;
	readyForDeletion = false;
	if (!isThreadRunning()) startThread();
}


bool ofxThreadedVideoPlayer::isReadyToBeDeleted(){
	return readyForDeletion;
}

