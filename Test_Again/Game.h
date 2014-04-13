#ifndef GAME_H_
#define GAME_H_

#include <glm/glm.hpp>

#include "GroundPlane.h"
#include "SDLEngine.h"
#include "Shaders.h"
#include "gl_adapters/uniform_matrix.h"
#include "units.h"

class Game {
   SDLEngine engine_;
   Shaders shaders_;
   GroundPlane ground_plane_;
   UniformMatrix projection_;
   UniformMatrix view_;

   void step(units::MS dt);
   void draw();

  public:
   Game();

   void mainLoop();
};

#endif // GAME_H_
