#include "ofApp.h"

void ofApp::exit(){

}

void ofApp::setup(){
	furry.setup();
 	sphere.set(100,8);
	ico.set(100,4);
	cone.set(100,100);
	cone.setResolution(20,20,20);
	cylinder.set(90,200);
	cylinder.setResolution(25,25,25);
	box.set(100);
	box.setResolution(20);

	gui.setup();
	gui.add(translate.set("translate",ofVec3f(0),ofVec3f(-1000),ofVec3f(1000)));
	gui.add(wireframe.set("wireframe",false));
	gui.add(mod.set("mode",true));
	gui.add(hair.set("hairLeng",0.f,0.f,1.f));
	gui.add(timer.set("time",0.f,0.f,.10f));
	gui.add(resolution.set("resolution",4,1,20));
	gui.add(color.set("colors",ofVec3f(0.3f,0.7f,1.0f),ofVec3f(0.f),ofVec3f(1.f)));
	gui.add(types.set("select primitive",0,0,5));
	gui.add(pol.set("select ofPrimitive",1,1,6));

	resolution.addListener(this,&ofApp::resolutionIco);
	cam.setFarClip(100000);
	cam.setNearClip(.1);
	cam.setVFlip(false);
}

void ofApp::resolutionIco(int & val){
	sphere.set(100,resolution);
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void ofApp::draw(){
	ofBackgroundGradient(ofColor(155),ofColor(0));
	cam.begin();
	ofEnableDepthTest(); 
	if(wireframe){
	 if(mod){
	    if(pol == 1){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       sphere.draw();
	       furry.end();
	       }
	    if(pol == 2){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       ico.draw();
	       furry.end();
	       }
	    if(pol == 3){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       cone.draw();
	       furry.end();
	       }
	    if(pol == 4){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       cylinder.draw();
	       furry.end();
	       }
  	  if(pol == 5){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       box.draw();
	       furry.end();
	       }
	 }
	}else{
	 if(mod){
	    if(pol == 1){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       sphere.drawWireframe();
	       furry.end();
	       }
	    if(pol == 2){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       ico.drawWireframe();
	       furry.end();
	       }
	    if(pol == 3){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       cone.drawWireframe();
	       furry.end();
  	     }
	    if(pol == 4){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       cylinder.drawWireframe();
	       furry.end();
	       }
	    if(pol == 5){
	       furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
	       box.drawWireframe();
	       furry.end();
	       }
	 }
	}    
	ofDisableDepthTest();
	cam.end();
	
	if(guiHide) gui.draw();
}

void ofApp::keyPressed(int key){
	if(key == 'g') guiHide=!guiHide;
	if(key == 'f') ofToggleFullscreen();
}
