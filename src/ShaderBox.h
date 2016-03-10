//
//  ShaderBox.h
//  ofxShaderSandbox
//
//  Created by Rob Sawyer on 3/10/16.
//
//

#ifndef ShaderBox_h
#define ShaderBox_h

#include "ofMain.h"
#include "pingPongBuffer.h"
#include "ofxShadertoy.h"

class ShaderBox{
public:
	void setup();
	void draw();
	void drawControls();
	void update(int passes);
	void keyPressed(int key);
	
	int getResolution();
	int getTotalShaders();
	
	vector<string> frags;
	vector<string> fragNames;
	
	ofxShadertoy shadertoy;
	
	pingPongBuffer pingPong;
	ofShader shader;
	ofFbo *textures;
	
	int nTextures;
	int resolHoriz;
	int resolVert;
	int resolution;
	int nFrag;
	
	// Shader Sand Box
	bool setCode(string _fragShader);
	bool compileCode(string shaderName);
	
	bool bFine;
	bool usePingPong;
	bool useShaderToy;
	
	string fragmentShader;
	
private:
	void updateShader(int passes);
};

#endif /* ShaderBox_h */
