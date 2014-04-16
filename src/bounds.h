#ifndef BOUNDS_H_
#define BOUNDS_H_

#include <algorithm>

struct Bounds {
   Bounds(float min, float max) {
      min_ = std::min(min, max);
      max_ = std::max(min, max);
   }

   // Returns a random value between min/max.
   float randomInclusive() const {
      float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // between 0.0f and 1.0f
      return r * (max_ - min_) + min_;
   }

  private:
   float min_;
   float max_;
};

#endif // BOUNDS_H_
