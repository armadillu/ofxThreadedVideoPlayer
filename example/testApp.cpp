#include "testApp.h"


void testApp::videoIsReadyCallback(ofxThreadedVideoPlayer* whichVideo){
	cout << "video " << whichVideo << " ready!" << endl;
}

void testApp::setup(){

	ofSetFrameRate(65);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofBackground(22);
	ofSetLineWidth(2);

	TIME_SAMPLE_SET_FRAMERATE(60);

	selectedVideo = -1;
	debug = false;

}


void testApp::update(){

}


void testApp::draw(){

	ofPushMatrix();
		float scale = 0.3;
		int x = 0;
		int y = 0;

		ofScale(scale, scale);

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



void testApp::keyPressed(int key){

	switch (key) {
		case ' ':{
			ofxThreadedVideoPlayer * v = new ofxThreadedVideoPlayer();
			v->setVideoReadyCallback(videoIsReadyCallback); //note how I setup a callback to be notified whenever the video is ready to play!
			v->loadVideo("chaos.mov");
			//v->play();
			videos.push_back(v);
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

		default:
			break;
	}
}


void testApp::keyReleased(int key){

}


void testApp::mouseMoved(int x, int y ){

}


void testApp::mouseDragged(int x, int y, int button){

}


void testApp::mousePressed(int x, int y, int button){

}


void testApp::mouseReleased(int x, int y, int button){

}


void testApp::windowResized(int w, int h){

}


void testApp::gotMessage(ofMessage msg){

}


void testApp::dragEvent(ofDragInfo dragInfo){
	
}
