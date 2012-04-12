AM_CFLAGS = -Wall 
bin_PROGRAMS = nengine
nengine_SOURCES = game.cpp resource.cpp shader.cpp tilemap.cpp \
                  drawable.cpp image.cpp renderer.cpp resourcemanager.cpp tile.cpp \
                  tileset.cpp font.cpp sprite.cpp megaman.cpp camera.cpp

nengine_LDADD = -L../lib/lib_json -ljsoncpp \
                -L../lib/stb_image -lstbimage

if NACL
nengine_LDADD += -lppapi -lppapi_cpp -lppapi_gles2
nengine_SOURCES += nacl.cpp
endif
if SDL
nengine_SOURCES += main.cpp
nengine_LDADD += $(OPENAL_LIBS) \
			     $(GL_LIBS) \
                 $(SDL_LIBS) \
                 $(GLEW_LIBS)
endif

EXTRA_DIST = camera.h drawable.h game.h image.h renderer.h resource.h \
             resourcemanager.h shader.h tile.h tilemap.h tileset.h font.h \
             sprite.h megaman.h

nengine_CFLAGS = -Wall -Wextra -g 

nengine_CXXFLAGS = -Wall -Wextra -g \
				   -I../include \
                   -I../lib/

if NACL
nengine_CXXFLAGS += -DTARGET_NACL
endif
if SDL
nengine_CXXFLAGS += -DTARGET_SDL \
                    $(OPENAL_CFLAGS) \
				    $(GL_CFLAGS) \
				    $(SDL_CFLAGS) \
                    $(GLEW_CFLAGS)
endif
