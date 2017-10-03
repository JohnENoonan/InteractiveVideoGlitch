#pragma once
#ifndef GLITCH_OPERATOR_H
#define GLITCH_OPERATOR_H
#include "ofMain.h"

class GlitchOperator {
	public:
		GlitchOperator(std::string file);
		GlitchOperator();
		void update();
		void randomColorChange();
		// sort functions
		void sortByChunkVert();
		void sortByChunkHor();
		void simpleSort();
		void blend();
		void peaks();
		// getters
		int getImgWidth();
		ofVideoPlayer getVideo();
		ofImage getImage();
		ofPixels getPixels();

		double thresh;
		float alpha;
		int numChunk;
		int choice;
		bool invert;
	private:
		int imgWidth;
		
		ofVideoPlayer video;
		ofImage img;
		ofPixels pixels;
};

#endif