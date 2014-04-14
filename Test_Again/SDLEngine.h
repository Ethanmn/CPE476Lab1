#ifndef SDL_ENGINE_H_
#define SDL_ENGINE_H_

#include <SDL.h>
#include <GL/glew.h>
#ifdef _WIN32
    #undef main
#endif

struct SDLEngine {
   SDLEngine() {
      SDL_Init(SDL_INIT_VIDEO);
      window_ = SDL_CreateWindow("Whatever", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
      context_ = SDL_GL_CreateContext(window_);
      SDL_GL_MakeCurrent(window_, context_);
      glewInit();
      glClearColor(0, 0, 1, 1); // Clear to solid blue.

      glClearDepth(1.0f);
      glDepthFunc(GL_LESS);
      glEnable(GL_DEPTH_TEST);// Enable Depth Testing
      glDisable(GL_LIGHTING);
      glShadeModel(GL_SMOOTH);
      glDisable(GL_LINE_SMOOTH);
      glEnable(GL_CULL_FACE);
   }

   ~SDLEngine() {
      SDL_GL_DeleteContext(context_);
      SDL_DestroyWindow(window_);
      SDL_Quit();
   }

   void swapWindow() { SDL_GL_SwapWindow(window_); }

  private:
   SDL_Window* window_;
   SDL_GLContext context_;
};

#endif // SDL_ENGINE_H_
