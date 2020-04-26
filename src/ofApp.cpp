#include "ofApp.h"

ofVideoPlayer vid;
//--------------------------------------------------------------
void ofApp::setup(){
	// init glitch op
	const std::string file = "videos/cb1280.mp4";
	glitch = GlitchOperator(file);
	glitch.setup();
	ofSetWindowShape(glitch.getImgWidth(), glitch.getImgHeight());
	ofSetFrameRate(30);
	ofSetWindowTitle("Video Glitch");
	// setup GUI
	glitchGroup.add(glitch.vidParams);
	gui.setup(glitchGroup);
}

//--------------------------------------------------------------
void ofApp::update(){
	// pass GUI data
	glitch.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// draw edited video
	glitch.draw();
	// draw gui
	if (guiShown) {
		gui.draw();
		// write what the mode is
		ofDrawBitmapString(glitch.getModeName(), gui.getPosition().x + gui.getWidth() + 20, gui.getPosition().y + 20);
	}	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case 't': {
			guiShown = !guiShown;
			break;
		}
		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
