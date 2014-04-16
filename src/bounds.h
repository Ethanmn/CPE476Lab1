#ifndef BOUNDS_H_
#define BOUNDS_H_

#include <algorithm>

struct Bounds {
   Bounds(float min, float max) {
      min_ = std::min(min, max);
      max_ = std::max(min, max);
   }

   Bounds shrink(float total_shrinkage) const {
      return Bounds(min_ + total_shrinkage / 2, max_ - total_shrinkage / 2);
   }

   // Returns a random value between min/max.
   float randomInclusive() const {
      float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // between 0.0f and 1.0f
      return r * (max_ - min_) + min_;
   }

   // Checks to see if |this| is within |bounds|.
   bool within(const Bounds& bounds) const {
      return bounds.min_ <= min_ && bounds.max_ >= max_;
   }

  private:
   float min_;
   float max_;
};

#endif // BOUNDS_H_
