#include "draw.h"

#define TOSTR(x) #x
#define MOVETO(x, y) "\033[%hhd;%hhdH%s", y, x

struct pixel {
    unsigned int status : 4;
    unsigned int prev_status : 4;
};

char template[] = "\
┏━━━━━━━━━━━━━━━━━━━━┓\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┃                    ┃░░\n\
┗━━━━━━━━━━━━━━━━━━━━┛░░\n\
 ░░░░░░░░░░░░░░░░░░░░░░░";


struct pixel state[200];


void set_pixel(uint8_t x, uint8_t y, bool fill) {
    state[y*10+x].status = (fill ? 1 : 0);
    return;
}


void update_screen() {
    uint8_t x, y;
    bool fill;
    struct pixel *pxl;
    for (y=0; y<20; y++) {
        for (x=0; x<10; x++) {
            pxl = &state[y*10+x];
            printf(MOVETO(1, 1), "");
            if(pxl->status == pxl->prev_status) continue;
            if(pxl->status) printf(MOVETO(x*2+2, y+2), "██");
            else printf(MOVETO(x*2+2, y+2), "  ");
            pxl->prev_status = pxl->status;
        }
    }
    return;
}


void screen_init() {
    printf(MOVETO(1, 1), template);
}


void screen_draw(bool *playfield, bool *block, uint8_t block_len, uint8_t block_x, uint8_t block_y) {
    uint8_t i, x, y, realx, realy;
    for (i=0; i<200; i++) {
        set_pixel(i % 10, i / 10, playfield[i]);
    }

    for (y=0; y<block_len; y++) {
        realy = block_y + y;
        if (realy < 0 || realy >= 20) continue;
        for (x=0; x<block_len; x++) {
            realx = block_x + x;
            if (realx < 0 || realx >= 10) continue;
            if (block[y*block_len+x]) set_pixel(realx, realy, 1);
        }
    }

    update_screen();

    return;
}
