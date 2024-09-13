// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_keycodes {
    MACRO1 = SAFE_RANGE,
    MACRO2,
    MACRO3
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    LT(0, KC_R),    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    LT(1,KC_F),    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(2),   KC_APP,  KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_tkl_ansi(
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, MACRO1, _______, _______, _______,    KC_MUTE, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_MPLY, KC_MSTP, KC_VOLU,
        _______, RGB_TOG, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, KC_PGUP, KC_UP,   _______, _______, _______, _______, _______,    KC_MPRV, KC_MNXT, KC_VOLD,
        _______, KC_LALT, KC_LCTL, KC_LSFT, _______, RGB_SAD, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,          _______,
        _______,          RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,_______, KC_PGDN, KC_PGDN, _______, _______, _______,          _______,             _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______,    _______, _______, _______
    ),
    [2] = LAYOUT_tkl_ansi(
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_MUTE, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_MPLY, KC_MSTP, KC_VOLU,
        _______, RGB_TOG, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______,    KC_MPRV, KC_MNXT, KC_VOLD,
        _______, RGB_MOD, RGB_VAD, RGB_SPD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______,
        _______,          RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,QK_BOOT, NK_TOGG, _______, _______, _______, _______,          _______,             _______,
        _______, _______, _______,                            EE_CLR,                             _______, _______, _______, _______,    _______, _______, _______
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0,KC_R):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_F5); // Intercept hold function to send F5
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case MACRO1:
            if (record->event.pressed) {
                SEND_STRING("alias l='ls -alh'");
            }
            break;
    }
    return true;
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }


    if (layer_state_is(1)) {
        rgb_matrix_set_color_all(RGB_OFF);
        rgb_matrix_set_color(40, RGB_GOLD); // U / pgup
        rgb_matrix_set_color(41, RGB_RED); // I
        rgb_matrix_set_color(56, RGB_GREEN); // H / home
        rgb_matrix_set_color(57, RGB_RED); // J
        rgb_matrix_set_color(58, RGB_RED); // K
        rgb_matrix_set_color(59, RGB_RED); // L
        rgb_matrix_set_color(60, RGB_GREEN); // ; / end
        rgb_matrix_set_color(70, RGB_GOLD); // M / pgdown
    }


    return false;
}
