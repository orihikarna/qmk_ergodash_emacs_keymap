#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include "process_emacs.h"

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    // for mytap_t
    LT_ESC,
    RT_SPC,
    CT_DEL,
    //ST_SPC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |   1   |   2   |   3   |   4   |   5   |       |                    |       |   6   |   7   |   8   |   9   |   0   |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  ESC  |   Q   |   W   |   E   |   R   |   T   |       |                    |       |   Y   |   U   |   I   |   O   |   P   |  - =  |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   A   |   S   |   D   |   F   |   G   |  ^ ~  |                    |  ¥ |  |   H   |   J   |   K   |   L   |  ; +  |  : *  |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  Tab  |   Z   |   X   |   C   |   V   |   B   |       |                    |       |   N   |   M   |   ,   |   .   |  / >  |  \ _  |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |  Alt  |  Ctrl | Lower |    | Raise | Shift | Space |       |       |       |       |       |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,                      KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,   \
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,                      KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_MINS, \
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    JP_CIRC,                    JP_YEN,  KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN, \
    KC_TAB,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,                      KC_NO,   KC_N,    KC_M,    JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS, \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_LALT, KC_LCTL, LOWER,    RAISE,   KC_RSFT, KC_SPC,           KC_NO,   KC_NO,   KC_NO,   KC_NO    \
  ),

  /* Raise
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |   F1  |   F2  |   F3  |   F4  |   F5  |       |                    |       |   F6  |   F7  |   F8  |   F9  |  F10  |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |PrntScr|   !   |   "   |   #   |   $   |   %   |       |                    |       |   &   |   '   |   (   |   )   |   @   |   =   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  Win  |   1   |   2   |   3   |   4   |   5   |  Del  |                    | Enter |   6   |   7   |   8   |   9   |   0   |   [   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  Caps |  Home | PageUp| PageDn|  End  |  F11  |       |                    |       |  F12  |  Left |   Up  |  Down | Right |   ]   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |  Alt  |  Ctrl | Lower |    | Raise | Shift | Space |       |       |       |       |       |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_RAISE] = LAYOUT(
    KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,                      KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,   \
    KC_PSCR, JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC, KC_NO,                      KC_NO,   JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_AT,   S(JP_MINS), \
    KC_LGUI, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_DEL,                     KC_ENT,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_LBRC, \
    KC_CAPS, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_F11,  KC_NO,                      KC_NO,   KC_F12,  KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, JP_RBRC, \
    KC_NO,   KC_NO, KC_NO,   KC_NO,            KC_LALT, KC_LCTL, LOWER,      RAISE,   KC_RSFT, KC_SPC,           KC_NO,   KC_NO,   KC_NO,   KC_NO    \
  ),

  /* Lower
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |   F1  |   F2  |   F3  |   F4  |   F5  |       |                    |       |   F6  |   F7  |   F8  |   F9  |  F10  |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * | RGB ON|   !   |   "   |   #   |   $   |   %   |       |                    |       |   &   |   '   |   (   |   )   |   @   |   =   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  MODE |   1   |   2   |   3   |   4   |   5   |   BS  |                    | Enter |   6   |   7   |   8   |   9   |   0   |   [   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * | BL ON |  Home | PageUp| PageDn|  End  |  F11  |       |                    |       |  F12  |  Left |   Up  |  Down | Right |   ]   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |  Alt  |  Ctrl | Lower |    | Raise | Shift | Space |       |       |       |       |       |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,                      KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,   \
    RGB_TOG, JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC, KC_NO,                      KC_NO,   JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_AT,   S(JP_MINS), \
    RGB_MOD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_BSPC,                    KC_ENT,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_LBRC, \
    BL_TOGG, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_F11,  KC_NO,                      KC_NO,   KC_F12,  KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, JP_RBRC, \
    KC_NO,   KC_NO, KC_NO,   KC_NO,            KC_LALT, KC_LCTL, LOWER,      RAISE,   KC_RSFT, KC_SPC,           KC_NO,   KC_NO,   KC_NO,   KC_NO    \
  ),
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

typedef struct {
    uint16_t keycode;
    uint16_t key_hold;
    uint16_t key_tap;
    uint16_t time;
    bool pressed;
} mytap_t;

static mytap_t taps[] = {
    { LT_ESC, LOWER,   KC_ESC,  false, 0 },
    { RT_SPC, RAISE,   KC_SPC,  false, 0 },
    { CT_DEL, KC_LCTL, KC_DEL,  false, 0 },
    //{ ST_SPC, KC_RSFT, KC_SPC,  false, 0 },
};
#define MYTAP_COUNT (sizeof( taps) / sizeof( taps[0] ))
#define MYTAPPING_TERM 500

static bool process_record_layer( uint16_t keycode, keyrecord_t* record ) {
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
            } else {
                layer_off(_LOWER);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
            break;
    }
    return true;
}

static bool _process_record_user( uint16_t keycode, keyrecord_t* record ) {
    if (process_record_layer( keycode, record ) == false) return false;
    if (process_record_emacs( keycode, record ) == false) return false;
    return true;
}

static keyrecord_t pressed   = { { { 0, 0 }, true,  0 }, { 0, 0, 0, 0, 0 } };
static keyrecord_t depressed = { { { 0, 0 }, false, 0 }, { 0, 0, 0, 0, 0 } };

static bool process_record_mytap( uint16_t keycode, keyrecord_t* record ) {
    bool cont = true;
    for (uint8_t n = 0; n < MYTAP_COUNT; ++n) {
        mytap_t* tap = &taps[n];
        if (tap->keycode == keycode) {
            if (record->event.pressed) {
                if (_process_record_user( tap->key_hold, &pressed )) register_code16( tap->key_hold );
                tap->pressed = true;
                tap->time = record->event.time;
            } else {
                if (_process_record_user( tap->key_hold, &depressed )) unregister_code16( tap->key_hold );
                if (tap->pressed) {
                    tap->pressed = false;
                    if (TIMER_DIFF_16( record->event.time, tap->time ) < MYTAPPING_TERM) {
                        if (_process_record_user( tap->key_tap, &pressed )) register_code16( tap->key_tap );
                        if (_process_record_user( tap->key_tap, &depressed )) unregister_code16( tap->key_tap );
                    }
                }
            }
            cont = false;            
        } else {
            if (record->event.pressed) {
                tap->pressed = false;
            }
        }
    }
    return cont;
}

static void mytap_clear_state( void ) {
    for (uint8_t n = 0; n < MYTAP_COUNT; ++n) {
        mytap_t* tap = &taps[n];
        tap->pressed = false;
    }
}

bool process_record_user( uint16_t keycode, keyrecord_t* record ) {
    if (process_record_mytap( keycode, record ) == false) return false;
    if (_process_record_user( keycode, record ) == false) {
        mytap_clear_state();
        return false;
    }
    return true;
}
