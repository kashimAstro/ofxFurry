#include "ofMain.h"

#define STRINGIFY(A) #A

class FurryPrimitive 
{
	public:
		void setRangeOrientation(int _r);
		void setRangeScale(int _r);
		void setScale(ofVec3f _s);
		void setOrientation(ofVec3f _d);
		void setTexture(ofImage _i);
		void setNoise(float _t, bool _n);
		void setCustomMesh(ofMesh _m);
		void setPrimitive(int prim);
		void setup(ofMesh _m);
		void setVecDirection(vector<ofVec3f> _d);
		void update(ofMesh _m);
		void draw(ofPolyRenderMode type);

		int getNumVert();
		ofMesh getMeshResized();

	private:
		ofTexture tex;
                ofBufferObject buffer;
                vector<ofMatrix4x4> matrices;
                ofVboMesh mesh,xmesh;
                ofShader shader;
		ofImage texture;
		ofVec3f arr[47];
		ofVec3f direction;
		int rangeorien;
		int rangescale;
		ofVec3f scale;
		bool noise,CustomMesh;
		float valueNoise;
		int resizedMesh;
		vector<ofVec3f> _dir;

		ofMesh ribbon(vector<ofVec3f> points, float _thickness);
};
