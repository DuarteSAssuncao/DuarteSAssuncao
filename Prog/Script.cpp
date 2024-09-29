#include <iostream>
#include <fstream>
#include "Color.hpp"
#include "Image.hpp"
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            if (command == "save") {
                save();
                continue;
            } 
            if (command == "invert") {
                invert();
                continue;
            }
            if (command == "to_gray_scale") {
                to_gray_scale();
                continue;
            }
            if (command == "replace") {
                replace();
                continue;
            }
            if (command == "fill") {
                fill();
                continue;
            }
            if (command == "h_mirror") {
                h_mirror();
                continue;
            }
            if (command == "v_mirror") {
                v_mirror();
                continue;
            }
            if (command == "add") {
                add();
                continue;
            }
            if (command == "median_filter") {
              median_filter();
              continue;
            }  
            if (command == "crop") {
                crop();
                continue;
            }
            if (command == "rotate_left") {
                rotate_left();
                continue;
            }
            if (command == "rotate_right") {
                rotate_right();
                continue;
            }
            if (command == "xpm2_open") {
                xpm2_open();
                continue;
            }
            if (command == "xpm2_save") {
                xpm2_save();
                continue;
            }
        }
    }


    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }


    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }


    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }


    void Script::invert() {
        // Transforms each individual pixel (r, g, b) to (255-r,255-g,255-b).
        for(Color & c: *image){
            c.red() = 255 - c.red();
            c.green() = 255 - c.green();
            c.blue() = 255 - c.blue();
        }
    }


    void Script::to_gray_scale() {
        // Transforms each individual pixel (r, g, b) to (v, v, v) where v = (r + g + b)/3. You should use integer division without rounding to compute v.
        for(Color & c: *image){
            unsigned char v = (c.red() + c.green() + c.blue()) / 3;
            c.red() = v;
            c.green() = v;
            c.blue() = v;
        }
    }


    void Script::replace() {
        // Replaces all (r1,  g1, b1) pixels by (r2,  g2, b2).
        int r1, g1, b1, r2, g2, b2;
        input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
        for(Color & c: *image){
            if(c.red() == r1 and c.green() == g1 and c.blue() == b1){
                c.red() = r2;
                c.green() = g2;
                c.blue() = b2;
            }
        }
    }


    void Script::fill() {
        // Assign (r, g, b) to all pixels contained in rectangle defined by top-left corner (x, y), width w, and height h, i.e., all pixels (x', y') such that x <= x' < x + w and y <= y' < y + h.
        int x, y, w, h;
        int r, g, b;
        input >> x >> y >> w >> h >> r >> g >> b;
        for(int i = x; i < x + w; i++){
            for(int j = y; j < y + h; j++){
                image->at(i, j).red() = r;
                image->at(i, j).green() = g;
                image->at(i, j).blue() = b;
            }
        }
    }


    void Script::h_mirror() {
        // Mirror image horizontally. Pixels (x, y) and (width() - 1 - x, y) for all 0 <= x < width() / 2 and 0 <= y < height().
        Color tmp = Color(0,0,0);
        for(int i = 0; i < image->width()/2; i++){
            for(int j = 0; j < image->height(); j++) {
              tmp = Color(image->at(i, j));
              image->at(i,j) = Color(image->at(image->width() - 1 - i, j));
              image->at(image->width() - 1 - i, j) = tmp;
            }
        }
    }


    void Script::v_mirror() {
        // Mirror image vertically. Pixels (x, y) and (x, height() - 1 - y) for all 0 <= x < width() and 0 <= y < height() / 2.
        Color tmp = Color(0,0,0);
        for(int i = 0; i < image->width(); i++){
            for(int j = 0; j < image->height()/2; j++) {
              tmp = Color(image->at(i, j));
              image->at(i,j) = Color(image->at(i, image->height() - 1 - j));
              image->at(i, image->height() - 1 - j) = tmp;
            }
        }
    }


    int rank_color(Color& c) {
      // rank color "scores" a color. Basically, it represents the colour as a single 32-bit integer, to ease comparison between two colours.
      // It follows the same representation in memory as the class Color.
      return (c.red() << 16) + (c.green() << 8) + c.blue();
    }

    void Script::add() {
        //Copy all pixels from image stored in PNG file filename, except pixels in that image with “neutral” color (r, g, b), to the rectangle of the current image with top-left corner (x, y) of the current image. The rectangle affected in the current image has the same dimensions as the given image, and you may assume that rectangle is within the current image bounds.
        string filename;
        input >> filename;
        Image* other = loadFromPNG(filename);
        int r, g, b, x, y;
        input >> r >> g >> b >> x >> y;
        int rgb_val = (r << 16) + (g << 8) + b;
        for(int i = 0; i < other->width(); i++) {
            for(int j = 0; j < other->height(); j++) {
                if (rank_color(other->at(i, j)) != rgb_val) {
                    image->at(i + x, j + y) = Color(other->at(i, j));
                }   
            }
        }
        delete other;
    }


    void median_valid_pixels(const Image *v, int x, int y, int mx, int my, int dist, std::vector<int>& reds, std::vector<int>& greens, std::vector<int>& blues) {
        // Select a window by coordinates and maximum distance, segragating the RGB values of each pixel.
        for (int i = -dist; i <= dist; ++i ) {
            for (int j = -dist; j <= dist; ++j) {
                int dx = x + i;
                int dy = y + j;
                if (dx >= 0 && dy >= 0 && dx < mx && dy < my) {
                Color pixel = v->at(dx, dy);
                reds.push_back(pixel.red());
                greens.push_back(pixel.green());
                blues.push_back(pixel.blue());
                }
            }
        }
    }

    int median_of(std::vector<int>& v) {
        // Calculate the median of any vector of integers.
        std::sort(v.begin(),v.end());
        if (v.size() % 2 != 0) {
            return v[v.size() / 2];
        } else {
            return (v[v.size() / 2] + v[v.size() / 2 - 1]) / 2;
        }
    }

    void Script::median_filter() {
        // Apply a median filter with window size ws >= 3 to the current image.
        int ws;
        input >> ws;
        int mx = image->width();
        int my = image->height();
        int distance = ws / 2;
        Image *res = new Image(mx,my);
        std::vector<int> reds;
        std::vector<int> greens;
        std::vector<int> blues;
        for (int i = 0; i < mx; ++i) {
            for (int j = 0; j < my; ++j) {
                median_valid_pixels(image, i, j, mx, my, distance, reds, greens, blues);
                res->at(i, j) = Color(median_of(reds), median_of(greens), median_of(blues)); 
                reds.clear();
                greens.clear();
                blues.clear();
            }
        }
        delete image;
        image = res;
    }


    void Script::crop() {
        // Crop the image, reducing it to all pixels contained in the rectangle defined by top-left corner (x, y), width w, and height h.You may assume that the rectangle is always within the current image bounds.
        int x, y, w, h;
        input >> x >> y >> w >> h;
        Image *result = new Image(w,h);
        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                result->at(i, j) = Color(image->at(i + x,j + y));
            }
        }
        delete image;
        image = result;
    }


    void Script::rotate_left() {
        // Rotate image left by 90 degrees.
        Image *result = new Image(image->height(), image->width());
        for(int i = 0; i < image->width(); i++){
            for(int j = 0; j < image->height(); j++){
                result->at(j, image->width() - i - 1) = image->at(i, j);   
                // Original(i, j) = Rotated(j, last_position_of_x - i)
            }
        }
        delete image;
        image = result;
    }


    void Script::rotate_right() {
        // Rotate image right by 90 degrees.
        Image *result = new Image(image->height(), image->width());
        for(int i = 0; i < image->width(); i++){
            for(int j = 0; j < image->height(); j++){
                result->at(image->height() - j - 1, i) = image->at(i, j);
                // Original(i, j) = Rotated(last_position_of_y - j, i)
            }
        }
        delete image;
        image = result;
    }


    void Script::xpm2_open() {
        // Read image stored in the XPM2 file format.
        clear_image_if_any();
        std::string filename;
        input >> filename;
        image = loadFromXPM2(filename);
    }


    void Script::xpm2_save() {
        // Save image to the XPM2 file format.
        std::string filename;
        input >> filename;
        saveToXPM2(filename, image);
    }
}
