#include "Game.h"
#include "Shaders.h"

#include <iostream>

Game::Game() {
   SDL_Init(SDL_INIT_EVERYTHING);
   window_ = SDL_CreateWindow("Whatever", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
   context_ = SDL_GL_CreateContext(window_);
   SDL_GL_MakeCurrent(window_, context_);
   glewInit();
}

Game::~Game() {
   SDL_GL_DeleteContext(context_);
   SDL_DestroyWindow(window_);
   SDL_Quit();
}

void Game::step(units::MS dt) {
}

void Game::draw() {
}

void Game::mainLoop() {
   const std::vector<float> ground_vertices{
      -0.5, -0.5, 0.0,
      0.5, -0.5, 0.0,
      -0.5, 0.5, 0.0,

      0.5, 0.5, 0.0,
      0.5, -0.5, 0.0,
      -0.5, 0.5, 0.0,
   };
   ArrayBufferObject groundBufferObject =
      createArrayBufferObject(ground_vertices, "aPosition", 3);

   Shaders shaders;

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

         Shader& shader = shaders.use(ShaderType::GROUND);
         shader.bindAndEnableAttributes({groundBufferObject});

         glDrawArrays(GL_TRIANGLES, 0, 6);

         shader.disableAttribute("aPosition");
         shaders.clear();

         draw();
         SDL_GL_SwapWindow(window_);
      }

      SDL_Delay(5);
   }
}
