#ifndef parameters_h
#define parameters_h

#include <cmath>

// Numeric parameters
const double PI = 3.14159265;

// Look Up table for sine wave 
const int senoide[] = {
    0x80, 0x83, 0x86, 0x89, 0x8c, 0x8f, 0x92, 0x95, 0x98, 0x9c, 0x9f, 0xa2,
    0xa5, 0xa8, 0xab, 0xae, 0xb0, 0xb3, 0xb6, 0xb9, 0xbc, 0xbf, 0xc1, 0xc4,
    0xc7, 0xc9, 0xcc, 0xce, 0xd1, 0xd3, 0xd5, 0xd8, 0xda, 0xdc, 0xde, 0xe0,
    0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xeb, 0xed, 0xef, 0xf0, 0xf2, 0xf3, 0xf4,
    0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfb, 0xfc, 0xfd, 0xfd, 0xfe, 0xfe,
    0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfd, 0xfd,
    0xfc, 0xfc, 0xfb, 0xfa, 0xf9, 0xf8, 0xf7, 0xf6, 0xf5, 0xf4, 0xf2, 0xf1,
    0xef, 0xee, 0xec, 0xeb, 0xe9, 0xe7, 0xe5, 0xe3, 0xe1, 0xdf, 0xdd, 0xdb,
    0xd9, 0xd7, 0xd4, 0xd2, 0xcf, 0xcd, 0xca, 0xc8, 0xc5, 0xc3, 0xc0, 0xbd,
    0xba, 0xb8, 0xb5, 0xb2, 0xaf, 0xac, 0xa9, 0xa6, 0xa3, 0xa0, 0x9d, 0x9a,
    0x97, 0x94, 0x91, 0x8e, 0x8a, 0x87, 0x84, 0x81, 0x7e, 0x7b, 0x78, 0x75,
    0x71, 0x6e, 0x6b, 0x68, 0x65, 0x62, 0x5f, 0x5c, 0x59, 0x56, 0x53, 0x50,
    0x4d, 0x4a, 0x47, 0x45, 0x42, 0x3f, 0x3c, 0x3a, 0x37, 0x35, 0x32, 0x30,
    0x2d, 0x2b, 0x28, 0x26, 0x24, 0x22, 0x20, 0x1e, 0x1c, 0x1a, 0x18, 0x16,
    0x14, 0x13, 0x11, 0x10, 0xe,  0xd,  0xb,  0xa,  0x9,  0x8,  0x7,  0x6,
    0x5,  0x4,  0x3,  0x3,  0x2,  0x2,  0x1,  0x1,  0x0,  0x0,  0x0,  0x0,
    0x0,  0x0,  0x0,  0x1,  0x1,  0x1,  0x2,  0x2,  0x3,  0x4,  0x4,  0x5,
    0x6,  0x7,  0x8,  0x9,  0xb,  0xc,  0xd,  0xf,  0x10, 0x12, 0x14, 0x15,
    0x17, 0x19, 0x1b, 0x1d, 0x1f, 0x21, 0x23, 0x25, 0x27, 0x2a, 0x2c, 0x2e,
    0x31, 0x33, 0x36, 0x38, 0x3b, 0x3e, 0x40, 0x43, 0x46, 0x49, 0x4c, 0x4f,
    0x51, 0x54, 0x57, 0x5a, 0x5d, 0x60, 0x63, 0x67, 0x6a, 0x6d, 0x70, 0x73,
    0x76, 0x79, 0x7c, 0x80}; 


// User interface parametes









#endif