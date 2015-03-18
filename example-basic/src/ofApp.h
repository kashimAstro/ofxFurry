#include "ofMain.h"
#include "ofxFurry.h"

class ofApp : public ofBaseApp{
        public:

        ofxFurry furry;
        ofEasyCam cam;

        void setup();
        void update();
        void draw();
        void keyPressed(int key);
};
