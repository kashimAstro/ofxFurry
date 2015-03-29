#include "ofApp.h"

void ofApp::setup(){
       kinect.init();
       kinect.open();
       kinect.setRegistration(true);
       kinect.setCameraTiltAngle(0);

	gui.setup();
        gui.add(translate.set("translate model",ofVec3f(-7,0,200),ofVec3f(-200,-200,-820),ofVec3f(200,200,820)));
        gui.add(color.set("color fur",ofVec3f(0.5,0.9,0.0),ofVec3f(0.f),ofVec3f(1.f)));
        gui.add(alpha.set("alpha color",0.7f,0.f,1.f));
        gui.add(hairLeng.set("fur leng",180.f,-550.f,550.f));
        gui.add(noise.set("noise",false));
        gui.add(tassellation.set("no tassellation",true));
        gui.add(distnect.set("distnect",1100,0,3000));
        gui.add(debug.set("debug",true));

       furry.initfurry(12,1000);
       cam.setFarClip(100000);
       cam.setNearClip(1.);
}

void ofApp::update(){
       ofSetWindowTitle(ofToString(ofGetFrameRate()));
       kinect.update();
       if(kinect.isFrameNew()) {
              furry.generatedMesh(kinect,distnect);
       }
}

void ofApp::draw(){
       ofBackgroundGradient(ofColor(0),ofColor(100));

       float n = 0.6f;
       if(noise){
            n = ofSignedNoise( ofGetElapsedTimef() );
       }

       cam.begin();
       cam.setScale(1,-1,1);
       furry.begin(cam, translate, color, hairLeng, alpha, n, tassellation );
            furry.kinectMesh();
       furry.end();
       cam.end();
       if(debug)
	       furry.drawDebug();
       gui.draw();
}

void ofApp::exit(){
	kinect.close();
}

void ofApp::keyPressed(int key){

}
