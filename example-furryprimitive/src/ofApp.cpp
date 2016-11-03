#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(scale.set("scale", ofVec3f(1),ofVec3f(0),ofVec3f(5) ));
	gui.add(changeprimitive.set("changeprimitive", 0,0,10));
	gui.add(wirefill.set("wire or fill",false));
	gui.add(stopNoise.set("stop noise",false));
	gui.add(direction.set("direction", ofVec3f(-3.06,-3.06,1),ofVec3f(-50),ofVec3f(50) ));
	gui.add(rangeorien.set("range orientation", 1,1,25));
	gui.add(rangescale.set("range scale", 1,1,25));
	changeprimitive.addListener(this,&ofApp::changePrimitive);

	ofSpherePrimitive sp;
	sp.set(100,45);
	mesh = sp.getMesh();

	furryprimitive.setup(mesh);
	meshWire = furryprimitive.getMeshResized();

	texture.load("texture.jpg");

	camera.setDistance(ofGetWidth()*6);
	camera.setFarClip(ofGetWidth()*12);
}

void ofApp::changePrimitive(int & v){
	if(v == 0) scale.set(ofVec3f(1,1,1.22));
	if(v == 1) scale.set(ofVec3f(1,1,10));
	if(v == 2) scale.set(ofVec3f(1,1,8));
	if(v == 3) scale.set(ofVec3f(0.32,0.2,10));
	if(v == 4) scale.set(ofVec3f(1,1,1));
	furryprimitive.setPrimitive(v);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	//direction.set(ofVec3f(ofNoise(ofGetElapsedTimef()*0.5),direction->y,direction->z));
        furryprimitive.setTexture(texture);
        furryprimitive.setRangeOrientation(rangeorien);
        furryprimitive.setRangeScale(rangescale);
        furryprimitive.setScale(scale);
        furryprimitive.setOrientation(direction);
        furryprimitive.setNoise(ofNoise(ofGetElapsedTimef()*0.5), stopNoise);
        furryprimitive.update(mesh);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::grey,ofColor::black);
	ofEnableDepthTest();
	camera.begin();
	meshWire.drawWireframe();
	if(wirefill)
		furryprimitive.draw(OF_MESH_FILL);
	else
		furryprimitive.draw(OF_MESH_WIREFRAME);
	camera.end();
	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
        if(key == 'f')
               ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
