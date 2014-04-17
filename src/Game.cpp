#include "Game.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "graphics/assimp/mesh_loader.h"
#include "graphics/model_view_uniform_matrix.h"
#include "vec_constants.h"

namespace {
   glm::mat4 projectionMatrix() {
      const float field_of_view_y = 80.0f;
      const float z_near = 0.1f;
      const float z_far = 100.0f;
      const float aspect_ratio = 640.0f/480.0f;
      return glm::perspective(field_of_view_y, aspect_ratio, z_near, z_far);
   }
}

Game::Game() :
   ground_plane_(shaders_),
   projection_(
         projectionMatrix(),
         shaders_.getUniforms(Uniform::PROJECTION)),
   cube_mesh_(Mesh::fromAssimpMesh(shaders_, loadMesh("../models/cube.obj")))
{
   glClearColor(0, 0, 0, 1); // Clear to solid blue.
   glClearDepth(1.0f);
   glDepthFunc(GL_LESS);
   glEnable(GL_DEPTH_TEST);// Enable Depth Testing
   glDisable(GL_LIGHTING);
   glShadeModel(GL_SMOOTH);
   glDisable(GL_LINE_SMOOTH);
   glEnable(GL_CULL_FACE);

   free_type_engine_.loadFont("/usr/share/fonts/TTF/DejaVuSans.ttf");
}

void Game::step(units::MS dt) {
   creation_countdown_ -= dt;
   if (creation_countdown_ <= 0) {
      game_objects_.push_back(GameObject(ground_plane_, cube_mesh_, shaders_));
      creation_countdown_ = 1500 + rand() % 250;
   }
   for (auto& game_object : game_objects_) {
      game_object.step(dt, ground_plane_, game_objects_);
      if (game_object.captured()) continue;
      if (camera_.bounding_sphere().collides(game_object.bounding_sphere())) {
         game_object.onCameraCollision();
         ++score_;
      }
   }
}

void Game::draw() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   const auto view = camera_.viewMatrix();
   // TODO: move to Shaders.
   auto& shaders = shaders_.getMap();
   for (auto& pair : shaders) {
      // where pair is (ShaderType, Shader)
      auto& shader = pair.second;
      shader.use();

      if (pair.first == ShaderType::GROUND) {
         // send uniforms to the shader
         shader.uniformMatrix(projection_);
         for (auto& game_object : game_objects_) {
            game_object.draw(shader, view);
         }

         ground_plane_.draw(shader, view);
      } else if (pair.first == ShaderType::TEXT) {
      }
   }
   shaders_.clear();
}

void Game::mainLoop() {
   Input input;
   bool running = true;
   SDL_Event event;
   units::MS previous_time = SDL_GetTicks();
   creation_countdown_ = 1500 + rand() % 250;
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
      { // Handle input
         if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
            running = false;
         }
         const float kMoveAmount = 0.2f;
         if (input.isKeyHeld(SDL_SCANCODE_W)) {
            camera_.translateForward(kMoveAmount);
         } else if (input.isKeyHeld(SDL_SCANCODE_S)) {
            camera_.translateForward(-kMoveAmount);
         }
         if (input.isKeyHeld(SDL_SCANCODE_A)) {
            camera_.translateStrafe(-kMoveAmount);
         } else if (input.isKeyHeld(SDL_SCANCODE_D)) {
            camera_.translateStrafe(kMoveAmount);
         }

         const float kAngle = 5.0f;
         if (input.isKeyHeld(SDL_SCANCODE_LEFT)) {
            camera_.rotateYaw(kAngle);
         } else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
            camera_.rotateYaw(-kAngle);
         }
         if (input.isKeyHeld(SDL_SCANCODE_UP)) {
            camera_.rotatePitch(-kAngle);
         } else if (input.isKeyHeld(SDL_SCANCODE_DOWN)) {
            camera_.rotatePitch(kAngle);
         }

         if (input.wasKeyPressed(SDL_SCANCODE_P)) {
            std::cout << "Objects: " << game_objects_.size() << std::endl;
            std::cout << "Captures: " << score_ << std::endl;
            std::cout << "FPS: " << fps_ << std::endl;
         }
      }

      {
         const units::MS current_time = SDL_GetTicks();
         const units::MS dt = current_time - previous_time;
         step(dt);
         previous_time = current_time;
         fps_ = 1000.0f / dt;
      }

      {
         draw();
         engine_.swapWindow();
      }

      SDL_Delay(5);
   }
}
