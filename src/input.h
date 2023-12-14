#include <stdbool.h>
#include <stdint.h>

typedef struct TetrisKeyStatus {
    bool d_up;
    bool d_down;
    bool d_left;
    bool d_right;
    bool r_left;
    bool r_right;
} TetrisKeyStatus;

uint8_t input_init();
uint8_t input_cleanup();
TetrisKeyStatus *input_status();
