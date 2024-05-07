#include QMK_KEYBOARD_H

#define _______ KC_TRNS

typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    LT(1, KC_ESC),   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_INSERT, KC_DEL,
    KC_GRV,          KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,   KC_BSPC,   KC_HOME,
    KC_TAB,          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,             KC_PGUP,
    KC_CAPS,         KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,    KC_PGDN,
    KC_LSHIFT,       KC_NO,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSHIFT,          KC_UP,     KC_END,
    KC_LCTL,         KC_LGUI,  KC_LALT,  KC_SPC,             MO(1),    KC_SPC,             LCTL(KC_C),         MO(1),    LCTL(KC_V), KC_LEFT,          KC_DOWN,   KC_RGHT
  ),

  [1] = LAYOUT(
    KC_WWW_FAVORITES,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,   KC_PAUSE, KC_SLCK,  _______,
    _______,           _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,           RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,           _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,           _______,  _______,  _______,  BL_DEC,   BL_TOGG,  BL_INC,   BL_STEP,  _______,  _______,  _______,  _______,  _______,            KC_AUDIO_VOL_UP,  _______,
    _______,           _______,  _______,                      _______,  _______,  _______,                      _______,  RESET,    KC_AUDIO_MUTE,  KC_MEDIA_PLAY_PAUSE,  KC_AUDIO_VOL_DOWN,  KC_MEDIA_NEXT_TRACK
  ),
};

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRB |= (1 << 2); PORTB &= ~(1 << 2);
    } else {
        DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
      case 1:
          rgblight_setrgb(RGB_RGB_WHITE);
          break;
      default: // for any other layers, or the default layer
          if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
            rgblight_setrgb(RGB_RED);
          } else {
            rgblight_setrgb (RGB_BLUE);
          }
          break;
  }
  return state;
}
