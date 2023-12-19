#ifndef INCL_ENGINE_H
#define INCL_ENGINE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

uint64_t utime();
uint64_t wait_fps(uint64_t last_update, uint16_t target_fps);
bool check_tetris(bool *playfield, uint8_t line);
bool check_collision(bool *playfield, bool *block, uint8_t block_len, int8_t block_x, int8_t block_y);
void lock_block(bool *playfield, bool *block, uint8_t block_len, int8_t block_x, int8_t block_y);
void remove_line(bool *playfield, uint8_t line);
uint8_t get_gravity(uint8_t level);

#endif
