/**
 * This file was generated automatically using scripts/fontmaking/Images2FontHeaders.py
 *
 * Font: Roboto
 * Font Size: 24pt
 * Generated On: 13 October 2024 @ 7:31 PM
 * License: https://www.apache.org/licenses/LICENSE-2.0.txt
 */

#pragma once

#include "AbstractFont.h"

#include <vector>

namespace epaperapi::fonts {
class Roboto_24pt : public AbstractFont {
  private:
    const std::string charset =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";

  public:
    Roboto_24pt() {}
    uint8_t GetFontSize() const override { return 24; }
    uint8_t GetHeight() const override { return 29; }
    std::string GetFontName() override { return "Roboto"; }
    std::string GetCharacterSet() const override { return charset; }
    const uint8_t* GetBitmapData() const override { return bitmap.data(); }
    const uint8_t* GetCharacterWidths() const override { return charWidths.data(); }

  private:
    const std::vector<uint8_t> charWidths = {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 13, 9,  13, 13, 6,
                                             7,  13, 6,  21, 13, 14, 13, 14, 8,  12, 8,  13, 12, 18, 12, 12, 12, 16, 15,
                                             16, 16, 14, 13, 16, 17, 7,  13, 16, 13, 21, 17, 17, 15, 17, 15, 14, 14, 16,
                                             15, 21, 15, 15, 14, 6,  8,  15, 13, 18, 15, 4,  8,  8,  10, 14, 5,  7,  6,
                                             10, 6,  5,  12, 13, 13, 11, 22, 7,  10, 6,  10, 11, 7,  8,  6,  8,  16, 6};

    const std::vector<uint8_t> bitmap = {
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   62,  3,   252, 56,  225, 131, 140, 12,  224, 103, 3,   56,  25,
        192, 206, 6,   112, 51,  129, 140, 12,  96,  227, 142, 15,  240, 62,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   1,   240, 63,  129, 28,  0,   224, 7,   0,   56,
        1,   192, 14,  0,   112, 3,   128, 28,  0,   224, 7,   0,   56,  1,   192, 14,  0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   62,  3,   252, 56,  227, 131, 152, 12,  0,
        96,  6,   0,   48,  3,   0,   48,  3,   0,   48,  3,   0,   48,  3,   128, 63,  253, 255, 224, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   62,  3,   252, 56,  227, 131, 152,
        28,  0,   192, 14,  3,   224, 31,  0,   28,  0,   112, 1,   152, 12,  224, 227, 134, 31,  240, 62,  0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   128, 60,  1,   224,
        31,  1,   184, 13,  192, 206, 12,  112, 99,  134, 28,  96,  227, 255, 223, 254, 1,   192, 14,  0,   112, 3,   128,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   127, 195, 254,
        24,  0,   192, 6,   0,   48,  1,   252, 15,  240, 225, 192, 6,   0,   48,  1,   204, 12,  96,  99,  135, 15,  240,
        31,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,
        0,   248, 14,  0,   224, 14,  0,   96,  3,   124, 31,  240, 225, 198, 6,   48,  49,  129, 140, 12,  96,  97,  135,
        15,  240, 30,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        1,   255, 207, 254, 0,   48,  3,   0,   24,  1,   192, 12,  0,   96,  6,   0,   48,  3,   0,   24,  1,   128, 12,
        0,   224, 6,   0,   112, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   62,  3,   252, 56,  225, 131, 140, 12,  96,  227, 134, 15,  224, 127, 7,   12,  48,  51,  129, 156,
        12,  224, 99,  135, 15,  240, 62,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   62,  3,   248, 56,  227, 131, 24,  28,  192, 102, 3,   56,  56,  227, 199, 254, 15,  48,
        3,   0,   24,  1,   192, 28,  7,   192, 56,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   224, 127, 131, 14,  56,  48,  1,   129, 252,
        63,  225, 131, 28,  24,  192, 199, 14,  31,  240, 125, 192, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   56,  1,   192, 14,  0,   112, 3,   128, 29,  224, 255, 199, 142, 56,  57,  192,
        206, 6,   112, 51,  129, 156, 12,  224, 231, 142, 55,  241, 158, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   224, 63,  195, 134, 24,
        25,  192, 206, 0,   96,  3,   128, 28,  0,   96,  99,  134, 15,  240, 62,  0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   192, 3,   0,   12,  0,   48,  0,   192, 251, 7,
        252, 56,  112, 192, 199, 3,   28,  12,  112, 49,  192, 199, 3,   12,  12,  56,  112, 127, 192, 251, 0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   1,   224, 63,  195, 134, 24,  57,  192, 207, 254, 127, 243, 0,   28,  0,   96,  3,   135, 15,  240, 63,  0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   120, 124, 48,  24,  12,  31,  143,
        193, 128, 192, 96,  48,  24,  12,  6,   3,   1,   128, 192, 96,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   204, 127, 99,  143, 56,  57,  129, 204, 14,
        96,  115, 3,   152, 28,  224, 227, 143, 31,  248, 61,  192, 14,  32,  97,  135, 15,  240, 31,  0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   24,  0,   192, 6,   0,   48,  1,   128, 13,  240, 127, 195, 142, 24,  48,  193,
        134, 12,  48,  97,  131, 12,  24,  96,  195, 6,   24,  48,  193, 128, 0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   3,   12,  0,   3,   12,  48,  195, 12,  48,  195, 12,  48,  195, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   12,  24,  0,   0,   193, 131, 6,   12,  24,  48,  96,  193, 131, 6,   12,  24,  48,  99,
        199, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   24,  0,   192, 6,   0,   48,  1,   128, 12,  60,  97,  131,
        24,  25,  128, 220, 7,   192, 62,  1,   216, 12,  224, 99,  131, 12,  24,  48,  193, 192, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   195, 12,  48,  195, 12,  48,  195, 12,  48,  195, 12,  48,  195, 0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   13,  241, 224, 127, 223, 195, 143, 142, 24,  56,  48,  193, 193, 134, 14,  12,
        48,  112, 97,  131, 131, 12,  28,  24,  96,  224, 195, 7,   6,   24,  56,  48,  193, 193, 128, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   13,  240, 127, 195, 142, 24,  48,  193, 134, 12,  48,  97,  131, 12,  24,  96,  195, 6,
        24,  48,  193, 128, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   120, 7,   248, 56,  112, 192, 199, 3,   152, 6,   96,  25,  128, 103,
        3,   140, 12,  56,  112, 127, 128, 120, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   25,  224, 223, 199, 142, 56,  57,  192, 206, 6,   112,
        51,  129, 156, 12,  224, 231, 142, 63,  241, 222, 14,  0,   112, 3,   128, 28,  0,   224, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   251, 7,   252, 56,  112, 192, 199,
        3,   28,  12,  96,  49,  128, 199, 3,   12,  12,  56,  112, 127, 192, 251, 0,   12,  0,   48,  0,   192, 3,   0,
        12,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   55,  63,  56,  48,  48,  48,  48,  48,  48,  48,
        48,  48,  48,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   15,  131, 252, 48,  231, 6,   112, 3,   224, 31,  192, 30,  0,   102, 6,   112, 227, 252, 15,  128, 0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   56,  56,  56,  254, 254, 56,  56,  56,  56,
        56,  56,  56,  56,  24,  30,  14,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   28,  24,  224, 199, 6,   56,  49,  193, 142, 12,  112, 99,  131, 28,  24,  96,  195,
        14,  31,  240, 125, 128, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   96,  102, 6,   112, 227, 12,  48,  193, 152, 25,  129, 152, 15,  0,   240, 15,
        0,   96,  6,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   14,  12,  25,  131, 6,   97,  225, 156, 120, 195, 30,
        48,  204, 204, 51,  51,  6,   205, 129, 161, 96,  120, 120, 30,  28,  3,   3,   0,   192, 192, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   96,  227, 12,  57,  193, 152, 15,  0,   240, 6,   0,   240, 31,  1,   152, 57,  199, 12,  224, 96,  0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        224, 230, 12,  96,  199, 28,  49,  131, 24,  57,  129, 176, 27,  1,   240, 14,  0,   224, 6,   0,   192, 12,  1,
        128, 120, 7,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   127, 231,
        254, 0,   192, 24,  3,   128, 112, 6,   0,   192, 28,  3,   128, 48,  7,   254, 127, 224, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   128, 3,   192, 3,   192, 3,
        192, 6,   96,  6,   96,  6,   96,  12,  48,  12,  48,  28,  56,  24,  24,  31,  248, 63,  252, 48,  12,  112, 14,
        96,  6,   224, 7,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   15,  248, 31,  248, 48,  56,  96,  48,  192, 97,  128, 195, 3,   7,   252, 15,  252, 24,  28,
        48,  24,  96,  56,  192, 113, 128, 195, 3,   135, 254, 15,  248, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   224, 15,  248, 28,  56,  56,  28,  48,
        12,  48,  12,  112, 2,   112, 0,   112, 0,   112, 0,   112, 0,   48,  14,  48,  12,  56,  12,  28,  56,  15,  248,
        7,   224, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   63,  192, 63,  240, 48,  120, 48,  24,  48,  28,  48,  12,  48,  12,  48,  12,  48,  12,  48,  12,
        48,  12,  48,  12,  48,  28,  48,  24,  48,  120, 63,  240, 63,  192, 0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   255, 143, 254, 48,  0,   192, 3,   0,   12,
        0,   48,  0,   255, 195, 255, 12,  0,   48,  0,   192, 3,   0,   12,  0,   48,  0,   255, 227, 255, 128, 0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 231, 255, 48,  1,
        128, 12,  0,   96,  3,   0,   24,  0,   255, 135, 252, 48,  1,   128, 12,  0,   96,  3,   0,   24,  0,   192, 0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,
        224, 15,  248, 28,  28,  56,  12,  48,  12,  48,  2,   112, 0,   112, 0,   112, 0,   112, 254, 112, 254, 48,  14,
        48,  14,  56,  14,  28,  14,  15,  252, 3,   240, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   192, 24,  96,  12,  48,  6,   24,  3,   12,  1,   134,
        0,   195, 0,   97,  255, 240, 255, 248, 96,  12,  48,  6,   24,  3,   12,  1,   134, 0,   195, 0,   97,  128, 48,
        192, 24,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   12,  24,  48,
        96,  193, 131, 6,   12,  24,  48,  96,  193, 131, 6,   12,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   1,   128, 12,  0,   96,  3,   0,   24,  0,   192, 6,   0,   48,  1,   128, 12,  0,   96,
        3,   24,  24,  192, 199, 14,  31,  224, 126, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   48,  30,  48,  56,  48,  48,  48,  96,  48,  224, 49,  192, 51,  128,
        55,  0,   63,  128, 61,  128, 57,  192, 48,  224, 48,  112, 48,  48,  48,  56,  48,  28,  48,  14,  0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   192, 6,   0,   48,
        1,   128, 12,  0,   96,  3,   0,   24,  0,   192, 6,   0,   48,  1,   128, 12,  0,   96,  3,   0,   31,  248, 255,
        192, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   224, 3,   135, 0,   60,  60,  1,   225, 224, 15,  13,  128, 216, 108, 6,   195, 112, 118, 25,
        131, 48,  204, 25,  134, 49,  140, 49,  140, 97,  142, 227, 12,  54,  24,  97,  176, 195, 7,   6,   24,  56,  48,
        193, 193, 128, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   224, 24,  112, 12,  60,  6,   30,  3,   13,  129, 134, 224, 195, 48,
        97,  140, 48,  199, 24,  97,  140, 48,  230, 24,  59,  12,  13,  134, 7,   195, 1,   225, 128, 112, 192, 56,  0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   15,  128, 31,  240, 28,  60,  28,  6,   12,  3,   134, 0,   199, 0,   99,  128, 49,  192, 24,  224, 12,
        112, 6,   24,  3,   12,  3,   135, 1,   129, 195, 192, 127, 192, 15,  128, 0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   15,  248, 31,  252, 48,  56,  96,
        56,  192, 49,  128, 99,  0,   198, 3,   140, 14,  31,  252, 63,  224, 96,  0,   192, 1,   128, 3,   0,   6,   0,
        12,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   15,  128, 31,  240, 28,  28,  12,  6,   12,  3,   134, 0,   195, 0,   97,  128, 48,  192, 24,
        96,  12,  48,  6,   24,  3,   12,  3,   131, 1,   129, 193, 192, 127, 192, 15,  224, 0,   56,  0,   14,  0,   2,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   15,  248, 31,  248, 48,
        56,  96,  56,  192, 113, 128, 227, 1,   198, 7,   15,  252, 31,  240, 48,  96,  96,  224, 192, 193, 129, 195, 1,
        134, 3,   140, 3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   252, 7,   252, 56,  113, 192, 231, 1,   156, 0,   56,  0,   124, 0,   252, 0,   124, 0,   56,
        0,   102, 1,   156, 6,   56,  56,  127, 192, 252, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   7,   255, 223, 255, 3,   0,   12,  0,   48,  0,   192, 3,   0,   12,  0,
        48,  0,   192, 3,   0,   12,  0,   48,  0,   192, 3,   0,   12,  0,   48,  0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   48,  12,  48,  12,  48,  12,  48,  12,
        48,  12,  48,  12,  48,  12,  48,  12,  48,  12,  48,  12,  48,  12,  48,  12,  48,  12,  56,  28,  28,  56,  15,
        240, 7,   224, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   56,  3,   176, 6,   112, 28,  96,  56,  192, 97,  193, 193, 131, 3,   6,   7,   28,  6,   48,  12,
        96,  29,  192, 27,  0,   54,  0,   56,  0,   112, 0,   224, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   128, 192, 236, 14,  6,   112,
        112, 49,  131, 193, 140, 30,  28,  97,  176, 195, 12,  198, 12,  102, 48,  102, 49,  131, 49,  152, 25,  134, 192,
        108, 54,  3,   193, 176, 30,  5,   128, 240, 56,  7,   1,   192, 24,  14,  0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   28,  7,   24,
        12,  56,  56,  56,  224, 49,  128, 119, 0,   124, 0,   120, 0,   224, 1,   224, 6,   192, 29,  192, 49,  192, 225,
        131, 131, 134, 3,   28,  7,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   56,  7,   56,  12,  48,  56,  112, 96,  97,  192, 227, 0,   206, 1,   216, 1,   240,
        3,   192, 3,   0,   6,   0,   12,  0,   24,  0,   48,  0,   96,  0,   192, 0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,   255, 159, 254, 0,   56,  1,   192, 6,
        0,   48,  1,   192, 14,  0,   48,  1,   192, 14,  0,   48,  1,   128, 14,  0,   112, 1,   255, 231, 255, 128, 0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   12,  48,  195, 12,  48,  195, 12,  48,  192,
        0,   0,   195, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   36,  36,  36,  36,  36,  36,  0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   198, 1,   140, 3,   16,  4,   32,  255, 241, 255, 224, 99,  0,   196, 1,   8,   2,   48,  127, 252,
        255, 248, 49,  128, 98,  0,   140, 1,   24,  6,   48,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   6,   0,   48,  1,   128, 62,  3,   252, 56,  97,  131, 140, 12,  96,  3,   128, 15,  0,
        63,  0,   60,  0,   112, 1,   156, 12,  224, 99,  135, 15,  240, 63,  0,   96,  3,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   224, 0,   204, 0,   99,  8,   24,
        71,  6,   17,  1,   140, 192, 51,  32,  7,   152, 0,   12,  0,   2,   120, 1,   179, 0,   200, 64,  34,  24,  24,
        134, 12,  33,  3,   12,  192, 1,   224, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   224, 15,  224, 24,  224, 48,  192, 97,  128, 198, 1,   248,
        1,   224, 3,   192, 29,  198, 49,  140, 193, 185, 129, 227, 129, 195, 135, 135, 255, 131, 227, 128, 0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   102, 102, 96,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   2,   7,   6,   12,  24,  24,  24,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  56,
        24,  24,  12,  6,   7,   2,   0,   0,   0,   0,   64,  224, 48,  48,  24,  24,  12,  12,  12,  12,  14,  14,  14,
        14,  14,  12,  12,  12,  12,  24,  24,  48,  48,  96,  192, 0,   0,   0,   0,   0,   0,   0,   0,   192, 48,  12,
        27,  127, 252, 48,  30,  12,  195, 56,  132, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   12,  0,   48,  0,
        192, 3,   0,   12,  7,   255, 159, 254, 3,   0,   12,  0,   48,  0,   192, 3,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,   57,  204,
        102, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   126, 252, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        195, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   24,  6,   3,   0,   192, 32,  24,  6,   3,
        0,   192, 32,  24,  6,   3,   0,   192, 32,  24,  6,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   3,   12,  0,   0,   0,   0,   0,   0,   0,   195, 0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   28,  0,   0,   0,   0,   0,   3,   24,  204, 102, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   64,  28,  7,   193, 240, 124, 6,   0,   120, 1,   240, 7,   192, 28,  0,
        64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   127, 227, 255, 0,   0,   0,   0,   0,   63,  241, 255, 128, 0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   8,   0,   112, 3,   224, 7,   192, 7,   128, 14,  1,   224, 124, 15,  128,
        112, 2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   7,   193, 252, 113, 204, 24,  3,   0,   96,  12,  3,   0,   224, 48,  14,  1,   128, 48,  0,   0,   0,
        24,  3,   128, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   15,  224, 0,   255, 224, 7,   3,   192, 56,  3,   129, 128, 6,   6,   15,  12,  48,  126,
        48,  195, 24,  66,  24,  97,  8,   97,  132, 97,  134, 17,  140, 16,  70,  48,  65,  24,  195, 12,  33,  158, 48,
        199, 223, 131, 14,  60,  6,   0,   0,   28,  0,   0,   60,  24,  0,   127, 224, 0,   126, 0,   0,   0,   0,   0,
        0,   1,   227, 198, 12,  24,  48,  96,  193, 131, 6,   12,  24,  48,  96,  193, 131, 6,   12,  24,  48,  120, 240,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   14,  1,   128, 112, 12,  3,   0,   96,  24,  7,   0,   192, 48,  6,
        1,   128, 96,  12,  3,   0,   96,  24,  7,   0,   0,   0,   0,   0,   0,   0,   0,   0,   62,  248, 227, 142, 56,
        227, 142, 56,  227, 142, 56,  227, 142, 56,  227, 142, 59,  239, 128, 0,   0,   0,   0,   0,   0,   0,   0,   0,
        192, 48,  30,  7,   131, 48,  204, 97,  152, 96,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,   255, 255, 224, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   14,  14,  14,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   3,   7,   12,  28,  24,  24,  24,  24,  24,  24,  56,  112, 112, 56,  24,  24,
        24,  24,  24,  28,  12,  14,  3,   0,   0,   0,   0,   0,   0,   3,   12,  48,  195, 12,  48,  195, 12,  48,  195,
        12,  48,  195, 12,  48,  192, 0,   0,   0,   0,   0,   0,   192, 224, 48,  48,  24,  24,  24,  24,  24,  24,  28,
        14,  14,  28,  24,  24,  24,  24,  24,  56,  48,  96,  192, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  6,   63,  6,
        51,  204, 96,  252, 96,  120, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0
    };
};
} // namespace epaperapi::fonts
