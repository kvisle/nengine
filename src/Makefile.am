AM_CFLAGS = -Wall 
bin_PROGRAMS = nengine
nengine_SOURCES = asset.cpp game.cpp main.cpp resource.cpp shader.cpp tilemap.cpp \
                  drawable.cpp image.cpp renderer.cpp resourcemanager.cpp tile.cpp \
                  tileset.cpp font.cpp sprite.cpp megaman.cpp

nengine_LDADD = -L../lib/lib_json -ljsoncpp \
                -L../lib/stb_image -lstbimage \
			    $(OPENAL_LIBS) \
			    $(GL_LIBS) \
                $(SDL_LIBS) \
                $(GLEW_LIBS)

EXTRA_DIST = asset.h camera.h drawable.h game.h image.h renderer.h resource.h \
             resourcemanager.h shader.h tile.h tilemap.h tileset.h font.h \
             sprite.h megaman.h

nengine_CFLAGS = -Wall -Wextra -g -pg

nengine_CXXFLAGS = -Wall -Wextra -g -pg \
				   -I../include \
                   -I../lib/ \
				   $(OPENAL_CFLAGS) \
				   $(GL_CFLAGS) \
				   $(SDL_CFLAGS) \
                   $(GLEW_CFLAGS)
