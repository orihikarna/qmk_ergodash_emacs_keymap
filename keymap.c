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

#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |       |       |       |       |       |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  ESC  |   Q   |   W   |   E   |   R   |   T   |       |                    |       |   Y   |   U   |   I   |   O   |   P   |   -   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  Tab  |   A   |   S   |   D   |   F   |   G   |  Del  |                    | Enter |   H  |    J   |   K   |   L   |   ;   |   :   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   Z   |   X   |   C   |   V   |   B   |       |                    |       |   N   |   M   |   ,   |   .   |   /   |   \   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       | PrtScr|  Menu |  Win  |       |  Alt  |  Ctrl | Lower |    | Raise | Shift | Space |       |  Left |  Down |  Up   | Right |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   \
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,                      KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_MINS, \
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_DEL,                     KC_ENT,  KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,                      KC_NO,   KC_N,    KC_M,    JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS, \
    KC_NO,   KC_PSCR, KC_LALT, KC_LGUI,          KC_LALT, KC_LCTL, LOWER,      RAISE, KC_RSFT, KC_SPC,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
  ),

  /* Lower
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |       |       |       |       |       |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  ESC  |   !   |   "   |   #   |   $   |   %   |       |                    |       |   &   |   '   |   (   |   )   |   -   |   @   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  Tab  |   1   |   2   |   3   |   4   |   5   |   BS  |                    | Enter |   6   |   7   |   8   |   9   |   0   |   [   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * | Shift |  Home | PageUp| PageDn|  End  |   ^   |       |                    |       |   ¥   |  Left |  Down |   Up  | Right |   ]   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       | PrtScr|  Menu |  Win  |       |  Alt  |  Ctrl | Lower |    | Raise | Shift | Space |       |  Left |  Down |  Up   | Right |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   \
    KC_ESC,  JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC, KC_NO,                      KC_NO,   JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_MINS, JP_AT,   \
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_BSPC,                    KC_ENT,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_LBRC, \
    KC_LSFT, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  JP_CIRC, KC_NO,                      KC_NO,   JP_YEN,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, JP_RBRC, \
    KC_NO,   KC_PSCR, KC_LALT, KC_LGUI,          KC_LALT, KC_LCTL, LOWER,      RAISE, KC_RSFT, KC_SPC,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
  ),

  /* Raise
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |       |       |       |       |       |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  ESC  |   !   |   "   |   #   |   $   |   %   |       |                    |       |   &   |   '   |   (   |   )   |   -   |   @   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |  Tab  |   1   |   2   |   3   |   4   |   5   |  F11  |                    |  F12  |   6   |   7   |   8   |   9   |   0   |   [   |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   F1  |   F2  |   F3  |   F4  |   F5  |       |                    |       |   F6  |   F7  |   F8  |   F9  |  F10  |   ]   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       | PrtScr|  Menu |  Win  |       |  Alt  |  Ctrl | Lower |    | Raise | Shift | Space |       |  Left |  Down |  Up   | Right |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_RAISE] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   \
    KC_ESC,  JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC, KC_NO,                      KC_NO,   JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_MINS, JP_AT,   \
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_F11,                     KC_F12,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_LBRC, \
    KC_LSFT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,                      KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  JP_RBRC, \
    KC_NO,   KC_PSCR, KC_LALT, KC_LGUI,          KC_LALT, KC_LCTL, LOWER,      RAISE, KC_RSFT, KC_SPC,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
  ),

  /* Adjust
   * ,--------------------------------------------------------                    --------------------------------------------------------.
   * |       |       |       |       |       |       |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |       |(Reset)| RGB ON|  MODE |  HUE- |  HUE+ |       |                    |       |  SAT- |  SAT+ |  VAL- |  VAL+ |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |       |       | BL ON |  BRTG |  INC  |  DEC  |       |                    |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+                    +-------+-------+-------+-------+-------+-------+-------|
   * |       |  Caps |  Win  |       | Insert|PrntScr|       |                    |       | Insert|ScrLock| Pause |NumLock|       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+    +-------+------ +-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |       |       |       |    |       |       |       |       |       |       |       |       |
   * ,-------------------------------+       +-----------------------+    +-----------------------+       +-------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC ,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_CAPS, KC_LGUI, _______, _______, KC_PSCR,_______,                       _______, KC_INS,  KC_SLCK, KC_PAUS, KC_NLCK, _______, _______, \
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (process_record_emacs(keycode, record) == false) {
    return false;
  }
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
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
  }
  return true;
}
