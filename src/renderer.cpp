#include <iostream>

#ifdef TARGET_SDL
#include <SDL.h>
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"
#include "renderer.h"
#include "resource.h"
#include "camera.h"

renderer::renderer(float w, float h)
{
#ifdef USE_GLEW
    glewInit();
#endif

    this->w = w;
    this->h = h;

    resource vertex("vertex.glsl"), fragment("fragment.glsl");
    s = new shader(&vertex, &fragment);
    s->use();

    ortho = glm::ortho<float>(0.0, w, h, 0.0, -10.0,  10.0);

    glGenBuffers (1, &vbo);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

renderer::~renderer()
{
    glDeleteBuffers (1, &vbo);
}

void
renderer::addOpQuad(camera *c,
                    float x, float y, float w, float h,
                    float r, float g, float b, float a)
{
    addQuad(tex, 0.0, c, x, y, w, h, 0.0, 0.0, 0.0, 0.0, r, g, b, a, 0, 0);
}

void
renderer::addQuad(GLuint qtex, camera *c,
                   float x, float y, float w, float h,
                   float tx, float ty, float tw, float th)
{
    addQuad(qtex, 1.0, c, x, y, w, h, tx, ty, tw, th, 1, 1, 1, 1, 0, 0);
}

void
renderer::addQuad(GLuint qtex, float usetex, camera *c,
                   float x, float y, float w, float h,
                   float tx, float ty, float tw, float th,
                   float r, float g, float b, float a)
{
    addQuad(qtex, usetex, c, x, y, w, h, tx, ty, tw, th, r, g, b, a, 0, 0);
}

void
renderer::addQuad(GLuint qtex, float usetex, camera *c,
                   float x, float y, float w, float h, 
                   float tx, float ty, float tw, float th,
                   float r, float g, float b, float a,
                   int flip_x, int flip_y)
{
    if ( qtex != tex )
    {
        flush_queue();
        tex = qtex;
    }

    if ( c )
    {
        x -= c->x;
        y -= c->y;
    }

    vertex2f v;

    // Colors
    v.r = r;
    v.g = g;
    v.b = b;
    v.a = a;

    // Using texture?
    v.tu = usetex;

    // Topleft
    v.x = x;
    v.y = y;
    v.s = flip_x ? tx+tw : tx;
    v.t = flip_y ? ty+th : ty;
    queue.push_back(v);

    // Topright
    v.x = x+w;
    v.y = y;
    v.s = flip_x ? tx : tx+tw;
    v.t = flip_y ? ty+th : ty;
    queue.push_back(v);

    // Bottomleft
    v.x = x;
    v.y = y+h;
    v.s = flip_x ? tx+tw : tx;
    v.t = flip_y ? ty : ty+th;
    queue.push_back(v);

    // Topright
    v.x = x+w;
    v.y = y;
    v.s = flip_x ? tx : tx+tw;
    v.t = flip_y ? ty+th : ty;
    queue.push_back(v);

    // Bottomleft
    v.x = x;
    v.y = y+h;
    v.s = flip_x ? tx+tw : tx;
    v.t = flip_y ? ty : ty+th;
    queue.push_back(v);

    // Bottomright
    v.x = x+w;
    v.y = y+h;
    v.s = flip_x ? tx : tx+tw;
    v.t = flip_y ? ty : ty+th;
    queue.push_back(v);
}

void
renderer::flush_queue()
{
    if ( queue.empty() )
        return;

    s->use();

    glBindBuffer(GL_ARRAY_BUFFER, s->uniformLocation("u_projectionMatrix"));
    glUniformMatrix4fv(s->uniformLocation("u_projectionMatrix"), 1, GL_FALSE, glm::value_ptr(ortho));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(s->uniformLocation("mytex"), 0);

    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, queue.size() * sizeof(vertex2f), &queue[0], GL_STATIC_DRAW);

    glVertexAttribPointer (s->attribLocation("a_position"), 2, GL_FLOAT, GL_FALSE, sizeof(vertex2f), 0);
    glEnableVertexAttribArray (s->attribLocation("a_position"));

    glVertexAttribPointer (s->attribLocation("aTextureCoord"), 2, GL_FLOAT, GL_FALSE, sizeof(vertex2f), (void *) (2 * sizeof (float)));
    glEnableVertexAttribArray (s->attribLocation("aTextureCoord"));

    glVertexAttribPointer (s->attribLocation("aColor"), 4, GL_FLOAT, GL_FALSE, sizeof(vertex2f), (void *) (4 * sizeof (float)));
    glEnableVertexAttribArray (s->attribLocation("aColor"));

    glVertexAttribPointer (s->attribLocation("useTex"), 1, GL_FLOAT, GL_FALSE, sizeof(vertex2f), (void *) (8 * sizeof (float)));
    glEnableVertexAttribArray (s->attribLocation("useTex"));


    glDrawArrays (GL_TRIANGLES, 0, queue.size());

    queue.clear();
}

void
renderer::swap()
{
    if ( !queue.empty() )
        flush_queue();

#ifdef TARGET_SDL
    SDL_GL_SwapBuffers();
#endif
#ifdef __native_client__

#endif
}

void
renderer::clear()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
