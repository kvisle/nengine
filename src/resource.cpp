#include <iostream>
#include <fstream>

#include "resource.h"

resource::resource(std::string name)
{
    std::string filename = "assets/" + name;
    length = 0;
    buffer = NULL;

    myname = name;

    std::cout << "Name: " << myname << std::endl;

    std::ifstream file(filename.c_str(), 
                       std::ios::in|std::ios::binary|std::ios::ate);

    if ( !file.is_open() )
    {
        std::cout << "Unable to open " << name << std::endl;
        return;
    }

    length = file.tellg();
    buffer = new char[length];
    file.seekg(0, std::ios::beg);
    file.read(buffer, length);
    if ( (file.rdstate() & std::ifstream::failbit ) != 0 )
        std::cerr << "Failbit set\n";
    file.close();

    std::cout << "resource(" << name << "): Read " 
              << length << " bytes" << std::endl;
}

resource::~resource()
{
    if (buffer)
    {
        delete buffer;
        std::cout << "resource(" << myname << "): Freed buffer" << std::endl;
    }
}

char *
resource::getRaw()
{
    return buffer;
}

int
resource::getLength()
{
    return length;
}

Json::Value
resource::getJson()
{
    Json::Value root;
    Json::Reader reader;

    if ( !reader.parse(buffer, root) ) {
        std::cout << "resource(" << myname << "): Json parsing failed" << std::endl;
    }

    return root;
}
