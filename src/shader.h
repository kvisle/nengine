#ifndef __SHADER_H__
#define __SHADER_H__

#include "gl.h"

class resource;

class shader {

    public:

        shader(resource *vertex, resource *fragment);
        ~shader();

        void use();
        int success();

        int uniformLocation(const char *name);
        int attribLocation(const char *name);

    private:

        GLuint compile(resource *program, GLenum st);
        GLuint link(GLuint vid, GLuint fid);

        GLuint fid, vid, program;

};

#endif /* __SHADER_H__ */
