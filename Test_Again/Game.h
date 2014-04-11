#ifndef GAME_H_
#define GAME_H_

#include "GroundPlane.h"
#include "SDLEngine.h"
#include "Shaders.h"
#include "units.h"

class Game {
   SDLEngine engine_;
   SDL_Window* window_;
   Shaders shaders_;
   GroundPlane ground_plane_;

   void step(units::MS dt);
   void draw();

  public:
   Game();

   void mainLoop();
};

#endif // GAME_H_
