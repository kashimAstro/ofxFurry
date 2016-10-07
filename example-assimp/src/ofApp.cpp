#include "ofApp.h"

int counter = 0;
float animationPosition;

void ofApp::exit(){

}

void ofApp::setup(){
	furry.setup();
	model.loadModel("models/northern_soul_spin_combo.dae",true);
	//model.setPosition(ofGetWidth()/2, (float)ofGetHeight()/2 , 0);
	model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	model.playAllAnimations();
        model.setPausedForAllAnimations(true);

	mesh = model.getMesh(0);

	gui.setup();
	gui.add(translate.set("translate",ofVec3f(0,0,0),ofVec3f(-1000),ofVec3f(1000)));
	gui.add(wireframe.set("wireframe",false));
	gui.add(hair.set("hairLeng",0.f,0.f,1.f));
	gui.add(timer.set("time",0.f,0.f,.10f));
	gui.add(color.set("colors",ofVec3f(0.3f,0.7f,1.0f),ofVec3f(0.f),ofVec3f(1.f)));
	gui.add(types.set("select primitive",0,0,5));
	gui.add(speedanim.set("speed animation",1000,0,5000));

	cam.setFarClip(100000);
	cam.setNearClip(.1);
	cam.setVFlip(false);
	texture.load("texture.jpg");

	ofDisableArbTex();
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	model.update();
        animationPosition = ofMap(counter,0,speedanim,0.0,1.0);
        counter++;
        if(counter>speedanim)
          counter=0;
        model.setPositionForAllAnimations(animationPosition);
        mesh = model.getCurrentAnimatedMesh(0);

	furry.setStripLength(hair);
	furry.setTranslate(translate);
        furry.setMoveTime(ofGetElapsedTimef()*timer);
        furry.setColors(color);
        furry.setTypes(types);
}

void ofApp::draw(){
	ofBackgroundGradient(ofColor(155),ofColor(0));
	cam.begin();
	cam.setScale(1,-1,1);
	ofEnableDepthTest(); 

	furry.setTexture(texture.getTexture());
	furry.setExternalMatrix(model.getModelMatrix(),true);// this important !
	if(wireframe){
	       furry.begin(cam);
	       mesh.drawWireframe();
	       furry.end();
	}else{
	       furry.begin(cam);
	       mesh.drawFaces();
	       furry.end();
	} 
	ofDisableDepthTest();
	cam.end();
	
	if(guiHide) gui.draw();
}

void ofApp::keyPressed(int key){
	if(key == 'g') guiHide=!guiHide;
	if(key == 'f') ofToggleFullscreen();
}
