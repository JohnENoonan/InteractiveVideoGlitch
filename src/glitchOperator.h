#pragma once
#ifndef GLITCH_OPERATOR_H
#define GLITCH_OPERATOR_H
#include "ofMain.h"

enum GlitchMode {
	BLEND,
	SIMPLE_SORT,
	HORIZONTAL_CHUNK,
	VERTICAL_CHUNK,
	BRIGHTNESS,
	DEFAULT
};

class GlitchOperator {
	public:
		GlitchOperator(std::string file);
		GlitchOperator();
		//~GlitchOperator();
		void update();
		void setup();
		void draw();
		// editing functions
		void randomColorChange();
		void sortByChunkVert();
		void sortByChunkHor();
		void simpleSort();
		void blend();
		void brightnessPeaks();
		// getters
		int getImgWidth() { return video.getWidth(); }
		int getImgHeight() { return video.getHeight(); }
		ofVideoPlayer getVideo() { return video; }
		ofPixels getPixels() { return pixels; }
		ofImage getImage();
		int getNumChoices() { return numChoices;  }
		double getThreshold() { return thresh; }
		float getAlpha() { return alpha; }
		int getMaxNumChunk() { return maxNumChunk; }
		int getMode() { return mode; }
		bool getInvert() { return invert; }
		string getModeName() const;
		int getYStep() { return yStep; }
		int getDivisor() { return divisor; }

		ofParameterGroup vidParams;
		void modeListener(int& val);

	private:
		// user specified 'constants' used for image control
		
		ofParameter<double> thresh; // brightness threshold for blending
		ofParameter<float> alpha; // alpha value for blending
		ofParameter<int> maxNumChunk; // max number of chunks for chunk sorting
		GlitchMode mode; // determines which operation to apply
		ofParameter<int> modeInt;
		ofParameter<bool> invert; // decides whether to randomize colors
		int numChoices = 5; // number of implemented pixel changing algorithms starting at 0
		ofParameter<int> yStep; // step for brightness lines
		ofParameter<int> divisor; // divisor for lines
		ofParameter<float> lineThickness;
		ofParameter<bool> useLineColor;
		ofParameter<bool> buildLines;
		vector<std::string> modeNames = { "Blend", "Simple Sort", "Sort Horizontal by Chunk",
			"Sort Vertical by Chunk", "Brightness Lines", "Normal" };
		// video edited
		ofVideoPlayer video;
		// pixel container that is directly edited
		ofPixels pixels;
		ofFbo fboCanvas;
		ofTexture textureCanvas;
};

#endif