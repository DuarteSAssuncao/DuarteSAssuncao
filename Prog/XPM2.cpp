#include "XPM2.hpp"
#include "Color.hpp"
#include "Image.hpp"
#include <cctype>
#include <fstream>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>


namespace prog {
    int hex_digit_to_int(char c) {
      c = tolower(c);
      if (c <= '9' && '0' <= c) {
        return c - '0';
      } else {
        return c - 'a' + 10;
      }
    }

    Color hex_to_RGB(std::string hex) {
      Color res;
      res.red() = 16 * hex_digit_to_int(hex[1]) + hex_digit_to_int(hex[2]);  
      res.green() = 16 * hex_digit_to_int(hex[3]) + hex_digit_to_int(hex[4]);  
      res.blue() = 16 * hex_digit_to_int(hex[5]) + hex_digit_to_int(hex[6]);  
      return res; 
    }

    Image* loadFromXPM2(const std::string& file) {
      std::string _; // Trash
      std::ifstream contents(file);
      if (!contents.is_open()) {
        return nullptr;
      }
      contents >> _ >> _; // ignore Header "! XMP"
      int x, y, ncolors, charlen; // width, height, number of colours, number of chars per colour;
      contents >> x >> y >> ncolors >> charlen;
      Image *res = new Image(x,y); 
      std::map<std::string,Color> colors; // Hashmap that maps symbols to actual colour values
      std::string key, value;
      for (int i = 0; i < ncolors; ++i) {
        contents >> key >> _ >> value;
        Color v = hex_to_RGB(value);
        colors[key] = v;
      }
      int im_y = 0;
      std::string line;
      while (contents >> line) { // Write each line to the image
        for (int im_x = 0; im_x < x; im_x += charlen) {
          res->at(im_x / charlen, im_y) = colors[line.substr(im_x,charlen)];
        }
        ++im_y;
      }
      return res;
    }


    std::string RGB_to_hex(Color pixel) {
        // Builds a string with the hexcode of a given RGB pixel.
        std::ostringstream oss;
        oss << '#' << std::hex << std::setfill('0') << std::setw(2) << (int)pixel.red() << std::setw(2) 
          << (int)pixel.green() << std::setw(2) << (int)pixel.blue();
        return oss.str();
    }

    std::map<std::string, std::string> hex_chars_map(const Image* image) {
        // Builds a map of all hexcodes present inside an image and their correspondent chars.
        std::map<std::string, std::string> hexChars;
        for (Color& pixel: *image) {
            std::string hex = RGB_to_hex(pixel);
            if (hexChars.find(hex) == hexChars.end()) {   // If a new color was found
                hexChars.insert({hex, "?"});
            }
        }
        char charCode = 33; // ASCII printable characters: 32-127 (space is 32)
        for (auto& pair: hexChars) {
            pair.second = charCode;
            charCode++;
        }
        return hexChars;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
		    std::ofstream fout(file);
        std::map<std::string, std::string> hexChars = hex_chars_map(image);
        fout << "! XPM2" << '\n'	                                   // Header
		         << image->width() << ' ' << image->height() << ' '      // Second line
             << hexChars.size() << ' ' << 1 << '\n';               

        for (auto pair: hexChars) {
            fout << pair.second << " c " << pair.first << '\n';     // Char mapping
        }

        for (int j = 0; j < image->height(); j++) {
            for (int i = 0; i < image->width(); i++) {
                fout << hexChars.at(RGB_to_hex(image->at(i, j)));   // Pixel encoding
            }
            fout << '\n';
        }
    }
}
