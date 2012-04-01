#include <iostream>

#include <SDL.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"
#include "renderer.h"
#include "resource.h"

renderer::renderer(float w, float h)
{
    glewInit();

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
renderer::addQuad(GLuint qtex, 
                   float x, float y, float w, float h, 
                   float tx, float ty, float tw, float th)
{
    if ( qtex != tex )
    {
        flush_queue();
        tex = qtex;
    }

    vertex2f v;
    
    // Topleft
    v.x = x;
    v.y = y;
    v.s = tx;
    v.t = ty;
    queue.push_back(v);

    // Topright
    v.x = x+w;
    v.y = y;
    v.s = tx+tw;
    v.t = ty;
    queue.push_back(v);

    // Bottomleft
    v.x = x;
    v.y = y+h;
    v.s = tx;
    v.t = ty+th;
    queue.push_back(v);

    // Topright
    v.x = x+w;
    v.y = y;
    v.s = tx+tw;
    v.t = ty;
    queue.push_back(v);

    // Bottomleft
    v.x = x;
    v.y = y+h;
    v.s = tx;
    v.t = ty+th;
    queue.push_back(v);

    // Bottomright
    v.x = x+w;
    v.y = y+h;
    v.s = tx+tw;
    v.t = ty+th;
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

    glDrawArrays (GL_TRIANGLES, 0, queue.size());

    queue.clear();
}

void
renderer::swap()
{
    if ( !queue.empty() )
        flush_queue();

    SDL_GL_SwapBuffers();
}

void
renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}