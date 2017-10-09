#pragma once
#ifndef GLITCH_OPERATOR_H
#define GLITCH_OPERATOR_H
#include "ofMain.h"

class GlitchOperator {
	public:
		GlitchOperator(std::string file);
		GlitchOperator();
		//~GlitchOperator();
		void update(int _alpha, int _choices, int _threshold, int _numChunk, int _rando, int _step, int _divisor);
		// editing functions
		void randomColorChange();
		void sortByChunkVert();
		void sortByChunkHor();
		void simpleSort();
		void blend();
		void brightnessPeaks();
		// getters
		int getImgWidth() { return video.getWidth(); }
		ofVideoPlayer getVideo() { return video; }
		ofPixels getPixels() { return pixels; }
		int getNumChoices() { return numChoices;  }
		double getThreshold() { return thresh; }
		float getAlpha() { return alpha; }
		int getMaxNumChunk() { return maxNumChunk; }
		int getMode() { return mode; }
		bool getInvert() { return invert; }
		string getModeName() {return modeNames[mode]; }


	private:
		// user specified 'constants' used for image control
		double thresh; // brightness threshold for blending
		float alpha; // alpha value for blending
		int maxNumChunk; // max number of chunks for chunk sorting
		int mode; // determines which operation to apply
		bool invert; // decides whether to randomize colors
		int numChoices = 5; // number of implemented pixel changing algorithms starting at 0
		int yStep; // step for brightness lines
		int divisor; // divisor for lines
		vector<std::string> modeNames = { "Blend", "Simple Sort", "Sort Horizontal by Chunk",
			"Sort Horizontal by Chunk", "Brightness Lines", "Normal" };
		// video edited
		ofVideoPlayer video;
		// pixel container that is directly edited
		ofPixels pixels;
};

#endif