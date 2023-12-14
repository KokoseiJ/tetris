#ifndef INCL_DRAW_H
#define INCL_DRAW_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void screen_init();
void screen_draw(bool *playfield, uint8_t **block, uint8_t block_len, uint8_t block_x, uint8_t block_y);
void draw_pixel(uint8_t x, uint8_t y, bool fill);

#endif
