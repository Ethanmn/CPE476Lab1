#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include <GL/glew.h>
#ifdef _WIN32
    #undef main
#endif

#include "units.h"

class Game {
   SDL_Window* window_;
   SDL_GLContext context_;

   void step(units::MS dt);
   void draw();

  public:
   Game();
   ~Game();

   void mainLoop();
};

#endif // GAME_H_
