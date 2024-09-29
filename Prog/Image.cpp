#include "Image.hpp"


namespace prog
{
  Image::Image(int w, int h, const Color &fill) {
    pixels_ = new Color[w*h];
    for (int i = 0; i < w*h; ++i) {
      pixels_[i] = fill;
    }
    w_ = w;
    h_ = h;
  }

  Image::~Image()
  {
    delete [] pixels_;
  }

  int Image::width() const { 
    return w_;
  }

  int Image::height() const {
    return h_;
  }

  Color* Image::begin() const {
    // Used on range base loops
    return &pixels_[0];
  }

  Color* Image::end() const {
    // Used on range based loops
    return &pixels_[w_*h_];
  }

  Color Err = {0,0,0};  // Color value for out of bounds access

  Color& Image::at(int x, int y) {
    // Mutable reference
    if (x >= 0 && x < this->width() && y >= 0 && y < this->height()) {
      return pixels_[x + y * this->width()];
    }
    return Err;
  }

  const Color& Image::at(int x, int y) const {
    // Read-only reference
    if (x >= 0 && x < this->width() && y >= 0 && y < this->height()) {
      return pixels_[x + y * this->width()];
    }
    return Err;
  }

}
