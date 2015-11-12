#include "ofMain.h"
#include "ofApp.h"

int main( ){
   ofGLWindowSettings settings;
   settings.setGLVersion(3, 2);
   settings.width = 1024;
   settings.height = 768;
   ofCreateWindow(settings);
   if(!ofGLCheckExtension("GL_ARB_geometry_shader4") && !ofGLCheckExtension("GL_EXT_geometry_shader4") && !ofIsGLProgrammableRenderer()){
      ofLogFatalError() << "geometry shaders not supported on this graphics card";
      return 1;
   }
   ofRunApp( new ofApp());
}
