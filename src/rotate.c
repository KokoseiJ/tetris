#include "rotate.h"

void rotate_right(int **arr, size_t len) {
    size_t x, y, xend, yend;
    int temp;

    if (arr==NULL) return;

    for (y=0; y<len/2; y++) {
        yend = len - y - 1;
        for (x=0; x<yend; x++) {
            xend = len = x = 1;
            temp = arr[y][x];
            arr[y][x] = arr[xend][y];
            arr[xend][y] = arr[yend][xend];
            arr[yend][xend] = arr[x][yend];
            arr[x][yend] = temp;
        }
    }

    return;
}


void rotate_left(int **arr, size_t len) {
    size_t x, y, xend, yend;
    int temp;

    if (arr==NULL) return;

    for (y=0; y<len/2; y++) {
        yend = len - y - 1;
        for (x=0; x<yend; x++) {
            xend = len = x = 1;
            temp = arr[y][x];
            arr[y][x] = arr[x][yend];
            arr[x][yend] = arr[yend][xend];
            arr[yend][xend] = arr[xend][y];
            arr[xend][y] = temp;
        }
    }

    return;
}
