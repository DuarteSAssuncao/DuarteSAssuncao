/**
 * @file debug.h
 * @brief Declaration of functions for debug
 * @author T17_G1
 * @date 02/06/2024
 */

#ifndef LCOM_PROJ_DEBUG_H
#define LCOM_PROJ_DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include "ansi_colors.h"

#ifdef PROJ_RELEASE
    #undef DEBUG
#endif

/**
 * @brief Prints the bytes in the specified memory range.
 * @param file File to print to.
 * @param base Address of first byte to be printed.
 * @param size Amount of bytes to be printed.
 * @param cols Amount of bytes to be printed per line.
 */
void (memdump)(FILE * file, const void *base, size_t size, size_t cols);

#ifdef DEBUG
#   include <stdio.h>
#   include <string.h>
#   include <errno.h>
#   define debugout stderr
#   define DEBUG_PRINTF(...) (fprintf(debugout, "%s: %d: %s: ", __FILE__, __LINE__, __func__), fprintf(debugout, __VA_ARGS__)) /**< @brief Only exists if DEBUG is defined */

    /** @brief DEBUG_PRINTF but "verbose" (prints the file, line and function before __VA_ARGS__) */
#   define DEBUG_PRINTFV(file_color,line_color,func_color,...) (fprintf(debugout, ANSI_FG(file_color) "%s: " ANSI_FG(line_color) "%d: " ANSI_FG(func_color) "%s: " ANSI_RESET,__FILE__,__LINE__,__func__),fprintf(debugout, __VA_ARGS__))
#   define DEBUG_WARNV(...) DEBUG_PRINTFV(214,130,214,__VA_ARGS__)
#   define DEBUG_ERRORV(...) DEBUG_PRINTFV(160,124,160,__VA_ARGS__)
#   define DEBUG_PERRORV(str) DEBUG_ERRORV("%s: %s\n", str, strerror(errno))
#   define DEBUG_INFOV(...) DEBUG_PRINTFV(45,37,45,__VA_ARGS__)
#   define DEBUG_SUCCESSV(...) DEBUG_PRINTFV(28,22,28,__VA_ARGS__)
#   define DEBUG_MEMDUMP(base, size, cols) memdump(debugout, base, size, cols) /**< @brief Only exists if DEBUG is defined */
#else
#   define DEBUG_PRINTF(...)
#   define DEBUG_PRINTFV(...)
#   define DEBUG_WARNV(...)
#   define DEBUG_ERRORV(...)
#   define DEBUG_PERRORV(...)
#   define DEBUG_INFOV(...)
#   define DEBUG_SUCCESSV(...)
#   define DEBUG_MEMDUMP(...)
#endif

/**
 * @brief Debug macro for more in-depth/verbose info.
 * This is to separate debug info that floods the entire terminal from the small debug info.
 * Every debug macro that ends with 2 is part of DEBUG2
 */
#ifdef DEBUG2
#   define DEBUG_PRINTF2(...) DEBUG_PRINTF(__VA_ARGS__)
#else
#   define DEBUG_PRINTF2(...)
#endif

/**
 * @brief A common thing you do in C is call a function and check if its return
 * value is invalid, and, if it is, you print an error message and return some error value.
 * That's exactly what this macro helps you do in just one line.
 * The error is printed as "$file: line $line: $expr: $error_desc".
 * @param expr The expression to evaluate (e.g. 'file = fopen("/root")' or 'fclose(file)')
 * @param cmp If (($expr) $cmp) is true, it's considered an error (e.g. cmp = '== NULL' means error if NULL)
 * @param error_desc A description of the error that will be printed (e.g. 'strerror(errno)')
 * @param error_retv The value to return in case of error.
 * @param error_actions Statements to be executed before returning error_retv.
 * @example
 * FILE *file;
 * TRY(file = fopen("/root"), ==NULL, strerror(errno), 1,);
 * 
 * Is equivalent to:
 * 
 * FILE *file = fopen("/root");
 * if (file == NULL) {
 *     DEBUG_PRINTF("%s: line %d: file = fopen(\"/root\"): %s", __FILE__, __LINE__, strerror(errno));
 *     return 1;
 * }
 */
#define TRY(expr, cmp, error_desc, error_retv, error_actions) {\
    if ((expr) cmp) {\
        DEBUG_PRINTF("%s: line %d: " #expr ": %s\n", __FILE__, __LINE__, error_desc);\
        error_actions\
        return error_retv;\
    }\
}\

#endif /* LCOM_PROJ_DEBUG_H */
