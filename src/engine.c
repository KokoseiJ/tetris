#include "engine.h"


bool check_collision(bool *playfield, bool *block, uint8_t block_len, int8_t block_x, int8_t block_y) {
    int8_t x, y, realx, realy;

    for (y=0; y<block_len; y++) {
        realy = block_y + y;
        if (realy < 0) continue;
        for (x=0; x<block_len; x++) {
            realx = block_x + x;
            if (block[y*block_len+x]) {
                if (realy >= 20 || realx < 0 || realx >= 10)
                    return true;
                if (playfield[realy*10+realx]) return true;
            }
        }
    }

    return false;
}

void lock_block(bool *playfield, bool *block, uint8_t block_len, int8_t block_x, int8_t block_y) {
    int8_t x, y, realx, realy;

    for (y=0; y<block_len; y++) {
        realy = block_y + y;
        for (x=0; x<block_len; x++) {
            realx = block_x + x;
            if (block[y*block_len+x]) {
                playfield[realy*10+realx] = true;
            }
        }
    }
}


bool check_tetris(bool *playfield, uint8_t line) {
    uint8_t check=0, x, linecount;

    for (x=0; x<10; x++) 
        check += (playfield[line * 10 + x] ? 1 : 0);

    return check == 10;
}


void remove_line(bool *playfield, uint8_t line) {
    if (line == 20) {
        memset(playfield, 0, 10);
    } else {
        memcpy(playfield+10, playfield, 10 * line);
    }
    return;
}

uint64_t utime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_nsec / 1000 + ts.tv_sec * 1000000);
}


uint64_t wait_fps(uint64_t last, uint16_t fps) {
    uint64_t next = last + 1000000 / fps;
    usleep(next - utime());
    return next;
}


uint8_t get_gravity(uint8_t level) {
    if (level < 9)
        return 48 - 5 * level;
    else if (level < 19)
        return 6 - (level - 7) / 3;
    else if (level < 29)
        return 2;
    else
        return 1;
}
