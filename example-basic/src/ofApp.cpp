#include "ofApp.h"

void ofApp::setup(){
        furry.initfurry();
        cam.setFarClip(100000);
        cam.setNearClip(1.);
        gui.setup();
        gui.add(translateA.set("translate model matrix A",ofVec3f(0,0,600),ofVec3f(-10,-10,-620),ofVec3f(10,10,620)));
        gui.add(translateB.set("translate model matrix B",ofVec3f(5.5,0,600),ofVec3f(-10,-10,-620),ofVec3f(10,10,620)));
        gui.add(color.set("color fur",ofVec3f(0.5,0.9,0.0),ofVec3f(0.f),ofVec3f(1.f)));
        gui.add(alpha.set("alpha color",0.7f,0.f,1.f));
        gui.add(hairLeng.set("fur leng",4.5,-50.f,50.f));
        gui.add(noise.set("noise",true));
}

void ofApp::update(){
       ofSetWindowTitle(ofToString(ofGetFrameRate()));
       furry.update();
}

void ofApp::draw(){
       ofBackground(ofColor(0));
       cam.begin();
           float n = 0;
           if(noise){
                n = ofSignedNoise( ofGetElapsedTimef() );
           }

           furry.begin( cam, translateA, color, hairLeng, alpha, n );
            ofDrawSphere(1.f);
           furry.end();

           furry.begin( cam, translateB, color, hairLeng, alpha, n );
            ofDrawCylinder(25.f, 20.f);
           furry.end();
       cam.end();
       gui.draw();
}

void ofApp::keyPressed(int key){

}
