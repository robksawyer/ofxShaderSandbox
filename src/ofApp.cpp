#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Global Settings
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	show_fps = true;
	bHideCursor = false;
	
	// FBO Kaleidoscope
	kScope.setup( shaderBox.resolVert, shaderBox.resolHoriz, 12);
	
	shaderBox.setup();
	
	passes = 1;

}

//--------------------------------------------------------------
void ofApp::update(){
	shaderBox.update(passes);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0,0,0);
	ofSetColor(255,255,255);
	
	
	kScope.begin( shaderBox.getResolution() );
	
	shaderBox.draw();
	
	kScope.end( shaderBox.getResolution() );
	
	
	if (show_fps == true){
		ofFill();
		ofSetColor(0,0,10,200);
		ofDrawRectangle(0,0,300,190);
		ofSetColor(180,180,180);
		ofNoFill();
		ofDrawRectangle(0,0,300,190);
		ofSetColor(255,255,255);
		ofDrawBitmapString("FPS: " + ofToString( ofGetFrameRate(), 2), 10, 1*15);
		ofDrawBitmapString("Some shader use your mouse movement!", 10, 2*15);
		ofDrawBitmapString("'f' Toggle Fullscreen.", 10, 3*15);
		ofDrawBitmapString("'s' Toggle Show INFO.", 10, 4*15);
		ofDrawBitmapString("'r' Change Resolution Divider: " + ofToString( shaderBox.getResolution() ), 10, 5 * 15);
		ofDrawBitmapString("'h' Toggle hide Cursor.", 10, 12 * 15);
		
		//Draw Kaleidoscope Controls
		kScope.drawControls();
		//Draw ShaderBox Controls
		shaderBox.drawControls();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key){
		case 's':
			if (show_fps == true){
				show_fps = false;
			} else{
				show_fps = true;
			}
			break;
		case 'f':
			ofToggleFullscreen();
			break;
		case 'h':
			if (bHideCursor == true){
				bHideCursor = false;
				ofShowCursor();
			} else{
				bHideCursor = true;
				ofHideCursor();
			}
			break;
	}
	
	kScope.keyPressed(key);
	shaderBox.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
