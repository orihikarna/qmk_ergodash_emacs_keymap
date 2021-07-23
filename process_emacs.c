#include QMK_KEYBOARD_H
#include "keymap_jp.h"

#define USE_JP
#define USE_TAP_HOLD_ALT_CTL
// #define AVOID_SINGLE_ALT_WINDOWS

#ifdef USE_JP
#define UKC_COMM JP_COMM
#define UKC_DOT  JP_DOT
#else
#define UKC_COMM KC_COMM
#define UKC_DOT  KC_DOT
#endif


// emacs mode modifiers (use left keycods)
#define MOD_C MOD_BIT(KC_LCTL)
#define MOD_S MOD_BIT(KC_LSFT)
#define MOD_M MOD_BIT(KC_LALT)
#define MOD_G MOD_BIT(KC_LGUI)
#define MOD_CS (MOD_C|MOD_S)
#define MOD_CM (MOD_C|MOD_M)
#define MOD_SM (MOD_S|MOD_M)

// any modifiers (use right keycodes)
#define ANY_C MOD_BIT(KC_RCTL)
#define ANY_S MOD_BIT(KC_RSFT)
#define ANY_M MOD_BIT(KC_RALT)
#define ANY_G MOD_BIT(KC_RGUI)
#define ANY_SM (ANY_S|ANY_M)

// emacs mode type
#define MOD_TABLE MOD_BIT(KC_LGUI)
#define MOD_MACRO MOD_BIT(KC_RGUI)


// declarations
typedef struct {
    uint8_t src_mods;// L: pressed, R: any
    uint8_t src_code;
    uint8_t dest_mods; // mapped mods, or mapped mode (macro, function)
    uint8_t dest_code;
} SMapEntry;

#define MAP_ENTRY_SIZE 4

typedef void (*map_table_on_enter_func_t)( void );
typedef void (*map_table_on_search_func_t)( uint8_t entry_index );

typedef struct {
    const uint8_t (*m_table)[MAP_ENTRY_SIZE];
    uint8_t m_size;
    map_table_on_enter_func_t m_on_enter_func;
    map_table_on_search_func_t m_on_search_func;
} SMapTable;


// definitions
#define MAP_TABLE_INDEX_NONE     0
#define MAP_TABLE_INDEX_DEFAULT  1
#define MAP_TABLE_INDEX_CXPREFIX 2
#define MAP_TABLE_INDEX_MARKSEL  3
#define MAP_TABLE_COUNT          4

enum map_macros {
    EMM_OpenLine,
    EMM_KillLine,
    EMM_SwapChars,
    EMM_KillWord,
    EMM_MarkCancel,
    EMM_MarkCut,
    EMM_MarkCopy,
};


// tap/hold
enum tap_hold_state {
    ETHS_Released,
    ETHS_Pressed,
    ETHS_Tapped,
    ETHS_Held,
};

typedef struct {
    uint8_t modcode;
    uint8_t state;
    uint16_t time;
} SModTapHold;



// implementations
static uint8_t map_table_index = MAP_TABLE_INDEX_DEFAULT;
static uint8_t pressed_mods = 0;
static uint8_t pressed_keycode = KC_NO;
static uint8_t registered_mods = 0;
static uint8_t mapped_mods = 0;
static uint8_t mapped_keycode = KC_NO;
#ifdef AVOID_SINGLE_ALT_WINDOWS
static bool is_single_alt_tap = false;
#endif
#ifdef USE_TAP_HOLD_ALT_CTL
static SModTapHold mod_taps[] = {
    { KC_LCTL, ETHS_Released, 0 },
    { KC_RCTL, ETHS_Released, 0 },
    { KC_LALT, ETHS_Released, 0 },
    { KC_RALT, ETHS_Released, 0 },
};
#define MOD_TAP_COUNT (sizeof( mod_taps ) / sizeof( mod_taps[0] ))
#endif


// macro definitions
static const uint16_t macro_openline[]    = { KC_ENT, KC_UP, KC_END, KC_NO };
static const uint16_t macro_killline[]    = { S(KC_END), C(KC_X), KC_NO };
static const uint16_t macro_swapchars[]   = { S(KC_RGHT), C(KC_X), KC_LEFT, C(KC_V), KC_RGHT, KC_NO };
static const uint16_t macro_killword[]    = { S(C(KC_RGHT)), C(KC_X), KC_NO };
static const uint16_t macro_mark_cancel[] = { KC_RGHT, KC_NO };
static const uint16_t macro_mark_cut[]    = { C(KC_X), KC_LEFT, KC_RGHT, KC_NO };
static const uint16_t macro_mark_copy[]   = { C(KC_C), KC_LEFT, KC_NO };

static const uint16_t* macro_seqs[] = {
    [EMM_OpenLine]   = macro_openline,
    [EMM_KillLine]   = macro_killline,
    [EMM_SwapChars]  = macro_swapchars,
    [EMM_KillWord]   = macro_killword,
    [EMM_MarkCancel] = macro_mark_cancel,
    [EMM_MarkCut]    = macro_mark_cut,
    [EMM_MarkCopy]   = macro_mark_copy,
};


// mapping tables
static const uint8_t map_table_none[][MAP_ENTRY_SIZE] = {
    { MOD_C         , KC_Q,    MOD_TABLE, MAP_TABLE_INDEX_DEFAULT },
};
#define MAP_COUNT_NONE (sizeof( map_table_none ) / sizeof( map_table_none[0] ))

static const uint8_t map_table_default[][MAP_ENTRY_SIZE] = {
    { MOD_C         , KC_Q,    MOD_TABLE, MAP_TABLE_INDEX_NONE },
    { MOD_C         , KC_X,    MOD_TABLE, MAP_TABLE_INDEX_CXPREFIX },
    { MOD_C         , KC_SPC,  MOD_TABLE, MAP_TABLE_INDEX_MARKSEL },
    { MOD_C         , KC_G,    0,         KC_ESC  },// Esc
    { MOD_C | ANY_SM, KC_M,    0,         KC_ENT  },// Enter
    { MOD_C | ANY_SM, KC_A,    0,         KC_HOME },// Home
    { MOD_C | ANY_SM, KC_E,    0,         KC_END  },// End
    { MOD_C | ANY_SM, KC_F,    0,         KC_RGHT },// Right
    { MOD_C | ANY_SM, KC_B,    0,         KC_LEFT },// Left
    { MOD_C | ANY_SM, KC_P,    0,         KC_UP   },// Up
    { MOD_C | ANY_SM, KC_N,    0,         KC_DOWN },// Down
    { MOD_C | ANY_SM, KC_R,    0,         KC_PGUP },// Page Up
    { MOD_C | ANY_SM, KC_V,    0,         KC_PGDN },// Page Down
    { MOD_M | ANY_S , KC_F,    MOD_C,     KC_RGHT },// next word
    { MOD_M | ANY_S , KC_B,    MOD_C,     KC_LEFT },// prev word
    { MOD_C | ANY_S , KC_D,    0,         KC_DEL  },// Del
    { MOD_C         , KC_H,    0,         KC_BSPC },// BS
    { MOD_C         , KC_S,    MOD_C,     KC_F    },// search (find)
    // macros
    { MOD_C         , KC_O,    MOD_MACRO, EMM_OpenLine },
    { MOD_C         , KC_K,    MOD_MACRO, EMM_KillLine },
    { MOD_C         , KC_T,    MOD_MACRO, EMM_SwapChars },
    { MOD_M         , KC_D,    MOD_MACRO, EMM_KillWord },
    { MOD_C | ANY_S , KC_I,    0,         KC_TAB  },// Tab
    { MOD_C         , KC_W,    MOD_C,     KC_X    },// cut
    { MOD_M         , KC_W,    MOD_C,     KC_C    },// copy
    { MOD_C         , KC_Y,    MOD_C,     KC_V    },// paste
    { MOD_M         , KC_Y,    MOD_C,     KC_Y    },// redo
    { MOD_SM        , UKC_COMM,MOD_C,     KC_HOME },// top
    { MOD_SM        , UKC_DOT, MOD_C,     KC_END  },// bottom
    // mac style
    { MOD_M         , KC_Z,    MOD_C,     KC_Z    },// undo
    { MOD_M         , KC_X,    MOD_C,     KC_X    },// cut
    { MOD_M         , KC_C,    MOD_C,     KC_C    },// copy
    { MOD_M         , KC_V,    MOD_C,     KC_V    },// paste
    { MOD_M         , KC_A,    MOD_C,     KC_A    },// All
    { MOD_M         , KC_S,    MOD_C,     KC_S    },// save
    { MOD_SM        , KC_Z,    MOD_C,     KC_Y    },// redo
    { MOD_M         , KC_N,    MOD_C,     KC_N    },// new
    { MOD_M         , KC_O,    MOD_C,     KC_O    },// open
    //  Ctrl+Num=Fn
    // { MOD_C | ANY_SM, KC_1,    0,         KC_F1   },// F1
    // { MOD_C | ANY_SM, KC_2,    0,         KC_F2   },// F2
    // { MOD_C | ANY_SM, KC_3,    0,         KC_F3   },// F3
    // { MOD_C | ANY_SM, KC_4,    0,         KC_F4   },// F4
    // { MOD_C | ANY_SM, KC_5,    0,         KC_F5   },// F5
    // { MOD_C | ANY_SM, KC_6,    0,         KC_F6   },// F6
    // { MOD_C | ANY_SM, KC_7,    0,         KC_F7   },// F7
    // { MOD_C | ANY_SM, KC_8,    0,         KC_F8   },// F8
    // { MOD_C | ANY_SM, KC_9,    0,         KC_F9   },// F9
    // { MOD_C | ANY_SM, KC_0,    0,         KC_F10  },// F10
#ifdef USE_JP
    { MOD_C         , JP_SCLN, 0,         JP_ZKHK },// IME
#endif
};
#define MAP_COUNT_DEFAULT (sizeof( map_table_default ) / sizeof( map_table_default[0] ))

const uint8_t map_table_cxprefix[][MAP_ENTRY_SIZE] = {
    { MOD_C         , KC_Q,    MOD_TABLE, MAP_TABLE_INDEX_NONE },
    { MOD_C         , KC_X,    MOD_TABLE, MAP_TABLE_INDEX_CXPREFIX },// not to go back to default by chatters of X key
    { MOD_C         , KC_S,    MOD_C,     KC_S    },// save
    { MOD_C         , KC_F,    MOD_C,     KC_O    },// open
    { MOD_C         , KC_C,    MOD_M,     KC_F4   },// close
    { 0             , KC_U,    MOD_C,     KC_Z    },// undo
    { 0             , KC_H,    MOD_C,     KC_A    },// All
};
#define MAP_COUNT_CXPREFIX (sizeof( map_table_cxprefix ) / sizeof( map_table_cxprefix[0] ))

static void map_table_cxprefix_on_enter( void ) {
    //backlight_enable();
}

static void map_table_cxprefix_on_search( uint8_t index ) {
    map_table_index = MAP_TABLE_INDEX_DEFAULT;
    //backlight_disable();
}

const uint8_t map_table_marksel[][MAP_ENTRY_SIZE] = {
    { MOD_C         , KC_Q,    MOD_TABLE, MAP_TABLE_INDEX_NONE },
    { MOD_C         , KC_G,    MOD_MACRO, EMM_MarkCancel },
    { MOD_C         , KC_W,    MOD_MACRO, EMM_MarkCut },// cut
    { MOD_M         , KC_W,    MOD_MACRO, EMM_MarkCopy },// copy
    { MOD_C         , KC_A,    MOD_S,     KC_HOME },
    { MOD_C         , KC_E,    MOD_S,     KC_END  },
    { MOD_C         , KC_F,    MOD_S,     KC_RGHT },
    { MOD_C         , KC_B,    MOD_S,     KC_LEFT },
    { MOD_C         , KC_P,    MOD_S,     KC_UP   },
    { MOD_C         , KC_N,    MOD_S,     KC_DOWN },
    { MOD_CS        , KC_V,    MOD_S,     KC_PGUP },
    { MOD_C         , KC_V,    MOD_S,     KC_PGDN },
    { MOD_M         , KC_F,    MOD_CS,    KC_RGHT },// next word
    { MOD_M         , KC_B,    MOD_CS,    KC_LEFT },// prev word
    { MOD_SM        , UKC_COMM,MOD_CS,    KC_HOME },
    { MOD_SM        , UKC_DOT, MOD_CS,    KC_END  },
    { 0             , KC_LEFT, MOD_S,     KC_LEFT },
    { 0             , KC_RGHT, MOD_S,     KC_RGHT },
    { 0             , KC_UP,   MOD_S,     KC_UP   },
    { 0             , KC_DOWN, MOD_S,     KC_DOWN },
};
#define MAP_COUNT_MARKSEL (sizeof( map_table_marksel ) / sizeof( map_table_marksel[0] ))

static void map_table_marksel_on_enter( void ) {
    backlight_enable();
}

static void map_table_marksel_on_search( uint8_t index ) {
    if (index < 4 || MAP_COUNT_MARKSEL <= index) {
        map_table_index = MAP_TABLE_INDEX_DEFAULT;
        backlight_disable();
    }
}

static SMapTable map_tables[MAP_TABLE_COUNT] = {
    [MAP_TABLE_INDEX_NONE]     = (SMapTable) { map_table_none,     MAP_COUNT_NONE,     NULL, NULL }, 
    [MAP_TABLE_INDEX_DEFAULT]  = (SMapTable) { map_table_default,  MAP_COUNT_DEFAULT,  NULL, NULL }, 
    [MAP_TABLE_INDEX_CXPREFIX] = (SMapTable) { map_table_cxprefix, MAP_COUNT_CXPREFIX, map_table_cxprefix_on_enter, map_table_cxprefix_on_search }, 
    [MAP_TABLE_INDEX_MARKSEL]  = (SMapTable) { map_table_marksel,  MAP_COUNT_MARKSEL,  map_table_marksel_on_enter, map_table_marksel_on_search },
};


// mapping functions
static bool match_mods2( uint8_t pressed, uint8_t mods, uint8_t* any_mods ) {
    pressed = (pressed | (pressed >> 4)) & 0x07;// combine Left & Right, ignore GUI
    const uint8_t req = mods & 0x0f;
    const uint8_t any = (mods >> 4) & 0x0f;
    *any_mods = pressed & any;
    return ((pressed & ~any) == (req & ~any));
}

static void register_mods2( uint8_t mods ) {
#ifdef AVOID_SINGLE_ALT_WINDOWS
    if (mods & MOD_MASK_ALT) {
        register_code( KC_LCTL );
        if (mods & MOD_BIT( KC_LALT )) register_code( KC_LALT );
        if (mods & MOD_BIT( KC_RALT )) register_code( KC_RALT );
        unregister_code( KC_LCTL );
    }
#else
    if (mods & MOD_BIT( KC_LALT )) register_code( KC_LALT );
    if (mods & MOD_BIT( KC_RALT )) register_code( KC_RALT );
#endif
    if (mods & MOD_BIT( KC_LCTL )) register_code( KC_LCTL );
    if (mods & MOD_BIT( KC_RCTL )) register_code( KC_RCTL );
    if (mods & MOD_BIT( KC_LSFT )) register_code( KC_LSFT );
    if (mods & MOD_BIT( KC_RSFT )) register_code( KC_RSFT );
}

static void unregister_mods2( uint8_t mods ) {
    if (mods & MOD_BIT( KC_RSFT )) unregister_code( KC_RSFT );
    if (mods & MOD_BIT( KC_LSFT )) unregister_code( KC_LSFT );
    if (mods & MOD_BIT( KC_RCTL )) unregister_code( KC_RCTL );
    if (mods & MOD_BIT( KC_LCTL )) unregister_code( KC_LCTL );
    if (mods & MOD_BIT( KC_RALT )) unregister_code( KC_RALT );
    if (mods & MOD_BIT( KC_LALT )) unregister_code( KC_LALT );
}

static void swap_mods2( uint8_t new_mods, uint8_t old_mods ) {
    const uint8_t unreg_mods = old_mods & ~new_mods;
    const uint8_t reg_mods = new_mods & ~old_mods;
    if (unreg_mods) unregister_mods2( unreg_mods );
    if (reg_mods) register_mods2( reg_mods );
}

// returns true when unmapped
static bool unmap_key( void ) {
    if (mapped_mods == 0 && mapped_keycode == KC_NO) {
        return false;
    }
    if (mapped_mods == MOD_TABLE) {
        // do nothing
    } else if (mapped_mods == MOD_MACRO) {
        // restore the mod keys
        register_mods2( registered_mods );
    } else {
        // release the mapped key/mods
        unregister_code( mapped_keycode );
        swap_mods2( registered_mods, mapped_mods );
    }
    mapped_mods = 0;
    mapped_keycode = KC_NO;
    return true;
}

static void map_key( uint8_t mods, uint8_t keycode ) {
    if (mods == MOD_TABLE) {
        map_table_index = keycode;
        const SMapTable* map_table = &map_tables[map_table_index];
        if (map_table->m_on_enter_func) {
            (*map_table->m_on_enter_func)();
        }
    } else if (mods == MOD_MACRO) {
        // release the currrent mods
        unregister_mods2( registered_mods );
        {// send the macro sequence
            const uint16_t* seq = macro_seqs[keycode];
            uint8_t n = 0;
            while (seq[n] != KC_NO) {
                tap_code16( seq[n] );
                n += 1;
            }
        }
    } else {
        // release the currrent mods
        // press the mapped key/mods
        swap_mods2( mods, registered_mods );
        register_code( keycode );
    }
    mapped_mods = mods;
    mapped_keycode = keycode;
}

#ifdef USE_TAP_HOLD_ALT_CTL
static bool modtap_is_tap( SModTapHold* tap, const keyrecord_t* record ) {
    const int16_t tdiff = TIMER_DIFF_16( record->event.time, tap->time );
    return (10 <= tdiff && tdiff < 300);
}

static bool modtap_on_press( const keyrecord_t* record, uint16_t modcode ) {
    bool to_register = true;
    for (uint8_t n = 0; n < MOD_TAP_COUNT; ++n) {
        SModTapHold* tap = &mod_taps[n];
        if (tap->modcode != modcode) continue;
        to_register = false;
        const bool is_tap = modtap_is_tap( tap, record );
        tap->time = record->event.time;
        switch (tap->state) {
          case ETHS_Released:
            tap->state = ETHS_Pressed;
            break;

          case ETHS_Tapped:
            if (is_tap) {
                tap->state = ETHS_Held;
                to_register = true;
            } else {
                tap->state = ETHS_Pressed;
            }
            break;
        }
        break;
    }
    if (to_register) {
        registered_mods |= MOD_BIT( modcode );
        register_code( modcode );
    }
    return false;
}

static bool modtap_on_release( const keyrecord_t* record, uint16_t modcode ) {
    for (uint8_t n = 0; n < MOD_TAP_COUNT; ++n) {
        SModTapHold* tap = &mod_taps[n];
        if (tap->modcode != modcode) continue;
        const bool is_tap = modtap_is_tap( tap, record );
        tap->time = record->event.time;
        switch (tap->state) {
          case ETHS_Pressed:
            if (is_tap) {
                tap->state = ETHS_Tapped;
            } else {
                tap->state = ETHS_Released;
            }
            break;

          case ETHS_Held:
            tap->state = ETHS_Released;
            break;
        }
        break;
    }
    if (registered_mods & MOD_BIT( modcode )) {
        registered_mods &= ~MOD_BIT( modcode );
        unregister_code( modcode );
    }
    return false;
}

static void modtap_hold_mods_if_pressed( uint8_t mods_mask ) {
    for (uint8_t n = 0; n < MOD_TAP_COUNT; ++n) {
        SModTapHold* tap = &mod_taps[n];
        const uint8_t mod_bit = MOD_BIT( tap->modcode );
        if ((mod_bit & mods_mask) == 0) continue;// not a target
        if ((mod_bit & pressed_mods) == 0) continue;// not pressed
        if (mod_bit & registered_mods) continue;// already held
        if (tap->state == ETHS_Pressed) {
            tap->state = ETHS_Held;
            registered_mods |= mod_bit;
            register_code( tap->modcode );
        }
    }
}
#endif
#ifdef AVOID_SINGLE_ALT_WINDOWS
// send CTL press/release when ALT is pressed to avoid that Windows menu gets focused
bool singlealt_on_press( uint16_t keycode ) {
                if ((keycode == KC_LALT || keycode == KC_RALT) && (pressed_mods & MOD_MASK_CTRL) == 0) {
                    register_code( KC_LCTL );
                    register_code( keycode );
                    unregister_code( KC_LCTL );
                    is_single_alt_tap = true;
                    return false;
                }
    return true;
            }

// activate ALT menu if no other keys were pressed / released after ALT was pressed
bool singleat_on_release( uint16_t keycode ) {
    if (is_single_alt_tap && (keycode == KC_LALT || keycode == KC_RALT)) {
                is_single_alt_tap = false;
                unregister_code( keycode );
                register_code( keycode );
                unregister_code( keycode );
                return false;
            }
    return true;
}
#endif

// the processor function
bool process_record_emacs( uint16_t keycode, keyrecord_t* record ) {
    _Static_assert( sizeof( SMapEntry ) == MAP_ENTRY_SIZE, "sizeof( SMapEntry ) != MAP_ENTRY_SIZE" );
#ifdef AVOID_SINGLE_ALT_WINDOWS
    if (is_single_alt_tap && (keycode != KC_LALT && keycode != KC_RALT)) {
        is_single_alt_tap = false;
    }
#endif
    if (IS_MOD( keycode )) {
        if (keycode == KC_LGUI || keycode == KC_RGUI) return true;
        // keep tracking the mod key state
        bool cont = true;
        if (record->event.pressed) {
            pressed_mods |= MOD_BIT( keycode );
#ifdef USE_TAP_HOLD_ALT_CTL
            cont = modtap_on_press( record, keycode );
#else
            registered_mods = pressed_mods;
#endif
#ifdef AVOID_SINGLE_ALT_WINDOWS
            if (singlealt_on_press( keycode ) == false) return false;
#endif
        } else {
            pressed_mods &= ~MOD_BIT( keycode );
#ifdef USE_TAP_HOLD_ALT_CTL
            cont = modtap_on_release( record, keycode );
#else
            registered_mods = pressed_mods;
#endif
#ifdef AVOID_SINGLE_ALT_WINDOWS
            if (singlealt_on_release( keycode ) == false) return false;
#endif
        }
        const bool unmapped = unmap_key();
        return !unmapped && cont;
    } else if (IS_KEY( keycode )) {
        if (record->event.pressed) {// pressed
            const bool unmapped = unmap_key();
            bool mapped = false;
            {// search table for mapping
                const SMapTable* map_table = &map_tables[map_table_index];
                const uint8_t num_entries = map_table->m_size;
                uint8_t index;
                for (index = 0; index < num_entries; ++index) {
                    const SMapEntry* map = (const SMapEntry*) map_table->m_table[index];
                    uint8_t any_mods = 0;
                    if (keycode == map->src_code && match_mods2( pressed_mods, map->src_mods, &any_mods )) {// found!
                        map_key( map->dest_mods | any_mods, map->dest_code );
                        pressed_keycode = keycode;
                        mapped = true;
                        break;
                    }
                }
                if (map_table->m_on_search_func) {
                    (*map_table->m_on_search_func)( index );
                }
            }
#ifdef USE_TAP_HOLD_ALT_CTL
            if (pressed_keycode == KC_NO && mapped == false && map_table_index == MAP_TABLE_INDEX_DEFAULT && pressed_mods != 0) {
                if (keycode == KC_TAB) {// special for Ctl-Tab, Alt-Tab
                    const uint8_t mods = (pressed_mods & (MOD_MASK_CTRL | MOD_MASK_ALT));
                    if (mods) {
                        modtap_hold_mods_if_pressed( mods );
                    }
                }
                map_key( pressed_mods, keycode );
                pressed_keycode = keycode;
                mapped = true;
            }
#endif
            if (unmapped == false && mapped == false) {
                // no processing here, leave it to the next chain
                return true;
            }
            // need to return false when unmapped, so register unmapped keycode here
            if (unmapped && mapped == false) {
                register_code( keycode );
            }
            return false;
        } else {// released
            if (pressed_keycode != KC_NO && pressed_keycode == keycode) {
                pressed_keycode = KC_NO;
                unmap_key();
                return false;
            }
        }
    }
    return true;
}
