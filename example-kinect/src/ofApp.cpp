#include "ofApp.h"

void ofApp::setup(){
       kinect.init();
       kinect.open();
       kinect.setRegistration(true);
       kinect.setCameraTiltAngle(0);

       furry.initfurry(6,1000);
       cam.setFarClip(100000);
       cam.setNearClip(1.);
}

void ofApp::update(){
       ofSetWindowTitle(ofToString(ofGetFrameRate()));
       kinect.update();
       if(kinect.isFrameNew()) {
              furry.generatedMesh(kinect);
       }
}

void ofApp::draw(){
       ofBackground(ofColor(0));

       cam.begin();
       cam.setScale(1,-1,1);
       furry.begin( cam, ofVec3f(0.,0.65,1.), 85.5, 0.6f, 0.f );
            furry.kinectMesh();
       furry.end();
       cam.end();

       furry.drawDebug();
}

void ofApp::exit(){
	kinect.close();
}

void ofApp::keyPressed(int key){

}
