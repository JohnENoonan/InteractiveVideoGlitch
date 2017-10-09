#include "ofApp.h"

ofVideoPlayer vid;
//--------------------------------------------------------------
void ofApp::setup(){
	// init glitch op
	int w = 100; 
	int h = 30;
	const std::string file = "videos/ny.mp4";
	glitch = GlitchOperator(file);
	gui.setup();
	gui.setPosition(30, 360);
	gui.add(mode.setup("Mode", 0, 0, glitch.getNumChoices()));
	gui.add(threshold.setup("Color threshold", 30, 10, 100));
	numChunk.setup("Max Chunk", 60, 10, 100);
	gui.add(&numChunk);
	gui.add(alpha.setup("Alpha", .2, 0, 1));
	gui.add(brightnessStep.setup("Brightness step", 7, 1, 20));
	gui.add(brightnessDivisor.setup("Brightness divisor", 20, 1, 255));
	gui.add(rando.setup("noise colors", false));

	

		
}

//--------------------------------------------------------------
void ofApp::update(){
	glitch.update(alpha, mode, threshold, numChunk, rando, brightnessStep, brightnessDivisor);
	//vid.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::darkGray);
	ofImage i;
	ofTexture t;
	i.setFromPixels(glitch.getPixels());
	i.draw(0,0);
	gui.draw();
	// write what the mode is
	ofDrawBitmapString(glitch.getModeName(), 30 + gui.getWidth() + 20, 400);
	//vid.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
