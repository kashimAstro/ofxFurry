#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFurry.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{
 public:
   ofEasyCam cam;
   ofxFurry furry;
   ofxAssimpModelLoader model;
   ofMesh mesh;
   bool guiHide;
      
   ofxPanel gui;
   ofParameter<ofVec3f> translate;
   ofParameter<bool> wireframe;
   ofParameter<float> hair;
   ofParameter<float> timer;
   ofParameter<ofVec3f> color;
   ofParameter<int> types;
   ofParameter<int> pol;
   ofRectangle rectangle;
   
   void exit();
   void setup();
   void update();
   void draw();
   void keyPressed(int key);
};
