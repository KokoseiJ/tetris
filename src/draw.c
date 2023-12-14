#include "draw.h"

#define TOSTR(x) #x
#define MOVETO(x, y) "\033[%hhd;%hhdH%s", y, x

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


void draw_pixel(uint8_t x, uint8_t y, bool fill) {
    if (fill) printf(MOVETO(x*2+2, y+2), "██");
    else printf(MOVETO(x*2+2, y+2), "  ");
    return;
}


void screen_init() {
    printf(MOVETO(0, 0), template);
}


void screen_draw(bool *playfield, uint8_t **block, uint8_t block_len, uint8_t block_x, uint8_t block_y) {
    uint8_t i;
    for (i=0; i<200; i++) {
        draw_pixel(i % 10, i / 10, playfield[i]);
    }
    return;
}
