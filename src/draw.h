#ifndef INCL_DRAW_H
#define INCL_DRAW_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void screen_init();
void screen_draw(bool *playfield, bool *block, uint8_t block_len, uint8_t block_x, uint8_t block_y);

#endif
