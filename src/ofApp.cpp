#include "ofApp.h"

ofVideoPlayer vid;
//--------------------------------------------------------------
void ofApp::setup(){
	// init glitch op
	int w = 100; 
	int h = 30;
	const std::string file = "videos/stairway.mp4";
	glitch = GlitchOperator(file);
	gui.setup();
	gui.setPosition(30, 360);
	gui.add(mode.setup("Mode", glitch.getMode(), 0, glitch.getNumChoices()));
	gui.add(threshold.setup("Color threshold", glitch.getThreshold(), 10, 100));
	gui.add(alpha.setup("Alpha", glitch.getAlpha(), 0, 1));
	numChunk.setup("Max Chunk", glitch.getMaxNumChunk(), 10, 100);
	gui.add(&numChunk);
	gui.add(brightnessStep.setup("Brightness step", glitch.getYStep(), 1, 20));
	gui.add(brightnessDivisor.setup("Brightness divisor", glitch.getDivisor(), 1, 255));
	gui.add(rando.setup("noise colors", glitch.getInvert()));

	

		
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
	ofDrawBitmapString(glitch.getModeName(), gui.getPosition().x + gui.getWidth() + 20, gui.getPosition().y + 20);
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
