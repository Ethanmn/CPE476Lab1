#include "Game.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

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
   ground_plane_(shaders_.at(ShaderType::GROUND)),
   projection_matrix_(projectionMatrix()),
   projection_uniforms_(shaders_.getUniforms("uProjectionMatrix"))
{
}

void Game::step(units::MS dt) {
}

void Game::draw() {
   auto& shaders = shaders_.getMap();
   for (auto& pair : shaders) {
      // where pair is (ShaderType, Shader)
      auto& shader = pair.second;
      shader.use();

      shader.uniformMat4(projection_uniforms_, glm::mat4());

      // bind constant uniforms

      ground_plane_.draw();

      // unbind uniforms
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
         glClearColor(0, 0, 0, 1);
         glClear(GL_COLOR_BUFFER_BIT);

         draw();

         engine_.swapWindow();
      }

      SDL_Delay(5);
   }
}
