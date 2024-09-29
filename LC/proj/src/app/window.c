/**
 * @file window.c
 * @brief Definition of functions which draw objects on the windows
 * @author T17_G1
 * @date 27/05/2024
 */

#include "window.h"
#include <graphics/graphics.h>
#include <graphics/letters.h>
#include <graphics/icons.h>
#include "shared.h"

/**
 * @brief Draw the given window on the screen
 * @param const window_t *window : window to draw
 * @return int : 0 on success
 */
int draw_window(const window_t *window) {
    vg_draw_image(window->buffer, window->width, window->height, window->x, window->y);
    return 0;
}

/**
 * @brief Creates a vew window
 * @param window_t *this : pointer to the window struct to be created
 * @param uint16_t x : x-position of leftmost pixel of the window
 * @param uint16_t y : y-position of upmost pixel of the window
 * @param uint16_t width : width of the window
 * @param uint16_t height : height of the window
 * @return int 0 if succeeded and non-zero otherwise
 */
int new_window(window_t * this, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    uint16_t x_res = vg_get_xres();
    uint16_t y_res = vg_get_yres();
    if(x < 0 || x >= x_res || y < 0 || y >= y_res || width < 33 || width >= x_res || height < 33 || height >= y_res) return 1;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->buffer = malloc(this->width * this->height * vg_bytes_per_pixel());
    if(this->buffer == NULL) return 1;

    draw_rect(this, 0, 0, this->width, this->height, 0xFFDDDDDD);
    draw_rect(this, 3, 30, this->width - 6, this->height - 33, 0xFFFFFFFF);
    xpm_image_t cross_i;
    uint8_t * cross = xpm_load(close_window_icon, XPM_8_8_8_8, &cross_i);
    if(cross == NULL) return 1;
    if(draw_image(this, cross, cross_i.width, cross_i.height, this->width - cross_i.width - 3, 3) != 0) return 1;

    return 0;
}

/**
 * @brief Closes the window
 * @note Note that the window to be closed will be removed from the windows array
 * @param window_t* this : window to be closed
 * @return int 0 if succeeded and non-zero otherwise
 */
int close_window(window_t * this){
    free(this->buffer);
    for(uint8_t i = 0; i < n_windows; i++) { // Remove the window from the window array:
        if((windows + i * sizeof(*windows)) == this) {
            void * dest = NULL;
            dest = memmove(
                windows + i,
                windows + i + 1,
                (n_windows - i - 1) * sizeof(*windows)
            );
            if(dest == NULL) return 1;
            n_windows--;
            break;
        }
    }
    return 0;
}

/**
 * @brief Turn a character into the respective sprite if available
 * @param char c : character to turn into a sprite
 * @return uint8_t* : memory address of the beginning of the sprite
 */
uint8_t * get_letter_xpm(char c){
    xpm_image_t letter_info;
    uint8_t * letter = NULL;
    switch (c){
        case 'A':  letter = xpm_load(letter_A,           XPM_8_8_8_8, &letter_info); break;
        case 'B':  letter = xpm_load(letter_B,           XPM_8_8_8_8, &letter_info); break;
        case 'C':  letter = xpm_load(letter_C,           XPM_8_8_8_8, &letter_info); break;
        case 'D':  letter = xpm_load(letter_D,           XPM_8_8_8_8, &letter_info); break;
        case 'E':  letter = xpm_load(letter_E,           XPM_8_8_8_8, &letter_info); break;
        case 'F':  letter = xpm_load(letter_F,           XPM_8_8_8_8, &letter_info); break;
        case 'G':  letter = xpm_load(letter_G,           XPM_8_8_8_8, &letter_info); break;
        case 'H':  letter = xpm_load(letter_H,           XPM_8_8_8_8, &letter_info); break;
        case 'I':  letter = xpm_load(letter_I,           XPM_8_8_8_8, &letter_info); break;
        case 'J':  letter = xpm_load(letter_J,           XPM_8_8_8_8, &letter_info); break;
        case 'K':  letter = xpm_load(letter_K,           XPM_8_8_8_8, &letter_info); break;
        case 'L':  letter = xpm_load(letter_L,           XPM_8_8_8_8, &letter_info); break;
        case 'M':  letter = xpm_load(letter_M,           XPM_8_8_8_8, &letter_info); break;
        case 'N':  letter = xpm_load(letter_N,           XPM_8_8_8_8, &letter_info); break;
        case 'O':  letter = xpm_load(letter_O,           XPM_8_8_8_8, &letter_info); break;
        case 'P':  letter = xpm_load(letter_P,           XPM_8_8_8_8, &letter_info); break;
        case 'Q':  letter = xpm_load(letter_Q,           XPM_8_8_8_8, &letter_info); break;
        case 'R':  letter = xpm_load(letter_R,           XPM_8_8_8_8, &letter_info); break;
        case 'S':  letter = xpm_load(letter_S,           XPM_8_8_8_8, &letter_info); break;
        case 'T':  letter = xpm_load(letter_T,           XPM_8_8_8_8, &letter_info); break;
        case 'U':  letter = xpm_load(letter_U,           XPM_8_8_8_8, &letter_info); break;
        case 'V':  letter = xpm_load(letter_V,           XPM_8_8_8_8, &letter_info); break;
        case 'W':  letter = xpm_load(letter_W,           XPM_8_8_8_8, &letter_info); break;
        case 'X':  letter = xpm_load(letter_X,           XPM_8_8_8_8, &letter_info); break;
        case 'Y':  letter = xpm_load(letter_Y,           XPM_8_8_8_8, &letter_info); break;
        case 'Z':  letter = xpm_load(letter_Z,           XPM_8_8_8_8, &letter_info); break;
        case 'a':  letter = xpm_load(letter_a,           XPM_8_8_8_8, &letter_info); break;
        case 'b':  letter = xpm_load(letter_b,           XPM_8_8_8_8, &letter_info); break;
        case 'c':  letter = xpm_load(letter_c,           XPM_8_8_8_8, &letter_info); break;
        case 'd':  letter = xpm_load(letter_d,           XPM_8_8_8_8, &letter_info); break;
        case 'e':  letter = xpm_load(letter_e,           XPM_8_8_8_8, &letter_info); break;
        case 'f':  letter = xpm_load(letter_f,           XPM_8_8_8_8, &letter_info); break;
        case 'g':  letter = xpm_load(letter_g,           XPM_8_8_8_8, &letter_info); break;
        case 'h':  letter = xpm_load(letter_h,           XPM_8_8_8_8, &letter_info); break;
        case 'i':  letter = xpm_load(letter_i,           XPM_8_8_8_8, &letter_info); break;
        case 'j':  letter = xpm_load(letter_j,           XPM_8_8_8_8, &letter_info); break;
        case 'k':  letter = xpm_load(letter_k,           XPM_8_8_8_8, &letter_info); break;
        case 'l':  letter = xpm_load(letter_l,           XPM_8_8_8_8, &letter_info); break;
        case 'm':  letter = xpm_load(letter_m,           XPM_8_8_8_8, &letter_info); break;
        case 'n':  letter = xpm_load(letter_n,           XPM_8_8_8_8, &letter_info); break;
        case 'o':  letter = xpm_load(letter_o,           XPM_8_8_8_8, &letter_info); break;
        case 'p':  letter = xpm_load(letter_p,           XPM_8_8_8_8, &letter_info); break;
        case 'q':  letter = xpm_load(letter_q,           XPM_8_8_8_8, &letter_info); break;
        case 'r':  letter = xpm_load(letter_r,           XPM_8_8_8_8, &letter_info); break;
        case 's':  letter = xpm_load(letter_s,           XPM_8_8_8_8, &letter_info); break;
        case 't':  letter = xpm_load(letter_t,           XPM_8_8_8_8, &letter_info); break;
        case 'u':  letter = xpm_load(letter_u,           XPM_8_8_8_8, &letter_info); break;
        case 'v':  letter = xpm_load(letter_v,           XPM_8_8_8_8, &letter_info); break;
        case 'w':  letter = xpm_load(letter_w,           XPM_8_8_8_8, &letter_info); break;
        case 'x':  letter = xpm_load(letter_x,           XPM_8_8_8_8, &letter_info); break;
        case 'y':  letter = xpm_load(letter_y,           XPM_8_8_8_8, &letter_info); break;
        case 'z':  letter = xpm_load(letter_z,           XPM_8_8_8_8, &letter_info); break;
        case '0':  letter = xpm_load(number_0,           XPM_8_8_8_8, &letter_info); break;
        case '1':  letter = xpm_load(number_1,           XPM_8_8_8_8, &letter_info); break;
        case '2':  letter = xpm_load(number_2,           XPM_8_8_8_8, &letter_info); break;
        case '3':  letter = xpm_load(number_3,           XPM_8_8_8_8, &letter_info); break;
        case '4':  letter = xpm_load(number_4,           XPM_8_8_8_8, &letter_info); break;
        case '5':  letter = xpm_load(number_5,           XPM_8_8_8_8, &letter_info); break;
        case '6':  letter = xpm_load(number_6,           XPM_8_8_8_8, &letter_info); break;
        case '7':  letter = xpm_load(number_7,           XPM_8_8_8_8, &letter_info); break;
        case '8':  letter = xpm_load(number_8,           XPM_8_8_8_8, &letter_info); break;
        case '9':  letter = xpm_load(number_9,           XPM_8_8_8_8, &letter_info); break;
        case ' ':  letter = xpm_load(char_space,         XPM_8_8_8_8, &letter_info); break;
        case '!':  letter = xpm_load(char_exclamation,   XPM_8_8_8_8, &letter_info); break;
        case '\"': letter = xpm_load(char_quote,         XPM_8_8_8_8, &letter_info); break;
        case '#':  letter = xpm_load(char_hash,          XPM_8_8_8_8, &letter_info); break;
        case '$':  letter = xpm_load(char_dollar,        XPM_8_8_8_8, &letter_info); break;
        case '%':  letter = xpm_load(char_percent,       XPM_8_8_8_8, &letter_info); break;
        case '&':  letter = xpm_load(char_ampersand,     XPM_8_8_8_8, &letter_info); break;
        case '\'': letter = xpm_load(char_apostrophe,    XPM_8_8_8_8, &letter_info); break;
        case '(':  letter = xpm_load(char_l_parenthesis, XPM_8_8_8_8, &letter_info); break;
        case ')':  letter = xpm_load(char_r_parenthesis, XPM_8_8_8_8, &letter_info); break;
        case '*':  letter = xpm_load(char_asterisk,      XPM_8_8_8_8, &letter_info); break;
        case '+':  letter = xpm_load(char_plus,          XPM_8_8_8_8, &letter_info); break;
        case ',':  letter = xpm_load(char_comma,         XPM_8_8_8_8, &letter_info); break;
        case '-':  letter = xpm_load(char_hyphen,        XPM_8_8_8_8, &letter_info); break;
        case '.':  letter = xpm_load(char_period,        XPM_8_8_8_8, &letter_info); break;
        case '/':  letter = xpm_load(char_slash,         XPM_8_8_8_8, &letter_info); break;
        case ':':  letter = xpm_load(char_colon,         XPM_8_8_8_8, &letter_info); break;
        case ';':  letter = xpm_load(char_semicolon,     XPM_8_8_8_8, &letter_info); break;
        case '<':  letter = xpm_load(char_less_than,     XPM_8_8_8_8, &letter_info); break;
        case '=':  letter = xpm_load(char_equal,         XPM_8_8_8_8, &letter_info); break;
        case '>':  letter = xpm_load(char_greater_than,  XPM_8_8_8_8, &letter_info); break;
        case '?':  letter = xpm_load(char_question,      XPM_8_8_8_8, &letter_info); break;
        case '@':  letter = xpm_load(char_at,            XPM_8_8_8_8, &letter_info); break;
        case '[':  letter = xpm_load(char_l_s_bracket,   XPM_8_8_8_8, &letter_info); break;
        case '\\': letter = xpm_load(char_back_slash,    XPM_8_8_8_8, &letter_info); break;
        case ']':  letter = xpm_load(char_r_s_bracket,   XPM_8_8_8_8, &letter_info); break;
        case '^':  letter = xpm_load(char_caret,         XPM_8_8_8_8, &letter_info); break;
        case '_':  letter = xpm_load(char_underscore,    XPM_8_8_8_8, &letter_info); break;
        case '`':  letter = xpm_load(char_grave_accent,  XPM_8_8_8_8, &letter_info); break;
        case '{':  letter = xpm_load(char_l_c_bracket,   XPM_8_8_8_8, &letter_info); break;
        case '|':  letter = xpm_load(char_v_bar,         XPM_8_8_8_8, &letter_info); break;
        case '}':  letter = xpm_load(char_r_c_bracket,   XPM_8_8_8_8, &letter_info); break;
        case '~':  letter = xpm_load(char_tilde,         XPM_8_8_8_8, &letter_info); break;

        default: return NULL;
    }
    return letter;
}

/**
 * @brief Draws text with a given size and color in the given window
 * @details Starting at the position given in x and y parameters, draws, with ther given color, in the given window each letter in the given string with an interval of (2 * size) pixels between each letter
 * @param const window_t * window : where to draw the text
 * @param uint16_t x : x-position of leftmost pixel of the text
 * @param uint16_t y : y-position of upmost pixel of the text
 * @param char string[] : text to draw on the window
 * @param uint16_t n_chars : number of characters to draw
 * @note The text will occupy a width of ((8 * n_chars - 2) * size) pixels, so make sure there is enough space available
 * @param uint32_t color : color of the text
 * @param uint8_t size : font size
 * @note Each letter has a height of 11 pixels and a width of 6 pixels. The height and width are multiplied by the size when the letter is drawn
 * @return int : 0 on success
 */
int draw_text(const window_t * window, uint16_t x, uint16_t y, char string[], uint16_t n_chars, uint32_t color, uint8_t size){
    if(y + 11 * size >= window->height) return 1; // Out of bounds
    for(uint16_t c = 0; c < n_chars; c++) {
        if(x + 6 * size >= window->width) return 1; // Out of bounds

        uint8_t * letter = get_letter_xpm(string[c]);
        if(letter == NULL) return 3; // Unable to load letter

        uint8_t Bpp = vg_bytes_per_pixel();

        for(uint16_t i = 0; i < 6; i++) {
            for(uint16_t j = 0; j < 11; j++) {
                for(uint16_t ii = 0; ii < size; ii++) {
                    for(uint16_t jj = 0; jj < size; jj++) {
                        uint8_t * pixel = window->buffer + ((y + j * size + jj) * window->width + x + i * size + ii) * Bpp;
                        // uint8_t * color = letter + (j * 6 + i) * Bpp;
                        if(*((uint8_t *)(letter + (j * 6 + i) * Bpp)) == 0xFF) continue;
                        if(memcpy(pixel, &color, Bpp) == NULL) return 4; // Unable to draw pixel
                    }
                }
            }
        }
        x += 8 * size;
    }

    return 0;
}
