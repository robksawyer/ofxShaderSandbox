//
//  ShaderBox.cpp
//  ofxShaderSandbox
//
//  Created by Rob Sawyer on 3/10/16.
//
//

#include "ShaderBox.h"

void ShaderBox::setup(){
	
	useShaderToy = true;
	usePingPong = false;
	
	resolHoriz = 1024;
	resolVert = 1024;
	
	loadFragFiles("frags/");
	
	resolution = 1;
	
	nFrag = 0;
	
	// now compile the first shader
	bFine = true;
	
	fragmentShader = frags[nFrag];
	ofLog(OF_LOG_NOTICE) << "Loading Shader" << fragmentShader;
	
	if(useShaderToy){
		shadertoy.load("frags/" + fragNames[nFrag]);
		ofSetFrameRate(60);
		shadertoy.setAdvanceTime(true);
	}
	
	if(usePingPong){
		pingPong.allocate( resolHoriz, resolVert, GL_RGB);
		pingPong.swap();
		compileCode(fragmentShader);
	}
	
}

void ShaderBox::loadFragFiles(string path){
	//Load the .frag files
	ofDirectory dir;
	dir.listDir(path);
	int fragDirSize = dir.size();
	cout << fragDirSize << endl;
	for (int val = 0; val < fragDirSize; val++){
		stringstream num;
		if (val+1 < 10){
			num << "frags/frag_000" << val+1 << ".frag";
		} else if (val+1 < 100){
			num << "frags/frag_00" << val+1 << ".frag";
		} else if (val+1 < 1000){
			num << "frags/frag_0" << val+1 << ".frag";
		} else {
			num << "frags/frag_" << val+1 << ".frag";
		}
		ofBuffer buffer = ofBufferFromFile(num.str());
		
		ofLog(OF_LOG_NOTICE) << "buffer" << ofToString(buffer);
		
		string tempStr = string(buffer);
		
		ofLog(OF_LOG_NOTICE) << "tempStr" << ofToString(tempStr);
		
		frags.push_back(tempStr);
		fragNames.push_back(num.str());
	}
	
	//	ofLog(OF_LOG_NOTICE) << ofToString(fragNames);
}

void ShaderBox::draw(){
	
	if(useShaderToy){
		shadertoy.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	} else if(usePingPong){
		pingPong.dst->draw(0,0);
	}
	
}

void ShaderBox::drawControls(){
	
	ofSetColor(255,255,255);
	ofDrawBitmapString("'Up' y 'Down' Cambia Shader", 10, 8 * 15);
	ofDrawBitmapString("Shader " + ofToString( nFrag + 1) + " of " + ofToString( getTotalShaders() ), 10, 9 * 15);
	if( bFine == true){
		ofSetColor(0,120,255);
		ofDrawBitmapString( ofToString(fragNames[nFrag]), 10, 10 * 15);
		ofDrawBitmapString("Shader Loaded Correctly!", 10, 11 * 15);
	} else {
		ofSetColor(255,0,0);
		ofDrawBitmapString( ofToString(fragNames[nFrag]), 10, 10 * 15);
		ofDrawBitmapString("Shader Loaded Incorrectly!", 10, 11 * 15);
	}

}

// This portion of the code was taken from:
// patriciogonzalezvivo/ofxComposer
// I don't remember if it was ever modified, I never used this code for anything but testing.
// I didn't ask Patricio for permission. Will send him an email.

// As most objects on openFrameworks, ofxFXObject have to be updated() in order to process the information on the GPU
void ShaderBox::update(int passes){
	
	if(usePingPong){
		updateShader(passes);
	}
	
}

void ShaderBox::keyPressed(int key){
	
	switch (key){
			
		case OF_KEY_UP:
			nFrag++;
			if (nFrag >= frags.size()) nFrag = 0;
			cout << endl << "--------" << endl << " Loading Frag: "<< nFrag+1 << endl << "--------" << endl;
			setCode(frags[nFrag]);
			break;
			
		case OF_KEY_DOWN:
			nFrag--;
			if (nFrag < 0) nFrag = frags.size()-1;
			cout << endl << "--------" << endl << " Loading Frag: "<< nFrag+1 << endl << "--------" << endl;
			setCode(frags[nFrag]);
			break;
			
		case 'r':
			resolution++;
			if (resolution == 3) resolution = 4;
			if (resolution > 4) resolution = 1;
			cout << resolution << endl;
			if(usePingPong){
				pingPong.allocate( resolHoriz/resolution, resolVert/resolution, GL_RGB);
				pingPong.swap();
			}
			break;
	}
}

int ShaderBox::getResolution(){
	return resolution;
}

int ShaderBox::getTotalShaders(){
	return frags.size();
}

bool ShaderBox::setCode(string _fragShader){
	bool loaded = false;
	
	if ( fragmentShader != _fragShader ){
		
		ofShader test;
		test.setupShaderFromSource(GL_FRAGMENT_SHADER, _fragShader);
		bFine = test.linkProgram();
		
		if( bFine ){
			fragmentShader = _fragShader;
			
			if(usePingPong){
				loaded = compileCode(fragmentShader);
			}
			
			if(useShaderToy){
				shadertoy.load(fragmentShader);
			}
			
		}
	}
	
	return loaded;
}

bool ShaderBox::compileCode(string shaderName){
	
	// Looks how many textures it¥s need on the injected fragment shader
	int num = 0;
	for (int i = 0; i < 10; i++){
		string searchFor = "tex" + ofToString(i);
		if ( shaderName.find(searchFor)!= -1)
			num++;
		else
			break;
	}
	
	// Check if it¥s the same number of tectures already created and allocated
	if ( num != nTextures ){
		// If the number of textures it¥s different
		if (textures != NULL ){
			if (nTextures > 0) {
				delete [] textures;
			}
		}
		// And initialate the right amount of textures
		nTextures = num;
		if (nTextures > 0){
			textures = new ofFbo[nTextures];
		} else if ( nTextures == 0 ){
			textures = NULL;
		}
		
		// In any case it will allocate the total amount of textures with the internalFormat need
		for( int i = 0; i < nTextures; i++){
			textures[i].allocate(resolHoriz/resolution, resolVert/resolution, GL_RGB);
			textures[i].begin();
			ofClear(0,255);
			textures[i].end();
		}
	}
	
	shader.unload();
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderName);
	bFine = shader.linkProgram();
	
	return bFine;
	
}

void ShaderBox::updateShader(int passes){
	// This process is going to be repeatted as many times as passes variable said
	for(int i = 0; i < passes; i++) {
		
		// All the process it¥s done on the pingPong ofxSwapBuffer ( basicaly two ofFbo that have a swap() funtion )
		pingPong.dst->begin();
		
		ofClear(0);
		shader.begin();
		
		// The other ofFbo of the ofxSwapBuffer can be access by calling the unicode "backbuffer"
		shader.setUniformTexture("backbuffer", pingPong.src->getTextureReference(), 1 );
		
		// All the needed textures are provided to the shader by this loop
		for( int i = 0; i < nTextures; i++){
			string texName = "tex" + ofToString(i);
			shader.setUniformTexture(texName.c_str(), textures[i].getTextureReference(), i+2 );
			string texRes = "size" + ofToString(i);
			shader.setUniform2f(texRes.c_str() , (float)textures[i].getWidth(), (float)textures[i].getHeight());
		}
		// Also there are some standar variables that are passes to the shaders
		// this ones follows the standar used by Ricardo Caballero's webGL Sandbox
		// http://mrdoob.com/projects/glsl_sandbox/ and ShaderToy by Inigo Quilez http://www.iquilezles.org/apps/shadertoy/
		// webGL interactive GLSL editors
		//
		shader.setUniform1f("time", ofGetElapsedTimef() );
		shader.setUniform2f("size", (float)(resolHoriz/resolution), (float)(resolVert/resolution));
		shader.setUniform2f("resolution", (float)(resolHoriz/resolution), (float)(resolVert/resolution));
		shader.setUniform2f("mouse", ((float)ofGetMouseX()/(float)ofGetWindowWidth()), 1-((float)ofGetMouseY()/(float)ofGetWindowHeight()));
		
		// renderFrame() is a built-in funtion of ofxFXObject that only draw a white box in order to
		// funtion as a frame here the textures could rest.
		// If you want to distort the points of a textures, probably you want to re-define the renderFrame funtion.
		glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(resolHoriz/resolution, 0, 0);
		glVertex3f(resolHoriz/resolution, resolVert/resolution, 0);
		glVertex3f(0, resolVert/resolution, 0);
		glEnd();
		
		shader.end();
		
		pingPong.dst->end();
		
		pingPong.swap();    // Swap the ofFbo's. Now dst is src and src is dst
	}
	
	pingPong.swap();        // After the loop the render information will be at the src ofFbo of the ofxSwapBuffer
	// this extra swap() call will put it on the dst one. Witch sounds more reasonable...
}