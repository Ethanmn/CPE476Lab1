#include <SDL.h>
#include <GL/glew.h>
#ifdef _WIN32
#undef main
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

int main() {
   SDL_Init(SDL_INIT_EVERYTHING);
   SDL_Window* window = SDL_CreateWindow("Whatever", 0, 0, 640, 480, SDL_WINDOW_OPENGL);
   SDL_GLContext context = SDL_GL_CreateContext(window);
   SDL_GL_MakeCurrent(window, context);
   glewInit();
   glClearColor(0, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   SDL_GL_SwapWindow(window);
   while (true)
   {
      SDL_Delay(5);
   }
   return 0;
}
