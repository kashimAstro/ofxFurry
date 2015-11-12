#include "ofxFurry.h"

      
void ofxFurry::exit(){
//	tkinect.exit();
}

void ofxFurry::setupKinect(int _dist1, int _dist2){
	ofDisableArbTex();
	shader.setGeometryInputType(GL_POINTS);
	shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	shader.setGeometryOutputCount((5 + 1) * (4 + 1) * 2);
	shader.load("shaders/render.vert","shaders/render.frag","shaders/render.geom");
	tkinect.init();
	tkinect.setDistance(dist1);
	tkinect.setDistance2(dist2);
	dist1=_dist1;
	dist2=_dist2;
}

void ofxFurry::setSteps(int steps){
	tkinect.setSteps(steps);
}

void ofxFurry::setDistance1(int dist){
	tkinect.setDistance(dist);
}

void ofxFurry::setDistance2(int dist2){
	tkinect.setDistance2(dist2);
}

void ofxFurry::kinectMesh(int i){
	tkinect.kinectMesh(i);
}

void ofxFurry::update(ofxKinect * kinect){
	tkinect.update(kinect);
}
//#else
void ofxFurry::setup(){
	ofDisableArbTex();
	shader.setGeometryInputType(GL_POINTS);
	shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	shader.setGeometryOutputCount((5 + 1) * (4 + 1) * 2);
	shader.load("shaders/render.vert","shaders/render.frag","shaders/render.geom");
}
//#endif

void ofxFurry::begin(ofEasyCam cam, float hairLeng, ofVec3f translate, float time, ofVec3f color,int types){
	ofMatrix4x4 camdist;
	camdist.preMultTranslate(translate);
	shader.begin();
	shader.setUniformMatrix4f("viewMatrix",cam.getModelViewProjectionMatrix());
	shader.setUniformMatrix4f("projectionMatrix",cam.getProjectionMatrix());
	shader.setUniformMatrix4f("modelMatrix", cam.getModelViewMatrix()*camdist);
	shader.setUniform1f("time",time);
	shader.setUniform1f("hairLeng",hairLeng);
	shader.setUniform3f("colors",color.x,color.y,color.z);
	shader.setUniform1i("polygonTypes",types);
	/*if(rectangle.inside(ofGetMouseX(),ofGetMouseY())){
	 ofLog()<<"inside sphere!";
	 shader.setUniform2f("collisionCoord",ofGetMouseX(),ofGetMouseY());
	}*/
}

void ofxFurry::end(){
	shader.end();
}
