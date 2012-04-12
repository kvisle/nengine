#ifndef __CAMERA_H__
#define __CAMERA_H__

class camera {
    public:
        camera(int x, int y, int w, int h);

        void snapAt(int x, int y);

        int x, y, w, h;

};

#endif /* __CAMERA_H__ */
