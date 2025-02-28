/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "quantum.h"

typedef enum {
    DISABLE_OVERRIDE,
    US_KEY_ON_JP_OS_OVERRIDE,
    JP_KEY_ON_US_OS_OVERRIDE,
} OVERRIDE_MODE;

typedef union {
    uint32_t raw;
    struct {
        uint8_t override_mode;
    };
} keyboard_config_t;

#include "jp_us_overrides.h"

enum kb_keycodes {
    DISABLE_KEY_OVERRIDES = QK_USER_0,
    ENABLE_US_KEY_ON_JP_OS_OVERRIDE,
    ENABLE_JP_KEY_ON_US_OS_OVERRIDE,
};

void set_key_override(OVERRIDE_MODE mode) {
    switch (mode) {
        case DISABLE_OVERRIDE:
            key_override_off();
            break;
        case US_KEY_ON_JP_OS_OVERRIDE:
            register_us_key_on_jp_os_overrides();
            key_override_on();
            break;
        case JP_KEY_ON_US_OS_OVERRIDE:
            register_jp_key_on_us_os_overrides();
            key_override_on();
            break;
    }
}



// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _ADJUST,
};

/*
enum custom_keycodes {
    JU_2 = SAFE_RANGE,
    JU_6,
    JU_7,
    JU_8,
    JU_9,
    JU_0,
    JU_MINS,
    JU_EQL,
    JU_LBRC,
    JU_RBRC,
    JU_BSLS,
    JU_SCLN,
    JU_QUOT,
    JU_GRV,
    JU_CAPS
  };
*/

#define KC_L_SPC LT(_LOWER, KC_SPC)  // lower
#define KC_R_ENT LT(_RAISE, KC_ENT)  // raise
#define KC_G_JA LGUI_T(KC_LNG1)      // cmd or win
#define KC_G_EN LGUI_T(KC_LNG2)      // cmd or win
#define KC_C_BS LCTL_T(KC_BSPC)      // ctrl
#define KC_A_DEL ALT_T(KC_DEL)       // alt

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
       KC_ESC , KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , KC_MINS,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
       KC_TAB , KC_A   , KC_S    , KC_D   , KC_F    , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , KC_SCLN, KC_QUOT,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
       KC_LSFT, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, KC_RSFT,
    //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                         KC_A_DEL, KC_G_EN, KC_L_SPC, KC_C_BS,     KC_C_BS, KC_R_ENT, KC_G_JA, KC_A_DEL
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_RAISE] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
       _______, KC_BSLS, KC_CIRC, KC_EXLM, KC_AMPR, KC_PIPE,     KC_AT  , KC_EQL , KC_PLUS, KC_ASTR, KC_PERC, KC_MINS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_LPRN, KC_HASH, KC_DLR , KC_DQT , KC_QUOT, KC_TILD,     KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, KC_GRV , KC_RPRN,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       _______, _______, _______, _______, KC_LCBR, KC_LBRC,     KC_RBRC, KC_RCBR, _______, _______, _______, _______,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         _______, _______, _______, _______,     _______, _______, _______, QK_BOOT
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),

    [_LOWER] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
       KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,     _______, KC_EQL , KC_PLUS, KC_ASTR, KC_PERC, KC_MINS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,     _______, _______, KC_COMM, KC_DOT , KC_SLSH, _______,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         QK_BOOT  , _______, _______, _______,     _______, _______, _______, _______
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),
    [_ADJUST] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),
};

keyboard_config_t keyboard_config;

#ifdef CONSOLE_ENABLE
    #include<print.h>
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {

#ifdef CONSOLE_ENABLE
uprintf("EN: keycode %u \n",keycode);
#endif

        switch (keycode) {

            #ifdef CONSOLE_ENABLE
                uprintf("Disable key       = %u\n",DISABLE_KEY_OVERRIDES);
                //uprintf("off key           = %u\n",KEY_OVERRIDE_OFF);
                uprintf("USKey On JPOS key = %u\n",ENABLE_US_KEY_ON_JP_OS_OVERRIDE);
                uprintf("JPKey On USOS key = %u\n",ENABLE_JP_KEY_ON_US_OS_OVERRIDE);
                uprintf("entered key = %u\n",keycode);
            #endif

            case DISABLE_KEY_OVERRIDES: {
            //case KEY_OVERRIDE_OFF: {
            #ifdef CONSOLE_ENABLE
                uprintf("Disable key overrides");
            #endif
                keyboard_config.override_mode = DISABLE_OVERRIDE;
                set_key_override(DISABLE_OVERRIDE);
                eeconfig_update_kb(keyboard_config.raw);
                return true;
            }
            case ENABLE_US_KEY_ON_JP_OS_OVERRIDE: {
                #ifdef CONSOLE_ENABLE
                    uprintf("Perform as an US keyboard on the OS configured for JP");
                #endif
                keyboard_config.override_mode = US_KEY_ON_JP_OS_OVERRIDE;
                set_key_override(US_KEY_ON_JP_OS_OVERRIDE);
                eeconfig_update_kb(keyboard_config.raw);
                return false;
            } break;
            case ENABLE_JP_KEY_ON_US_OS_OVERRIDE: {
                #ifdef CONSOLE_ENABLE
                    println("Perform as a JP keyboard on the OS configured for US");
                #endif
                keyboard_config.override_mode = JP_KEY_ON_US_OS_OVERRIDE;
                set_key_override(JP_KEY_ON_US_OS_OVERRIDE);
                eeconfig_update_kb(keyboard_config.raw);
                return false;
            } break;
        }
    }

    return true;
  }


/*
#ifdef CONSOLE_ENABLE
    #include<print.h>
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool lshift = false;
    static bool rshift = false;

#ifdef CONSOLE_ENABLE
    uprintf("EN: keycode %u \n",keycode);
#endif

    switch (keycode) {
      case JU_2:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LBRC);
            unregister_code(KC_LBRC);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_2);
            unregister_code(KC_2);
          }
        }
        return false;
      case JU_6:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_EQL);
            unregister_code(KC_EQL);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_6);
            unregister_code(KC_6);
          }
        }
        return false;
      case JU_7:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_6);
            unregister_code(KC_6);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_7);
            unregister_code(KC_7);
          }
        }
        return false;
      case JU_8:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_QUOT);
            unregister_code(KC_QUOT);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_8);
            unregister_code(KC_8);
          }
        }
        return false;
      case JU_9:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_8);
            unregister_code(KC_8);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_9);
            unregister_code(KC_9);
          }
        }
        return false;
      case JU_0:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_9);
            unregister_code(KC_9);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_0);
            unregister_code(KC_0);
          }
        }
        return false;
      case JU_MINS:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_INT1);
            unregister_code(KC_INT1);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_MINS);
            unregister_code(KC_MINS);
          }
        }
        return false;
      case JU_EQL:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_SCLN);
            unregister_code(KC_SCLN);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_LSFT);
            register_code(KC_MINS);
            unregister_code(KC_MINS);
            unregister_code(KC_LSFT);
          }
        }
        return false;
      case JU_LBRC:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_RBRC);
            unregister_code(KC_RBRC);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_RBRC);
            unregister_code(KC_RBRC);
          }
        }
        return false;
      case JU_RBRC:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_NUHS);
            unregister_code(KC_NUHS);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_NUHS);
            unregister_code(KC_NUHS);
          }
        }
        return false;
      case JU_BSLS:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_INT3);
            unregister_code(KC_INT3);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_INT1);
            unregister_code(KC_INT1);
          }
        }
        return false;
      case JU_SCLN:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_QUOT);
            unregister_code(KC_QUOT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_SCLN);
            unregister_code(KC_SCLN);
          }
        }
        return false;
      case JU_QUOT:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_2);
            unregister_code(KC_2);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_LSFT);
            register_code(KC_7);
            unregister_code(KC_7);
            unregister_code(KC_LSFT);
          }
        }
        return false;
      case JU_GRV:
        if (record->event.pressed) {
          lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
          rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
          if (lshift || rshift) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
            register_code(KC_LSFT);
            register_code(KC_EQL);
            unregister_code(KC_EQL);
            unregister_code(KC_LSFT);
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          } else {
            register_code(KC_LSFT);
            register_code(KC_LBRC);
            unregister_code(KC_LBRC);
            unregister_code(KC_LSFT);
          }
        }
        return false;
      case JU_CAPS:
        if (record->event.pressed) {
          register_code(KC_LSFT);
          register_code(KC_CAPS);
          unregister_code(KC_CAPS);
          unregister_code(KC_LSFT);
        }
        return false;
    }
    return true;
  }
*/
