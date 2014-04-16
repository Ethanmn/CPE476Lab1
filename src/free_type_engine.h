#ifndef FREE_TYPE_ENGINE_H_
#define FREE_TYPE_ENGINE_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>

struct FreeTypeEngine {
   FreeTypeEngine();

   void loadFont(const std::string& font);

  private:
   FT_Library library_;
   std::map<std::string, FT_Face> fonts_;
};

#endif // FREE_TYPE_ENGINE_H_
