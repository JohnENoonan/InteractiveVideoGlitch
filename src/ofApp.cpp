#include "ofApp.h"

ofVideoPlayer vid;
//--------------------------------------------------------------
void ofApp::setup(){
	// init glitch op
	//ofSetWindowShape(1280, 720);
	std::string vidFile = "videos/stairway.mp4";
	if (arguments.size() >= 2) {
		vidFile = arguments[1];
		if (arguments.size() == 3) {
			renderOut = (bool)(ofToLower(arguments[2]) == "true");
		}
	}	
	cout << vidFile << endl;
	glitch = GlitchOperator(vidFile);
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
	if (renderOut) {
		glitch.getImage().save("render/" + ofToString(ofGetFrameNum()) + ".png");
	}
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
	if (key == 't' || key == '~') {
		guiShown = !guiShown;
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
