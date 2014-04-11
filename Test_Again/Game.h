#ifndef GAME_H_
#define GAME_H_

#include "SDLEngine.h"
#include "Shaders.h"
#include "units.h"

class Game {
   SDLEngine engine_;
   SDL_Window* window_;
   Shaders shaders_;
   ArrayBufferObject ground_buffer_object_;

   void step(units::MS dt);
   void draw();

  public:
   Game();

   void mainLoop();
};

#endif // GAME_H_
