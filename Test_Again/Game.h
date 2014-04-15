#ifndef GAME_H_
#define GAME_H_

#include <glm/glm.hpp>

#include "gl_adapters/uniform_matrix.h"
#include "GroundPlane.h"
#include "input.h"
#include "mesh.h"
#include "SDLEngine.h"
#include "Shaders.h"
#include "units.h"

class Game {
   SDLEngine engine_;
   Shaders shaders_;
   GroundPlane ground_plane_;
   UniformMatrix projection_;
   glm::mat4 view_;
   Mesh cube_mesh_;
   Input input_;

   void step(units::MS dt);
   void draw();

  public:
   Game();

   void mainLoop();
};

#endif // GAME_H_
