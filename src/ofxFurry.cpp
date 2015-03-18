#include "ofMain.h"
#include "ofxFurry.h"

void ofxFurry::initfurry(int _pointSkip, int _dist) {
    shader.setGeometryInputType(GL_LINES);
    shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    shader.setGeometryOutputCount((5 + 1) * (4 + 1) * 2);

    /* GLSL */
    string shaderProgGeom = STRINGIFY(
        \n#version 150\n
        \n#define N 9\n
        layout(triangles) in;
        layout(line_strip) out;
        layout(max_vertices = N) out;
        const float NSTEPS = N;
        uniform float hairLeng;
        uniform float time;
        uniform float timex;
        uniform float noTass;
        uniform mat4 projection;
        uniform mat4 modelview;
        uniform vec4 radius=vec4(1.);
        out float stime;
        out vec3 fcolor;
        out vec3 weight;
        void main() {
                  stime=time;
                  vec3 a = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
                  vec3 b = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
                  vec3 center = vec3(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
                  vec3 normal = normalize(cross(b, a));
                  float delta = hairLeng / float(NSTEPS);
                  float t = delta;
                  for (int j = 0; j < NSTEPS; ++j) {
                      fcolor = vec3(t / hairLeng);
                      vec3 position = normal * t + center;
                      position.x += -.2  * timex;
                      position.y += -.9  * t * timex/2.;
                      position.z += -1.8 * t * timex/2.;
                      gl_Position = projection * modelview * vec4(position, 1.0);
                      EmitVertex();
                      if(noTass == 1.0){
                              weight = vec3(1.0, 0.0, 0.0);
                              gl_Position = projection * modelview * gl_in[0].gl_Position * radius;
                              EmitVertex();
                              weight = vec3(0.0, 1.0, 0.0);
                              gl_Position = projection * modelview * gl_in[1].gl_Position * radius;
                              EmitVertex();
                              weight = vec3(0.0, 0.0, 1.0);
                              gl_Position = projection * modelview * gl_in[2].gl_Position * radius;
                              EmitVertex();
                      }
                      t += delta;
                  }
                  EndPrimitive();
        }
    );

    string shaderProgVert = STRINGIFY(
        \n#version 150\n
        in vec3 position;
        in vec3 normal;
        out vec3 gnormal;
        void main() {
          gl_Position = vec4(position, 1.0);
          gnormal = normal;
        }
    );

    string shaderProgFrag = STRINGIFY(
        \n#version 150\n
        uniform float color;
        uniform float alpha;
        uniform vec3 colored;
        in vec3 fcolor;
        in float stime;
        in vec3 weight;
        out vec4 frag_color;
        const float DISCARD_AT = .1;
        const float BACKGROUND_AT = 0.05;
        const float BACKGROUND = 1.0;
        void main() {
                float mindist = min(weight.r, min(weight.g, weight.b));
                if (mindist > DISCARD_AT) discard;
                float intensity = mindist > BACKGROUND_AT ? BACKGROUND : color;
                frag_color += vec4(vec3(intensity), 1.0);
                frag_color = vec4(vec3(fcolor.r*colored.r,fcolor.g*colored.g,fcolor.b*colored.b), alpha);
        }
    );

    /* GLSL */
    shader.setupShaderFromSource(GL_GEOMETRY_SHADER_EXT, shaderProgGeom);
    shader.setupShaderFromSource(GL_VERTEX_SHADER, shaderProgVert);
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgFrag);
    shader.linkProgram();

    printf("Max output vertices: %i\n", shader.getGeometryMaxOutputCount());

    blob.allocate(640,480,OF_IMAGE_GRAYSCALE);
    colorAlpha=255;
    pointSkip=_pointSkip;
    distnect=_dist;
}

void ofxFurry::generatedMesh(ofxKinect &kinect) {
    del.reset();
    unsigned char* pix = new unsigned char[640*480];
    for(int x=0;x<640;x+=1) {
         for(int y=0;y<480;y+=1) {
              float distance = kinect.getDistanceAt(x, y);
              int pIndex = x + y * 640;
              pix[pIndex] = 0;
              if(distance > 100 && distance < distnect) { //
                    pix[pIndex] = 255;
              }
         }
    }
    blob.setFromPixels(pix, 640, 480, OF_IMAGE_GRAYSCALE);
    int numPoints = 0;
    for(int x=0;x<640;x+=pointSkip) {
       for(int y=0;y<480;y+=pointSkip) {
            int pIndex = x + 640 * y;
            if(blob.getPixels()[pIndex]> 0) {
                ofVec3f wc = kinect.getWorldCoordinateAt(x, y);
                wc.x = x - 320.0;
                        wc.y = y - 240.0;
                if(abs(wc.z) > 100 && abs(wc.z ) < 2000) { //
                    wc.z = -wc.z;
                        wc.x += ofSignedNoise(wc.x,wc.z)*noiseAmount;
                                    wc.y += ofSignedNoise(wc.y,wc.z)*noiseAmount;
                    wc.x = ofClamp(wc.x, -320,320);
                    wc.y = ofClamp(wc.y, -240,240);
                    del.addPoint(wc);
                }
                numPoints++;
            }
        }
    }

    if(numPoints >0) del.triangulate();
    for(int i=0;i<del.triangleMesh.getNumVertices();i++) { del.triangleMesh.addColor(ofColor(0,0,0)); }
        for(int i=0;i<del.triangleMesh.getNumIndices()/3;i+=1) {
            ofVec3f v = del.triangleMesh.getVertex(del.triangleMesh.getIndex(i*3));
            v.x = ofClamp(v.x, -319,319);
            v.y = ofClamp(v.y, -239, 239);
            ofColor c = kinect.getColorAt(v.x+320.0, v.y+240.0);
            c.a = colorAlpha;
            del.triangleMesh.setColor(del.triangleMesh.getIndex(i*3),c);
            del.triangleMesh.setColor(del.triangleMesh.getIndex(i*3+1),c);
            del.triangleMesh.setColor(del.triangleMesh.getIndex(i*3+2),c);
        }

    convertedMesh.clear();
    for(int i=0;i<del.triangleMesh.getNumIndices()/3;i+=1) {
        int indx1 = del.triangleMesh.getIndex(i*3);
        ofVec3f p1 = del.triangleMesh.getVertex(indx1);
        int indx2 = del.triangleMesh.getIndex(i*3+1);
        ofVec3f p2 = del.triangleMesh.getVertex(indx2);
        int indx3 = del.triangleMesh.getIndex(i*3+2);
        ofVec3f p3 = del.triangleMesh.getVertex(indx3);
        ofVec3f triangleCenter = (p1+p2+p3)/3.0;
        triangleCenter.x += 320;
        triangleCenter.y += 240;
        triangleCenter.x = floor(ofClamp(triangleCenter.x, 0,640));
        triangleCenter.y = floor(ofClamp(triangleCenter.y, 0,480));
        int pixIndex = triangleCenter.x + triangleCenter.y * 640;
        if(pix[pixIndex] > 0) {
            convertedMesh.addVertex(p1);
            convertedMesh.addColor(del.triangleMesh.getColor(indx1));
            convertedMesh.addVertex(p2);
            convertedMesh.addColor(del.triangleMesh.getColor(indx2));
            convertedMesh.addVertex(p3);
            convertedMesh.addColor(del.triangleMesh.getColor(indx3));
        }
    }
    delete pix;
}

void ofxFurry::kinectMesh(){
    ofTranslate(0, -80, 1100);
    convertedMesh.draw();
}

void ofxFurry::drawDebug() {
    blob.draw(280,20,blob.getWidth()/3,blob.getHeight()/3);
    ofPushMatrix();
    ofTranslate(650,-250,0);
    del.draw();
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(1100,-250,0);
    convertedMesh.drawWireframe();
    ofPopMatrix();
}

void ofxFurry::begin(ofEasyCam cam, ofVec3f color, float hairLeng, float alpha , float noise ,  bool noTassellation){
    glEnable(GL_DEPTH_TEST);
    shader.begin();
        shader.setUniform1f("hairLeng",hairLeng);
    shader.setUniform1f("timex",noise );
    float tass=0.;
    if(noTassellation==true)
          tass = 1.;
        shader.setUniform1f("noTass",tass);
        shader.setUniformMatrix4f("projection",cam.getProjectionMatrix());
        shader.setUniformMatrix4f("modelview", cam.getModelViewMatrix());
        shader.setUniform1f("alpha", alpha);
        shader.setUniform3f("colored", color.x,color.y,color.z);
}

void ofxFurry::end(){
    shader.end();
    glDisable(GL_DEPTH_TEST);
}

/*end*/
