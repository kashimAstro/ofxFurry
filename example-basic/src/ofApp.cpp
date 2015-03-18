#include "ofApp.h"

void ofApp::setup(){
       furry.initfurry();
       cam.setFarClip(100000);
       cam.setNearClip(1.);
}

void ofApp::update(){
       ofSetWindowTitle(ofToString(ofGetFrameRate()));
       furry.update();
}

void ofApp::draw(){
       ofBackground(ofColor(0));
       cam.begin();
           furry.begin( cam, ofVec3f(1.,0.,0.), 4.2, 0.7f, ofSignedNoise( ofGetElapsedTimef() ) );
            ofDrawSphere(1.f);
           furry.end();
       cam.end();
}

void ofApp::keyPressed(int key){

}
