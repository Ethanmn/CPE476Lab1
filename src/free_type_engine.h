#ifndef FREE_TYPE_ENGINE_H_
#define FREE_TYPE_ENGINE_H_

#include <ft2build.h>
#include FT_FREETYPE_H

struct FreeTypeEngine {
   FreeTypeEngine() {
      FT_Library ft;

      if(FT_Init_FreeType(&ft)) {
         fprintf(stderr, "Could not init freetype library\n");
         exit(EXIT_FAILURE);
      }
   }

  private:
};

#endif // FREE_TYPE_ENGINE_H_
