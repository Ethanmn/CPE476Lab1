#include "Game.h"
#include "Shader.h"

namespace {
   inline void unbindBuffers() {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }
   inline void clearShader() {
      glUseProgram(0);
   }
};

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
   const float ground_vertices[] = {
      -0.5, -0.5, 0.0,
      0.5, -0.5, 0.0,
      -0.5, 0.5, 0.0,

      0.5, 0.5, 0.0,
      0.5, -0.5, 0.0,
      -0.5, 0.5, 0.0,
   };

   GLuint ground_vao;
   glGenBuffers(1, &ground_vao);
   glBindVertexArray(ground_vao);

   GLuint ground_vbo;
   glGenBuffers(1, &ground_vbo);
   glBindBuffer(GL_ARRAY_BUFFER, ground_vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(ground_vertices), ground_vertices, GL_STATIC_DRAW);
   unbindBuffers();

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
      }

      const units::MS current_time = SDL_GetTicks();
      const units::MS dt = current_time - previous_time;
      step(dt);
      previous_time = current_time;

      glClearColor(0, 0, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      shader.use();
      glBindBuffer(GL_ARRAY_BUFFER, ground_vbo);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glDisableVertexAttribArray(0);
      clearShader();

      draw();
      SDL_GL_SwapWindow(window_);

      SDL_Delay(5);
   }
}
