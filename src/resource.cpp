#include <iostream>
#include <fstream>
#include <cstring>

#include "resource.h"

#ifdef __native_client__
#include "assets.h"

extern "C" {

struct tar {
    char name[100];   char _unused[24];
    char size[12];    char _padding[376];
} *tar;

static int
is_file_in_tar( struct tar *tar, const char *name, char **start, unsigned int *length )
{
    for ( ; tar->name[0]; tar+=1+(*length+511)/512 ) 
    {
        sscanf( tar->size, "%o", length);
        if ( !strcmp(tar->name,name) )
        {
            *start = (char*)(tar+1);
            return 1;
        }
    }
    return 0;
}

}
#endif

resource::resource(std::string name)
{
    std::string filename = "assets/" + name;
    length = 0;
    buffer = NULL;

    myname = name;

    std::cout << "Name: " << myname << std::endl;

#ifdef __native_client__
    printf("Gonna load resources (%s)!!\n", filename.c_str());
    fflush(stdout);

    char *start;
    if ( 
        is_file_in_tar((struct tar *)asset_tarfile, 
                        filename.c_str(), 
                        &start, 
                        &length) ) {
        buffer = new char[length];
        memcpy(buffer, start, length);
    }
    else {
        printf("Could not find file in archive.\n");
    }
    fflush(stdout);
#else
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
#endif

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
