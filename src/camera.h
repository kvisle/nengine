#ifndef __CAMERA_H__
#define __CAMERA_H__

class sprite;

class camera {
    public:
        camera(int x, int y, int w, int h);

        void snapAt(int x, int y);
        void centerAt(int x, int y);
        void keepInFrame(sprite *s, int margx, int margy);
        void resetCamera();
        void saveCamera();

        int x, y, w, h;

    private:
        int _x, _y, _w, _h;

};

#endif /* __CAMERA_H__ */
