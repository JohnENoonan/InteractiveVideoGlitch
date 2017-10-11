#include "glitchOperator.h"


////////////// Constructors /////////////////////
// takes string that is path to video
GlitchOperator::GlitchOperator(std::string file) {
	// load and init video
	video.load(file);
	video.setLoopState(OF_LOOP_NORMAL);
	video.play();
	// set base values
	maxNumChunk = 30;
	thresh = 30;
	alpha = .2;
	mode = 0;
	yStep = 7;
	divisor = 20;
	invert = false;
}

GlitchOperator::GlitchOperator() {
	GlitchOperator("videos/swamp.mp4");
}

// update member variables and perform pixel corrections based on uder input
void GlitchOperator::update(int _alpha, int _choices, int _threshold, int _numChunk, int _rando, int _step, int _divisor) {
	// update video
	video.update();
	// get pixels from current frame
	pixels = video.getPixels();
	// update member variables
	thresh = _threshold;
	alpha = _alpha;
	maxNumChunk = _numChunk;
	mode = _choices;
	invert = _rando;
	yStep = _step;
	divisor = _divisor;

	switch (mode) {
		case 0:
			blend();
			break;
		case 1:
			simpleSort();
			break;
		case 2:
			sortByChunkHor();
			break;
		case 3:
			sortByChunkVert();
			break;
		case 4:
			brightnessPeaks();
			break;

		case 5:
			break;
	}
	if (invert) {
		randomColorChange();
	}
}

// Randomly reorders the RGB channels
void GlitchOperator::randomColorChange() {
	for (int x = 0; x < video.getWidth(); ++x) {
		for (int y = 0; y < video.getHeight(); ++y) {
			ofColor c = pixels.getColor(x, y);
			ofColor cols[3] = {(int)c.r, (int)c.g, (int)c.b};
			ofColor newC = ofColor(c[ofRandom(3)], c[ofRandom(3)], c[ofRandom(3)], 255);
			pixels.setColor(x, y, newC);
		}
	}
}

// alpha blend each pixel with its neighbor
void GlitchOperator::blend() {
	// iterate throuch each pixel
	for (int x = 0; x < video.getWidth(); ++x) {
		for (int y = 0; y < video.getHeight()-1; ++y) {
			ofColor curr = pixels.getColor(x, y);
			ofColor below = pixels.getColor(x, y+1);
			
			if (std::abs(curr.getBrightness() - below.getBrightness()) > thresh) {
				//std::cout <<std::abs(curr.getBrightness() - below.getBrightness()) std::abs(curr.getBrightness() - below.getBrightness()) << std::endl;
				ofColor temp = curr;
				curr.lerp(below, alpha);
				//below.lerp(temp, 1);
				below = temp;
			}
			pixels.setColor(x, y, curr);
			pixels.setColor(x, y + 1, below);
		}
	}
	for (int x = 0; x < video.getWidth()-1; ++x) {
		for (int y = 0; y < video.getHeight(); ++y) {
			ofColor curr = pixels.getColor(x, y);
			ofColor right = pixels.getColor(x+1, y );

			if (std::abs(curr.getBrightness() - right.getBrightness()) > thresh) {
				//std::cout <<std::abs(curr.getBrightness() - below.getBrightness()) std::abs(curr.getBrightness() - below.getBrightness()) << std::endl;
				ofColor temp = curr;
				curr.lerp(right, alpha);
				//below.lerp(temp, 1);
				right = temp;
			}
			pixels.setColor(x, y, curr);
			pixels.setColor(x+1, y, right);
		}
	}
}

// compare function for brightness
bool compareBrightness(ofColor a, ofColor b) {
	return a.getBrightness() > b.getBrightness();
}

// sort each pixel vertically
void GlitchOperator::simpleSort() {
	for (int x = 0; x < video.getWidth(); ++x) {
		vector<ofColor> line;
		for (int y = 0; y < video.getHeight(); ++y) {
			line.push_back(pixels.getColor(x, y));
		}
		ofSort(line, compareBrightness);
		for (int y = 0; y < video.getHeight(); ++y) {
			pixels.setColor(x, y, line[y]);
		}
	}
}

void GlitchOperator::sortByChunkVert() {
	maxNumChunk = ofRandom(5, maxNumChunk);
	for (int y = 0; y < video.getHeight(); ++y) {
		for (int x = 0; x < video.getWidth()- maxNumChunk; x+= maxNumChunk) {
			vector<ofColor> c;
			for (int j = 0; j<maxNumChunk; j++) {
				c.push_back(pixels.getColor(x + j, y));
			}
			ofSort(c, compareBrightness);
			for (int j = 0; j<maxNumChunk; j++) {
				pixels.setColor(x + j, y, c[j]);
			}
		}
	}
	
}

void GlitchOperator::sortByChunkHor() {
	maxNumChunk = ofRandom(5, maxNumChunk);
	for (int x = 0; x < video.getWidth(); ++x) {
		for (int y = 0; y < video.getHeight() - maxNumChunk; y += maxNumChunk) {
			vector<ofColor> c;
			for (int j = 0; j<maxNumChunk; j++) {
				c.push_back(pixels.getColor(x, y+j));
			}
			ofSort(c, compareBrightness);
			for (int j = 0; j<maxNumChunk; j++) {
				pixels.setColor(x, y+j, c[j]);
			}
		}
	}
	
}


// draw lines based on brightness
void GlitchOperator::brightnessPeaks() {
	// new 'canvas'
	ofFbo fbo;
	// color of the lines
	ofColor line = ofColor::black;
	fbo.allocate(video.getWidth(), video.getHeight());
	fbo.begin();
	ofBackground(ofColor::white);
	ofSetColor(line);
	for (int y = yStep; y < video.getHeight(); y += yStep) {
		ofPoint prev = ofPoint(0, y + (pixels.getColor(0,y).getBrightness())/divisor);
		for (int x = 0; x < video.getWidth(); x+=4) {
			float brightness = pixels.getColor(x, y).getBrightness();
			// keep lines inside of eachother divide by 255
			float per = brightness / divisor;
			int h = (int)(per * yStep);
			ofDrawLine(ofPoint(x, y + h), prev);
			prev = ofPoint(x, y + h);
		}
		////if (!prev.x == video.getWidth() - 1){
		//	ofDrawLine(prev, ofPoint(video.getWidth()-1,
		//			   y + (pixels.getColor(video.getWidth() - 1, y).getBrightness()) / divisor));
		////}
	}
	fbo.end();
	// save image to pixels
	fbo.readToPixels(pixels);
}
