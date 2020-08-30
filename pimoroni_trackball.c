#include "pimoroni_trackball.h"
#include "i2c_master.h"

static uint8_t scrolling      = 0;
static int16_t x_offset       = 0;
static int16_t y_offset       = 0;
static int16_t h_offset       = 0;
static int16_t v_offset       = 0;
static int16_t precisionSpeed = 0;

static bool left_down = false;
static bool right_down = false;
static bool middle_down = false;

#ifndef I2C_TIMEOUT
#    define I2C_TIMEOUT 35
#endif

void trackball_set_rgbw(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    uint8_t data[] = {0x00, red, green, blue, white};
    i2c_transmit(TRACKBALL_WRITE, data, sizeof(data), I2C_TIMEOUT);
}

void update_member(int8_t* member, int16_t* offset) {
    if (*offset > 127) {
        *member = 127;
        *offset -= 127;
    } else if (*offset < -127) {
        *member = -127;
        *offset += 127;
    } else {
        *member = *offset;
        *offset = 0;
    }
}

int16_t trackball_get_precision(void) { return precisionSpeed; }
void    trackball_set_precision(int16_t precision) { precisionSpeed = precision; }
bool    trackball_is_scrolling(void) { return scrolling; }
void    trackball_set_scrolling(bool scroll) { scrolling = scroll; }

void trackball_set_left(bool pressed) { left_down = pressed; }
void trackball_set_right(bool pressed) { right_down = pressed; }
void trackball_set_middle(bool pressed) { middle_down = pressed; }

__attribute__((weak)) void pointing_device_init(void) { trackball_set_rgbw(0x00,0x00,0x00,0x00); }

/*int16_t get_speed(int16_t val)
{
    if (val < 0) { val = -val; }
    if (val < 10) { return 1; }
    if (val < 100) { return 4; }
    return 8;
}*/

struct Speed {
    int16_t value;
    int16_t multiplier;
};

int16_t get_speed(const struct Speed* speeds, int8_t length, int16_t val)
{
    if (val < 0) { val = -val; }
    for (int16_t i = 0; i < length - 1; ++i) {
        if (val < speeds[i].value) {
            return speeds[i].multiplier;
        }
    }

    return speeds[length-1].multiplier;
}

const struct Speed x_speeds[] = {
    { .value = 10, .multiplier = 1 },
    { .value = 100, .multiplier = 2 },
    { .value = 150, .multiplier = 4 },
    { .value = 0, .multiplier = 8 },
};

const struct Speed y_speeds[] = {
    { .value = 10, .multiplier = 1 },
    { .value = 100, .multiplier = 6 },
    { .value = 0, .multiplier = 10 },
};

#define ARRAY_LENGTH(X) (sizeof(X) / sizeof(X[0]))

void pointing_device_task(void) {
    //static bool debounce;
    //static uint16_t debounce_timer;
    uint8_t state[5] = {};
    if (i2c_readReg(TRACKBALL_WRITE, 0x04, state, 5, I2C_TIMEOUT) == I2C_STATUS_SUCCESS) {
        //if (!state[4] && !debounce) {
            int16_t x = state[2] - state[3];
            int16_t y = state[1] - state[0];
            int8_t sx = x < 0 ? -1 : 1;
            int8_t sy = y < 0 ? -1 : 1;
            // Apply the multiplier in stages:
            // 0-100 1x
            // 100-300 2x
            // 400+ 8x or something like that
            if (scrolling) {
                x = x * x / 2 * (1 + precisionSpeed) * sx;
                y = y * y / 2 * (1 + precisionSpeed) * sy;
                h_offset -= x;
                v_offset += y;
            } else {
                int16_t xspeed = get_speed(&x_speeds[0], ARRAY_LENGTH(x_speeds), x);
                int16_t yspeed = get_speed(&y_speeds[0], ARRAY_LENGTH(y_speeds), y);
                x = x * x * (xspeed + precisionSpeed) * sx;
                y = y * y * (yspeed + precisionSpeed) * sy;
                //x = x * x * precisionSpeed * sx;
                //y = y * y * precisionSpeed * sy;
                x_offset -= x;
                y_offset -= y;
            }
        //} else {
        //    if (state[4]) {
        //        debounce = true;
        //        debounce_timer = timer_read();
        //    }
//        }
    }

    //if (timer_elapsed(debounce_timer) > MOUSE_DEBOUNCE) debounce = false;

    report_mouse_t mouse = pointing_device_get_report();

    const bool trackball_pressed = state[4] & (1 << 7);
    if (trackball_pressed || left_down) {
        mouse.buttons |= MOUSE_BTN1;
    } else {
        mouse.buttons &= ~MOUSE_BTN1;
    }

    if (right_down) {
        mouse.buttons |= MOUSE_BTN2;
    } else {
        mouse.buttons &= ~MOUSE_BTN2;
    }

    if (middle_down) {
        mouse.buttons |= MOUSE_BTN3;
    } else {
        mouse.buttons &= ~MOUSE_BTN3;
    }

    update_member(&mouse.x, &x_offset);
    update_member(&mouse.y, &y_offset);
    update_member(&mouse.h, &h_offset);
    update_member(&mouse.v, &v_offset);

    pointing_device_set_report(mouse);
    pointing_device_send();
}
