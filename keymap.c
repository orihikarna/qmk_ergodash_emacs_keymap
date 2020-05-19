#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include "process_emacs.h"

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |       |       |       |       |       |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  ESC  |   Q   |   W   |   E   |   R   |   T   |       |                    |       |   Y   |   U   |   I   |   O   |   P   |   -   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  Tab  |   A   |   S   |   D   |   F   |   G   |       |                    |       |   H   |   J   |   K   |   L   |   ;   |   :   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   Z   |   X   |   C   |   V   |   B   |       |                    |       |   N   |   M   |   ,   |   .   |   /   |   \   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |  Alt  |  Ctrl |Low/Del|    |       |Raz/Ent|Sft/Spc|       |       |       |       |       |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   \
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,                      KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_MINS, \
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,                      KC_NO,   KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,                      KC_NO,   KC_N,    KC_M,    JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS, \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_LALT, KC_LCTL, LOWER,      KC_NO, RAISE, KC_RSFT,            KC_NO,   KC_NO,   KC_NO,   KC_NO    \
  ),

  /* Lower
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |       |       |       |       |       |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  ESC  |   !   |   "   |   #   |   $   |   %   |       |                    |       |   &   |   '   |   (   |   )   |   @   |   =   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  Tab  |   1   |   2   |   3   |   4   |   5   |       |                    |       |   6   |   7   |   8   |   9   |   0   |   [   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * | Shift |       |       |       |  Win  |PrntScr|       |                    |       |   ^   |   ¥   |   ,   |   .   |   /   |   ]   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |  Alt  |  Ctrl |Low/Del|    |       |Raz/Ent|Sft/Spc|       |       |       |       |       |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   \
    KC_ESC,  JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC, KC_NO,                      KC_NO,   JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_AT,   S(JP_MINS), \
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,                      KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_LBRC, \
    KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_LGUI, KC_PSCR, KC_NO,                      KC_NO,   JP_CIRC, JP_YEN,  JP_COMM, JP_DOT,  JP_SLSH, JP_RBRC, \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_LALT, KC_LCTL, LOWER,      KC_NO, RAISE, KC_RSFT,            KC_NO,   KC_NO,   KC_NO,   KC_NO    \
  ),

  /* Raise
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |       |       |       |       |       |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  ESC  |   !   |   "   |   #   |   $   |   %   |       |                    |       |       |  Home | PageUp| PageDn|  End  |   =   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  Tab  |   1   |   2   |   3   |   4   |   5   |       |                    |       |       |  Left |  Down |   Up  | Right |  F12  |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   F1  |   F2  |   F3  |   F4  |   F5  |       |                    |       |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |  Alt  |  Ctrl |Low/Del|    |       |Raz/Ent|Sft/Spc|       |       |       |       |       |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_RAISE] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   \
    KC_ESC,  JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC, KC_NO,                      KC_NO,   KC_NO,   KC_HOME, KC_PGUP, KC_PGDN, KC_END,  S(JP_MINS), \
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,                      KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_F12,  \
    KC_LSFT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,                      KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_LALT, KC_LCTL, LOWER,      KC_NO, RAISE, KC_RSFT,            KC_NO,   KC_NO,   KC_NO,   KC_NO    \
  ),

  /* Adjust
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |       |       |       |       |       |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |       |(Reset)| RGB ON|  MODE |  HUE- |  HUE+ |       |                    |       |  SAT- |  SAT+ |  VAL- |  VAL+ |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |       |       | BL ON |  BRTG |  INC  |  DEC  |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |       |  Caps | Insert|       |  Win  |PrntScr|       |                    |       |       |ScrLock| Pause |NumLock|       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |       |       |       |    |       |       |       |       |       |       |       |       |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC ,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_CAPS, KC_INS,  _______, KC_LGUI, KC_PSCR,_______,                       _______, _______, KC_SLCK, KC_PAUS, KC_NLCK, _______, _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

typedef struct {
    bool pressed;
    uint16_t time;
} mytap_t;

static mytap_t tap_lower = { false, 0 };
static mytap_t tap_raise = { false, 0 };
static mytap_t tap_rsft = { false, 0 };

bool process_record_user_default( uint16_t keycode, keyrecord_t* record ) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                tap_lower.pressed = true;
                tap_lower.time = record->event.time;
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                if (tap_lower.pressed) {
                    tap_lower.pressed = false;
                    if (TIMER_DIFF_16( record->event.time, tap_lower.time ) < TAPPING_TERM) {
                        tap_code( KC_DEL );
                    }
                }
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                tap_raise.pressed = true;
                tap_raise.time = record->event.time;
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                if (tap_raise.pressed) {
                    tap_raise.pressed = false;
                    if (TIMER_DIFF_16( record->event.time, tap_raise.time ) < TAPPING_TERM) {
                        tap_code( KC_ENT );
                    }
                }
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        default:
            if (record->event.pressed) {
                tap_lower.pressed = false;
                tap_raise.pressed = false;
            }
            break;
    }
    return true;
}

static keyrecord_t pressed = {{{0,0},true,0}, {0,0,0,0,0}};
static keyrecord_t depressed = {{{0,0},false,0}, {0,0,0,0,0}};

bool process_record_user( uint16_t keycode, keyrecord_t* record ) {
    if (process_record_user_default( keycode, record ) == false) return false;
    switch (keycode) {
        case KC_RSFT:
            if (record->event.pressed) {
                tap_rsft.pressed = true;
                tap_rsft.time = record->event.time;
            } else if (tap_rsft.pressed) {
                tap_rsft.pressed = false;
                if (TIMER_DIFF_16( record->event.time, tap_rsft.time ) < TAPPING_TERM) {
                    if (process_record_emacs( keycode, record )) unregister_code( keycode );
                    if (process_record_emacs( KC_SPC, &pressed )) register_code( KC_SPC );
                    if (process_record_emacs( KC_SPC, &depressed )) unregister_code( KC_SPC );
                    return false;
                }
            }
            break;
        default:
            if (record->event.pressed) {
                tap_rsft.pressed = false;
            }
            break;
    }
    if (process_record_emacs( keycode, record ) == false) return false;
    return true;
}
