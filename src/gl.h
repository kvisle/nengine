/*
    Includes different GL-headers based on different platforms.
*/
#ifndef __crosslib_gl_h__
#define __crosslib_gl_h__

 #ifdef __ANDROID__

  #include <GLES2/gl2.h>
  #include <GLES2/gl2ext.h>

 #elif IPHONE

  #include <OpenGLES/ES2/gl.h>
  #include <OpenGLES/ES2/glext.h>

 #elif __native_client__

  #include <GLES2/gl2.h>
//  #include <GLES2/gl2ext.h>
//  #include <ppapi/c/ppb_opengles.h>

 #else

  #define USE_GLEW
  #include <GL/glew.h>
  #include <GL/gl.h>

 #endif

#endif
