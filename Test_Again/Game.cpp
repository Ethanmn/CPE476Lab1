#include "Game.h"

#include <iostream>

const std::vector<float> ground_vertices{
   -0.5, -0.5, 0.0,
   0.5, -0.5, 0.0,
   -0.5, 0.5, 0.0,

   0.5, 0.5, 0.0,
   0.5, -0.5, 0.0,
   -0.5, 0.5, 0.0,
};

Game::Game() :
   window_(engine_.window()),
   ground_plane_(shaders_.use(ShaderType::GROUND))
{
}

void Game::step(units::MS dt) {
}

void Game::draw() {
   ground_plane_.draw();
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

         SDL_GL_SwapWindow(window_);
      }

      SDL_Delay(5);
   }
}
