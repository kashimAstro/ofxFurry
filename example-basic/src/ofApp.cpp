#include "ofApp.h"

void ofApp::setup(){
        furry.initfurry();
        cam.setFarClip(100000);
        cam.setNearClip(1.);
        gui.setup();
        gui.add(translateA.set("translate model matrix A",ofVec3f(10,0,600),ofVec3f(-10,-10,-620),ofVec3f(10,10,620)));
        gui.add(translateB.set("translate model matrix B",ofVec3f(-10,0,600),ofVec3f(-10,-10,-620),ofVec3f(10,10,620)));
        gui.add(translateC.set("translate model matrix C",ofVec3f(-7,0,200),ofVec3f(-100,-100,-620),ofVec3f(100,100,620)));
        gui.add(color.set("color fur",ofVec3f(0.5,0.9,0.0),ofVec3f(0.f),ofVec3f(1.f)));
        gui.add(alpha.set("alpha color",0.7f,0.f,1.f));
        gui.add(hairLeng.set("fur leng",4.5,-150.f,150.f));
        gui.add(noise.set("noise",true));
        gui.add(tassellation.set("no tassellation",true));
        model.loadModel("model.obj",true);
        w=ofGetScreenWidth();
        h=ofGetScreenHeight();
}

void ofApp::update(){
       ofSetWindowTitle(ofToString(ofGetFrameRate()));
       furry.update();
}

void ofApp::draw(){
       ofBackgroundGradient(ofColor(150),ofColor(25));
       cam.begin();
           float n = 0;
           if(noise){
                n = ofSignedNoise( ofGetElapsedTimef() );
           }

           furry.begin( cam, translateA, color, hairLeng, alpha, n, tassellation );
            ofDrawSphere(1.f);
           furry.end();

           furry.begin( cam, translateB, color, hairLeng, alpha, n, tassellation );
            ofDrawCylinder(5.f, 10.f);
           furry.end();

           furry.begin( cam, translateC, color, hairLeng, alpha, n, tassellation );
            model.drawFaces();
           furry.end();

       cam.end();
       gui.draw();
}

void ofApp::keyPressed(int key){

}
