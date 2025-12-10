// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _QWRT,
    _NAV,
    _UTIL,
    _SYM,
};

// it's too complicated to make the matrix right now...
// const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {

// };

// AUTO-SHIFT

// Fixing retro-shift on home row mods.
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    if (IS_RETRO(keycode))
        return true;

    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            return true;
        default:
            return false;
    }
}

// COMBOS

const uint16_t PROGMEM c_enter[] = {LT(_NAV, KC_SPC), QK_REP, COMBO_END};
const uint16_t PROGMEM c_tn_enter[] = {LCTL_T(KC_T), RCTL_T(KC_N), COMBO_END};

combo_t key_combos[] = {
    COMBO(c_enter, KC_ENT),
    COMBO(c_tn_enter, KC_ENT),
};

// KEYMAP / LAYERS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        C(KC_G), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC,
        KC_ESC, KC_A,LALT_T(KC_R),LGUI_T(KC_S),LCTL_T(KC_T), KC_G,               KC_M, RCTL_T(KC_N), RGUI_T(KC_E),RALT_T(KC_I),KC_O,  KC_QUOT,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_GRAVE,                           KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                     OSL(_SYM), OS_LSFT, LT(_NAV, KC_SPC),        QK_REP, LT(_UTIL, KC_BSPC), QK_AREP
    ),

    [_QWRT] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                            KC_LGUI, DF(_BASE), KC_SPC,           KC_ENT,  KC_BSPC,  KC_RBRC
    ),

    [_NAV] = LAYOUT(
        KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        DF(_QWRT),KC_TRNS, MS_BTN1, MS_UP, MS_BTN2, C(KC_TAB),                            KC_TRNS, KC_TRNS, KC_END,  KC_HOME, KC_TRNS, KC_F12,
        A(KC_LEFT),A(KC_RIGHT), MS_LEFT, MS_DOWN, MS_RGHT, LCS(KC_TAB),                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGDN, KC_PGUP,
        MS_WHLL, MS_WHLR, MS_WHLD, MS_BTN3, MS_WHLU, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, TO(_BASE), KC_TRNS,          KC_ENT,  QK_LLCK,  KC_TRNS
    ),

    [_UTIL] = LAYOUT(
        AS_TOGG,  AS_DOWN, AS_UP,   AS_RPT,  KC_TRNS, KC_TRNS,                            KC_MSTP, KC_MPRV, KC_MNXT, KC_MPLY, KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_PSCR, KC_TRNS, KC_INS,A(KC_INS), KC_TRNS,                            KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_F20,  KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS,  KC_TRNS,
        //        全角     英数    無変換   変換　　ひらがな
        KC_TRNS,  KC_LNG5, KC_LNG2, KC_INT5, KC_INT4, KC_INT2,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //                                                    한영 かな
                                            QK_LLCK, KC_TRNS,  KC_LNG1,          KC_TRNS,  KC_TRNS,  KC_TRNS
    ),

    [_SYM] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //                                                                                (        ~        +        -        `        %
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_LPRN, KC_TILD, KC_PLUS, KC_MINS, KC_GRV,  KC_PERC,
        //                                                                                =        [        {        }        ]        &
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_EQL,  KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_AMPR,
        //                                                                                )        _        <        >         *        $
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_RPRN,  KC_UNDS, KC_LABK, KC_RABK, KC_ASTR, KC_DLR,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           QK_REP,  KC_DEL,  KC_APP
    )

};
