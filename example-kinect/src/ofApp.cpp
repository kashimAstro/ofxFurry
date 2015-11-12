#include "ofApp.h"

   void ofApp::exit(){

   }
   
   void ofApp::setup(){
      ofSetLogLevel(OF_LOG_VERBOSE);
      kinect.setRegistration(true);
      kinect.init();
      kinect.open();
      if(kinect.isConnected()) {
           ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
           ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
           ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
           ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
      }

      furry.setupKinect(1100,1200);
         

      gui.setup();
      gui.add(translate.set("translate",ofVec3f(0),ofVec3f(-1000),ofVec3f(1000)));
      gui.add(wireframe.set("wireframe",false));
      gui.add(mod.set("mode",true));
      gui.add(hair.set("hairLeng",0.f,0.f,1.f));
      gui.add(timer.set("time",0.f,0.f,.10f));
      gui.add(color.set("colors",ofVec3f(0.3f,0.7f,1.0f),ofVec3f(0.f),ofVec3f(1.f)));
      gui.add(types.set("select primitive",0,0,5));
      gui.add(dist.set("dist kinect",1100,0,3000));
      gui.add(dist2.set("dist2 kinect",1200,0,3000));
      gui.add(steps.set("steps",2,2,10));
      gui.add(pol.set("select ofPrimitive",1,1,6));

      cam.setFarClip(100000);
      cam.setNearClip(.1);
      cam.setVFlip(false);
   }
   
   void ofApp::update(){
      ofSetWindowTitle(ofToString(ofGetFrameRate()));
      furry.setSteps(steps);
      furry.setDistance1(dist);
      furry.setDistance2(dist2);

      kinect.update();
      if(kinect.isFrameNew()){
         furry.update(&kinect);
      }
   }

   void ofApp::draw(){
      ofBackgroundGradient(ofColor(155),ofColor(0));
      cam.begin();
      ofEnableDepthTest();
          
      if(wireframe){
            furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
            furry.kinectMesh(0);
            furry.end();
      }else{
            furry.begin(cam,hair,translate,ofGetElapsedTimef()*timer,color,types);
            furry.kinectMesh(1);
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
