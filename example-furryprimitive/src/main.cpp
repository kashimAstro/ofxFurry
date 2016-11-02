#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "ofxFurry.h"

class ofApp : public ofBaseApp{
	public:
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
		ofVec3f arr[47];

		void setup(){
			gui.setup();
			gui.add(scale.set("scale", ofVec3f(1),ofVec3f(0),ofVec3f(5) ));
			gui.add(speedanim.set("speed animation", 0,0,2000 ));
			gui.add(changeprimitive.set("changeprimitive", 0,0,10));
			gui.add(wirefill.set("wire or fill",false));
			gui.add(direction.set("direction", ofVec3f(-3.06,-3.06,1),ofVec3f(-50),ofVec3f(50) ));
			gui.add(rangeorien.set("range orientation", 1,1,25));
			gui.add(rangescale.set("range scale", 1,1,25));
			changeprimitive.addListener(this,&ofApp::changePrimitive);

			model.loadModel("model.dae",true);
		        model.setRotation(180,180,1,0,0);
                        model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
                        model.playAllAnimations();
                        model.setPausedForAllAnimations(true);
			mesh = model.getMesh(0);

			furryprimitive.setup(mesh);
			ofImage imf;
			imf.load("texture.jpg");
                        texture.push_back(imf);
			imf.load("texture1.jpg");
                        texture.push_back(imf);
			imf.load("texture2.jpg");
                        texture.push_back(imf);
			pcounter=0;

		        camera.setDistance(ofGetWidth()*6);
		        camera.setFarClip(ofGetWidth()*12);
		}

		void changePrimitive(int & v){
			if(v == 0) scale.set(ofVec3f(1,1,1.22));
			if(v == 1) scale.set(ofVec3f(1,1,10));
			if(v == 2) scale.set(ofVec3f(1,1,8));
			if(v == 3) scale.set(ofVec3f(0.32,0.2,10));
			if(v == 4) scale.set(ofVec3f(1,1,1));

			furryprimitive.primitive(v);
		}

		void update(){
			ofSetWindowTitle(ofToString(ofGetFrameRate()));

			furryprimitive.setTexture(texture[pcounter]);
			furryprimitive.setRangeOrientation(rangeorien);
			furryprimitive.setRangeScale(rangescale);
			furryprimitive.setScale(scale);
			furryprimitive.setOrientation(direction);

			model.update();
                        animationPosition = ofMap(acounter,0,speedanim,0.0,1.0);
                        acounter++;
                        if(acounter>speedanim) acounter=0;
                        model.setPositionForAllAnimations(animationPosition);
                        mesh = model.getCurrentAnimatedMesh(0);
                        furryprimitive.update(mesh);
		}

		void draw(){
		 	ofBackgroundGradient(ofColor::cyan,ofColor::black);

                        ofEnableDepthTest();
		      	camera.begin();
			furryprimitive.draw(wirefill);
			camera.end();
                        ofDisableDepthTest();

			gui.draw();
		}

		void keyPressed(int key){
			if(key == ' '){
				pcounter++;
				if(pcounter>=texture.size())
					pcounter=0;
			}
			if(key == 'f')
				ofToggleFullscreen();
		}
};

int main()
{
	ofGLWindowSettings settings;
	settings.setGLVersion(3,2);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
