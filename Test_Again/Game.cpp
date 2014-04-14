#include "Game.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "assimp/mesh_loader.h"

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
            glm::vec3(-5.0f, -5.0f, -5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)),
         shaders_.getUniforms(Uniform::VIEW)),
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
      shader.uniformMatrix(view_);

      glm::mat4 model_matrix(glm::translate(glm::mat4(), glm::vec3(0.0f, -2.0f, -0.0f)));
      shader.uniformMatrix(
            { glm::transpose(glm::inverse(model_matrix)),
              shaders_.getUniforms(Uniform::NORMAL) });

      shader.drawMesh(
            { model_matrix,
              shaders_.getUniforms(Uniform::MODEL)
            },
            cube_mesh_);

      model_matrix = glm::mat4();
      shader.uniformMatrix(
            { glm::transpose(glm::inverse(model_matrix)),
              shaders_.getUniforms(Uniform::NORMAL) });
      ground_plane_.draw(shader);
   }
   shaders_.clear();
}

void Game::mainLoop() {
   bool running = true;
   SDL_Event event;
   units::MS previous_time = SDL_GetTicks();
   while (running)
   {
      // Handle input
      while (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            running = false;
         }

         if (event.type == SDL_KEYDOWN && event.key.repeat == false) {
             if (event.key.keysym.sym == SDLK_w) {
                 //FORWARD
                std::cout << "FORWARD HO!" << std::endl;
             }
             else if (event.key.keysym.sym == SDLK_s) {
                 //BACKWARD
                std::cout << "BACK IT UP!" << std::endl;
             }
             if (event.key.keysym.sym == SDLK_a) {
                 //LEFT
                std::cout << "TO THE LEFT TO THE LEFT!" << std::endl;
             }
             else if (event.key.keysym.sym == SDLK_d) {
                 //RIGHT
                std::cout << "RIGHT YOUR WRONGS!" << std::endl;
             }
         }

         if (event.type == SDL_KEYUP)
         {
             if (event.key.keysym.sym == SDLK_w) {
                 //FORWARD OFF
                std::cout << "FORWARD OFF!" << std::endl;
             }
             if (event.key.keysym.sym == SDLK_s) {
                 //BACKWARD OFF
                std::cout << "BACKWARD OFF!" << std::endl;
             }
             if (event.key.keysym.sym == SDLK_a) {
                 //LEFT OFF
                std::cout << "LEFT OFF!" << std::endl;
             }
             if (event.key.keysym.sym == SDLK_d) {
                 //RIGHT OFF
                std::cout << "RIGHT OFF!" << std::endl;
             }
         }
      }

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
