#include <iostream>
#include <cstdio>
#include "stb_image.h"

#include "image.h"

image::image(const unsigned char * buffer, int length)
{
    int n;

    texid = 0;
    pixels = stbi_load_from_memory(buffer, length, &w, &h, &n, 0);

    std::cout << "image(\?\?): Loaded image from memory, it's " << w << "x" << h << std::endl;
}

image::~image()
{
    stbi_image_free(pixels);
    glDeleteTextures(1, &texid);
}

GLuint
image::getTexture()
{
    if ( !texid )
    {
        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }

    return texid;
}

void
image::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, getTexture());
}
