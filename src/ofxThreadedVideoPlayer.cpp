//
//  ofxThreadedVideoPlayer.cpp
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 04/03/14.
//
//

#include "ofxThreadedVideoPlayer.h"

ofxThreadedVideoPlayer::ofxThreadedVideoPlayer(){
	player = NULL;
	loaded = false;
	loopMode = OF_LOOP_NORMAL;
	needToNotifyDelegate = false;
	readyForPlayback = false;
	player = new ofxAVFVideoPlayerExtension();
}

ofxThreadedVideoPlayer::~ofxThreadedVideoPlayer(){
	//cout << "~ofxThreadedVideoPlayer()" << endl;
	if ( player ){
		delete player;
	};
}

void ofxThreadedVideoPlayer::loadVideo(string path){
	videopPath = path;
	loaded = player->loadMovie(videopPath);
	player->setLoopState(loopMode);
	needToNotifyDelegate = true;
}

void ofxThreadedVideoPlayer::play(){
	if(loaded){
		player->setPaused(false);
		player->play();
	}else{
		cout << "can't play before we load a movie!" << endl;
	}
}

void ofxThreadedVideoPlayer::stop(){
	//stopNow = true;
	player->setPaused(true);
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




bool ofxThreadedVideoPlayer::hasFinished(){
	bool ret = false;
	ret = player->getIsMovieDone();
	return ret;
}


void ofxThreadedVideoPlayer::update(){


	//lock();
	if(player){

		bool reallyLoaded = player->isReallyLoaded();
		ofTexture * tex = player->getTexture();

		if( reallyLoaded && tex){

			player->update();

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
	//unlock();
}


void ofxThreadedVideoPlayer::draw(float x, float y, float w, float h){

	if(player && loaded){
		bool reallyLoaded = player->isReallyLoaded();
		ofTexture * tex = player->getTexture();

		if( reallyLoaded && tex){
			tex->draw(x,y, w, h ); //doing this instead if drawing the player directly to avoid 2 textureUpdate calls (one to see if texture is there, one to draw)
		}
	}
}


void ofxThreadedVideoPlayer::draw(float x, float y, bool drawDebug){

	if(player && loaded){

		bool reallyLoaded = player->isReallyLoaded();
		ofTexture * tex = player->getTexture();

		if( reallyLoaded && tex){
			tex->draw(x,y, player->getWidth(), player->getHeight() ); //doing this instead if drawing the player directly to avoid 2 textureUpdate calls (one to see if texture is there, one to draw)
		}
	}
}

void ofxThreadedVideoPlayer::drawDebug(float x, float y){
	string debug =	string("") +
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
		player->stop();
		player->play();
		player->setPosition( ofClamp(percent,0.0f,1.0f) );
	}
}

float ofxThreadedVideoPlayer::getPosition(){
	if(player){
		float p = player->getPosition();
		return p;
	}
	return 0;
}


float ofxThreadedVideoPlayer::getDuration(){
	if(player){
		float d = player->getDuration();
		return d;
	}
	return 0;
}

