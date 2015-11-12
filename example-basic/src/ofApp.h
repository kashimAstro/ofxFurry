#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFurry.h"

class ofApp : public ofBaseApp{
 public:
   ofEasyCam cam;
   ofxFurry furry;
   ofSpherePrimitive sphere;
   ofIcoSpherePrimitive ico;
   ofConePrimitive cone;
   ofCylinderPrimitive cylinder;
   ofBoxPrimitive box;
   bool guiHide;
      
   ofxPanel gui;
   ofParameter<ofVec3f> translate;
   ofParameter<bool> wireframe;
   ofParameter<float> hair;
   ofParameter<float> timer;
   ofParameter<int> resolution;
   ofParameter<ofVec3f> color;
   ofParameter<bool> mod;
   ofParameter<int> types;
   ofParameter<int> pol;
   ofRectangle rectangle;
   
   void exit();
   void setup();
   void resolutionIco(int & val);
   void update();
   void draw();
   void keyPressed(int key);
};
