#include QMK_KEYBOARD_H
#include "led.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FL 1

#define _______ KC_TRNS


enum custom_keycodes {
  EMAIL1 = SAFE_RANGE,
  EMAIL2,
  MACRO1,
  MACRO2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_ortho_6x4(
  KC_F22, MACRO1, EMAIL1, KC_F13,\
  KC_F23, MACRO2, EMAIL2, KC_F14,\
  KC_F24, KC_MSTP, KC_F19, KC_F15,\
  KC_MUTE, KC_MPRV, KC_F20, KC_F16,\
  KC_VOLD, KC_MPLY, KC_F21, KC_F17,\
  KC_VOLU, KC_MNXT, MO(_FL), KC_F18),


[_FL] = LAYOUT_ortho_6x4(
  RESET, BL_ON, KC_S, KC_L, \
  KC_L, BL_OFF, KC_S, KC_L, \
  RGB_TOG, RGB_SPD, KC_O, KC_L, \
  RGB_MOD, RGB_SPI, KC_O, KC_L, \
  RGB_VAD, RGB_SAD, KC_O, KC_L, \
  RGB_VAI, RGB_SAI, KC_TRNS, KC_L),
};


const uint16_t PROGMEM fn_actions[] = {
    [0] = MO(_FL),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
      case BL_TOGG:
         if (record->event.pressed) {
            cospad_bl_led_togg();
         }
         return false;
      case BL_ON:
         if (record->event.pressed) {
            cospad_bl_led_on();
         }
         return false;
      case BL_OFF:
         if(record->event.pressed) {
            cospad_bl_led_off();
         }
         return false;
      case EMAIL1:
        if (record->event.pressed) {
          SEND_STRING("kenneth.skertchly@gmail.com");
        }
        return true;
      case EMAIL2:
        if (record->event.pressed) {
          SEND_STRING("kenneth.skertchly@silvercar.com");
        }
        return true;
      case MACRO1:
        if (record->event.pressed) {
          SEND_STRING("alias l='ls -alh'");
        }
        return true;
      case MACRO2:
        if (record->event.pressed) {
          SEND_STRING("sudo !!"SS_TAP(X_ENTER));
        }
        return true;
      default:
         return true;
   }
}
