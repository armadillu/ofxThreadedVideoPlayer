#include "testApp.h"




void testApp::setup(){

	ofSetFrameRate(65);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofBackground(22);
	ofSetLineWidth(2);

	selectedVideo = -1;
	debug = false;
}


void testApp::update(){
	mutex.lock();
	for(int i = 0; i < videos.size(); i++){
		videos[i]->update();
	}
	mutex.unlock();
}

void testApp::videoIsReadyCallback(ofxThreadedVideoPlayerStatus &status){

	cout << "video at "<< status.path << " is ready for playback!" << endl;
	//start playback as soon as the video is ready!
	status.player->play();
}



void testApp::draw(){

	ofPushMatrix();
		float scale = 0.3;
		int x = 0;
		int y = 0;

		ofScale(scale, scale);

		mutex.lock();
		for(int i = 0; i < videos.size(); i++){

			ofPushMatrix();
				ofTranslate(x, y);
				videos[i]->draw(0,0, debug);
				if(i==selectedVideo){
					ofNoFill();
					ofSetColor(255,0,0);
					ofRect(0, 0, videos[i]->getWidth(), videos[i]->getHeight());
					ofSetColor(255);
					ofFill();
				}
			
				x += videos[i]->getWidth();
				if (x * scale > ofGetWidth()){
					x = 0;
					y += videos[i]->getHeight();
				}
			ofPopMatrix();

		}
		mutex.unlock();
	ofPopMatrix();

	ofDrawBitmapString("numPlayers: " + ofToString(videos.size()), 8, 140);

	//clock hand to see threading in action
	ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		ofRotate(360 * ofGetElapsedTimef(), 0, 0, 1);
		ofTriangle(10, 0, -10, 0, 0, 200);
	ofPopMatrix();

	ofDrawBitmapStringHighlight("SPACEBAR to add video\n"
								"LEFT / RIGHT ARROW_KEYS to select video\n"
								"'1' to play selected video\n"
								"'2' to stop selected video\n"
								"'l' to disable loop on selected video\n"
								"'L' to enable loop on selected video\n"
								"'r' to rewind on selected video\n"
								"'f' to fastForward selected video\n"
								"'d' to toggle debug"
								,
								20,
								ofGetHeight() - 120
								);

}


void testApp::addvideo(){

	ofxThreadedVideoPlayer * v = new ofxThreadedVideoPlayer();
	//we want to know when the movie will be ready to play!
	ofAddListener(v->videoIsReadyEvent, this, &testApp::videoIsReadyCallback);
	v->loadVideo("chaos.mov");
	//v->play();
	videos.push_back(v);
}


void testApp::keyPressed(int key){

	switch (key) {
		case ' ':{
			addvideo();
			if(selectedVideo == -1) selectedVideo = 0;
		}break;

		case OF_KEY_LEFT:{
			selectedVideo --;
			if(selectedVideo < 0 ) selectedVideo = videos.size() - 1;
		}break;

		case OF_KEY_RIGHT:{
			selectedVideo ++;
			if(selectedVideo >= videos.size() ) selectedVideo = 0;
		}break;

		case '1':{
			if (selectedVideo >= 0) videos[selectedVideo]->play();
		}break;

		case '2':{
			if (selectedVideo >= 0) videos[selectedVideo]->stop();
		}break;

		case 'l':{
			if (selectedVideo >= 0) videos[selectedVideo]->setLoopMode(OF_LOOP_NONE);
		}break;

		case 'L':{
			if (selectedVideo >= 0) videos[selectedVideo]->setLoopMode(OF_LOOP_NORMAL);
		}break;

		case 'r':{
			if (selectedVideo >= 0) videos[selectedVideo]->setPosition(videos[selectedVideo]->getPosition() - 0.1);
		}break;

		case 'f':{
			if (selectedVideo >= 0) videos[selectedVideo]->setPosition(videos[selectedVideo]->getPosition() + 0.1);
		}break;

		case 'd': debug = !debug; break;

		case 'D':{

			mutex.lock();
			if(videos.size()){
				ofxThreadedVideoPlayer* p = videos[0];
				videos.erase(videos.begin());
				p->deleteMe();
				p = NULL;
			}
			mutex.unlock();
			
		}break;

		default:
			break;
	}
}
