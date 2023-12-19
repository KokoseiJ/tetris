#ifndef INCL_DRAW_H
#define INCL_DRAW_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MOVETO(x, y) "\033[%hhd;%hhdH%s", y, x

void screen_init();
void screen_draw(bool *playfield, bool *block, uint8_t block_len, int8_t block_x, int8_t block_y);

#endif
