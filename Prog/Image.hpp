#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
  class Image
  {
    private:
      Color* pixels_; // Pixels are stored in a contiguous memory allocation.
      int w_; // width
      int h_; // height

    public:
      // Constructor and deconstructor
      Image(int w, int h, const Color &fill = {255, 255, 255});
      ~Image();

      int width() const;
      int height() const;
      Color* begin() const; // Used on range-based loops
      Color* end() const;  // Used on range-based loops
      Color &at(int x, int y);
      const Color &at(int x, int y) const;
  };
}
#endif
