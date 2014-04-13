#ifndef GAME_H_
#define GAME_H_

#include <glm/glm.hpp>

#include "GroundPlane.h"
#include "SDLEngine.h"
#include "Shaders.h"
#include "projection.h"
#include "units.h"

class Game {
   SDLEngine engine_;
   Shaders shaders_;
   GroundPlane ground_plane_;
   Projection projection_;

   const glm::mat4 view_matrix_;
   GLUniformLocationMap view_uniforms_;

   void step(units::MS dt);
   void draw();

  public:
   Game();

   void mainLoop();
};

#endif // GAME_H_
