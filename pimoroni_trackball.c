#ifdef PIMORONI_TRACKBALL_ENABLE

#include "pimoroni_trackball.h"
#include "i2c_master.h"

#ifdef DEBUG_POLLING
    #include <print.h>
#endif

static uint8_t scrolling      = 0;
static int16_t x_offset       = 0;
static int16_t y_offset       = 0;
static int16_t h_offset       = 0;
static int16_t v_offset       = 0;
static int16_t precisionSpeed = 0;

static bool dirty = false;
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

void trackball_set_left(bool pressed) { 
    dirty |= pressed != left_down;
    left_down = pressed; 
}
void trackball_set_right(bool pressed) { 
    dirty |= pressed != right_down;
    right_down = pressed; 
}
void trackball_set_middle(bool pressed) { 
    dirty |= pressed != middle_down;
    middle_down = pressed; 
}

__attribute__((weak)) void pointing_device_init(void) { trackball_set_rgbw(0x00,0x00,0x00,0x00); }

inline int16_t max(int16_t x, int16_t y) {
    return x < y ? y : x;
}

uint16_t poll_timer = 0;
uint16_t poll_count = 0;
static bool trackball_pressed_prev = false;

uint16_t scroll_debounce = 0;
uint16_t layer_timer = 0;
bool is_layer_timer_canceled = false;
bool is_layer_oneshot_enabled = false;
uint16_t layer_cancel_count = 0;

bool pm_is_layer_oneshot_enabled(void)
{
    return is_layer_oneshot_enabled;
}

void pm_start_layer(void)
{
    layer_timer = timer_read();
    if (layer_state_is(0) && !pm_is_layer_oneshot_enabled()) {
        layer_cancel_count = 0;
        is_layer_timer_canceled = false;
        is_layer_oneshot_enabled = true;
        layer_move(2);
    }
}

void pm_cancel_layer_all(void)
{
    is_layer_oneshot_enabled = false;
}

void pm_cancel_layer_timer(void)
{
    // TODO - maybe instead of hard reset
    // we add a grace period?
    if (pm_is_layer_oneshot_enabled()) {
        ++layer_cancel_count;
        is_layer_timer_canceled = true;
    }
}

void pm_reset_layer(void)
{
    if (layer_cancel_count == 0) {
        layer_cancel_count = 1;
    }
    //uprintf("count is %d\n", layer_cancel_count);
    if (pm_is_layer_oneshot_enabled() && --layer_cancel_count == 0)
    {
        //uprintf("reset layer\n");
        is_layer_oneshot_enabled = false;
        if (layer_state_is(2)) {
            layer_move(0);
        }
    }
}

int layer_timer_speed = LAYER_TIMER_MID;
int layer_set_timer = 0;
bool layer_timer_on = false;

int min(int a, int b)
{
    return a < b ? a : b;
}

void set_layer_speed(int speed)
{
    layer_timer_speed = max(0, min(2000, speed));
    layer_set_timer = timer_read();
    layer_timer_on = true;
}

void reset_layer_timer(void)
{
    trackball_set_rgbw(200, 0, 0, 0);
    set_layer_speed(LAYER_TIMER_MID);
}

void increase_layer_timer(void)
{
    trackball_set_rgbw(200, 100, 0, 0);
    set_layer_speed(layer_timer_speed + 50);
}

void decrease_layer_timer(void)
{
    trackball_set_rgbw(0, 0, 0, 200);
    set_layer_speed(layer_timer_speed - 50);
}

void pm_check_timer(void)
{
    if (timer_elapsed(layer_timer) >= layer_timer_speed
            && pm_is_layer_oneshot_enabled()
            && !is_layer_timer_canceled) 
    {
        //uprintf("timer\n");
        is_layer_oneshot_enabled = false;
        if (layer_state_is(2)) {
            layer_move(0);
        }
    }
}

void pointing_device_task(void) {

#ifdef DEBUG_POLLING
    if (timer_elapsed(poll_timer) >= 1000)
    {
        poll_timer = timer_read();
        //uprintf("Poll count %u\n", poll_count);
        poll_count = 0;
    }
    ++poll_count;
#endif

    if (layer_timer_on
         && timer_elapsed(layer_set_timer) >= 500)
    {
        layer_set_timer = 0;
        layer_timer_on = false;
        trackball_set_rgbw(0, 0, 0, 0);
    }

    bool mouse_moved = false;
    uint8_t state[5] = {};
    if (i2c_readReg(TRACKBALL_WRITE, 0x04, state, 5, I2C_TIMEOUT) == I2C_STATUS_SUCCESS) {
            int16_t x = state[2] - state[3];
            int16_t y = state[1] - state[0];
            if (x != 0 || y != 0) {
                //uprintf("x %d y %d\n", x, y);
                mouse_moved = true;
                dirty = true;
            } else { goto no_data; }
            int8_t sx = x < 0 ? -1 : 1;
            int8_t sy = y < 0 ? -1 : 1;
            if (scrolling) {
                if (scroll_debounce == 0 || timer_elapsed(scroll_debounce) >= 15) {
                    scroll_debounce = timer_read();
                    x = abs(x);
                    y = abs(y);
                    x = x > 0 ? 1 : x;
                    y = y > 0 ? 1 : y;
                    x = x * (1 + precisionSpeed) * sx;
                    y = y * (1 + precisionSpeed) * sy;
                    h_offset = -x;
                    v_offset = y;
                   // uprintf("%d %d %d\n", x, y, v_offset);
                } else {
                    dirty = false;
                }
            } else {
                // This seems to feel OK if mouse acceleration is turned on
                // Seems to be okay at the same mouse acceleration as the
                // laptop trackpad
                x = x * x * (1 + precisionSpeed) * sx;
                y = y * y * (1 + precisionSpeed) * sy;

                // Mouse is rotated a bit
                x_offset -= x;
                y_offset -= y;
            }
    }
no_data: ;

    if (mouse_moved)
    {
        pm_start_layer();
    }
    else
    {
        pm_check_timer();
    }

    const bool trackball_pressed = state[4] & (1 << 7);
    dirty |= trackball_pressed_prev != trackball_pressed;
    trackball_pressed_prev = trackball_pressed;
    // If we don't need to send a report, don't.
    // Seems to speed up the keyboard polling
    // by 6-7x from 125hz (USB polling speed)
    // to ~680hz. Granted it lowers back down
    // when using the mouse. But should make
    // the keyboard a bit more responsive when
    // not using the mouse.
    if (dirty) {
        dirty = false;

        report_mouse_t mouse = pointing_device_get_report();

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
}
#endif
