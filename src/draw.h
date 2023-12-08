#ifndef INCL_DRAW_H
#define INCL_DRAW_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

void screen_init();
void screen_draw(uint8_t *playfield, uint8_t **block, uint8_t block_x, uint8_t block_y);
void draw_pixel(uint8_t x, uint8_t y, uint8_t fill);

#endif
