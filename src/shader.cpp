#include <iostream>
#include <cstring>
#include <cstdio>

#include "resource.h"
#include "shader.h"

shader::shader(resource *vertex, resource *fragment)
{
    vid = compile(vertex, GL_VERTEX_SHADER);
    fid = compile(fragment, GL_FRAGMENT_SHADER);
    program = link(vid, fid);
}

shader::~shader()
{
    glDeleteProgram(program);
    glDeleteShader(vid);
    glDeleteShader(fid);
}


void
shader::use()
{
    glUseProgram(program);
}

int
shader::success()
{

    return 1;
}

int
shader::attribLocation(const char *name)
{
    return glGetAttribLocation(program, name);
}

int
shader::uniformLocation(const char *name)
{
    return glGetUniformLocation(program, name);
}

GLuint
shader::compile(resource *program, GLenum st)
{
    char buf[4096];
    char * raw = program->getRaw();
    GLuint shader;
    GLint status, source_length;

    shader = glCreateShader(st);
    source_length = program->getLength();

    glShaderSource(shader, 1, (const char **) &raw, &source_length);

    glCompileShader(shader);

    glGetShaderiv (shader, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        GLsizei length;
        glGetShaderInfoLog (shader, sizeof (buf), &length, buf);
        std::cout << "Failed to compile shader: " << buf << std::endl;
        fflush(stdout);
        return 0;
    }

    return shader;
}

GLuint
shader::link(GLuint vid, GLuint fid)
{
    GLuint program = glCreateProgram();
    GLint status;

    glAttachShader(program, vid);
    glAttachShader(program, fid);

    glLinkProgram(program);

    glGetProgramiv (program, GL_LINK_STATUS, &status);

    glBindAttribLocation (program, 0, "aVertexPosition");
    glBindAttribLocation (program, 1, "aTextureCoord");
    glBindAttribLocation (program, 2, "aColor");
    glBindAttribLocation (program, 3, "useTex");

    if (!status)
    {
        std::cout << "Failed to link shader program" << std::endl;
        fflush(stdout);
        return 0;
    }

    return program;
}
