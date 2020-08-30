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
  PM_LEFT,
  PM_RIGHT,
  PM_MIDDLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    KC_GRAVE,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,                                           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,       KC_EQUAL,       KC_DELETE,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           TG(1),                                          TG(2),          KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLASH,
    TT(2),          KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_ENTER,
    KC_LSHIFT,      LCTL_T(KC_Z),   KC_X,           KC_C,           KC_V,           KC_B,           KC_HYPR,                                        KC_MEH,         KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_QUES,        KC_RSHIFT,
    LT(1,KC_GRAVE), KC_QUOTE,       LALT(KC_LSHIFT),KC_LALT,        KC_LGUI,                                                                                                        KC_TRANSPARENT, KC_DOWN,        KC_LBRACKET,    KC_RBRACKET,    MO(1),
                                                                                                    LALT_T(KC_APPLICATION),KC_LGUI,        KC_LALT,        LCTL_T(KC_ESCAPE),
                                                                                                                    KC_HOME,        KC_PGUP,
                                                                                    KC_SPACE,       KC_BSPACE,      KC_END,         KC_PGDOWN,      KC_ESCAPE,      KC_ENTER
  ),
  [1] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_UP,          KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_F12,
    KC_TRANSPARENT, KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRAVE,                                                                       KC_DOWN,        KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_PERC,        KC_CIRC,        KC_LBRACKET,    KC_RBRACKET,    KC_TILD,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_AMPR,        KC_1,           KC_2,           KC_3,           KC_BSLASH,      KC_TRANSPARENT,
    KC_TRANSPARENT, KC_EQUAL,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_DOT,         KC_0,           KC_EQUAL,       KC_TRANSPARENT,
                                                                                                    RGB_MOD,        HSV_172_255_255,RGB_TOG,        RGB_SLD,
                                                                                                                    HSV_86_255_128, KC_TRANSPARENT,
                                                                                    RGB_VAD,        RGB_VAI,        HSV_27_255_255, KC_TRANSPARENT, RGB_HUD,        RGB_HUI
  ),
  [2] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, PM_PRECISION,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,KC_UP,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, PM_RIGHT,     PM_MIDDLE,     PM_LEFT,     PM_SCROLL,                                                                           KC_MEDIA_PREV_TRACK,KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_MEDIA_NEXT_TRACK,KC_MEDIA_PLAY_PAUSE,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, WEBUSB_PAIR,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_WWW_BACK
  ),
};


void run_trackball_cleanup(void) {
    if (trackball_is_scrolling()) {
        trackball_set_rgbw(RGB_CYAN, 0x00);
    } else if (trackball_get_precision() != 0) {
        trackball_set_rgbw(RGB_GREEN, 0x00);
    } else {
        trackball_set_rgbw(0, 0, 0, 0);
    }
}

void keyboard_post_init_user(void)
{
//	trackball_set_rgbw(RGB_MAGENTA, 0x00);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
	  return false;
	case PM_LEFT:
	  trackball_set_left(record->event.pressed);
	  return false;
	case PM_RIGHT:
	  trackball_set_right(record->event.pressed);
	  return false;
	case PM_MIDDLE:
	  trackball_set_middle(record->event.pressed);
	  return false;
	case PM_PRECISION:
	  if (record->event.pressed) {
		trackball_set_precision(7);
	  } else {
		trackball_set_precision(0);
	  }
	  run_trackball_cleanup();
	  return false;
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
