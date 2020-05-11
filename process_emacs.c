#include QMK_KEYBOARD_H
#include "keymap_jp.h"

// emacs mode modifiers (use left keycods)
#define MOD_C MOD_BIT(KC_LCTL)
#define MOD_S MOD_BIT(KC_LSFT)
#define MOD_M MOD_BIT(KC_LALT)
#define MOD_G MOD_BIG(KC_LGUI)
#define MOD_CS (MOD_C|MOD_S)
#define MOD_SM (MOD_S|MOD_M)

// emacs mode type (use right keycodes)
#define MOD_TABLE MOD_BIT(KC_RCTL)
#define MOD_MACRO MOD_BIT(KC_RSFT)


// declarations
typedef struct {
    uint8_t src_mods;
    uint8_t src_code;
    uint8_t dest_mods; // mapped mods, or mapped mode (macro, function)
    uint8_t dest_code;
} SMapEntry;

#define MAP_ENTRY_SIZE sizeof( SMapEntry )

typedef void (*key_func_t)( uint8_t keycode );

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


// implementations
static uint8_t map_table_index = MAP_TABLE_INDEX_DEFAULT;
static uint8_t pressed_mods = 0;
static uint8_t pressed_keycode = KC_NO;
static uint8_t mapped_mods = 0;
static uint8_t mapped_keycode = KC_NO;


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
    { MOD_C,    KC_Q,    MOD_TABLE, MAP_TABLE_INDEX_DEFAULT },
};
#define MAP_COUNT_NONE (sizeof( map_table_none ) / sizeof( map_table_none[0] ))

static const uint8_t map_table_default[][MAP_ENTRY_SIZE] = {
    { MOD_C,    KC_Q,    MOD_TABLE, MAP_TABLE_INDEX_NONE },
    { MOD_C,    KC_X,    MOD_TABLE, MAP_TABLE_INDEX_CXPREFIX },
    { MOD_C,    KC_SPC,  MOD_TABLE, MAP_TABLE_INDEX_MARKSEL },
    { MOD_C,    KC_G,    0,         KC_ESC  },// Esc
    { MOD_C,    KC_M,    0,         KC_ENT  },// Enter
    { MOD_C,    KC_A,    0,         KC_HOME },// Home
    { MOD_C,    KC_E,    0,         KC_END  },// End
    { MOD_C,    KC_F,    0,         KC_RGHT },// Right
    { MOD_C,    KC_B,    0,         KC_LEFT },// Left
    { MOD_C,    KC_P,    0,         KC_UP   },// Up
    { MOD_C,    KC_N,    0,         KC_DOWN },// Down
    { MOD_CS,   KC_V,    0,         KC_PGUP },// Page Up
    { MOD_C,    KC_V,    0,         KC_PGDN },// Page Down
    { MOD_M,    KC_F,    MOD_C,     KC_RGHT },// next word
    { MOD_M,    KC_B,    MOD_C,     KC_LEFT },// prev word
    { MOD_C,    KC_D,    0,         KC_DEL  },// Del
    { MOD_C,    KC_H,    0,         KC_BSPC },// BS
    { MOD_C,    KC_S,    MOD_C,     KC_F    },// search (find)
    // macros
    { MOD_C,    KC_O,    MOD_MACRO, EMM_OpenLine },
    { MOD_C,    KC_K,    MOD_MACRO, EMM_KillLine },
    { MOD_C,    KC_T,    MOD_MACRO, EMM_SwapChars },
    { MOD_M,    KC_D,    MOD_MACRO, EMM_KillWord },
    { MOD_C,    JP_SCLN, 0,         JP_ZKHK },// IME
    { MOD_C,    KC_I,    0,         KC_TAB  },// Tab
    { MOD_CS,   KC_I,    MOD_S,     KC_TAB  },// S-Tab
    { MOD_C,    KC_W,    MOD_C,     KC_X    },// cut
    { MOD_M,    KC_W,    MOD_C,     KC_C    },// copy
    { MOD_C,    KC_Y,    MOD_C,     KC_V    },// paste
    { MOD_M,    KC_Y,    MOD_C,     KC_Y    },// redo
    { MOD_SM,   JP_COMM, MOD_C,     KC_HOME },// top
    { MOD_SM,   JP_DOT,  MOD_C,     KC_END  },// bottom
    // mac style
    { MOD_M,    KC_Z,    MOD_C,     KC_Z },// undo
    { MOD_M,    KC_X,    MOD_C,     KC_X },// cut
    { MOD_M,    KC_C,    MOD_C,     KC_C },// copy
    { MOD_M,    KC_V,    MOD_C,     KC_V },// paste
    { MOD_M,    KC_S,    MOD_C,     KC_S },// save
    { MOD_SM,   KC_Z,    MOD_C,     KC_Y },// redo
    { MOD_M,    KC_N,    MOD_C,     KC_N },// new
    { MOD_M,    KC_O,    MOD_C,     KC_O },// open
};
#define MAP_COUNT_DEFAULT (sizeof( map_table_default ) / sizeof( map_table_default[0] ))

const uint8_t map_table_cxprefix[][MAP_ENTRY_SIZE] = {
    { MOD_C,    KC_Q,    MOD_TABLE, MAP_TABLE_INDEX_NONE },
    { MOD_C,    KC_S,    MOD_C,     KC_S },// save
    { MOD_C,    KC_F,    MOD_C,     KC_O },// open
    { MOD_C,    KC_C,    MOD_M,     KC_F4 },// close
    { 0,        KC_U,    MOD_C,     KC_Z },// undo
    { 0,        KC_H,    MOD_C,     KC_A },// All
};
#define MAP_COUNT_CXPREFIX (sizeof( map_table_cxprefix ) / sizeof( map_table_cxprefix[0] ))

static void map_table_cxcprefix_on_search( uint8_t index ) {
    map_table_index = MAP_TABLE_INDEX_DEFAULT;
}

const uint8_t map_table_marksel[][MAP_ENTRY_SIZE] = {
    { MOD_C,    KC_Q,    MOD_TABLE, MAP_TABLE_INDEX_NONE },
    { MOD_C,    KC_G,    MOD_MACRO, EMM_MarkCancel },
    { MOD_C,    KC_W,    MOD_MACRO, EMM_MarkCut },// cut
    { MOD_M,    KC_W,    MOD_MACRO, EMM_MarkCopy },// copy
    { MOD_C,    KC_A,    MOD_S,     KC_HOME },
    { MOD_C,    KC_E,    MOD_S,     KC_END },
    { MOD_C,    KC_F,    MOD_S,     KC_RGHT },
    { MOD_C,    KC_B,    MOD_S,     KC_LEFT },
    { MOD_C,    KC_P,    MOD_S,     KC_UP },
    { MOD_C,    KC_N,    MOD_S,     KC_DOWN },
    { MOD_CS,   KC_V,    MOD_S,     KC_PGUP },
    { MOD_C,    KC_V,    MOD_S,     KC_PGDN },
    { MOD_M,    KC_F,    MOD_CS,    KC_RGHT },// next word
    { MOD_M,    KC_B,    MOD_CS,    KC_LEFT },// prev word
    { MOD_SM,   JP_COMM, MOD_CS,    KC_HOME },
    { MOD_SM,   JP_DOT,  MOD_CS,    KC_END },
    { 0,        KC_LEFT, MOD_S,     KC_LEFT },
    { 0,        KC_RGHT, MOD_S,     KC_RGHT },
    { 0,        KC_UP,   MOD_S,     KC_UP },
    { 0,        KC_DOWN, MOD_S,     KC_DOWN },
};
#define MAP_COUNT_MARKSEL (sizeof( map_table_marksel ) / sizeof( map_table_marksel[0] ))

static void map_table_marksel_on_enter( void ) {
    backlight_toggle();
}

static void map_table_marksel_on_search( uint8_t index ) {
    if (index < 4 || MAP_COUNT_MARKSEL <= index) {
        map_table_index = MAP_TABLE_INDEX_DEFAULT;
        backlight_toggle();
    }
}

static SMapTable map_tables[MAP_TABLE_COUNT] = {
    [MAP_TABLE_INDEX_NONE]     = (SMapTable) { map_table_none,     MAP_COUNT_NONE,     NULL, NULL }, 
    [MAP_TABLE_INDEX_DEFAULT]  = (SMapTable) { map_table_default,  MAP_COUNT_DEFAULT,  NULL, NULL }, 
    [MAP_TABLE_INDEX_CXPREFIX] = (SMapTable) { map_table_cxprefix, MAP_COUNT_CXPREFIX, NULL, map_table_cxcprefix_on_search }, 
    [MAP_TABLE_INDEX_MARKSEL]  = (SMapTable) { map_table_marksel,  MAP_COUNT_MARKSEL,  map_table_marksel_on_enter, map_table_marksel_on_search },
};


// mapping functions
static bool match_mods2( uint8_t pressed, uint8_t mods ) {
    pressed = (pressed | (pressed >> 4)) & 0x07;
    return (pressed == mods);
}

static void register_mods2( uint8_t mods ) {
    if (mods & MOD_MASK_ALT) {
        register_code( KC_LCTL );
        if (mods & MOD_BIT( KC_LALT )) register_code( KC_LALT );
        if (mods & MOD_BIT( KC_RALT )) register_code( KC_RALT );
        unregister_code( KC_LCTL );
    }
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

// returns true when unmapped
static bool unmap_key( void ) {
    if (mapped_mods == 0 && mapped_keycode == KC_NO) {
        return false;
    }
    if (mapped_mods == MOD_TABLE) {
        // do nothing
    } else if (mapped_mods == MOD_MACRO) {
        register_mods2( pressed_mods );
    } else {
        unregister_code( mapped_keycode );
        unregister_mods2( mapped_mods );
        register_mods2( pressed_mods );
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
        unregister_mods2( pressed_mods );
        {// send the macro sequence
            const uint16_t* seq = macro_seqs[keycode];
            uint8_t n = 0;
            while (seq[n] != KC_NO) {
                tap_code16( seq[n] );
                n += 1;
            }
        }
    } else {
        unregister_mods2( pressed_mods );
        register_mods2( mods );
        register_code( keycode );
    }
    mapped_mods = mods;
    mapped_keycode = keycode;
}

// the processor function
bool process_record_emacs( uint16_t keycode, keyrecord_t* record ) {
    if (IS_MOD( keycode )) {
        // keep tracking the mod key state
        if (record->event.pressed) {
            pressed_mods |= MOD_BIT( keycode );
            {// avoid ALT menu (Windows)
                if ((keycode == KC_LALT || keycode == KC_RALT) && (pressed_mods & MOD_MASK_CTRL) == 0) {
                    register_code( KC_LCTL );
                    register_code( keycode );
                    unregister_code( KC_LCTL );
                    return false;
                }
            }
        } else {
            pressed_mods &= ~MOD_BIT( keycode );
        }
        return !unmap_key();
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
                    if (match_mods2( pressed_mods, map->src_mods ) && keycode == map->src_code) {// found!
                        pressed_keycode = keycode;
                        map_key( map->dest_mods, map->dest_code );
                        mapped = true;
                        break;
                    }
                }
                if (map_table->m_on_search_func) {
                    (*map_table->m_on_search_func)( index );
                }
            }
            if (unmapped == false && mapped == false) {
                return true;
            }
            if (unmapped && !mapped) {
                register_code( keycode );
            }
            return false;
        } else {// released
            if (pressed_keycode != KC_NO && keycode == pressed_keycode) {
                pressed_keycode = KC_NO;
                unmap_key();
                return false;
            }
        }
    }
    return true;
}
