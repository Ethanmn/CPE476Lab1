#include "Game.h"
#include "Shader.h"
#include <stdio.h>

Game::Game() {
   SDL_Init(SDL_INIT_EVERYTHING);
   window_ = SDL_CreateWindow("Whatever", 0, 0, 640, 480, SDL_WINDOW_OPENGL);
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
   Shader shader("../shaders/vert.glsl", "../shaders/frag.glsl");

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

         if (event.type == SDL_KEYDOWN)
         {
             if (event.key.keysym.sym == SDLK_w) {
                 //FORWARD
                 printf("FORWARD HO!");
             }
             else if (event.key.keysym.sym == SDLK_s) {
                 //BACKWARD
                 printf("BACK IT UP!");
             }
             if (event.key.keysym.sym == SDLK_a) {
                 //LEFT
                 printf("TO THE LEFT TO THE LEFT!");
             }
             else if (event.key.keysym.sym == SDLK_d) {
                 //RIGHT
                 printf("RIGHT YOUR WRONGS!");
             }
         }

         if (event.type == SDL_KEYUP)
         {
             if (event.key.keysym.sym == SDLK_w) {
                 //FORWARD OFF
                 printf("FORWARD OFF!");
             }
             if (event.key.keysym.sym == SDLK_s) {
                 //BACKWARD OFF
                 printf("FORWARD OFF!");
             }
             if (event.key.keysym.sym == SDLK_a) {
                 //LEFT OFF
                 printf("FORWARD OFF!");
             }
             if (event.key.keysym.sym == SDLK_d) {
                 //RIGHT OFF
                 printf("FORWARD OFF!");
             }
         }

      }

      const units::MS current_time = SDL_GetTicks();
      const units::MS dt = current_time - previous_time;
      step(dt);
      previous_time = current_time;

      glClearColor(0, 0, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT);
      draw();
      SDL_GL_SwapWindow(window_);

      SDL_Delay(5);
   }
}
