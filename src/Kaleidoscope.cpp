//
//  Kaleidoscope.cpp
//  ofxShaderSandbox
//
//  Created by Rob Sawyer on 3/10/16.
//
//

#include "Kaleidoscope.h"

void Kaleidoscope::setup(int v, int h, int slices){
	fboKaleidoscopeA.allocate( h, v, GL_RGB);
	fboKaleidoscopeB.allocate( h/2, v/2, GL_RGB);
	fboKaleidoscopeC.allocate( h/4, v/4, GL_RGB);
	
	bKaleidoscope = false;
	KaleidoscopeSlices = slices;
}

void Kaleidoscope::draw(int resolution, int v, int h){
	
	ofClear(0,0,0,0);
	ofBackground(0,0,0);
	ofSetColor(255,255,255);
	ofEnableAlphaBlending();
	
	if (bKaleidoscope == false){
		
		if(resolution == 1 ){
			fboKaleidoscopeA.draw(0, ofGetWindowHeight(), ofGetWindowWidth(), -ofGetWindowHeight());
		} else if (resolution == 2 ){
			fboKaleidoscopeB.draw(0, ofGetWindowHeight(), ofGetWindowWidth(), -ofGetWindowHeight());
		}else if (resolution == 4 ){
			fboKaleidoscopeC.draw(0, ofGetWindowHeight(), ofGetWindowWidth(), -ofGetWindowHeight());
		}
		
	} else {
		
		float distCenter = ofGetWindowHeight() / 2;
		float nSlices = KaleidoscopeSlices * 2;
		float angleTemp = 360/nSlices;
		float catOpuesto = tan(angleTemp*(PI/180)) * distCenter;
		
		if(resolution == 1 ){
			fboKaleidoscopeA.getTextureReference().bind();
		} else if (resolution == 2 ){
			fboKaleidoscopeB.getTextureReference().bind();
		}else if (resolution == 4 ){
			fboKaleidoscopeC.getTextureReference().bind();
		}
		ofPushMatrix();
		ofTranslate( ( ofGetWindowWidth() ) / 2, ( ofGetWindowHeight() ) /2 );
		for (int slice = 0; slice  < nSlices/2; slice++){
			ofPushMatrix();
			ofRotateZ(slice * angleTemp * 2);
			glBegin( GL_TRIANGLES );
			glTexCoord2d( ( (v/resolution) / 2), ( (v/resolution) / 2) );
			glVertex2d(0,0);
			glTexCoord2d( ( (v/resolution) /2) + catOpuesto/resolution + 80 / (float)resolution , ( (v/resolution) / 2 ) + ( (float)distCenter / (float)resolution) );
			glVertex2d(catOpuesto, -distCenter);
			glTexCoord2d( ( (v/resolution) /2) - catOpuesto/resolution + 80 / (float)resolution , ( (v/resolution) / 2 ) + ( (float)distCenter / (float)resolution) );
			glVertex2d(-catOpuesto, -distCenter);
			glEnd();
			ofPopMatrix();
		}
		ofPopMatrix();
		if(resolution == 1 ){
			fboKaleidoscopeA.getTextureReference().unbind();
		} else if (resolution == 2 ){
			fboKaleidoscopeB.getTextureReference().unbind();
		}else if (resolution == 4 ){
			fboKaleidoscopeC.getTextureReference().unbind();
		}
		ofSetColor(255,255,255);
		ofPushMatrix();
		ofTranslate(ofGetWindowWidth()/2,ofGetWindowHeight()/2);
		for (int slice = 0; slice  < nSlices/2; slice++){
			ofPushMatrix();
			ofRotateZ(slice*angleTemp*2);
			ofDrawLine(catOpuesto, -distCenter, -catOpuesto, -distCenter);
			ofPopMatrix();
		}
		ofPopMatrix();
	}

}

void Kaleidoscope::drawControls(){
	if( bKaleidoscope == true){
		ofDrawBitmapString("'k' Toggle Kaleidoscope: ON!", 10, 6 * 15);
		ofDrawBitmapString("'1' y '2' Kaleidoscope Slices: " + getSlicesAsString(), 10, 7 * 15);
	} else {
		ofDrawBitmapString("'k' Toggle Kaleidoscope: OFF", 10, 6 * 15);
		ofSetColor(100,100,100);
		ofDrawBitmapString("'1' y '2' Kaleidoscope Slices: " + getSlicesAsString(), 10, 7 * 15);
	}
}

void Kaleidoscope::keyPressed(int key){
	switch (key){
		case 'k':
			bKaleidoscope = !bKaleidoscope;
			break;
		case '2':
			if(bKaleidoscope == true){
				KaleidoscopeSlices+=2;
				if (KaleidoscopeSlices >= 100) KaleidoscopeSlices = 100;
			}
			break;
		case '1':
			if(bKaleidoscope == true){
				KaleidoscopeSlices-=2;
				if (KaleidoscopeSlices < 2) KaleidoscopeSlices = 2;
			}
			break;
	}
}

float Kaleidoscope::getSlices(){
	return KaleidoscopeSlices;
}

string Kaleidoscope::getSlicesAsString(){
	return ofToString(KaleidoscopeSlices);
}

void Kaleidoscope::begin(int resolution){
	if(resolution == 1 ){
		beginA();
	} else if (resolution == 2 ){
		beginB();
	}else if (resolution == 4 ){
		beginC();
	}
}

void Kaleidoscope::end(int resolution){
	if(resolution == 1 ){
		endA();
	} else if (resolution == 2 ){
		endB();
	}else if (resolution == 4 ){
		endC();
	}
}

void Kaleidoscope::beginA(){
	fboKaleidoscopeA.begin();
}

void Kaleidoscope::beginB(){
	fboKaleidoscopeB.begin();
}

void Kaleidoscope::beginC(){
	fboKaleidoscopeC.begin();
}

void Kaleidoscope::endA(){
	fboKaleidoscopeA.end();
}

void Kaleidoscope::endB(){
	fboKaleidoscopeB.end();
}

void Kaleidoscope::endC(){
	fboKaleidoscopeC.end();
}