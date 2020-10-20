#include QMK_KEYBOARD_H
#include "version.h"
/*
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_bepo.h"
#include "keymap_italian.h"
#include "keymap_slovenian.h"
#include "keymap_danish.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"
*/

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)

#include "pimoroni_trackball.h"

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  HSV_172_255_255,
  HSV_86_255_128,
  HSV_27_255_255,
  PM_SCROLL,
  PM_PRECISION,
  PM_PRECISION_2,
  PM_PRECISION_3,
  PM_LEFT,
  PM_RIGHT,
  PM_MIDDLE,
  PM_LAYER_FAST,
  PM_LAYER_MID,
  PM_LAYER_SLOW,
  MO_LAYER_0,
  TOGGLE_DEBUG_MODE
};

//  struct action_layer_bitop {
//    uint8_t bits : 4;
//    uint8_t xbit : 1;
//    uint8_t part : 3;
//    uint8_t on : 2;
//    uint8_t op : 2;
//    uint8_t kind : 4;
//  } layer_bitop;
//  QK_LAYER_TAP = 0x4000-0x4FFF
//  QK_TOGGLE_LAYER = 0x5300-0x53FF
//  ON_PRESS = 1

#define LTP(layer, kc) (QK_LAYER_TOGGLE | (((layer)&0xF) << 8) | ((kc)&0xFF))

// 35332 - ON_RELEASE LAYER 2 [TG(2)]
// 35076 - ON_PRESS LAYER 2 [TG(2)]

#define _x_ KC_TRANSPARENT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    KC_ESCAPE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, /**/ KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPACE,
    KC_TAB,    KC_Q, KC_W, KC_E, KC_R, KC_T, MO(1),   /**/ KC_GRAVE,KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLASH,
    KC_LCTL,   KC_A, KC_S, KC_D, KC_F, KC_G,            /**/ KC_H,  KC_J, KC_K, KC_L, KC_SCOLON,  KC_ENTER,
    KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_QUOTE,     /**/ MO(1), KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT,

    TO(4), KC_DELETE, LALT(KC_LSHIFT), KC_LALT, KC_LGUI, /**/ KC_TRANSPARENT, KC_LBRACKET, KC_RBRACKET, KC_MEH, KC_RCTL,
                                 PM_LAYER_FAST, PM_LAYER_MID,        KC_HOME,        PM_LAYER_SLOW,
                                 TO(2),        KC_PGUP,
                                 KC_SPACE,       KC_BSPACE,      LT(2, KC_END),         KC_PGDOWN,      KC_ESCAPE,      KC_ENTER
  ),
  [1] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_F1,    KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 TT(3), KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    KC_TRANSPARENT, KC_EXLM,  KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_UP,          KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_F12,
    KC_TRANSPARENT, KC_HASH,  KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRAVE,                                                                       KC_DOWN,        KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_PERC,  KC_CIRC,        KC_LBRACKET,    KC_RBRACKET,    KC_TILD,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_AMPR,        KC_1,           KC_2,           KC_3,           KC_BSLASH,      KC_TRANSPARENT,
    KC_TRANSPARENT, KC_EQUAL, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_0,         KC_DOT,           KC_EQUAL,       KC_MINUS,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, PM_PRECISION, PM_PRECISION_2,           PM_PRECISION_3, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, PM_LEFT,KC_UP,          PM_RIGHT, PM_MIDDLE, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO, PM_RIGHT,     PM_MIDDLE,     PM_LEFT,     PM_SCROLL,                                                                           KC_MEDIA_PREV_TRACK,KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_MEDIA_NEXT_TRACK,KC_MEDIA_PLAY_PAUSE,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TO(0),                                 KC_TRANSPARENT, KC_WWW_FORWARD, KC_WWW_BACK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, WEBUSB_PAIR,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, MO_LAYER_0, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 TO(1), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TOGGLE_DEBUG_MODE,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    RGB_MOD,        HSV_172_255_255,RGB_TOG,        RGB_SLD,
                                                                                                                    HSV_86_255_128, KC_TRANSPARENT,
                                                                                    RGB_VAD,        RGB_VAI,        HSV_27_255_255, KC_TRANSPARENT, RGB_HUD,        RGB_HUI
  ),
  [4] = LAYOUT_ergodox_pretty(
    _x_, _x_, _x_, _x_, _x_, _x_, _x_,    _x_, _x_, _x_, _x_, _x_, _x_, _x_,
    _x_, _x_, _x_, _x_, _x_, _x_, _x_,    _x_, PM_MIDDLE, PM_LEFT, KC_UP, PM_RIGHT, _x_, _x_,
    _x_, _x_, _x_, _x_, _x_, _x_,         _x_, KC_LEFT, KC_DOWN, KC_RIGHT, _x_, _x_,
    _x_, _x_, _x_, _x_, _x_, _x_, _x_,    _x_, _x_, _x_, _x_, _x_, _x_, _x_,
    TO(5), _x_, PM_MIDDLE, PM_RIGHT, PM_LEFT,   _x_, _x_, _x_, _x_, _x_,
                   _x_, _x_, _x_, _x_,
                   TO(0), _x_,
                   _x_, _x_,  _x_, _x_, _x_, _x_ 
  ),
  [5] = LAYOUT_ergodox_pretty(
    _x_, _x_, _x_, _x_, _x_, _x_, _x_,    _x_, _x_, _x_, _x_, _x_, _x_, _x_,
    _x_, _x_, KC_UP, _x_, _x_, _x_, _x_,    _x_, PM_MIDDLE, PM_LEFT, KC_UP, PM_RIGHT, _x_, _x_,
    _x_, KC_LEFT, KC_DOWN, KC_RIGHT, _x_, _x_,         _x_, KC_LEFT, KC_DOWN, KC_RIGHT, _x_, _x_,
    _x_, _x_, _x_, _x_, _x_, _x_, _x_,    _x_, _x_, _x_, _x_, _x_, _x_, _x_,
    TO(4), _x_, PM_MIDDLE, PM_RIGHT, PM_LEFT,   _x_, _x_, _x_, _x_, _x_,
                   _x_, _x_, _x_, _x_,
                   TO(0), _x_,
                   _x_, _x_,  _x_, _x_, _x_, _x_ 
  ),
};

void run_trackball_cleanup(void) {
    if (trackball_is_scrolling()) {
      //  trackball_set_rgbw(RGB_CYAN, 0x00);
    } else if (trackball_get_precision() != 0) {
      //  trackball_set_rgbw(RGB_GREEN, 0x00);
    } else {
        //trackball_set_rgbw(0, 0, 0, 0);
    }
}

void keyboard_post_init_user(void)
{
//	trackball_set_rgbw(RGB_MAGENTA, 0x00);
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record)
{
  //uprintf("post record\n");
  if (pm_is_layer_oneshot_enabled()) {
      if (!record->event.pressed) {
          //uprintf("key released\n");
          pm_reset_layer();
      }
  }
}

void do_trackball_precision(uint16_t level, uint16_t keycode, keyrecord_t *record)
{
  if (record->event.pressed) {
    trackball_set_precision(level);
  } else if (trackball_get_precision() == level) {
    trackball_set_precision(0);
  }
  run_trackball_cleanup();
  post_process_record_user(keycode, record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    pm_cancel_layer_timer();
  }

  switch (keycode) {
    case 20496: // TO(2)
        if (record->event.pressed) {
            if (pm_is_layer_oneshot_enabled()) {
                // Cancel our reset to layer 2
                pm_cancel_layer_all();
                return false;
            }
        }
        return true;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_172_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(172,255,255);
      }
      return false;
    case HSV_86_255_128:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(86,255,128);
      }
      return false;
    case HSV_27_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(27,255,255);
      }
      return false;
	case PM_SCROLL:
	  trackball_set_scrolling(record->event.pressed);
	  run_trackball_cleanup();
      post_process_record_user(keycode, record);
	  return false;
	case PM_LEFT:
	  trackball_set_left(record->event.pressed);
      post_process_record_user(keycode, record);
	  return false;
	case PM_RIGHT:
	  trackball_set_right(record->event.pressed);
      post_process_record_user(keycode, record);
	  return false;
	case PM_MIDDLE:
	  trackball_set_middle(record->event.pressed);
      post_process_record_user(keycode, record);
	  return false;
	case PM_PRECISION:
      do_trackball_precision(2, keycode, record);
	  return false;
	case PM_PRECISION_2:
      do_trackball_precision(8, keycode, record);
	  return false;
	case PM_PRECISION_3:
      do_trackball_precision(16, keycode, record);
	  return false;
    case PM_LAYER_FAST:
      increase_layer_timer();
      post_process_record_user(keycode, record);
      return false;
    case PM_LAYER_MID:
      reset_layer_timer();
      post_process_record_user(keycode, record);
      return false;
    case PM_LAYER_SLOW:
      decrease_layer_timer();
      post_process_record_user(keycode, record);
      return false;
    case MO_LAYER_0:
      if (record->event.pressed) {
        layer_move(0);
      } else {
        layer_move(2);
      }
      post_process_record_user(keycode, record);
      return false;
	  /*
	case TOGGLE_DEBUG_MODE:
	  if (record->event.pressed) {
		  debug_enable = !debug_enable;
		  const uint16_t val = TG(2);
		  uprintf("%d\n", val);
		  uprintf("Debug mode is %d\n", debug_enable);
	  }
	  break;
	  */
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

  uint8_t layer = biton32(state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};
