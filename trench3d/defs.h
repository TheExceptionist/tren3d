/*
========================================================
File: defs.h
Author: Kenneth Stepney
Purpose: Provides basic utilities to all components of this program

========================================================
*/

#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>
#include <stdio.h>

#include "e_math.h"

#define TRUE 1
#define FALSE 0

#define DEBUG

namespace e_std
{
    typedef uint8_t e_byte;
    typedef uint16_t e_halfword;
    typedef uint32_t e_word;
    typedef uint64_t e_doubleword;

    typedef int8_t e_int8;
    typedef int16_t e_int16;
    typedef int32_t e_int32;
    typedef int64_t e_int64;

    typedef const char* e_str;
    typedef e_byte e_bool;

    typedef struct color_s color_t;

    struct color_s 
    {
        e_byte a;
        e_byte r;
        e_byte g;
        e_byte b;

        color_t& operator/=(int value)
        {
            r /= value;
            g /= value;
            b /= value;

            return *this;
        }
    };

}

const e_std::color_t RED = {0xFF, 0xFF, 0, 0};
const e_std::color_t BLUE = {0xFF, 0, 0, 0xFF};
const e_std::color_t GREEN = {0xFF, 0, 0xFF, 0};
const e_std::color_t GRAY = {0xFF, 0xd3, 0xd3, 0xd3};
const e_std::color_t DARK_BLUE = {0xFF, 0, 0x33, 0x66};
const e_std::color_t BLACK = {0xFF, 0, 0, 0};

#endif
