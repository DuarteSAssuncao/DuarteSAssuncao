/**
 * @file debug.c
 * @brief Definition of min(), max() and memdump()
 * @author T17_G1
 * @date 27/05/2024
 */

#include "debug.h"
#include "extra_utils.h"
#include <string.h>
#include <stdio.h>

#ifndef min
    #define min(a,b) (((a) < (b)) ? (a) : (b))
    #define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

/**
 * @brief Write contents of memory to file
 * @param FILE * file : pointer to file to write on
 * @param const void *base : where to start
 * @param size_t size : number of rows * number of columns
 * @param size_t cols : number of columns
 * @return void
 */
void (memdump)(FILE * file, const void *base, size_t size, size_t cols) {
    const uint8_t *ptr = base;
    size_t rows = size / cols;

    char rangestr[128], range_format[] = "% 99zus :", header_format[] = "% 07s : Bytes\n";
    size_t digits = 1, temp = size;
    while ((temp /= 10) != 0) ++digits;
    size_t rangestrsize = max(2 * digits + 1, strlen("Range"));
    sprintf(range_format, "%% %zus :", rangestrsize);
    sprintf(header_format, "%% %zus : Bytes\n", rangestrsize);

    fprintf(file, header_format, "Range");
    for (size_t i = 0; i < rows; ++i) {
        sprintf(rangestr, "%zu-%zu", cols * i, cols * i + cols - 1);
        fprintf(file, range_format, rangestr);
        for (size_t j = 0; j < cols; ++j)
            fprintf(file, " %02x", *(ptr + cols*i + j));
        fprintf(file, "\n");
    }

    if (size % cols == 0) {
        fprintf(file, "\n");
        return;
    }

    sprintf(rangestr, "%zu-%zu", cols * rows, cols * rows + size % cols - 1);
    fprintf(file, range_format, rangestr);
    for (size_t j = 0; j < size % cols; ++j)
        fprintf(file, " %02x", *(ptr + cols*rows + j));
    fprintf(file, "\n");
}
