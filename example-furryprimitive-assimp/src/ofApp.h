#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "ofxFurry.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		FurryPrimitive furryprimitive;
                ofVboMesh mesh;
                ofEasyCam camera;
                ofxAssimpModelLoader model;
                vector<ofImage> texture;
                float animationPosition;
                int acounter,pcounter;
                ofxPanel gui;
                ofParameter<ofVec3f> scale;
                ofParameter<float> speedanim;
                ofParameter<int>   changeprimitive;
                ofParameter<bool>  wirefill;
                ofParameter<ofVec3f> direction;
                ofParameter<int> rangeorien;
                ofParameter<int> rangescale;
                void changePrimitive(int & v);
};
