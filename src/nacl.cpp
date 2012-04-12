#include <stdio.h>

#include <tr1/memory>

//#include <ppapi/c/ppb_opengles.h>

#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/module.h>

#include <ppapi/gles2/gl2ext_ppapi.h>
#include <ppapi/cpp/completion_callback.h>
#include <ppapi/cpp/graphics_3d_client.h>
#include <ppapi/cpp/graphics_3d.h>
#include <ppapi/cpp/size.h>
#include <ppapi/cpp/rect.h>

#include <ppapi/cpp/input_event.h>

#include "gl.h"

#include "game.h"
#include "input.h"
#include "resource.h"

//#include "geturl_handler.h"

namespace {
    void FlushCallback(void* data, int32_t result);
}

namespace nengine {

    class OpenGLContext : public pp::Graphics3DClient {
    public:

        explicit OpenGLContext(pp::Instance* instance) : pp::Graphics3DClient(instance), flush_pending_(false) {
            pp::Module* module = pp::Module::Get();
            assert(module);
            gles2_interface_ = static_cast<const struct PPB_OpenGLES2*>(
                module->GetBrowserInterface(PPB_OPENGLES2_INTERFACE));
            assert(gles2_interface_);
            puts("Got opengl context!");
        }


        virtual ~OpenGLContext() {
            glSetCurrentContextPPAPI(0);
        }

        virtual void Graphics3DContextLost() {
            assert(!"Unexpectedly lost graphics context");
        }

        bool MakeContextCurrent(pp::Instance* instance) {
            if (instance == NULL) {
                glSetCurrentContextPPAPI(0);
                return false;
            }

            if (context_.is_null()) {
                const int32_t attribs[] = {
                    PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 8,
                    PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 24,
                    PP_GRAPHICS3DATTRIB_STENCIL_SIZE, 8,
                    PP_GRAPHICS3DATTRIB_SAMPLES, 0,
                    PP_GRAPHICS3DATTRIB_SAMPLE_BUFFERS, 0,
                    PP_GRAPHICS3DATTRIB_WIDTH, size_.width(),
                    PP_GRAPHICS3DATTRIB_HEIGHT, size_.height(),
                    PP_GRAPHICS3DATTRIB_NONE
                };

                context_ = pp::Graphics3D(instance, /*pp::Graphics3D(), */ (const int32_t *)&attribs);

                if (context_.is_null()) {
                    glSetCurrentContextPPAPI(0);
                    return false;
                }

                instance->BindGraphics(context_);
            }

            glSetCurrentContextPPAPI(context_.pp_resource());
            return true;
        }

        void FlushContext() {
            if (flush_pending()) {
                return;
            }
            set_flush_pending(true);
            context_.SwapBuffers(pp::CompletionCallback(&FlushCallback, this));
        }

        void InvalidateContext(pp::Instance* instance) {
            glSetCurrentContextPPAPI(0);
        }

        void ResizeContext(const pp::Size& size) {
            size_ = size;
            if (!context_.is_null()) {
                context_.ResizeBuffers(size.width(), size.height());
            }
        }

        const struct PPB_OpenGLES2* gles2() const {
            return gles2_interface_;
        }

        const PP_Resource gl_context() const {
            return context_.pp_resource();
        }

        bool flush_pending() const {
            return flush_pending_;
        }
        void set_flush_pending(bool flag) {
            flush_pending_ = flag;
        }

    private:
        pp::Size size_;
        pp::Graphics3D context_;
        bool flush_pending_;

        const struct PPB_OpenGLES2* gles2_interface_;

    };

    typedef std::tr1::shared_ptr<OpenGLContext> SharedOpenGLContext;

    void UpdateCallback(void* data, int32_t /*result*/);

    class UpdateScheduler {
    public:
        UpdateScheduler(int32_t delay, void * foo) : delay_(delay), foo_(foo) { };
        ~UpdateScheduler();

    private:
        int32_t delay_;  // milliseconds
        void * foo_;
    };

    class NengineInstance : public pp::Instance {

    public:
        explicit NengineInstance(PP_Instance instance) : pp::Instance(instance) {
            RequestInputEvents(PP_INPUTEVENT_CLASS_MOUSE | PP_INPUTEVENT_CLASS_WHEEL);
            RequestFilteringInputEvents(PP_INPUTEVENT_CLASS_KEYBOARD);
        }
        virtual ~NengineInstance() {}

        virtual void DidChangeView(const pp::Rect& position, const pp::Rect& clip) {
            if (opengl_context_ == NULL)
                opengl_context_.reset(new OpenGLContext(this));

            opengl_context_->InvalidateContext(this);
            opengl_context_->ResizeContext(position.size());

            if (!opengl_context_->MakeContextCurrent(this))
                return;

            glViewport(0, 0, position.width(), position.height());
            glClearColor(0.0, 0.0, 0.0, 0.0);

            if (g == NULL)
            {
                g = new game();
                UpdateScheduler(16, this);
            }
        }

        void Update(void) {
            UpdateScheduler(16, this);
            if ( g == NULL ) {
                return;
            }
            g->update();
            g->render();
            opengl_context_->FlushContext();
        }

        virtual bool HandleInputEvent(const pp::InputEvent& event) {
            if ( g == NULL )
                return true;

            pp::KeyboardInputEvent k(event);

            switch (event.GetType()) {
                case PP_INPUTEVENT_TYPE_KEYDOWN:
                    printf("k.GetKeyCode (down): %c\n", k.GetKeyCode());
                    g->in->keys[k.GetKeyCode()] = 1;
                    break;
                case PP_INPUTEVENT_TYPE_KEYUP:
                    printf("k.GetKeyCode (up): %c\n", k.GetKeyCode());
                    g->in->keys[k.GetKeyCode()] = 0;
                    break;
                default:
                    break;
            }
            fflush(stdout);
            return true;
        }


    private:
        SharedOpenGLContext opengl_context_;
        game *g;


    };



    class NengineModule : public pp::Module {

    public:
        NengineModule() : pp::Module() {}

        virtual ~NengineModule() {
            glTerminatePPAPI();
        }

        virtual bool Init() {
            return glInitializePPAPI(get_browser_interface()) == GL_TRUE;
        }

        virtual pp::Instance* CreateInstance(PP_Instance instance) {
            return new NengineInstance(instance);
        }

    };

    void UpdateCallback(void* data, int32_t /*result*/) {
        NengineInstance* m = static_cast<NengineInstance*>(data);
        m->Update();
    }

    UpdateScheduler::~UpdateScheduler() {
        pp::Core* core = pp::Module::Get()->core();
        core->CallOnMainThread(delay_, pp::CompletionCallback(nengine::UpdateCallback, foo_));
    }


}

namespace {
    void FlushCallback(void* data, int32_t result) {
        static_cast<nengine::OpenGLContext*>(data)->set_flush_pending(false);
    }
}

namespace pp {
    Module* CreateModule() {
        return new nengine::NengineModule();
    }
}
