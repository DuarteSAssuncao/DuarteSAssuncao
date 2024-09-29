/**
 * @file letters.h
 * @brief XPM of all the available letters
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LETTERS_H
#define LETTERS_H

#include <stddef.h>
#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include "sprite.h"

/**
 * @brief Turn a character (as an int) to a XPM
 * @param int c : character (as an int)
 * @return const char* const* : XPM
 */
const char*const* get_char_xpm(int c);

/**
 * @brief Load the character sprites
 * @param sprite_t result[256] : where to load the sprites
 * @return int : 0 on success
 */
int load_char_sprites(sprite_t result[256]);

//! XPM of the uppercase letter 'A'
static xpm_row_t const letter_A[] = {
"6 11 2 1",
". c #FFFFFF",
"A c #000000",
"..AA..",
"..AA..",
".A..A.",
".A..A.",
".AAAA.",
"A....A",
"A....A",
"A....A",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'B'
static xpm_row_t const letter_B[] = {
"6 11 2 1",
". c #FFFFFF",
"B c #000000",
"BBBB..",
"B...B.",
"B...B.",
"BBBBB.",
"B....B",
"B....B",
"B....B",
"BBBBB.",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'C'
static xpm_row_t const letter_C[]= {
"6 11 2 1",
". c #FFFFFF",
"C c #000000",
"..CCC.",
".C...C",
"C.....",
"C.....",
"C.....",
"C.....",
".C...C",
"..CCC.",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'D'
static xpm_row_t const letter_D []={
"6 11 2 1",
". c #FFFFFF",
"D c #000000",
"DDDD..",
"D...D.",
"D....D",
"D....D",
"D....D",
"D....D",
"D...D.",
"DDDD..",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'E'
static xpm_row_t const letter_E  []={
"6 11 2 1",
". c #FFFFFF",
"E c #000000",
"EEEEEE",
"E.....",
"E.....",
"EEEEE.",
"E.....",
"E.....",
"E.....",
"EEEEEE",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'F'
static xpm_row_t const letter_F[] = {
"6 11 2 1",
". c #FFFFFF",
"F c #000000",
"FFFFFF",
"F.....",
"F.....",
"FFFF..",
"F.....",
"F.....",
"F.....",
"F.....",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'G'
static xpm_row_t const letter_G[] = {
"6 11 2 1",
". c #FFFFFF",
"G c #000000",
"..GGG.",
".G...G",
"G.....",
"G.....",
"G..GGG",
"G....G",
".G...G",
"..GGG.",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'H'
static xpm_row_t const letter_H[] = {
"6 11 2 1",
". c #FFFFFF",
"H c #000000",
"H....H",
"H....H",
"H....H",
"HHHHHH",
"H....H",
"H....H",
"H....H",
"H....H",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'I'
static xpm_row_t const letter_I[] = {
"6 11 2 1",
". c #FFFFFF",
"I c #000000",
"IIIIII",
"..I...",
"..I...",
"..I...",
"..I...",
"..I...",
"..I...",
"IIIIII",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'J'
static xpm_row_t const letter_J[] = {
"6 11 2 1",
". c #FFFFFF",
"J c #000000",
".JJJJJ",
".....J",
".....J",
".....J",
".....J",
".....J",
".....J",
"JJJJJ.",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'K'
static xpm_row_t const letter_K[] = {
"6 11 2 1",
". c #FFFFFF",
"K c #000000",
"K....K",
"K...K.",
"K..K..",
"K.K...",
"KKK...",
"K..K..",
"K...K.",
"K....K",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'L'
static xpm_row_t const letter_L[] = {
"6 11 2 1",
". c #FFFFFF",
"L c #000000",
"L.....",
"L.....",
"L.....",
"L.....",
"L.....",
"L.....",
"L.....",
"LLLLLL",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'M'
static xpm_row_t const letter_M[] = {
"6 11 2 1",
". c #FFFFFF",
"M c #000000",
"MM..MM",
"MM..MM",
"M.MM.M",
"M.MM.M",
"M....M",
"M....M",
"M....M",
"M....M",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'N'
static xpm_row_t const letter_N[] = {
"6 11 2 1",
". c #FFFFFF",
"N c #000000",
"NN...N",
"NN...N",
"N.N..N",
"N.N..N",
"N..N.N",
"N..N.N",
"N...NN",
"N...NN",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'O'
static xpm_row_t const letter_O[] = {
"6 11 2 1",
". c #FFFFFF",
"O c #000000",
"..OO..",
".O..O.",
"O....O",
"O....O",
"O....O",
"O....O",
".O..O.",
"..OO..",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'P'
static xpm_row_t const letter_P[] = {
"6 11 2 1",
". c #FFFFFF",
"P c #000000",
"PPPPP.",
"P....P",
"P....P",
"P....P",
"PPPPP.",
"P.....",
"P.....",
"P.....",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'Q'
static xpm_row_t const letter_Q[] = {
"6 11 2 1",
". c #FFFFFF",
"Q c #000000",
"..QQ..",
".Q..Q.",
"Q....Q",
"Q....Q",
"Q....Q",
"Q..Q.Q",
".Q..Q.",
"..QQ.Q",
".....Q",
"......",
"......"};

//! XPM of the uppercase letter 'R'
static xpm_row_t const letter_R[] = {
"6 11 2 1",
". c #FFFFFF",
"R c #000000",
"RRRRR.",
"R....R",
"R....R",
"R....R",
"RRRRR.",
"R..R..",
"R...R.",
"R....R",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'S'
static xpm_row_t const letter_S[] = {
"6 11 2 1",
". c #FFFFFF",
"S c #000000",
".SSSS.",
"S....S",
"S.....",
".SS...",
"...SS.",
".....S",
"S....S",
".SSSS.",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'T'
static xpm_row_t const letter_T[] = {
"6 11 2 1",
". c #FFFFFF",
"T c #000000",
"TTTTTT",
"..T...",
"..T...",
"..T...",
"..T...",
"..T...",
"..T...",
"..T...",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'U'
static xpm_row_t const letter_U[] = {
"6 11 2 1",
". c #FFFFFF",
"U c #000000",
"U....U",
"U....U",
"U....U",
"U....U",
"U....U",
"U....U",
"U....U",
".UUUU.",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'V'
static xpm_row_t const letter_V[] = {
"6 11 2 1",
". c #FFFFFF",
"V c #000000",
"V....V",
"V....V",
"V...V.",
".V..V.",
".V.V..",
".V.V..",
"..V...",
"..V...",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'W'
static xpm_row_t const letter_W[] = {
"6 11 2 1",
". c #FFFFFF",
"W c #000000",
"W....W",
"W....W",
"W....W",
"W....W",
"W.WW.W",
"W.WW.W",
"WW..WW",
"WW..WW",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'X'
static xpm_row_t const letter_X[] = {
"6 11 2 1",
". c #FFFFFF",
"X c #000000",
"X....X",
"X....X",
".X..X.",
"..XX..",
"..XX..",
".X..X.",
"X....X",
"X....X",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'Y'
static xpm_row_t const letter_Y[] = {
"6 11 2 1",
". c #FFFFFF",
"Y c #000000",
"Y....Y",
"Y....Y",
".Y..Y.",
".Y.Y..",
"..Y...",
"..Y...",
"..Y...",
"..Y...",
"......",
"......",
"......"};

//! XPM of the uppercase letter 'Z'
static xpm_row_t const letter_Z[] = {
"6 11 2 1",
". c #FFFFFF",
"Z c #000000",
"ZZZZZZ",
".....Z",
"....Z.",
"...Z..",
"..Z...",
".Z....",
"Z.....",
"ZZZZZZ",
"......",
"......",
"......"};

// -------------------------------------------

//! XPM of the lowercase letter 'a'
static xpm_row_t const letter_a[] = {
"6 11 2 1",
". c #FFFFFF",
"a c #000000",
"......",
"......",
".aaaa.",
".....a",
".aaaaa",
"a....a",
"a....a",
".aaaaa",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'b'
static xpm_row_t const letter_b[] = {
"6 11 2 1",
". c #FFFFFF",
"b c #000000",
"b.....",
"b.....",
"b.....",
"bbbbb.",
"b....b",
"b....b",
"b....b",
"bbbbb.",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'c'
static xpm_row_t const letter_c[]= {
"6 11 2 1",
". c #FFFFFF",
"c c #000000",
"......",
"......",
".cccc.",
"c....c",
"c.....",
"c.....",
"c....c",
".cccc.",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'd'
static xpm_row_t const letter_d[]={
"6 11 2 1",
". c #FFFFFF",
"d c #000000",
".....d",
".....d",
".....d",
".ddddd",
"d....d",
"d....d",
"d....d",
".ddddd",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'e'
static xpm_row_t const letter_e[]={
"6 11 2 1",
". c #FFFFFF",
"e c #000000",
"......",
"......",
".eeee.",
"e....e",
"eeeeee",
"e.....",
"e....e",
".eeee.",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'f'
static xpm_row_t const letter_f[] = {
"6 11 2 1",
". c #FFFFFF",
"f c #000000",
"..ffff",
".f....",
".f....",
"fffff.",
".f....",
".f....",
".f....",
".f....",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'g'
static xpm_row_t const letter_g[] = {
"6 11 2 1",
". c #FFFFFF",
"g c #000000",
"......",
"......",
".ggg.g",
"g...g.",
"g...g.",
".ggg..",
"g.....",
".gggg.",
"g....g",
"g....g",
".gggg."};

//! XPM of the lowercase letter 'h'
static xpm_row_t const letter_h[] = {
"6 11 2 1",
". c #FFFFFF",
"h c #000000",
"h.....",
"h.....",
"h.....",
"hhhhh.",
"h....h",
"h....h",
"h....h",
"h....h",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'i'
static xpm_row_t const letter_i[] = {
"6 11 2 1",
". c #FFFFFF",
"i c #000000",
"......",
"..i...",
"......",
".ii...",
"..i...",
"..i...",
"..i...",
"iiiiii",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'j'
static xpm_row_t const letter_j[] = {
"6 11 2 1",
". c #FFFFFF",
"j c #000000",
"......",
"....j.",
"......",
"..jjjj",
"....j.",
"....j.",
"....j.",
"....j.",
"....j.",
"jjjj..",
"......"};

//! XPM of the lowercase letter 'k'
static xpm_row_t const letter_k[] = {
"6 11 2 1",
". c #FFFFFF",
"k c #000000",
"......",
"k.....",
"k....k",
"k...k.",
"k..k..",
"kkkk..",
"k...k.",
"k....k",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'l'
static xpm_row_t const letter_l[] = {
"6 11 2 1",
". c #FFFFFF",
"l c #000000",
"lll...",
"..l...",
"..l...",
"..l...",
"..l...",
"..l...",
"..l..l",
"...ll.",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'm'
static xpm_row_t const letter_m[] = {
"6 11 2 1",
". c #FFFFFF",
"m c #000000",
"......",
"......",
"mmm.m.",
"m..m.m",
"m..m.m",
"m..m.m",
"m..m.m",
"m..m.m",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'n'
static xpm_row_t const letter_n[] = {
"6 11 2 1",
". c #FFFFFF",
"n c #000000",
"......",
"......",
"nnnnn.",
"n....n",
"n....n",
"n....n",
"n....n",
"n....n",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'o'
static xpm_row_t const letter_o[] = {
"6 11 2 1",
". c #FFFFFF",
"o c #000000",
"......",
"......",
".oooo.",
"o....o",
"o....o",
"o....o",
"o....o",
".oooo.",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'p'
static xpm_row_t const letter_p[] = {
"6 11 2 1",
". c #FFFFFF",
"p c #000000",
"......",
"......",
"ppppp.",
"p....p",
"p....p",
"p....p",
"p....p",
"ppppp.",
"p.....",
"p.....",
"p....."};

//! XPM of the lowercase letter 'q'
static xpm_row_t const letter_q[] = {
"6 11 2 1",
". c #FFFFFF",
"q c #000000",
"......",
"......",
".qqqqq",
"q....q",
"q....q",
"q....q",
"q....q",
".qqqqq",
".....q",
".....q",
".....q"};

//! XPM of the lowercase letter 'r'
static xpm_row_t const letter_r[] = {
"6 11 2 1",
". c #FFFFFF",
"r c #000000",
"......",
"......",
"r.rrr.",
"rr...r",
"r.....",
"r.....",
"r.....",
"r.....",
"......",
"......",
"......"};

//! XPM of the lowercase letter 's'
static xpm_row_t const letter_s[] = {
"6 11 2 1",
". c #FFFFFF",
"s c #000000",
"......",
"......",
".sssss",
"s.....",
".ss...",
"...ss.",
".....s",
"sssss.",
"......",
"......",
"......"};

//! XPM of the lowercase letter 't'
static xpm_row_t const letter_t[] = {
"6 11 2 1",
". c #FFFFFF",
"t c #000000",
".t....",
".t....",
"ttttt.",
".t....",
".t....",
".t....",
".t...t",
"..ttt.",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'u'
static xpm_row_t const letter_u[] = {
"6 11 2 1",
". c #FFFFFF",
"u c #000000",
"......",
"......",
"u....u",
"u....u",
"u....u",
"u....u",
"u....u",
".uuuuu",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'v'
static xpm_row_t const letter_v[] = {
"6 11 2 1",
". c #FFFFFF",
"v c #000000",
"......",
"......",
"v....v",
"v...v.",
".v..v.",
".v.v..",
"..v...",
"..v...",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'w'
static xpm_row_t const letter_w[] = {
"6 11 2 1",
". c #FFFFFF",
"w c #000000",
"......",
"......",
"w....w",
"w....w",
"w.w..w",
"w.w..w",
"www.ww",
"ww.ww.",
"w..w..",
"......",
"......"};

//! XPM of the lowercase letter 'x'
static xpm_row_t const letter_x[] = {
"6 11 2 1",
". c #FFFFFF",
"x c #000000",
"......",
"......",
"x...xx",
".x.x..",
"..x...",
"..x...",
".x.x..",
"x...xx",
"......",
"......",
"......"};

//! XPM of the lowercase letter 'y'
static xpm_row_t const letter_y[] = {
"6 11 2 1",
". c #FFFFFF",
"y c #000000",
"......",
"......",
"yy...y",
".y...y",
".y...y",
"..y.y.",
"..y.y.",
"...y..",
"...y..",
"...y..",
"yyy..."};

//! XPM of the lowercase letter 'z'
static xpm_row_t const letter_z[] = {
"6 11 2 1",
". c #FFFFFF",
"z c #000000",
"......",
"......",
"zzzzzz",
"....z.",
"...z..",
"..z...",
".z....",
"zzzzzz",
"......",
"......",
"......"};

// -------------------------------------------

//! XPM of the number 0
static xpm_row_t const number_0[] = {
"6 11 2 1",
". c #FFFFFF",
"0 c #000000",
".0000.",
"0....0",
"0...00",
"0..0.0",
"0.0..0",
"00...0",
"0....0",
".0000.",
"......",
"......",
"......"};

//! XPM of the number 1
static xpm_row_t const number_1[] = {
"6 11 2 1",
". c #FFFFFF",
"1 c #000000",
"..1...",
".11...",
"1.1...",
"..1...",
"..1...",
"..1...",
"..1...",
"111111",
"......",
"......",
"......"};

//! XPM of the number 2
static xpm_row_t const number_2[] = {
"6 11 2 1",
". c #FFFFFF",
"2 c #000000",
".2222.",
"2....2",
".....2",
"....2.",
"...2..",
"..2...",
".2....",
"222222",
"......",
"......",
"......"};

//! XPM of the number 3
static xpm_row_t const number_3[] = {
"6 11 2 1",
". c #FFFFFF",
"3 c #000000",
".3333.",
"3....3",
".....3",
"..333.",
".....3",
".....3",
"3....3",
".3333.",
"......",
"......",
"......"};

//! XPM of the number 4
static xpm_row_t const number_4[] = {
"6 11 2 1",
". c #FFFFFF",
"4 c #000000",
"....4.",
"...44.",
"..4.4.",
".4..4.",
"4...4.",
"444444",
"....4.",
"....4.",
"......",
"......",
"......"};

//! XPM of the number 5
static xpm_row_t const number_5[] = {
"6 11 2 1",
". c #FFFFFF",
"5 c #000000",
"555555",
"5.....",
"5.....",
"55555.",
".....5",
".....5",
"5....5",
".5555.",
"......",
"......",
"......"};

//! XPM of the number 6
static xpm_row_t const number_6[] = {
"6 11 2 1",
". c #FFFFFF",
"6 c #000000",
"..666.",
".6....",
"6.....",
"66666.",
"6....6",
"6....6",
"6....6",
".6666.",
"......",
"......",
"......"};

//! XPM of the number 7
static xpm_row_t const number_7[] = {
"6 11 2 1",
". c #FFFFFF",
"7 c #000000",
"777777",
".....7",
"....7.",
"....7.",
"...7..",
"...7..",
"..7...",
"..7...",
"......",
"......",
"......"};

//! XPM of the number 8
static xpm_row_t const number_8[] = {
"6 11 2 1",
". c #FFFFFF",
"8 c #000000",
".8888.",
"8....8",
"8....8",
".8888.",
"8....8",
"8....8",
"8....8",
".8888.",
"......",
"......",
"......"};

//! XPM of the number 9
static xpm_row_t const number_9[] = {
"6 11 2 1",
". c #FFFFFF",
"9 c #000000",
".9999.",
"9....9",
"9....9",
"9....9",
".99999",
".....9",
"....9.",
".999..",
"......",
"......",
"......"};

// -------------------------------------------

//! XPM of the character SPACE ' '
static xpm_row_t const char_space[] = {
"6 11 1 1",
". c #FFFFFF",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"......"};

//! XPM of the character '!'
static xpm_row_t const char_exclamation[] = {
"6 11 2 1",
". c #FFFFFF",
"! c #000000",
"......",
"..!...",
"..!...",
"..!...",
"..!...",
"..!...",
"......",
"..!...",
"......",
"......",
"......"};

//! XPM of the character "
static xpm_row_t const char_quote[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
".#..#.",
".#..#.",
".#..#.",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"......"};

//! XPM of the character '#'
static xpm_row_t const char_hash[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
".#.#..",
".#.#..",
"#####.",
".#.#,.",
".#.#..",
"#####.",
".#.#..",
".#.#..",
"......",
"......",
"......"};

//! XPM of the character '$'
static xpm_row_t const char_dollar[] = {
"6 11 2 1",
". c #FFFFFF",
". c #000000",
"..$...",
".$$$$$",
"$.$...",
"$.$...",
".$$$$.",
"..$..$",
"..$..$",
"$$$$$.",
"..$...",
"......",
"......"};

//! XPM of the character '%'
static xpm_row_t const char_percent[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
".#..#.",
"#.##..",
"#.##..",
".##...",
"..#.#.",
".#.#.#",
".#.#.#",
"#...#.",
"......",
"......",
"......"};

//! XPM of the character '&'
static xpm_row_t const char_ampersand[] = {
"6 11 2 1",
". c #FFFFFF",
"& c #000000",
".&&...",
"&..&..",
"&..&..",
".&&..&",
"&..&.&",
"&...&.",
"&...&.",
".$$$.&",
"......",
"......",
"......"};

//! XPM of the character '
static xpm_row_t const char_apostrophe[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"..#...",
"..#...",
"..#...",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"......"};

//! XPM of the character '('
static xpm_row_t const char_l_parenthesis[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"....#.",
"...#..",
"..#...",
"..#...",
"..#...",
"..#...",
"...#..",
"....#.",
"......",
"......",
"......"};

//! XPM of the character ')'
static xpm_row_t const char_r_parenthesis[] = {
"6 11 2 1",
". c #FFFFFF",
". c #000000",
".#....",
"..#...",
"...#..",
"...#..",
"...#..",
"...#..",
"..#...",
".#....",
"......",
"......",
"......"};

//! XPM of the character '*'
static xpm_row_t const char_asterisk[] = {
"6 11 2 1",
". c #FFFFFF",
"* c #000000",
"......",
"......",
"..*...",
"*.*.*.",
".***..",
"*.*.*.",
"..*...",
"......",
"......",
"......",
"......"};

//! XPM of the character '+'
static xpm_row_t const char_plus[] = {
"6 11 2 1",
". c #FFFFFF",
"+ c #000000",
"......",
"......",
"..+...",
"..+...",
"+++++.",
"..+...",
"..+...",
"......",
"......",
"......",
"......"};

//! XPM of the character ','
static xpm_row_t const char_comma[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"......",
"......",
"......",
"......",
"......",
"......",
"...#..",
"...#..",
"..#...",
".#....",
"......"};

//! XPM of the character '-'
static xpm_row_t const char_hyphen[] = {
"6 11 2 1",
". c #FFFFFF",
"- c #000000",
"......",
"......",
"......",
"......",
"......",
"------",
"......",
"......",
"......",
"......",
"......"};

//! XPM of the character '.'
static xpm_row_t const char_period[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"......",
"......",
"......",
"......",
"......",
"......",
".##...",
".##...",
"......",
"......",
"......"};

//! XPM of the character '/'
static xpm_row_t const char_slash[] = {
"6 11 2 1",
". c #FFFFFF",
"/ c #000000",
"...../",
"..../.",
".../..",
".../..",
"../...",
"../...",
"./....",
"/.....",
"......",
"......",
"......"};

//! XPM of the character ':'
static xpm_row_t const char_colon[] = {
"6 11 2 1",
". c #FFFFFF",
": c #000000",
"......",
"......",
"..::..",
"..::..",
"......",
"......",
"..::..",
"..::..",
"......",
"......",
"......"};

//! XPM of the character ';'
static xpm_row_t const char_semicolon[] = {
"6 11 2 1",
". c #FFFFFF",
"; c #000000",
"......",
"......",
"......",
"..;;..",
"..;;..",
"......",
"...;..",
"...;..",
"..;...",
".;....",
"......"};

//! XPM of the character '<'
static xpm_row_t const char_less_than[] = {
"6 11 2 1",
". c #FFFFFF",
"< c #000000",
"......",
"......",
"....<<",
"..<<..",
"<<....",
"..<<..",
"....<<",
"......",
"......",
"......",
"......"};

//! XPM of the character '='
static xpm_row_t const char_equal[] = {
"6 11 2 1",
". c #FFFFFF",
"= c #000000",
"......",
"......",
"......",
"======",
"......",
"======",
"......",
"......",
"......",
"......",
"......"};

//! XPM of the character '>'
static xpm_row_t const char_greater_than[] = {
"6 11 2 1",
". c #FFFFFF",
"> c #000000",
"......",
"......",
">>....",
"..>>..",
"....>>",
"..>>..",
">>....",
"......",
"......",
"......",
"......"};

//! XPM of the character '?'
static xpm_row_t const char_question[] = {
"6 11 2 1",
". c #FFFFFF",
"? c #000000",
".????.",
"?....?",
"....?.",
"...?..",
"...?..",
"......",
"..??..",
"..??..",
"......",
"......",
"......"};

//! XPM of the character '@'
static xpm_row_t const char_at[] = {
"6 11 2 1",
". c #FFFFFF",
"@ c #000000",
"..@@..",
".@..@.",
"@.@@.@",
"@@.@.@",
"@@.@.@",
"@.@@@.",
".@....",
"..@@@@",
"......",
"......",
"......"};

//! XPM of the character '['
static xpm_row_t const char_l_s_bracket[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
".####.",
".#....",
".#....",
".#....",
".#....",
".#....",
".#....",
".####.",
"......",
"......",
"......"};

//! XPM of the character '\'
static xpm_row_t const char_back_slash[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"#.....",
".#....",
"..#...",
"..#...",
"...#..",
"...#..",
"....#.",
".....#",
"......",
"......",
"......"};

//! XPM of the character ']'
static xpm_row_t const char_r_s_bracket[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
".####.",
"....#.",
"....#.",
"....#.",
"....#.",
"....#.",
"....#.",
".####.",
"......",
"......",
"......"};

//! XPM of the character '^'
static xpm_row_t const char_caret[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"..#...",
".#.#..",
".#.#..",
"#...#.",
"#...#.",
"......",
"......",
"......",
"......",
"......",
"......"};

//! XPM of the character '_'
static xpm_row_t const char_underscore[] = {
"6 11 2 1",
". c #FFFFFF",
"_ c #000000",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"______",
"......",
"......"};

//! XPM of the character '`'
static xpm_row_t const char_grave_accent[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"#.....",
".#....",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"......",
"......"};

//! XPM of the character '{'
static xpm_row_t const char_l_c_bracket[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"......",
"....##",
"...#..",
"...#..",
".##...",
"...#..",
"...#..",
"....##",
"......",
"......",
"......"};

//! XPM of the character '|'
static xpm_row_t const char_v_bar[] = {
"6 11 2 1",
". c #FFFFFF",
"| c #000000",
"..|...",
"..|...",
"..|...",
"..|...",
"..|...",
"..|...",
"..|...",
"..|...",
"......",
"......",
"......"};

//! XPM of the character '}'
static xpm_row_t const char_r_c_bracket[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"......",
"##....",
"..#...",
"..#...",
"...##.",
"..#...",
"..#...",
"##....",
"......",
"......",
"......"};

//! XPM of the character '~'
static xpm_row_t const char_tilde[] = {
"6 11 2 1",
". c #FFFFFF",
"# c #000000",
"......",
"......",
"......",
".##..#",
"#..##.",
"......",
"......",
"......",
"......",
"......",
"......"};

#endif
