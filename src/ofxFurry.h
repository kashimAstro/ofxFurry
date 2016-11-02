#pragma once
#include "ofMain.h"
#include "type.h"
#include "glsl.h"
//#ifdef KINECT_MODE
//      #pragma message("KINECT_MODE=ACTIVED")
	#include "ofxKinect.h"
	#include "THKinect.h"
//#endif
#include "furryPrimitive.h"

class ofxFurry {
 public:
   ofShader shader;
   THKinect tkinect;
   glsl glslContext;
   ofMatrix4x4 Mmat;
   bool Mcheck;
   int dist1,dist2;
   void setSteps(int steps);
   void setDistance1(int dist);
   void setDistance2(int dist2);
   void kinectMesh(int i);   
   void setupKinect(int _dist1=1100, int _dist2=1200);
   void update(ofxKinect *kinect);

   void setStripLength(float _len);
   void setTranslate(ofVec3f _tr);
   void setMoveTime(float _time);
   void setColors(ofVec3f _col);
   void setTypes(int _ty);
   void setTexture(ofTexture _tex);


   ofVec3f colors;
   ofVec3f translate;
   int types;
   float time;
   float len;
   ofTexture tex;
   int NOTex;

   void setup();
   void setExternalMatrix(ofMatrix4x4 mat,bool check);
   void exit();
   void begin(ofEasyCam cam);
   void end();
};
