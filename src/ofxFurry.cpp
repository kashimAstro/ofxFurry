#include "ofxFurry.h"

void ofxFurry::exit(){
//	tkinect.exit();
}

void ofxFurry::setupKinect(int _dist1, int _dist2){
	colors    = ofVec3f(0.2,0.3,0.9);
	translate = ofVec3f(0,0,0);
	types     = 1;
	time      = ofGetElapsedTimef();
	len       = 10.0f;
	NOTex     = 0;
	ofDisableArbTex();
	shader.setGeometryInputType(GL_POINTS);
	shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	shader.setGeometryOutputCount((5 + 1) * (4 + 1) * 2);
        //shader.load("shaders/render.vert","shaders/render.frag","shaders/render.geom");

	vector<string> str_shader = glslContext.getFurry();
        ofLog()<<"SIZE-SHADER::"<<str_shader.size();
        /* GLSL */
        shader.setupShaderFromSource(GL_GEOMETRY_SHADER_EXT, str_shader[2]);
        shader.setupShaderFromSource(GL_VERTEX_SHADER,       str_shader[0]);
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER,     str_shader[1]);
        shader.linkProgram();

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
	colors    = ofVec3f(0.2,0.3,0.9);
	translate = ofVec3f(0,0,0);
	types     = 1;
	time      = ofGetElapsedTimef();
	len       = 10.0f;
	NOTex     = 0;

	ofDisableArbTex();
	shader.setGeometryInputType(GL_POINTS);
	shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	shader.setGeometryOutputCount((5 + 1) * (4 + 1) * 2);
//	shader.load("shaders/render.vert","shaders/render.frag","shaders/render.geom");
	vector<string> str_shader = glslContext.getFurry();
        ofLog()<<"SIZE-SHADER::"<<str_shader.size();
        /* GLSL */
        shader.setupShaderFromSource(GL_GEOMETRY_SHADER_EXT, str_shader[2]);
        shader.setupShaderFromSource(GL_VERTEX_SHADER,       str_shader[0]);
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER,     str_shader[1]);
        shader.linkProgram();


}
//#endif
void ofxFurry::setExternalMatrix(ofMatrix4x4 mat, bool check){
	Mmat = mat;
	Mcheck = check;
}

void ofxFurry::setStripLength(float _len){
	len = _len;	
}

void ofxFurry::setTranslate(ofVec3f _tr){
	translate = _tr;		
}

void ofxFurry::setMoveTime(float _time){
	time = _time;
}

void ofxFurry::setColors(ofVec3f _col){
	colors = _col;	
}

void ofxFurry::setTypes(int _ty){
	types = _ty;
}

void ofxFurry::setTexture(ofTexture _tex){
	tex = _tex;
	NOTex = 1;
}

void ofxFurry::begin(ofEasyCam cam){//float hairLeng, ofVec3f translate, float time, ofVec3f color,int types){
	ofMatrix4x4 camdist;
	camdist.preMultTranslate(translate);
	shader.begin();
	if(Mcheck)
		shader.setUniformMatrix4f("viewMatrix", Mmat*camdist);
	else
		shader.setUniformMatrix4f("viewMatrix",cam.getModelViewProjectionMatrix());
	shader.setUniformMatrix4f("projectionMatrix",cam.getProjectionMatrix());
	shader.setUniformMatrix4f("modelMatrix", cam.getModelViewMatrix()*camdist);
	shader.setUniform1f("time",time);
	shader.setUniform1f("hairLeng",len);
	shader.setUniform3f("colors",colors.x,colors.y,colors.z);
	shader.setUniform1i("polygonTypes",types);

	shader.setUniform1i("NOTex",NOTex);
	if(NOTex == 1)
	{
		shader.setUniformTexture("texture",tex,0);
	}
	/*if(rectangle.inside(ofGetMouseX(),ofGetMouseY())){
	 ofLog()<<"inside sphere!";
	 shader.setUniform2f("collisionCoord",ofGetMouseX(),ofGetMouseY());
	}*/
}

void ofxFurry::end(){
	shader.end();
}
