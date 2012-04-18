#ifndef __INPUT_H__
#define __INPUT_H__

#include <map>
#include <vector>

#define NINPUT_KEYDOWN   0x00000001
#define NINPUT_KEYUP     0x00000002
#define NINPUT_MOUSEDOWN 0x00000003
#define NINPUT_MOUSEUP   0x00000004
#define NINPUT_MOUSEMOVE 0x00000005

class drawable;

struct nkey {
    int type;
    int sym;
};

struct nmousemove {
    int type;
    int x, y;
};

struct nmousebutton {
    int type;
    int button;
};

union ninput{
    int type;
    struct nkey key;
    struct nmousemove mmove;
    struct nmousebutton mbutton;
};

class input {
    public:
        std::map<int, int> keys;
        void subscribe(drawable *s);
        void unsubscribe(drawable *s);
        void read_input(union ninput in);

    private:
        std::vector<drawable *> subscribers;

};

#endif /* __INPUT_H__ */
