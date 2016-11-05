#include "ofApp.h"

vector<ofVec3f> dii;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);
	gui.setup();
	gui.add(scale.set("scale", ofVec3f(1.5,25,1.5),ofVec3f(0),ofVec3f(50) ));
	gui.add(changeprimitive.set("changeprimitive", 3,0,10));
	gui.add(wirefill.set("wire or fill",true));
	changeprimitive.addListener(this,&ofApp::changePrimitive);

	ofSpherePrimitive sp;
	sp.set(100,45);
	mesh = sp.getMesh();
	furryprimitive.setup(mesh);
	meshWire = furryprimitive.getMeshResized();
	texture.load("texture5.jpg");
	for(int i = 0; i < furryprimitive.getNumVert(); i++){
		dii.push_back(ofVec3f(ofSignedNoise(ofGetElapsedTimef()*5.f)+ofRandom(-5,5)));
	}
	furryprimitive.setVecDirection(dii);
        furryprimitive.setTexture(texture);
	furryprimitive.setPrimitive(OFX_BUFFER_TYPE_D);

	camera.setDistance(ofGetWidth()*6);
	camera.setFarClip(ofGetWidth()*12);
        ofEnableNormalizedTexCoords();
}

void ofApp::changePrimitive(int & v){
	furryprimitive.setPrimitive(v);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
        furryprimitive.setScale(scale);
        furryprimitive.update(mesh);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::grey,ofColor::black);
	ofEnableDepthTest();
	camera.begin();
	if(wirefill)
	{
		texture.bind();
		meshWire.draw();
		texture.unbind();
		furryprimitive.draw(OF_MESH_FILL);
	}
	else{
		texture.bind();
		meshWire.drawWireframe();
		texture.unbind();
		furryprimitive.draw(OF_MESH_WIREFRAME);
	}
	camera.end();
	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
        if(key == 'f')
               ofToggleFullscreen();
	if(key == ' '){
		dii.clear();
		for(int i = 0; i < furryprimitive.getNumVert(); i++){
			dii.push_back(ofVec3f(ofSignedNoise(ofGetElapsedTimef()*5.f)+ofRandom(-5,5)));
		}
		furryprimitive.setVecDirection(dii);
	}
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
