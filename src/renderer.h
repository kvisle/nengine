#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct vertex2f {
    float x, y, s, t;
};

class shader;

class renderer {
    public:
        renderer(float w, float h);
        ~renderer();

        void addQuad(GLuint tex, 
                     float x, float y, float w, float h,
                     float tx, float ty, float tw, float th);
        void flush_queue();
        void swap();
        void clear();

        float w, h;

    private:

        std::vector<vertex2f> queue;
        GLuint tex, vbo;

        shader * s;
        glm::mat4 ortho;
};

#endif /* __RENDERER_H__ */
