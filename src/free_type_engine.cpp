#include "free_type_engine.h"

FreeTypeEngine::FreeTypeEngine() {
   if (FT_Init_FreeType(&library_)) {
      fprintf(stderr, "Could not init freetype library\n");
      exit(EXIT_FAILURE);
   }
}

void FreeTypeEngine::loadFont(const std::string& font_path) {
   FT_Face face;

   if(FT_New_Face(library_, font_path.c_str(), 0, &face)) {
      fprintf(stderr, "Could not open font_path: %s. Make sure to leave in the extension.\n", font_path.c_str());
      exit(EXIT_FAILURE);
   }

   //TODO: not in here.
   FT_Set_Pixel_Sizes(face, 0, 24);
}
