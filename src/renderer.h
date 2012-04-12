#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>

#include "gl.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct vertex2f {
    float x, y, s, t, r, g, b, a, tu;
};

class shader;
class camera;

class renderer {
    public:
        renderer(float w, float h);
        ~renderer();

        void addOpQuad(camera *c,
                       float x, float y, float w, float h,
                       float r, float g, float b, float a);
        void addQuad(GLuint tex, camera *c,
                     float x, float y, float w, float h,
                     float tx, float ty, float tw, float th);
        void addQuad(GLuint tex, float useTex, camera *c,
                     float x, float y, float w, float h,
                     float tx, float ty, float tw, float th,
                     float r, float g, float b, float a);
        void addQuad(GLuint tex, float useTex, camera *c,
                     float x, float y, float w, float h,
                     float tx, float ty, float tw, float th,
                     float r, float g, float b, float a,
                     int flip_x, int flip_y);
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
