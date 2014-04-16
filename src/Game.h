#ifndef GAME_H_
#define GAME_H_

#include <glm/glm.hpp>

#include "camera.h"
#include "graphics/gl_adapters/uniform_matrix.h"
#include "GroundPlane.h"
#include "input.h"
#include "graphics/mesh.h"
#include "SDLEngine.h"
#include "graphics/Shaders.h"
#include "units.h"

class Game {
   SDLEngine engine_;
   Shaders shaders_;
   GroundPlane ground_plane_;
   UniformMatrix projection_;
   Camera camera_;
   Mesh cube_mesh_;
   Input input_;

   void step(units::MS dt);
   void draw();

  public:
   Game();

   void mainLoop();
};

#endif // GAME_H_
