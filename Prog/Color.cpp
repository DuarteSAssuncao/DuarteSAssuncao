#include "Color.hpp"

namespace prog {
    // Default constructor
    Color::Color(): r_(0), g_(0), b_(0) {}

    // Copy constructor
    Color::Color(const Color& other) {
        r_ = other.red();
        g_ = other.green();
        b_ = other.blue();
    }

    // Constructor using supplied values
    Color::Color(rgb_value red, rgb_value green, rgb_value blue): r_(red), g_(green), b_(blue) {}


    // Red getter (read-only)
    rgb_value Color::red() const {
        return r_;
    }

    // Green getter (read-only)
    rgb_value Color::green() const {
        return g_;
    }

    // Blue getter (read-only)
    rgb_value Color::blue() const {
        return b_;
    }

    // Red getter (mutable)
    rgb_value& Color::red() {
        return r_;
    }

    // Green getter (mutable)
    rgb_value& Color::green() {
        return g_;
    }

    // Blue getter (mutable)
    rgb_value& Color::blue() {
        return b_;
    }
    
}
