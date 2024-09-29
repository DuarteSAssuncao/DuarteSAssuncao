SUBMISSION INFORMATION
======================
Group identifier: 03.03
Summary of implemented features:
- Color()
- Color(const Color& c)
- Color(rgb_value r, rgb_value g, rgb_value b)
- rgb_value red() const
- rgb_value green() const  
- rgb_value blue() const
- rgb_value& red()
- rgb_value& green()
- rgb_value& blue()

- Image(int w, int h, const Color& fill = {255, 255, 255})
- ~Image()
- int width() const
- int height() const
- Color& at(int x, int y)
- const Color& at(int x, int y) const

- run()
- invert
- to_gray_scale
- replace r1 g1 b1 r2 g2 b2
- fill x y w h r g b
- h_mirror
- v_mirror
- add filename x y r g b
- crop x y w h
- rotate_left
- rotate_right
- median_filter ws
- xpm2_open filename
- Image* loadFromXPM2(const std::string& file)
- xpm2_save filename
- void saveToXPM2(const std::string& file, const Image* image)