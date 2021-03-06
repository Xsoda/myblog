#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <crtdbg.h>

typedef struct _huff_sym_s {
    unsigned int code;
    unsigned int bits;
} huff_sym_t;

huff_sym_t huff_sym[] = {
    { 0x1ff8, 13 },
    { 0x7fffd8, 23 },
    { 0xfffffe2, 28 },
    { 0xfffffe3, 28 },
    { 0xfffffe4, 28 },
    { 0xfffffe5, 28 },
    { 0xfffffe6, 28 },
    { 0xfffffe7, 28 },
    { 0xfffffe8, 28 },
    { 0xffffea, 24 },
    { 0x3ffffffc, 30 },
    { 0xfffffe9, 28 },
    { 0xfffffea, 28 },
    { 0x3ffffffd, 30 },
    { 0xfffffeb, 28 },
    { 0xfffffec, 28 },
    { 0xfffffed, 28 },
    { 0xfffffee, 28 },
    { 0xfffffef, 28 },
    { 0xffffff0, 28 },
    { 0xffffff1, 28 },
    { 0xffffff2, 28 },
    { 0x3ffffffe, 30 },
    { 0xffffff3, 28 },
    { 0xffffff4, 28 },
    { 0xffffff5, 28 },
    { 0xffffff6, 28 },
    { 0xffffff7, 28 },
    { 0xffffff8, 28 },
    { 0xffffff9, 28 },
    { 0xffffffa, 28 },
    { 0xffffffb, 28 },
    { 0x14, 6 },
    { 0x3f8, 10 },
    { 0x3f9, 10 },
    { 0xffa, 12 },
    { 0x1ff9, 13 },
    { 0x15, 6 },
    { 0xf8, 8 },
    { 0x7fa, 11 },
    { 0x3fa, 10 },
    { 0x3fb, 10 },
    { 0xf9, 8 },
    { 0x7fb, 11 },
    { 0xfa, 8 },
    { 0x16, 6 },
    { 0x17, 6 },
    { 0x18, 6 },
    { 0x0, 5 },
    { 0x1, 5 },
    { 0x2, 5 },
    { 0x19, 6 },
    { 0x1a, 6 },
    { 0x1b, 6 },
    { 0x1c, 6 },
    { 0x1d, 6 },
    { 0x1e, 6 },
    { 0x1f, 6 },
    { 0x5c, 7 },
    { 0xfb, 8 },
    { 0x7ffc, 15 },
    { 0x20, 6 },
    { 0xffb, 12 },
    { 0x3fc, 10 },
    { 0x1ffa, 13 },
    { 0x21, 6 },
    { 0x5d, 7 },
    { 0x5e, 7 },
    { 0x5f, 7 },
    { 0x60, 7 },
    { 0x61, 7 },
    { 0x62, 7 },
    { 0x63, 7 },
    { 0x64, 7 },
    { 0x65, 7 },
    { 0x66, 7 },
    { 0x67, 7 },
    { 0x68, 7 },
    { 0x69, 7 },
    { 0x6a, 7 },
    { 0x6b, 7 },
    { 0x6c, 7 },
    { 0x6d, 7 },
    { 0x6e, 7 },
    { 0x6f, 7 },
    { 0x70, 7 },
    { 0x71, 7 },
    { 0x72, 7 },
    { 0xfc, 8 },
    { 0x73, 7 },
    { 0xfd, 8 },
    { 0x1ffb, 13 },
    { 0x7fff0, 19 },
    { 0x1ffc, 13 },
    { 0x3ffc, 14 },
    { 0x22, 6 },
    { 0x7ffd, 15 },
    { 0x3, 5 },
    { 0x23, 6 },
    { 0x4, 5 },
    { 0x24, 6 },
    { 0x5, 5 },
    { 0x25, 6 },
    { 0x26, 6 },
    { 0x27, 6 },
    { 0x6, 5 },
    { 0x74, 7 },
    { 0x75, 7 },
    { 0x28, 6 },
    { 0x29, 6 },
    { 0x2a, 6 },
    { 0x7, 5 },
    { 0x2b, 6 },
    { 0x76, 7 },
    { 0x2c, 6 },
    { 0x8, 5 },
    { 0x9, 5 },
    { 0x2d, 6 },
    { 0x77, 7 },
    { 0x78, 7 },
    { 0x79, 7 },
    { 0x7a, 7 },
    { 0x7b, 7 },
    { 0x7ffe, 15 },
    { 0x7fc, 11 },
    { 0x3ffd, 14 },
    { 0x1ffd, 13 },
    { 0xffffffc, 28 },
    { 0xfffe6, 20 },
    { 0x3fffd2, 22 },
    { 0xfffe7, 20 },
    { 0xfffe8, 20 },
    { 0x3fffd3, 22 },
    { 0x3fffd4, 22 },
    { 0x3fffd5, 22 },
    { 0x7fffd9, 23 },
    { 0x3fffd6, 22 },
    { 0x7fffda, 23 },
    { 0x7fffdb, 23 },
    { 0x7fffdc, 23 },
    { 0x7fffdd, 23 },
    { 0x7fffde, 23 },
    { 0xffffeb, 24 },
    { 0x7fffdf, 23 },
    { 0xffffec, 24 },
    { 0xffffed, 24 },
    { 0x3fffd7, 22 },
    { 0x7fffe0, 23 },
    { 0xffffee, 24 },
    { 0x7fffe1, 23 },
    { 0x7fffe2, 23 },
    { 0x7fffe3, 23 },
    { 0x7fffe4, 23 },
    { 0x1fffdc, 21 },
    { 0x3fffd8, 22 },
    { 0x7fffe5, 23 },
    { 0x3fffd9, 22 },
    { 0x7fffe6, 23 },
    { 0x7fffe7, 23 },
    { 0xffffef, 24 },
    { 0x3fffda, 22 },
    { 0x1fffdd, 21 },
    { 0xfffe9, 20 },
    { 0x3fffdb, 22 },
    { 0x3fffdc, 22 },
    { 0x7fffe8, 23 },
    { 0x7fffe9, 23 },
    { 0x1fffde, 21 },
    { 0x7fffea, 23 },
    { 0x3fffdd, 22 },
    { 0x3fffde, 22 },
    { 0xfffff0, 24 },
    { 0x1fffdf, 21 },
    { 0x3fffdf, 22 },
    { 0x7fffeb, 23 },
    { 0x7fffec, 23 },
    { 0x1fffe0, 21 },
    { 0x1fffe1, 21 },
    { 0x3fffe0, 22 },
    { 0x1fffe2, 21 },
    { 0x7fffed, 23 },
    { 0x3fffe1, 22 },
    { 0x7fffee, 23 },
    { 0x7fffef, 23 },
    { 0xfffea, 20 },
    { 0x3fffe2, 22 },
    { 0x3fffe3, 22 },
    { 0x3fffe4, 22 },
    { 0x7ffff0, 23 },
    { 0x3fffe5, 22 },
    { 0x3fffe6, 22 },
    { 0x7ffff1, 23 },
    { 0x3ffffe0, 26 },
    { 0x3ffffe1, 26 },
    { 0xfffeb, 20 },
    { 0x7fff1, 19 },
    { 0x3fffe7, 22 },
    { 0x7ffff2, 23 },
    { 0x3fffe8, 22 },
    { 0x1ffffec, 25 },
    { 0x3ffffe2, 26 },
    { 0x3ffffe3, 26 },
    { 0x3ffffe4, 26 },
    { 0x7ffffde, 27 },
    { 0x7ffffdf, 27 },
    { 0x3ffffe5, 26 },
    { 0xfffff1, 24 },
    { 0x1ffffed, 25 },
    { 0x7fff2, 19 },
    { 0x1fffe3, 21 },
    { 0x3ffffe6, 26 },
    { 0x7ffffe0, 27 },
    { 0x7ffffe1, 27 },
    { 0x3ffffe7, 26 },
    { 0x7ffffe2, 27 },
    { 0xfffff2, 24 },
    { 0x1fffe4, 21 },
    { 0x1fffe5, 21 },
    { 0x3ffffe8, 26 },
    { 0x3ffffe9, 26 },
    { 0xffffffd, 28 },
    { 0x7ffffe3, 27 },
    { 0x7ffffe4, 27 },
    { 0x7ffffe5, 27 },
    { 0xfffec, 20 },
    { 0xfffff3, 24 },
    { 0xfffed, 20 },
    { 0x1fffe6, 21 },
    { 0x3fffe9, 22 },
    { 0x1fffe7, 21 },
    { 0x1fffe8, 21 },
    { 0x7ffff3, 23 },
    { 0x3fffea, 22 },
    { 0x3fffeb, 22 },
    { 0x1ffffee, 25 },
    { 0x1ffffef, 25 },
    { 0xfffff4, 24 },
    { 0xfffff5, 24 },
    { 0x3ffffea, 26 },
    { 0x7ffff4, 23 },
    { 0x3ffffeb, 26 },
    { 0x7ffffe6, 27 },
    { 0x3ffffec, 26 },
    { 0x3ffffed, 26 },
    { 0x7ffffe7, 27 },
    { 0x7ffffe8, 27 },
    { 0x7ffffe9, 27 },
    { 0x7ffffea, 27 },
    { 0x7ffffeb, 27 },
    { 0xffffffe, 28 },
    { 0x7ffffec, 27 },
    { 0x7ffffed, 27 },
    { 0x7ffffee, 27 },
    { 0x7ffffef, 27 },
    { 0x7fffff0, 27 },
    { 0x3ffffee, 26 }
};

typedef struct _huff_decode_node_s {
    int idx;
    char ending;
    unsigned char sym;
    struct _huff_decode_node_s *child[16];
} huff_decode_node_t;

typedef struct _huff_decode_state_s {
    unsigned char next;
    unsigned char sym;
    unsigned char ending;
} huff_decode_state_t;

huff_decode_state_t decode_state[][16] = {
    {
        { 0x01, 0x00, 0x00 }, { 0x02, 0x00, 0x00 },
        { 0x03, 0x00, 0x00 }, { 0x04, 0x00, 0x00 },
        { 0x05, 0x00, 0x00 }, { 0x06, 0x00, 0x00 },
        { 0x07, 0x00, 0x00 }, { 0x08, 0x00, 0x00 },
        { 0x09, 0x00, 0x00 }, { 0x0a, 0x00, 0x00 },
        { 0x0b, 0x00, 0x00 }, { 0x0c, 0x00, 0x00 },
        { 0x0d, 0x00, 0x00 }, { 0x0e, 0x00, 0x00 },
        { 0x0f, 0x00, 0x00 }, { 0x10, 0x00, 0x00 },
    },
    {
        { 0x00, 0x30, 0x01 }, { 0x00, 0x30, 0x01 },
        { 0x00, 0x30, 0x01 }, { 0x00, 0x30, 0x01 },
        { 0x00, 0x30, 0x01 }, { 0x00, 0x30, 0x01 },
        { 0x00, 0x30, 0x01 }, { 0x00, 0x30, 0x01 },
        { 0x00, 0x31, 0x01 }, { 0x00, 0x31, 0x01 },
        { 0x00, 0x31, 0x01 }, { 0x00, 0x31, 0x01 },
        { 0x00, 0x31, 0x01 }, { 0x00, 0x31, 0x01 },
        { 0x00, 0x31, 0x01 }, { 0x00, 0x31, 0x01 },
    },
    {
        { 0x00, 0x32, 0x01 }, { 0x00, 0x32, 0x01 },
        { 0x00, 0x32, 0x01 }, { 0x00, 0x32, 0x01 },
        { 0x00, 0x32, 0x01 }, { 0x00, 0x32, 0x01 },
        { 0x00, 0x32, 0x01 }, { 0x00, 0x32, 0x01 },
        { 0x00, 0x61, 0x01 }, { 0x00, 0x61, 0x01 },
        { 0x00, 0x61, 0x01 }, { 0x00, 0x61, 0x01 },
        { 0x00, 0x61, 0x01 }, { 0x00, 0x61, 0x01 },
        { 0x00, 0x61, 0x01 }, { 0x00, 0x61, 0x01 },
    },
    {
        { 0x00, 0x63, 0x01 }, { 0x00, 0x63, 0x01 },
        { 0x00, 0x63, 0x01 }, { 0x00, 0x63, 0x01 },
        { 0x00, 0x63, 0x01 }, { 0x00, 0x63, 0x01 },
        { 0x00, 0x63, 0x01 }, { 0x00, 0x63, 0x01 },
        { 0x00, 0x65, 0x01 }, { 0x00, 0x65, 0x01 },
        { 0x00, 0x65, 0x01 }, { 0x00, 0x65, 0x01 },
        { 0x00, 0x65, 0x01 }, { 0x00, 0x65, 0x01 },
        { 0x00, 0x65, 0x01 }, { 0x00, 0x65, 0x01 },
    },
    {
        { 0x00, 0x69, 0x01 }, { 0x00, 0x69, 0x01 },
        { 0x00, 0x69, 0x01 }, { 0x00, 0x69, 0x01 },
        { 0x00, 0x69, 0x01 }, { 0x00, 0x69, 0x01 },
        { 0x00, 0x69, 0x01 }, { 0x00, 0x69, 0x01 },
        { 0x00, 0x6f, 0x01 }, { 0x00, 0x6f, 0x01 },
        { 0x00, 0x6f, 0x01 }, { 0x00, 0x6f, 0x01 },
        { 0x00, 0x6f, 0x01 }, { 0x00, 0x6f, 0x01 },
        { 0x00, 0x6f, 0x01 }, { 0x00, 0x6f, 0x01 },
    },
    {
        { 0x00, 0x73, 0x01 }, { 0x00, 0x73, 0x01 },
        { 0x00, 0x73, 0x01 }, { 0x00, 0x73, 0x01 },
        { 0x00, 0x73, 0x01 }, { 0x00, 0x73, 0x01 },
        { 0x00, 0x73, 0x01 }, { 0x00, 0x73, 0x01 },
        { 0x00, 0x74, 0x01 }, { 0x00, 0x74, 0x01 },
        { 0x00, 0x74, 0x01 }, { 0x00, 0x74, 0x01 },
        { 0x00, 0x74, 0x01 }, { 0x00, 0x74, 0x01 },
        { 0x00, 0x74, 0x01 }, { 0x00, 0x74, 0x01 },
    },
    {
        { 0x00, 0x20, 0x01 }, { 0x00, 0x20, 0x01 },
        { 0x00, 0x20, 0x01 }, { 0x00, 0x20, 0x01 },
        { 0x00, 0x25, 0x01 }, { 0x00, 0x25, 0x01 },
        { 0x00, 0x25, 0x01 }, { 0x00, 0x25, 0x01 },
        { 0x00, 0x2d, 0x01 }, { 0x00, 0x2d, 0x01 },
        { 0x00, 0x2d, 0x01 }, { 0x00, 0x2d, 0x01 },
        { 0x00, 0x2e, 0x01 }, { 0x00, 0x2e, 0x01 },
        { 0x00, 0x2e, 0x01 }, { 0x00, 0x2e, 0x01 },
    },
    {
        { 0x00, 0x2f, 0x01 }, { 0x00, 0x2f, 0x01 },
        { 0x00, 0x2f, 0x01 }, { 0x00, 0x2f, 0x01 },
        { 0x00, 0x33, 0x01 }, { 0x00, 0x33, 0x01 },
        { 0x00, 0x33, 0x01 }, { 0x00, 0x33, 0x01 },
        { 0x00, 0x34, 0x01 }, { 0x00, 0x34, 0x01 },
        { 0x00, 0x34, 0x01 }, { 0x00, 0x34, 0x01 },
        { 0x00, 0x35, 0x01 }, { 0x00, 0x35, 0x01 },
        { 0x00, 0x35, 0x01 }, { 0x00, 0x35, 0x01 },
    },
    {
        { 0x00, 0x36, 0x01 }, { 0x00, 0x36, 0x01 },
        { 0x00, 0x36, 0x01 }, { 0x00, 0x36, 0x01 },
        { 0x00, 0x37, 0x01 }, { 0x00, 0x37, 0x01 },
        { 0x00, 0x37, 0x01 }, { 0x00, 0x37, 0x01 },
        { 0x00, 0x38, 0x01 }, { 0x00, 0x38, 0x01 },
        { 0x00, 0x38, 0x01 }, { 0x00, 0x38, 0x01 },
        { 0x00, 0x39, 0x01 }, { 0x00, 0x39, 0x01 },
        { 0x00, 0x39, 0x01 }, { 0x00, 0x39, 0x01 },
    },
    {
        { 0x00, 0x3d, 0x01 }, { 0x00, 0x3d, 0x01 },
        { 0x00, 0x3d, 0x01 }, { 0x00, 0x3d, 0x01 },
        { 0x00, 0x41, 0x01 }, { 0x00, 0x41, 0x01 },
        { 0x00, 0x41, 0x01 }, { 0x00, 0x41, 0x01 },
        { 0x00, 0x5f, 0x01 }, { 0x00, 0x5f, 0x01 },
        { 0x00, 0x5f, 0x01 }, { 0x00, 0x5f, 0x01 },
        { 0x00, 0x62, 0x01 }, { 0x00, 0x62, 0x01 },
        { 0x00, 0x62, 0x01 }, { 0x00, 0x62, 0x01 },
    },
    {
        { 0x00, 0x64, 0x01 }, { 0x00, 0x64, 0x01 },
        { 0x00, 0x64, 0x01 }, { 0x00, 0x64, 0x01 },
        { 0x00, 0x66, 0x01 }, { 0x00, 0x66, 0x01 },
        { 0x00, 0x66, 0x01 }, { 0x00, 0x66, 0x01 },
        { 0x00, 0x67, 0x01 }, { 0x00, 0x67, 0x01 },
        { 0x00, 0x67, 0x01 }, { 0x00, 0x67, 0x01 },
        { 0x00, 0x68, 0x01 }, { 0x00, 0x68, 0x01 },
        { 0x00, 0x68, 0x01 }, { 0x00, 0x68, 0x01 },
    },
    {
        { 0x00, 0x6c, 0x01 }, { 0x00, 0x6c, 0x01 },
        { 0x00, 0x6c, 0x01 }, { 0x00, 0x6c, 0x01 },
        { 0x00, 0x6d, 0x01 }, { 0x00, 0x6d, 0x01 },
        { 0x00, 0x6d, 0x01 }, { 0x00, 0x6d, 0x01 },
        { 0x00, 0x6e, 0x01 }, { 0x00, 0x6e, 0x01 },
        { 0x00, 0x6e, 0x01 }, { 0x00, 0x6e, 0x01 },
        { 0x00, 0x70, 0x01 }, { 0x00, 0x70, 0x01 },
        { 0x00, 0x70, 0x01 }, { 0x00, 0x70, 0x01 },
    },
    {
        { 0x00, 0x72, 0x01 }, { 0x00, 0x72, 0x01 },
        { 0x00, 0x72, 0x01 }, { 0x00, 0x72, 0x01 },
        { 0x00, 0x75, 0x01 }, { 0x00, 0x75, 0x01 },
        { 0x00, 0x75, 0x01 }, { 0x00, 0x75, 0x01 },
        { 0x00, 0x3a, 0x01 }, { 0x00, 0x3a, 0x01 },
        { 0x00, 0x42, 0x01 }, { 0x00, 0x42, 0x01 },
        { 0x00, 0x43, 0x01 }, { 0x00, 0x43, 0x01 },
        { 0x00, 0x44, 0x01 }, { 0x00, 0x44, 0x01 },
    },
    {
        { 0x00, 0x45, 0x01 }, { 0x00, 0x45, 0x01 },
        { 0x00, 0x46, 0x01 }, { 0x00, 0x46, 0x01 },
        { 0x00, 0x47, 0x01 }, { 0x00, 0x47, 0x01 },
        { 0x00, 0x48, 0x01 }, { 0x00, 0x48, 0x01 },
        { 0x00, 0x49, 0x01 }, { 0x00, 0x49, 0x01 },
        { 0x00, 0x4a, 0x01 }, { 0x00, 0x4a, 0x01 },
        { 0x00, 0x4b, 0x01 }, { 0x00, 0x4b, 0x01 },
        { 0x00, 0x4c, 0x01 }, { 0x00, 0x4c, 0x01 },
    },
    {
        { 0x00, 0x4d, 0x01 }, { 0x00, 0x4d, 0x01 },
        { 0x00, 0x4e, 0x01 }, { 0x00, 0x4e, 0x01 },
        { 0x00, 0x4f, 0x01 }, { 0x00, 0x4f, 0x01 },
        { 0x00, 0x50, 0x01 }, { 0x00, 0x50, 0x01 },
        { 0x00, 0x51, 0x01 }, { 0x00, 0x51, 0x01 },
        { 0x00, 0x52, 0x01 }, { 0x00, 0x52, 0x01 },
        { 0x00, 0x53, 0x01 }, { 0x00, 0x53, 0x01 },
        { 0x00, 0x54, 0x01 }, { 0x00, 0x54, 0x01 },
    },
    {
        { 0x00, 0x55, 0x01 }, { 0x00, 0x55, 0x01 },
        { 0x00, 0x56, 0x01 }, { 0x00, 0x56, 0x01 },
        { 0x00, 0x57, 0x01 }, { 0x00, 0x57, 0x01 },
        { 0x00, 0x59, 0x01 }, { 0x00, 0x59, 0x01 },
        { 0x00, 0x6a, 0x01 }, { 0x00, 0x6a, 0x01 },
        { 0x00, 0x6b, 0x01 }, { 0x00, 0x6b, 0x01 },
        { 0x00, 0x71, 0x01 }, { 0x00, 0x71, 0x01 },
        { 0x00, 0x76, 0x01 }, { 0x00, 0x76, 0x01 },
    },
    {
        { 0x00, 0x77, 0x01 }, { 0x00, 0x77, 0x01 },
        { 0x00, 0x78, 0x01 }, { 0x00, 0x78, 0x01 },
        { 0x00, 0x79, 0x01 }, { 0x00, 0x79, 0x01 },
        { 0x00, 0x7a, 0x01 }, { 0x00, 0x7a, 0x01 },
        { 0x00, 0x26, 0x01 }, { 0x00, 0x2a, 0x01 },
        { 0x00, 0x2c, 0x01 }, { 0x00, 0x3b, 0x01 },
        { 0x00, 0x58, 0x01 }, { 0x00, 0x5a, 0x01 },
        { 0x11, 0x00, 0x00 }, { 0x12, 0x00, 0x00 },
    },
    {
        { 0x00, 0x21, 0x01 }, { 0x00, 0x21, 0x01 },
        { 0x00, 0x21, 0x01 }, { 0x00, 0x21, 0x01 },
        { 0x00, 0x22, 0x01 }, { 0x00, 0x22, 0x01 },
        { 0x00, 0x22, 0x01 }, { 0x00, 0x22, 0x01 },
        { 0x00, 0x28, 0x01 }, { 0x00, 0x28, 0x01 },
        { 0x00, 0x28, 0x01 }, { 0x00, 0x28, 0x01 },
        { 0x00, 0x29, 0x01 }, { 0x00, 0x29, 0x01 },
        { 0x00, 0x29, 0x01 }, { 0x00, 0x29, 0x01 },
    },
    {
        { 0x00, 0x3f, 0x01 }, { 0x00, 0x3f, 0x01 },
        { 0x00, 0x3f, 0x01 }, { 0x00, 0x3f, 0x01 },
        { 0x00, 0x27, 0x01 }, { 0x00, 0x27, 0x01 },
        { 0x00, 0x2b, 0x01 }, { 0x00, 0x2b, 0x01 },
        { 0x00, 0x7c, 0x01 }, { 0x00, 0x7c, 0x01 },
        { 0x00, 0x23, 0x01 }, { 0x00, 0x3e, 0x01 },
        { 0x13, 0x00, 0x00 }, { 0x14, 0x00, 0x00 },
        { 0x15, 0x00, 0x00 }, { 0x16, 0x00, 0x00 },
    },
    {
        { 0x00, 0x00, 0x01 }, { 0x00, 0x00, 0x01 },
        { 0x00, 0x00, 0x01 }, { 0x00, 0x00, 0x01 },
        { 0x00, 0x00, 0x01 }, { 0x00, 0x00, 0x01 },
        { 0x00, 0x00, 0x01 }, { 0x00, 0x00, 0x01 },
        { 0x00, 0x24, 0x01 }, { 0x00, 0x24, 0x01 },
        { 0x00, 0x24, 0x01 }, { 0x00, 0x24, 0x01 },
        { 0x00, 0x24, 0x01 }, { 0x00, 0x24, 0x01 },
        { 0x00, 0x24, 0x01 }, { 0x00, 0x24, 0x01 },
    },
    {
        { 0x00, 0x40, 0x01 }, { 0x00, 0x40, 0x01 },
        { 0x00, 0x40, 0x01 }, { 0x00, 0x40, 0x01 },
        { 0x00, 0x40, 0x01 }, { 0x00, 0x40, 0x01 },
        { 0x00, 0x40, 0x01 }, { 0x00, 0x40, 0x01 },
        { 0x00, 0x5b, 0x01 }, { 0x00, 0x5b, 0x01 },
        { 0x00, 0x5b, 0x01 }, { 0x00, 0x5b, 0x01 },
        { 0x00, 0x5b, 0x01 }, { 0x00, 0x5b, 0x01 },
        { 0x00, 0x5b, 0x01 }, { 0x00, 0x5b, 0x01 },
    },
    {
        { 0x00, 0x5d, 0x01 }, { 0x00, 0x5d, 0x01 },
        { 0x00, 0x5d, 0x01 }, { 0x00, 0x5d, 0x01 },
        { 0x00, 0x5d, 0x01 }, { 0x00, 0x5d, 0x01 },
        { 0x00, 0x5d, 0x01 }, { 0x00, 0x5d, 0x01 },
        { 0x00, 0x7e, 0x01 }, { 0x00, 0x7e, 0x01 },
        { 0x00, 0x7e, 0x01 }, { 0x00, 0x7e, 0x01 },
        { 0x00, 0x7e, 0x01 }, { 0x00, 0x7e, 0x01 },
        { 0x00, 0x7e, 0x01 }, { 0x00, 0x7e, 0x01 },
    },
    {
        { 0x00, 0x5e, 0x01 }, { 0x00, 0x5e, 0x01 },
        { 0x00, 0x5e, 0x01 }, { 0x00, 0x5e, 0x01 },
        { 0x00, 0x7d, 0x01 }, { 0x00, 0x7d, 0x01 },
        { 0x00, 0x7d, 0x01 }, { 0x00, 0x7d, 0x01 },
        { 0x00, 0x3c, 0x01 }, { 0x00, 0x3c, 0x01 },
        { 0x00, 0x60, 0x01 }, { 0x00, 0x60, 0x01 },
        { 0x00, 0x7b, 0x01 }, { 0x00, 0x7b, 0x01 },
        { 0x17, 0x00, 0x00 }, { 0x1a, 0x00, 0x00 },
    },
    {
        { 0x00, 0x5c, 0x01 }, { 0x00, 0x5c, 0x01 },
        { 0x00, 0xc3, 0x01 }, { 0x00, 0xc3, 0x01 },
        { 0x00, 0xd0, 0x01 }, { 0x00, 0xd0, 0x01 },
        { 0x00, 0x80, 0x01 }, { 0x00, 0x82, 0x01 },
        { 0x00, 0x83, 0x01 }, { 0x00, 0xa2, 0x01 },
        { 0x00, 0xb8, 0x01 }, { 0x00, 0xc2, 0x01 },
        { 0x00, 0xe0, 0x01 }, { 0x00, 0xe2, 0x01 },
        { 0x18, 0x00, 0x00 }, { 0x19, 0x00, 0x00 },
    },
    {
        { 0x00, 0x99, 0x01 }, { 0x00, 0x99, 0x01 },
        { 0x00, 0x99, 0x01 }, { 0x00, 0x99, 0x01 },
        { 0x00, 0x99, 0x01 }, { 0x00, 0x99, 0x01 },
        { 0x00, 0x99, 0x01 }, { 0x00, 0x99, 0x01 },
        { 0x00, 0xa1, 0x01 }, { 0x00, 0xa1, 0x01 },
        { 0x00, 0xa1, 0x01 }, { 0x00, 0xa1, 0x01 },
        { 0x00, 0xa1, 0x01 }, { 0x00, 0xa1, 0x01 },
        { 0x00, 0xa1, 0x01 }, { 0x00, 0xa1, 0x01 },
    },
    {
        { 0x00, 0xa7, 0x01 }, { 0x00, 0xa7, 0x01 },
        { 0x00, 0xa7, 0x01 }, { 0x00, 0xa7, 0x01 },
        { 0x00, 0xa7, 0x01 }, { 0x00, 0xa7, 0x01 },
        { 0x00, 0xa7, 0x01 }, { 0x00, 0xa7, 0x01 },
        { 0x00, 0xac, 0x01 }, { 0x00, 0xac, 0x01 },
        { 0x00, 0xac, 0x01 }, { 0x00, 0xac, 0x01 },
        { 0x00, 0xac, 0x01 }, { 0x00, 0xac, 0x01 },
        { 0x00, 0xac, 0x01 }, { 0x00, 0xac, 0x01 },
    },
    {
        { 0x1b, 0x00, 0x00 }, { 0x1c, 0x00, 0x00 },
        { 0x1d, 0x00, 0x00 }, { 0x1e, 0x00, 0x00 },
        { 0x1f, 0x00, 0x00 }, { 0x20, 0x00, 0x00 },
        { 0x21, 0x00, 0x00 }, { 0x22, 0x00, 0x00 },
        { 0x23, 0x00, 0x00 }, { 0x24, 0x00, 0x00 },
        { 0x25, 0x00, 0x00 }, { 0x26, 0x00, 0x00 },
        { 0x27, 0x00, 0x00 }, { 0x28, 0x00, 0x00 },
        { 0x29, 0x00, 0x00 }, { 0x2a, 0x00, 0x00 },
    },
    {
        { 0x00, 0xb0, 0x01 }, { 0x00, 0xb0, 0x01 },
        { 0x00, 0xb0, 0x01 }, { 0x00, 0xb0, 0x01 },
        { 0x00, 0xb0, 0x01 }, { 0x00, 0xb0, 0x01 },
        { 0x00, 0xb0, 0x01 }, { 0x00, 0xb0, 0x01 },
        { 0x00, 0xb1, 0x01 }, { 0x00, 0xb1, 0x01 },
        { 0x00, 0xb1, 0x01 }, { 0x00, 0xb1, 0x01 },
        { 0x00, 0xb1, 0x01 }, { 0x00, 0xb1, 0x01 },
        { 0x00, 0xb1, 0x01 }, { 0x00, 0xb1, 0x01 },
    },
    {
        { 0x00, 0xb3, 0x01 }, { 0x00, 0xb3, 0x01 },
        { 0x00, 0xb3, 0x01 }, { 0x00, 0xb3, 0x01 },
        { 0x00, 0xb3, 0x01 }, { 0x00, 0xb3, 0x01 },
        { 0x00, 0xb3, 0x01 }, { 0x00, 0xb3, 0x01 },
        { 0x00, 0xd1, 0x01 }, { 0x00, 0xd1, 0x01 },
        { 0x00, 0xd1, 0x01 }, { 0x00, 0xd1, 0x01 },
        { 0x00, 0xd1, 0x01 }, { 0x00, 0xd1, 0x01 },
        { 0x00, 0xd1, 0x01 }, { 0x00, 0xd1, 0x01 },
    },
    {
        { 0x00, 0xd8, 0x01 }, { 0x00, 0xd8, 0x01 },
        { 0x00, 0xd8, 0x01 }, { 0x00, 0xd8, 0x01 },
        { 0x00, 0xd8, 0x01 }, { 0x00, 0xd8, 0x01 },
        { 0x00, 0xd8, 0x01 }, { 0x00, 0xd8, 0x01 },
        { 0x00, 0xd9, 0x01 }, { 0x00, 0xd9, 0x01 },
        { 0x00, 0xd9, 0x01 }, { 0x00, 0xd9, 0x01 },
        { 0x00, 0xd9, 0x01 }, { 0x00, 0xd9, 0x01 },
        { 0x00, 0xd9, 0x01 }, { 0x00, 0xd9, 0x01 },
    },
    {
        { 0x00, 0xe3, 0x01 }, { 0x00, 0xe3, 0x01 },
        { 0x00, 0xe3, 0x01 }, { 0x00, 0xe3, 0x01 },
        { 0x00, 0xe3, 0x01 }, { 0x00, 0xe3, 0x01 },
        { 0x00, 0xe3, 0x01 }, { 0x00, 0xe3, 0x01 },
        { 0x00, 0xe5, 0x01 }, { 0x00, 0xe5, 0x01 },
        { 0x00, 0xe5, 0x01 }, { 0x00, 0xe5, 0x01 },
        { 0x00, 0xe5, 0x01 }, { 0x00, 0xe5, 0x01 },
        { 0x00, 0xe5, 0x01 }, { 0x00, 0xe5, 0x01 },
    },
    {
        { 0x00, 0xe6, 0x01 }, { 0x00, 0xe6, 0x01 },
        { 0x00, 0xe6, 0x01 }, { 0x00, 0xe6, 0x01 },
        { 0x00, 0xe6, 0x01 }, { 0x00, 0xe6, 0x01 },
        { 0x00, 0xe6, 0x01 }, { 0x00, 0xe6, 0x01 },
        { 0x00, 0x81, 0x01 }, { 0x00, 0x81, 0x01 },
        { 0x00, 0x81, 0x01 }, { 0x00, 0x81, 0x01 },
        { 0x00, 0x84, 0x01 }, { 0x00, 0x84, 0x01 },
        { 0x00, 0x84, 0x01 }, { 0x00, 0x84, 0x01 },
    },
    {
        { 0x00, 0x85, 0x01 }, { 0x00, 0x85, 0x01 },
        { 0x00, 0x85, 0x01 }, { 0x00, 0x85, 0x01 },
        { 0x00, 0x86, 0x01 }, { 0x00, 0x86, 0x01 },
        { 0x00, 0x86, 0x01 }, { 0x00, 0x86, 0x01 },
        { 0x00, 0x88, 0x01 }, { 0x00, 0x88, 0x01 },
        { 0x00, 0x88, 0x01 }, { 0x00, 0x88, 0x01 },
        { 0x00, 0x92, 0x01 }, { 0x00, 0x92, 0x01 },
        { 0x00, 0x92, 0x01 }, { 0x00, 0x92, 0x01 },
    },
    {
        { 0x00, 0x9a, 0x01 }, { 0x00, 0x9a, 0x01 },
        { 0x00, 0x9a, 0x01 }, { 0x00, 0x9a, 0x01 },
        { 0x00, 0x9c, 0x01 }, { 0x00, 0x9c, 0x01 },
        { 0x00, 0x9c, 0x01 }, { 0x00, 0x9c, 0x01 },
        { 0x00, 0xa0, 0x01 }, { 0x00, 0xa0, 0x01 },
        { 0x00, 0xa0, 0x01 }, { 0x00, 0xa0, 0x01 },
        { 0x00, 0xa3, 0x01 }, { 0x00, 0xa3, 0x01 },
        { 0x00, 0xa3, 0x01 }, { 0x00, 0xa3, 0x01 },
    },
    {
        { 0x00, 0xa4, 0x01 }, { 0x00, 0xa4, 0x01 },
        { 0x00, 0xa4, 0x01 }, { 0x00, 0xa4, 0x01 },
        { 0x00, 0xa9, 0x01 }, { 0x00, 0xa9, 0x01 },
        { 0x00, 0xa9, 0x01 }, { 0x00, 0xa9, 0x01 },
        { 0x00, 0xaa, 0x01 }, { 0x00, 0xaa, 0x01 },
        { 0x00, 0xaa, 0x01 }, { 0x00, 0xaa, 0x01 },
        { 0x00, 0xad, 0x01 }, { 0x00, 0xad, 0x01 },
        { 0x00, 0xad, 0x01 }, { 0x00, 0xad, 0x01 },
    },
    {
        { 0x00, 0xb2, 0x01 }, { 0x00, 0xb2, 0x01 },
        { 0x00, 0xb2, 0x01 }, { 0x00, 0xb2, 0x01 },
        { 0x00, 0xb5, 0x01 }, { 0x00, 0xb5, 0x01 },
        { 0x00, 0xb5, 0x01 }, { 0x00, 0xb5, 0x01 },
        { 0x00, 0xb9, 0x01 }, { 0x00, 0xb9, 0x01 },
        { 0x00, 0xb9, 0x01 }, { 0x00, 0xb9, 0x01 },
        { 0x00, 0xba, 0x01 }, { 0x00, 0xba, 0x01 },
        { 0x00, 0xba, 0x01 }, { 0x00, 0xba, 0x01 },
    },
    {
        { 0x00, 0xbb, 0x01 }, { 0x00, 0xbb, 0x01 },
        { 0x00, 0xbb, 0x01 }, { 0x00, 0xbb, 0x01 },
        { 0x00, 0xbd, 0x01 }, { 0x00, 0xbd, 0x01 },
        { 0x00, 0xbd, 0x01 }, { 0x00, 0xbd, 0x01 },
        { 0x00, 0xbe, 0x01 }, { 0x00, 0xbe, 0x01 },
        { 0x00, 0xbe, 0x01 }, { 0x00, 0xbe, 0x01 },
        { 0x00, 0xc4, 0x01 }, { 0x00, 0xc4, 0x01 },
        { 0x00, 0xc4, 0x01 }, { 0x00, 0xc4, 0x01 },
    },
    {
        { 0x00, 0xc6, 0x01 }, { 0x00, 0xc6, 0x01 },
        { 0x00, 0xc6, 0x01 }, { 0x00, 0xc6, 0x01 },
        { 0x00, 0xe4, 0x01 }, { 0x00, 0xe4, 0x01 },
        { 0x00, 0xe4, 0x01 }, { 0x00, 0xe4, 0x01 },
        { 0x00, 0xe8, 0x01 }, { 0x00, 0xe8, 0x01 },
        { 0x00, 0xe8, 0x01 }, { 0x00, 0xe8, 0x01 },
        { 0x00, 0xe9, 0x01 }, { 0x00, 0xe9, 0x01 },
        { 0x00, 0xe9, 0x01 }, { 0x00, 0xe9, 0x01 },
    },
    {
        { 0x00, 0x01, 0x01 }, { 0x00, 0x01, 0x01 },
        { 0x00, 0x87, 0x01 }, { 0x00, 0x87, 0x01 },
        { 0x00, 0x89, 0x01 }, { 0x00, 0x89, 0x01 },
        { 0x00, 0x8a, 0x01 }, { 0x00, 0x8a, 0x01 },
        { 0x00, 0x8b, 0x01 }, { 0x00, 0x8b, 0x01 },
        { 0x00, 0x8c, 0x01 }, { 0x00, 0x8c, 0x01 },
        { 0x00, 0x8d, 0x01 }, { 0x00, 0x8d, 0x01 },
        { 0x00, 0x8f, 0x01 }, { 0x00, 0x8f, 0x01 },
    },
    {
        { 0x00, 0x93, 0x01 }, { 0x00, 0x93, 0x01 },
        { 0x00, 0x95, 0x01 }, { 0x00, 0x95, 0x01 },
        { 0x00, 0x96, 0x01 }, { 0x00, 0x96, 0x01 },
        { 0x00, 0x97, 0x01 }, { 0x00, 0x97, 0x01 },
        { 0x00, 0x98, 0x01 }, { 0x00, 0x98, 0x01 },
        { 0x00, 0x9b, 0x01 }, { 0x00, 0x9b, 0x01 },
        { 0x00, 0x9d, 0x01 }, { 0x00, 0x9d, 0x01 },
        { 0x00, 0x9e, 0x01 }, { 0x00, 0x9e, 0x01 },
    },
    {
        { 0x00, 0xa5, 0x01 }, { 0x00, 0xa5, 0x01 },
        { 0x00, 0xa6, 0x01 }, { 0x00, 0xa6, 0x01 },
        { 0x00, 0xa8, 0x01 }, { 0x00, 0xa8, 0x01 },
        { 0x00, 0xae, 0x01 }, { 0x00, 0xae, 0x01 },
        { 0x00, 0xaf, 0x01 }, { 0x00, 0xaf, 0x01 },
        { 0x00, 0xb4, 0x01 }, { 0x00, 0xb4, 0x01 },
        { 0x00, 0xb6, 0x01 }, { 0x00, 0xb6, 0x01 },
        { 0x00, 0xb7, 0x01 }, { 0x00, 0xb7, 0x01 },
    },
    {
        { 0x00, 0xbc, 0x01 }, { 0x00, 0xbc, 0x01 },
        { 0x00, 0xbf, 0x01 }, { 0x00, 0xbf, 0x01 },
        { 0x00, 0xc5, 0x01 }, { 0x00, 0xc5, 0x01 },
        { 0x00, 0xe7, 0x01 }, { 0x00, 0xe7, 0x01 },
        { 0x00, 0xef, 0x01 }, { 0x00, 0xef, 0x01 },
        { 0x00, 0x09, 0x01 }, { 0x00, 0x8e, 0x01 },
        { 0x00, 0x90, 0x01 }, { 0x00, 0x91, 0x01 },
        { 0x00, 0x94, 0x01 }, { 0x00, 0x9f, 0x01 },
    },
    {
        { 0x00, 0xab, 0x01 }, { 0x00, 0xce, 0x01 },
        { 0x00, 0xd7, 0x01 }, { 0x00, 0xe1, 0x01 },
        { 0x00, 0xec, 0x01 }, { 0x00, 0xed, 0x01 },
        { 0x2b, 0x00, 0x00 }, { 0x2c, 0x00, 0x00 },
        { 0x2d, 0x00, 0x00 }, { 0x2e, 0x00, 0x00 },
        { 0x2f, 0x00, 0x00 }, { 0x30, 0x00, 0x00 },
        { 0x31, 0x00, 0x00 }, { 0x32, 0x00, 0x00 },
        { 0x33, 0x00, 0x00 }, { 0x34, 0x00, 0x00 },
    },
    {
        { 0x00, 0xc7, 0x01 }, { 0x00, 0xc7, 0x01 },
        { 0x00, 0xc7, 0x01 }, { 0x00, 0xc7, 0x01 },
        { 0x00, 0xc7, 0x01 }, { 0x00, 0xc7, 0x01 },
        { 0x00, 0xc7, 0x01 }, { 0x00, 0xc7, 0x01 },
        { 0x00, 0xcf, 0x01 }, { 0x00, 0xcf, 0x01 },
        { 0x00, 0xcf, 0x01 }, { 0x00, 0xcf, 0x01 },
        { 0x00, 0xcf, 0x01 }, { 0x00, 0xcf, 0x01 },
        { 0x00, 0xcf, 0x01 }, { 0x00, 0xcf, 0x01 },
    },
    {
        { 0x00, 0xea, 0x01 }, { 0x00, 0xea, 0x01 },
        { 0x00, 0xea, 0x01 }, { 0x00, 0xea, 0x01 },
        { 0x00, 0xea, 0x01 }, { 0x00, 0xea, 0x01 },
        { 0x00, 0xea, 0x01 }, { 0x00, 0xea, 0x01 },
        { 0x00, 0xeb, 0x01 }, { 0x00, 0xeb, 0x01 },
        { 0x00, 0xeb, 0x01 }, { 0x00, 0xeb, 0x01 },
        { 0x00, 0xeb, 0x01 }, { 0x00, 0xeb, 0x01 },
        { 0x00, 0xeb, 0x01 }, { 0x00, 0xeb, 0x01 },
    },
    {
        { 0x00, 0xc0, 0x01 }, { 0x00, 0xc0, 0x01 },
        { 0x00, 0xc0, 0x01 }, { 0x00, 0xc0, 0x01 },
        { 0x00, 0xc1, 0x01 }, { 0x00, 0xc1, 0x01 },
        { 0x00, 0xc1, 0x01 }, { 0x00, 0xc1, 0x01 },
        { 0x00, 0xc8, 0x01 }, { 0x00, 0xc8, 0x01 },
        { 0x00, 0xc8, 0x01 }, { 0x00, 0xc8, 0x01 },
        { 0x00, 0xc9, 0x01 }, { 0x00, 0xc9, 0x01 },
        { 0x00, 0xc9, 0x01 }, { 0x00, 0xc9, 0x01 },
    },
    {
        { 0x00, 0xca, 0x01 }, { 0x00, 0xca, 0x01 },
        { 0x00, 0xca, 0x01 }, { 0x00, 0xca, 0x01 },
        { 0x00, 0xcd, 0x01 }, { 0x00, 0xcd, 0x01 },
        { 0x00, 0xcd, 0x01 }, { 0x00, 0xcd, 0x01 },
        { 0x00, 0xd2, 0x01 }, { 0x00, 0xd2, 0x01 },
        { 0x00, 0xd2, 0x01 }, { 0x00, 0xd2, 0x01 },
        { 0x00, 0xd5, 0x01 }, { 0x00, 0xd5, 0x01 },
        { 0x00, 0xd5, 0x01 }, { 0x00, 0xd5, 0x01 },
    },
    {
        { 0x00, 0xda, 0x01 }, { 0x00, 0xda, 0x01 },
        { 0x00, 0xda, 0x01 }, { 0x00, 0xda, 0x01 },
        { 0x00, 0xdb, 0x01 }, { 0x00, 0xdb, 0x01 },
        { 0x00, 0xdb, 0x01 }, { 0x00, 0xdb, 0x01 },
        { 0x00, 0xee, 0x01 }, { 0x00, 0xee, 0x01 },
        { 0x00, 0xee, 0x01 }, { 0x00, 0xee, 0x01 },
        { 0x00, 0xf0, 0x01 }, { 0x00, 0xf0, 0x01 },
        { 0x00, 0xf0, 0x01 }, { 0x00, 0xf0, 0x01 },
    },
    {
        { 0x00, 0xf2, 0x01 }, { 0x00, 0xf2, 0x01 },
        { 0x00, 0xf2, 0x01 }, { 0x00, 0xf2, 0x01 },
        { 0x00, 0xf3, 0x01 }, { 0x00, 0xf3, 0x01 },
        { 0x00, 0xf3, 0x01 }, { 0x00, 0xf3, 0x01 },
        { 0x00, 0xff, 0x01 }, { 0x00, 0xff, 0x01 },
        { 0x00, 0xff, 0x01 }, { 0x00, 0xff, 0x01 },
        { 0x00, 0xcb, 0x01 }, { 0x00, 0xcb, 0x01 },
        { 0x00, 0xcc, 0x01 }, { 0x00, 0xcc, 0x01 },
    },
    {
        { 0x00, 0xd3, 0x01 }, { 0x00, 0xd3, 0x01 },
        { 0x00, 0xd4, 0x01 }, { 0x00, 0xd4, 0x01 },
        { 0x00, 0xd6, 0x01 }, { 0x00, 0xd6, 0x01 },
        { 0x00, 0xdd, 0x01 }, { 0x00, 0xdd, 0x01 },
        { 0x00, 0xde, 0x01 }, { 0x00, 0xde, 0x01 },
        { 0x00, 0xdf, 0x01 }, { 0x00, 0xdf, 0x01 },
        { 0x00, 0xf1, 0x01 }, { 0x00, 0xf1, 0x01 },
        { 0x00, 0xf4, 0x01 }, { 0x00, 0xf4, 0x01 },
    },
    {
        { 0x00, 0xf5, 0x01 }, { 0x00, 0xf5, 0x01 },
        { 0x00, 0xf6, 0x01 }, { 0x00, 0xf6, 0x01 },
        { 0x00, 0xf7, 0x01 }, { 0x00, 0xf7, 0x01 },
        { 0x00, 0xf8, 0x01 }, { 0x00, 0xf8, 0x01 },
        { 0x00, 0xfa, 0x01 }, { 0x00, 0xfa, 0x01 },
        { 0x00, 0xfb, 0x01 }, { 0x00, 0xfb, 0x01 },
        { 0x00, 0xfc, 0x01 }, { 0x00, 0xfc, 0x01 },
        { 0x00, 0xfd, 0x01 }, { 0x00, 0xfd, 0x01 },
    },
    {
        { 0x00, 0xfe, 0x01 }, { 0x00, 0xfe, 0x01 },
        { 0x00, 0x02, 0x01 }, { 0x00, 0x03, 0x01 },
        { 0x00, 0x04, 0x01 }, { 0x00, 0x05, 0x01 },
        { 0x00, 0x06, 0x01 }, { 0x00, 0x07, 0x01 },
        { 0x00, 0x08, 0x01 }, { 0x00, 0x0b, 0x01 },
        { 0x00, 0x0c, 0x01 }, { 0x00, 0x0e, 0x01 },
        { 0x00, 0x0f, 0x01 }, { 0x00, 0x10, 0x01 },
        { 0x00, 0x11, 0x01 }, { 0x00, 0x12, 0x01 },
    },
    {
        { 0x00, 0x13, 0x01 }, { 0x00, 0x14, 0x01 },
        { 0x00, 0x15, 0x01 }, { 0x00, 0x17, 0x01 },
        { 0x00, 0x18, 0x01 }, { 0x00, 0x19, 0x01 },
        { 0x00, 0x1a, 0x01 }, { 0x00, 0x1b, 0x01 },
        { 0x00, 0x1c, 0x01 }, { 0x00, 0x1d, 0x01 },
        { 0x00, 0x1e, 0x01 }, { 0x00, 0x1f, 0x01 },
        { 0x00, 0x7f, 0x01 }, { 0x00, 0xdc, 0x01 },
        { 0x00, 0xf9, 0x01 }, { 0x35, 0x00, 0x00 },
    },
    {
        { 0x00, 0x0a, 0x01 }, { 0x00, 0x0a, 0x01 },
        { 0x00, 0x0a, 0x01 }, { 0x00, 0x0a, 0x01 },
        { 0x00, 0x0d, 0x01 }, { 0x00, 0x0d, 0x01 },
        { 0x00, 0x0d, 0x01 }, { 0x00, 0x0d, 0x01 },
        { 0x00, 0x16, 0x01 }, { 0x00, 0x16, 0x01 },
        { 0x00, 0x16, 0x01 }, { 0x00, 0x16, 0x01 },
        { 0xcc, 0xcc, 0xcc }, { 0xcc, 0xcc, 0xcc },
        { 0xcc, 0xcc, 0xcc }, { 0xcc, 0xcc, 0xcc },
    }
};

void destroy_huff_decode_tree(huff_decode_node_t *node) {
    int i;
    huff_decode_node_t *tmp = NULL;
    for (i = 0; i < 16; i++) {
        if (node->child[i] != NULL && node->child[i] != tmp) {
            tmp = node->child[i];
            node->child[i] = NULL;
            destroy_huff_decode_tree(tmp);
            free(tmp);
        }
    }
}

huff_decode_node_t *build_huff_decode_tree(unsigned char split_bits[256][8]) {
    int i, j;
    huff_decode_node_t *root;
    root = (huff_decode_node_t *)malloc(sizeof(huff_decode_node_t));
    memset(root, 0, sizeof(huff_decode_node_t));

    for (i = 0; i < 256; i++) {
        int idx;
        huff_decode_node_t *node;
        huff_decode_node_t *tmp = root;
        for (j = 0; j < huff_sym[i].bits / 4; j++) {
            idx = split_bits[i][j];
            node = tmp;
            if (node->child[idx] == NULL) {
                node->child[idx] = (huff_decode_node_t *)malloc(sizeof(huff_decode_node_t));
                memset(node->child[idx], 0, sizeof(huff_decode_node_t));
            }
            tmp = node->child[idx];
        }

        if (huff_sym[i].bits % 4) {
            idx = split_bits[i][j];
            node = tmp;
            tmp = (huff_decode_node_t *)malloc(sizeof(huff_decode_node_t));
            memset(tmp, 0, sizeof(huff_decode_node_t));
            tmp->ending = 1;
            tmp->sym = i;

            idx <<= (4 - huff_sym[i].bits % 4);
            for (j = 0; j < (1 << (4 - huff_sym[i].bits % 4)); j++) {
                assert(node->child[idx + j] == NULL);
                node->child[idx + j] = tmp;
            }
        } else {
            tmp->ending = 1;
            tmp->sym = i;
        }
    }
    return root;
}

int index_decode_node(huff_decode_node_t *node, int idx) {
    int i;
    node->idx = idx++;
    for (i = 0; i < 16; i++) {
        if (node->child[i] && !node->child[i]->ending) {
            idx = index_decode_node(node->child[i], idx);
        }
    }
    return idx;
}

void convert_node_to_state_table(huff_decode_node_t *node, huff_decode_state_t state[55][16]) {
    int i;
    int idx = node->idx;
    for (i = 0; i < 16; i++) {
        if (node->child[i]) {
            state[idx][i].ending = node->child[i]->ending;
            state[idx][i].next = node->child[i]->idx;
            state[idx][i].sym = node->child[i]->sym;
            convert_node_to_state_table(node->child[i], state);
        }
    }
}

char *huff_write_bits(char *dst, int *bits_offset, huff_sym_t *sym) {
    int off = *bits_offset;
    int remain = sym->bits;
    int code = sym->code;
    if (off) {
        if (8 - off >= remain) {
            *dst |= code << ( 8 - remain - off);
            off += remain;
            remain = 0;
            if (off == 8) dst++;
        } else {
            *dst++ |= code >> (remain - (8 - off));
            remain = remain - (8 - off);
            off += sym->bits - remain;
        }
    }
    for (; remain >= 8; remain -= 8) {
        code = sym->code;
        code <<= 32 - remain;
        code >>= 24;
        *dst++ = (unsigned char)code;
    }
    if (remain > 0) {
        code = sym->code;
        code <<= 8 - remain;
        *dst = (unsigned char)code;
        off = remain;
    }
    *bits_offset = off % 8;
    return dst;
}

int huff_encode(char *dst, int cap, const char *src, int src_len) {
    int i, bits, off, idx, remain;
    unsigned int code;
    if (src_len == -1)
        src_len = strlen(src);
    bits = 0;
    for (i = 0; i < src_len; i++) {
        huff_sym_t *sym = &huff_sym[(unsigned char)src[i]];
        code = sym->code;
        remain = sym->bits;
        idx = bits / 8;
        off = bits % 8;
        if (off) {
            if (8 - off >= remain) {
                dst[idx] |= code << (8 - remain - off);
                bits += remain;
                remain = 0;
            } else {
                dst[idx] |= code >> (remain - (8 - off));
                bits += 8 - off;
                remain -= 8 - off;
            }
        }
        if (remain) {
            assert(bits % 8 == 0);
            for (; remain >= 8; remain -= 8) {
                code = sym->code;
                idx = bits / 8;
                code <<= 32 - remain;
                code >>= 24;
                dst[idx] = (unsigned char)code;
                bits += 8;
            }
        }
        if (remain > 0) {
            code = sym->code;
            idx = bits / 8;
            code <<= 8 - remain;
            dst[idx] = (unsigned char)code;
            bits += remain;
        }
        if (bits > cap * 8) {
            return cap;
        }
    }
    if (bits % 8) {
        idx = bits / 8;
        off = bits % 8;
        dst[idx] |= (1 << (8 - off)) - 1;
        bits += 8 - off;
    }
    assert(bits % 8 == 0);
    return bits / 8;
}

int huff_decode(char *dst, int cap, const char *src, int src_len) {
    huff_decode_state_t *state;
    int cur = 0;
    int bits = 0;
    int src_bits = src_len * 8;
    int len = 0;
    unsigned char c = 0;
    do {
        int idx = bits / 8;
        int off = bits % 8;
        c = src[idx];
        c <<= off;
        c >>= 4;
        if (off > 4) {
            c |= (unsigned char)src[idx + 1] >> (8 - off % 4);
        }
        bits += 4;
        state = &decode_state[cur][c];
        if (state->ending) {
            dst[len++] = state->sym;
            cur = 0;
            if (huff_sym[state->sym].bits % 4)
                bits -= 4 - huff_sym[state->sym].bits % 4;
        } else {
            cur = state->next;
        }
    } while (bits + 4 <= src_bits && len < cap);
    dst[len] = 0;
    return len;
}

int main(int argc, char **argv) {
    char dst[32];
    char buf[64];
    int i, j, node_cnt;
    huff_decode_node_t *root;
    unsigned char split_bits[256][8];
    huff_decode_state_t state[55][16];

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    /* split huffman code to n * 4 bits */
    for (i = 0; i < 256; i++) {
        unsigned int code = huff_sym[i].code;
        int bits = huff_sym[i].bits;

        for (j = 0; j < bits / 4; j++) {
            unsigned int four_bits = code;
            four_bits <<= 32 - bits + j * 4;
            four_bits >>= 28;
            split_bits[i][j] = (unsigned char)four_bits;
        }

        if (bits % 4) {
            unsigned int remain_bits = code;
            remain_bits &= (1 << (bits % 4)) - 1;
            split_bits[i][bits / 4] = (unsigned char)remain_bits;
        }
    }
    for (i = 0; i < 256; i++) {
        fprintf(stdout, "[%d]:", huff_sym[i].bits);
        for (j = 0; j <= 8; j++) {
            if (j < (huff_sym[i].bits + 3) / 4) {
                fprintf(stdout, " %d", split_bits[i][j]);
            } else {
                fprintf(stdout, "\n");
                break;
            }
        }
    }

    /* build decode tree */
    root = build_huff_decode_tree(split_bits);
    node_cnt = index_decode_node(root, 0);
    fprintf(stdout, "node count: %d\n", node_cnt + 1);
    convert_node_to_state_table(root, state);
    destroy_huff_decode_tree(root);
    free(root);
    for (i = 0; i < 55; i++) {
        fprintf(stdout, "{\n");
        for (j = 0; j < 16; j++) {
            fprintf(stdout, "   { 0x%02x, 0x%02x, 0x%02x },\n", state[i][j].next, state[i][j].sym, state[i][j].ending);
        }
        fprintf(stdout, "},\n");
    }
    huff_encode(dst, sizeof(dst), "ABCDE", 5);
    huff_decode(dst + 10, 100, dst, 5);
#define HUFF_BITS "\xd0\x7a\xbe\x94\x10\x54\xd4\x44\xa8\x20\x05\x95\x04\x0b\x81\x66\xe0\x84\xa6\x2d\x1b\xff"
    i = huff_decode(dst, sizeof(dst), HUFF_BITS, sizeof(HUFF_BITS) - 1);
    j = huff_encode(buf, sizeof(buf), dst, i);
    _CrtDumpMemoryLeaks();
    return 0;
}
