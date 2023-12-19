#include "input.h"
#include "draw.h"
#include "engine.h"
#include "rotate.h"
#include "blocks.h"
#include <stdlib.h>
#include <time.h>


uint16_t level_multiplier[5] = {0, 40, 100, 300, 1200};

bool meow[200] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
bool empty[200] = {0,};

bool block[25] = {
    0, 0, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 0, 0
};

int main(int argc, char *argv[]) {
    TetrisKeyStatus pre_status, status;
    int8_t i, x, y, newx, newy, rotation, newrotation, lines_at_once;

    uint8_t cur, gravity, drop_framecount;
    uint16_t lines=0, level = 0;
    uint32_t score=0;

    uint64_t last_update = utime();
    bool is_fastdrop;
    bool playfield[200] = {0,};

    srand(time(0));
    status = (TetrisKeyStatus){0, 0, 0, 0, 0, 0};

    drop_framecount = 0;

    x = 3;
    y = -2;
    rotation = 0;
    cur = rand() % 7;

    if (argc >= 2) {
        level = strtol(argv[1], NULL, 10);
    }

    printf("level %d", level);

    gravity = get_gravity(level);

    input_init();
    screen_init();

    while(true) {
        newx = x;
        newy = y;

        pre_status = status;
        status = *input_status();
        // printf("%d %d %d %d %d %d", status.d_up, status.d_down, status.d_left, status.d_right, status.r_left, status.r_right);

        if (!pre_status.r_left && status.r_left) {
            newrotation = rotation - 1;
            if (newrotation < 0) newrotation = blocks[cur].cases - 1;
            if (!check_collision(playfield, blocks[cur].shapes[newrotation], blocks[cur].len, x, y))
                rotation = newrotation;
        }

        if (!pre_status.r_right && status.r_right) {
            if (!check_collision(playfield, blocks[cur].shapes[(rotation+1)%blocks[cur].cases], blocks[cur].len, x, y))
                rotation = (rotation + 1) % blocks[cur].cases;
        }

        if (!pre_status.d_left && status.d_left)
            newx--;
        if (!pre_status.d_right && status.d_right)
            newx++;
        if (!pre_status.d_up && status.d_up);
        if ((!pre_status.d_down || is_fastdrop) && status.d_down) is_fastdrop = true;
        else is_fastdrop = false;

        if (!check_collision(playfield, blocks[cur].shapes[rotation], 5, newx, y)) {
            x = newx;
        }

        if (drop_framecount >= (is_fastdrop ? 2 : gravity)) {
            newy++;
            if (check_collision(playfield, blocks[cur].shapes[rotation], blocks[cur].len, x, newy)) {
                lock_block(playfield, blocks[cur].shapes[rotation], blocks[cur].len, x, y);

                lines_at_once = 0;
                for (i=0; i<20; i++) {
                    if (check_tetris(playfield, i)) {
                        remove_line(playfield, i);
                        lines_at_once++;
                    };
                }

                score += level_multiplier[lines_at_once % 5] * 40 * (level+1);

                x = 3;
                y = -2;
                rotation = 0;
                cur = rand() % 7;
                is_fastdrop = false;
            } else y = newy;
            drop_framecount = 0;
        }

        drop_framecount++;

        screen_draw(playfield, blocks[cur].shapes[rotation], 5, x, y);

        printf(MOVETO(26, 2), "SCORE");
        printf(MOVETO(26, 3), "");
        printf("%06d", score);
        printf(MOVETO(26, 5), "LEVEL");
        printf(MOVETO(29, 6), "");
        printf("%02d", level);
        printf(MOVETO(25,23), "");
        printf("%d", gravity);

        last_update = wait_fps(last_update, 60);
    }
}
