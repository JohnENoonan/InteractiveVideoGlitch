#include "glitchOperator.h"


////////////// Constructors /////////////////////
// takes string that is path to video
GlitchOperator::GlitchOperator(std::string file) {
	// load and init video
	video.load(file);
	video.setLoopState(OF_LOOP_NORMAL);
	video.play();
}

void GlitchOperator::setup() {
	fboCanvas.allocate(video.getWidth(), video.getHeight(), GL_RGB);
	textureCanvas.allocate(video.getWidth(), video.getHeight(), GL_RGB);
	mode = GlitchMode::BLEND;
	// set up gui 
	vidParams.setName("Glitch Controls");
	vidParams.add(modeInt.set("Mode", 0, 0, 5));
	modeInt.addListener(this, &GlitchOperator::modeListener);
	vidParams.add(thresh.set("Brightness Threshold", 30, 10, 100));
	vidParams.add(alpha.set("Alpha", .2f, 0.0f, 1.0f));
	vidParams.add(maxNumChunk.set("Max Chunks", 30, 10, 100));
	vidParams.add(yStep.set("Brightness Step", 7, 1, 20));
	vidParams.add(divisor.set("Brightness Divisor", 20, 1, 255));
	vidParams.add(lineThickness.set("Line Thickness", 1, 0, 10));
	vidParams.add(useLineColor.set("Use Line Color", false));
	vidParams.add(buildLines.set("Buil Up Lines", false));
	vidParams.add(invert.set("Noise Colors", false));
}

GlitchOperator::GlitchOperator() {
	GlitchOperator("videos/swamp.mp4");
}

// update member variables and perform pixel corrections based on uder input
void GlitchOperator::update() {
	// update video
	video.update();
	// get pixels from current frame
	pixels = video.getPixels();

	switch (mode) {
		case GlitchMode::BLEND:
			blend();
			break;
		case GlitchMode::SIMPLE_SORT:
			simpleSort();
			break;
		case GlitchMode::HORIZONTAL_CHUNK:
			sortByChunkHor();
			break;
		case GlitchMode::VERTICAL_CHUNK:
			sortByChunkVert();
			break;
		case GlitchMode::BRIGHTNESS:
			brightnessPeaks();
			break;

		case GlitchMode::DEFAULT:
			break;
	}
	if (invert) {
		randomColorChange();
	}
}

void GlitchOperator::draw() {
	//ofImage i;
	
	//i.setFromPixels(pixels);
	//i.draw(0, 0);
	switch (mode) {
		case GlitchMode::BLEND:
		case GlitchMode::SIMPLE_SORT:
		case GlitchMode::HORIZONTAL_CHUNK:
		case GlitchMode::VERTICAL_CHUNK: {
			
			textureCanvas.loadData(pixels);
			textureCanvas.draw(0, 0);
			break;
		}
		case GlitchMode::BRIGHTNESS:
			fboCanvas.draw(0, 0);
			break;
		default: {
			video.draw(0, 0);
			break;
		}
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
	// blend vertically
	for (int x = 0; x < video.getWidth(); ++x) {
		for (int y = 0; y < video.getHeight()-1; ++y) {
			ofColor curr = pixels.getColor(x, y);
			ofColor below = pixels.getColor(x, y+1);
			if (std::abs(curr.getBrightness() - below.getBrightness()) > thresh) {
				ofColor temp = curr;
				curr.lerp(below, alpha);
				below = temp;
			}
			pixels.setColor(x, y, curr);
			pixels.setColor(x, y + 1, below);
		}
	}
	// blend horizontally
	for (int x = 0; x < video.getWidth()-1; ++x) {
		for (int y = 0; y < video.getHeight(); ++y) {
			ofColor curr = pixels.getColor(x, y);
			ofColor right = pixels.getColor(x+1, y );

			if (std::abs(curr.getBrightness() - right.getBrightness()) > thresh) {
				ofColor temp = curr;
				curr.lerp(right, alpha);
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

// create chunks of pixels and sort them vertically
void GlitchOperator::sortByChunkVert() {
	int chunks = ofRandom(5, maxNumChunk);
	for (int y = 0; y < video.getHeight(); ++y) {
		for (int x = 0; x < video.getWidth()- chunks; x+= chunks) {
			vector<ofColor> c;
			for (int j = 0; j< chunks; j++) {
				c.push_back(pixels.getColor(x + j, y));
			}
			ofSort(c, compareBrightness);
			for (int j = 0; j< chunks; j++) {
				pixels.setColor(x + j, y, c[j]);
			}
		}
	}
	
}

// sort by chunks of pixels horizontally
void GlitchOperator::sortByChunkHor() {
	int chunks = ofRandom(5, maxNumChunk);
	for (int x = 0; x < video.getWidth(); ++x) {
		for (int y = 0; y < video.getHeight() - chunks; y += chunks) {
			vector<ofColor> c;
			for (int j = 0; j< chunks; j++) {
				c.push_back(pixels.getColor(x, y+j));
			}
			ofSort(c, compareBrightness);
			for (int j = 0; j< chunks; j++) {
				pixels.setColor(x, y+j, c[j]);
			}
		}
	}
	
}

// draw lines on canvas based on brightness to create  image of video
void GlitchOperator::brightnessPeaks() {
	// color of the lines
	ofColor line = ofColor::black;
	fboCanvas.begin();
		ofSetLineWidth(lineThickness);
		if (useLineColor) {
			if (!buildLines) {
				ofBackground(ofColor::black);
			}
		}
		else {
			ofBackground(ofColor::white);
		}
		for (int y = yStep; y < video.getHeight(); y += yStep) {
			// the previous pixel point that was sampled
			ofPoint prev = ofPoint(0, y + (pixels.getColor(0,y).getBrightness())/divisor);
			for (int x = 0; x < video.getWidth(); x+=4) {
				ofColor pixCol = pixels.getColor(x, y);
				float brightness = pixCol.getBrightness();
				if (!useLineColor) {
					ofSetColor(line);
				}
				else {
					
					ofSetColor(pixCol);
				}
				
				// to keep lines inside of eachother divide by 255
				float per = brightness / divisor;
				int h = (int)(per * yStep);
				ofDrawLine(ofPoint(x, y + h), prev);
				prev = ofPoint(x, y + h);
			}
		}
	fboCanvas.end();
	// save image to pixels
	fboCanvas.readToPixels(pixels);
}

string GlitchOperator::getModeName() const {
	switch (mode) {
		case GlitchMode::BLEND:
			return "Blend";
			break;
		case GlitchMode::SIMPLE_SORT:
			return "Simple Sort";
			break;
		case GlitchMode::HORIZONTAL_CHUNK:
			return "Horizontal";
			break;
		case GlitchMode::VERTICAL_CHUNK:
			return "Vertical";
			break;
		case GlitchMode::BRIGHTNESS:
			return "Peaks";
			break;
		default: {
			return "Normal";
			break;
		}
	}
}

void GlitchOperator::modeListener(int& val) {
	switch (val) {
		case 0:
			mode = GlitchMode::BLEND;
			break;
		case 1:
			mode = GlitchMode::SIMPLE_SORT;
			break;
		case 2:
			mode = GlitchMode::HORIZONTAL_CHUNK;
			break;
		case 3:
			mode = GlitchMode::VERTICAL_CHUNK;
			break;
		case 4:
			mode = GlitchMode::BRIGHTNESS;
			break;
		default: {
			mode = GlitchMode::DEFAULT;
			break;
		}
	}
}