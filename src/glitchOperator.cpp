#include "glitchOperator.h"


////////////// Constructors /////////////////////
// takes string that is path to video
GlitchOperator::GlitchOperator(std::string file) {
	// load and init video
	video.load(file);
	video.setLoopState(OF_LOOP_NORMAL);
	video.play();
	imgWidth = video.getWidth();
	numChunk = 30;
	thresh = 50;
	alpha = .5;
	choice = 0;
	invert = false;
}

GlitchOperator::GlitchOperator() {
	GlitchOperator("vidoes/swamp.mp4");
}


void GlitchOperator::update() {
	// update video
	video.update();
	// get pixels from current frame
	pixels = video.getPixelsRef();
	switch (choice) {
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
	}
	if (invert) {
		randomColorChange();
	}
}

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
	numChunk = ofRandom(5, numChunk);
	for (int y = 0; y < video.getHeight(); ++y) {
		for (int x = 0; x < video.getWidth()-numChunk; x+= numChunk) {
			vector<ofColor> c;
			for (int j = 0; j<numChunk; j++) {
				c.push_back(pixels.getColor(x + j, y));
			}
			ofSort(c, compareBrightness);
			for (int j = 0; j<numChunk; j++) {
				pixels.setColor(x + j, y, c[j]);
			}
		}
	}
	
}

void GlitchOperator::sortByChunkHor() {
	numChunk = ofRandom(5, numChunk);
	for (int x = 0; x < video.getWidth(); ++x) {
		for (int y = 0; y < video.getHeight() - numChunk; y += numChunk) {
			vector<ofColor> c;
			for (int j = 0; j<numChunk; j++) {
				c.push_back(pixels.getColor(x, y+j));
			}
			ofSort(c, compareBrightness);
			for (int j = 0; j<numChunk; j++) {
				pixels.setColor(x, y+j, c[j]);
			}
		}
	}
	
}

void GlitchOperator::peaks() {
	int yStep = 10;
	ofImage img;
	ofColor line = ofColor::aquamarine;
	img.allocate(video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
	img.setColor(ofColor::bisque);
	for (int y = yStep; y < video.getHeight(); y = yStep) {
		for (int x = 0; x < video.getWidth(); x+=4) {
			float brightness = pixels.getColor(x, y).getBrightness();
			float per = brightness / 255.0;
			int h = (int)(per * yStep);
			img.setColor(x, y + h, line);
		}
	}
	pixels = img.getPixels();
}

ofImage GlitchOperator::getImage() {
	return img;
}

ofPixels GlitchOperator::getPixels() {
	return pixels;
}

// Getters
int GlitchOperator::getImgWidth() { return imgWidth; }
ofVideoPlayer GlitchOperator::getVideo() { return video; }
