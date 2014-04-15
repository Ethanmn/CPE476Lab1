#include "Game.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "assimp/mesh_loader.h"
#include "model_view_uniform_matrix.h"

const std::vector<float> ground_vertices{
   -0.5, -0.5, 0.0,
   0.5, -0.5, 0.0,
   -0.5, 0.5, 0.0,

   0.5, 0.5, 0.0,
   0.5, -0.5, 0.0,
   -0.5, 0.5, 0.0,
};

glm::mat4 projectionMatrix() {
   const float field_of_view_y = 80.0f;
   const float z_near = 0.1f;
   const float z_far = 100.0f;
   const float aspect_ratio = 640.0f/480.0f;
   return glm::perspective(field_of_view_y, aspect_ratio, z_near, z_far);
}

Game::Game() :
   ground_plane_(shaders_),
   projection_(
         projectionMatrix(),
         shaders_.getUniforms(Uniform::PROJECTION)),
   view_(glm::lookAt(
            glm::vec3(3.0f, 3.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f))),
   cube_mesh_(Mesh::fromAssimpMesh(shaders_, loadMesh("../models/cube.obj")))
{
}

void Game::step(units::MS) {
}

void Game::draw() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // TODO: move to Shaders.
   auto& shaders = shaders_.getMap();
   for (auto& pair : shaders) {
      // where pair is (ShaderType, Shader)
      auto& shader = pair.second;
      shader.use();

      // send uniforms to the shader
      shader.uniformMatrix(projection_);

      glm::mat4 model_matrix(
            glm::rotate(
               glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)),
               0.0f,
               glm::vec3(0.0f, 1.0f, 0.0f)));
      shader.drawMesh(
            ModelViewUniformMatrix(
               shaders_,
               model_matrix).calculateAffineUniforms(view_),
            cube_mesh_);

      ground_plane_.draw(shader, view_);
   }
   shaders_.clear();
}

void Game::mainLoop() {
   Input input;
   bool running = true;
   SDL_Event event;
   units::MS previous_time = SDL_GetTicks();
   while (running) {
      {  // Collect input
         input.beginFrame();
         while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
               running = false;
            }

            if (event.type == SDL_KEYDOWN && event.key.repeat == false) {
               input.keyDown(event.key);
            } else if (event.type == SDL_KEYUP) {
               input.keyUp(event.key);
            }
         }
      }
      // Handle input

      {
         const units::MS current_time = SDL_GetTicks();
         const units::MS dt = current_time - previous_time;
         step(dt);
         previous_time = current_time;
      }

      {
         draw();
         engine_.swapWindow();
      }

      SDL_Delay(5);
   }
}
