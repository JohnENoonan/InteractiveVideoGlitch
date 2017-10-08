#include "ofApp.h"

ofVideoPlayer vid;
//--------------------------------------------------------------
void ofApp::setup(){
	// init glitch op
	int w = 100; 
	int h = 30;
	gui.setup();
	gui.setPosition(30, 360);
	gui.add(choices.setup("choices", 0, 0, 3));
	gui.add(threshold.setup("threshold", 30, 10, 100));
	gui.add(numChunk.setup("numChunk", 60, 10, 100));
	gui.add(alpha.setup("alpha", .2, 0, 1));
	gui.add(rando.setup("noise colors", false));

	const std::string file = "videos/ny.mp4";
	//vid.load(file);
	//vid.setLoopState(OF_LOOP_NORMAL);
	//vid.play();

	glitch = GlitchOperator(file);	
}

//--------------------------------------------------------------
void ofApp::update(){
	glitch.alpha = alpha;
	glitch.choice = choices;
	glitch.thresh = threshold;
	glitch.numChunk = numChunk;
	glitch.invert = rando;
	glitch.update();
	//vid.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofImage i;
	i.setFromPixels(glitch.getPixels());
	i.draw(0,0);
	gui.draw();
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
