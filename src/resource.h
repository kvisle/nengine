#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>

#include "json/json.h"

class resource {
    public:

        resource(std::string name);
        ~resource();

        char * getRaw();
        int getLength();
        Json::Value getJson();

    private:

        char * buffer;
        unsigned int length;
        std::string myname;

};

#endif /* __RESOURCE_H__ */
