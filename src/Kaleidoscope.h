//
//  Kaleidoscope.h
//  ofxShaderSandbox
//
//  Created by Rob Sawyer on 3/10/16.
//
//

#ifndef Kaleidoscope_h
#define Kaleidoscope_h

#include "ofMain.h"

class Kaleidoscope{
public:
	
	void setup(int v, int h, int slices);
	void draw(int resolution, int v, int h);
	void drawControls();
	void keyPressed(int key);
	
	void begin(int resolution);
	void end(int resolution);
	
	void beginA();
	void beginB();
	void beginC();
	void endA();
	void endB();
	void endC();
	
	float getSlices();
	string getSlicesAsString();
	
	// Kaleidoscope
	ofFbo fboKaleidoscopeA;
	ofFbo fboKaleidoscopeB;
	ofFbo fboKaleidoscopeC;
	ofFbo completaParaSyphon;
	float KaleidoscopeSlices;
	
	bool bKaleidoscope;

};

#endif /* Kaleidoscope_h */
