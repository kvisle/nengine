#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

class image {
    public:
        image(const unsigned char * buffer, int length);
        ~image();

        GLuint getTexture();
        void bindTexture();

        int w, h;
        unsigned char *pixels;

    private:
        GLuint texid;

};

#endif /* __IMAGE_H__ */
