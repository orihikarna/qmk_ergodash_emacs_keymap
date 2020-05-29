# qmk_ergodash_emacs_keymap

## Summary

This is a personal keymap (Japanese) for ergodash/rev1.

This also implements an Emacs key-binding mode for Windows.

The emacs part is provided in separate files:
- process_emacs.c
- process_emacs.h

so that they can be used in other keymaps.


## Limitation

* This module does not support tapping features such as LT, MT etc.
In fact, it does not work with non-basic keycodes that generates basic keycodes as a result of some processing.
This is because such non-basic keycodes will be handled in the later stage of process_record chain, and the generated keycodes will never be passed to this module.
In order to realize features similar to LT, MT, however, you can use a method used in `keymap.c` where tapping is handled within `process_record_user()` and the generated keycodes are passed to `process_record_emacs()` to allow for this module to handle them. A limitation of this method is that it cannot enjoy keyrepeat by OS because the tapping will only be sent when the key is released.

* If this module is used, Windows' ALT menu (a single tap of ALT) will be disabled.


## How to use Emacs mode

Because QMK is changing actively, this repository is not a fork of the entire qmk_firmware repository, but is a submodule which is expected to be cloned under some specific keymap directory.

For example:
```
$ cd qmk_firmware/keyboards/ergodash/rev1/keymaps/
$ git submodule add https://github.com/orihikarna/qmk_ergodash_emacs_keymap.git your_keymap_name
```

To enable the Emacs mode in your keymap, include `process_emacs.h` in `keymap.c` as:
```
#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include "process_emacs.h"
```

and, then call `process_record_emacs()` in the beginning of `process_record_user()` as follows:
```
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (process_record_emacs(keycode, record) == false) {
    return false;
  }
  ...
}
```

Also, do not forget to add the source file to `rules.mk`:
```
...

SRC += process_emacs.c
```


## Supported Emacs key bindings:

### Default mode

| Input  | Translation  | Description  |
|---|---|---|
| C-q  |   | Toggle Emacs mode  |
| C-x  |   | C-x prefix key  |
| C-' '|   | Enter mark selection  |
| C-g  | Esc  | Cancel  |
| C-*S-*M-m  | Enter  | Enter  |
| C-*S-*M-a  | Home  | Beginning  |
| C-*S-*M-e  | End  | End  |
| C-*S-*M-f  | ->  | Right  |
| C-*S-*M-b  | <-  | Left  |
| C-*S-*M-p  | ^  | Up  |
| C-*S-*M-n  | v  | Down  |
| C-*S-*M-r  | PageUp  | Page up  |
| C-*S-*M-v  | PageDown  | Page down  |
| M-*S-f  | C-'->'  | Next word  |
| M-*S-b  | C-'<-'  | Previous word  |
| C-*S-d  | Del  | Delete  |
| C-h  | BS  | Backspace  |
| C-s  | C-f  | Forward search -> Find  |
| C-o  | Ent, Up, End  | Open line  |
| C-k  | S-End, C-x  | Kill line  |
| C-t  | S-Right, C-x, Left, C-v, Right  | Swap chars  |
| M-d  | CS-Right, C-x  | Kill word  |
| C-*S-i  | Tab  | Tab  |
| C-w  | C-x  | Cut  |
| M-w  | C-c  | Copy  |
| C-y  | C-v  | Paste  |
| M-y  | C-y  | Redo  |
| S-M-,  | C-Home  | Top  |
| S-M-.  | C-End  | Bottom  |

In addition, here are defined MacOS style shortcuts although these are not Emacsen.

| Input  | Translation  | Description  |
|---|---|---|
| M-z  | C-z  | Undo  |
| M-x  | C-x  | Cut  |
| M-c  | C-c  | Copy  |
| M-v  | C-v  | Paste  |
| M-a  | C-a  | All  |
| M-s  | C-s  | Save  |
| SM-z  | C-y  | Redo  |
| M-n  | C-n  | New  |
| M-o  | C-o  | Open  |

And finally, toggle Japanese IME (when `USE_JP` is defined).

| Input  | Translation  | Description  |
|---|---|---|
| C-;  | 全角半角  | Toggle Japanese IME  |

Extra : function keys
| Input  | Translation  |
|---|---|
| C-*S-*M-1  | F1  |
| C-*S-*M-2  | F2  |
| C-*S-*M-3  | F3  |
| C-*S-*M-4  | F4  |
| C-*S-*M-5  | F5  |
| C-*S-*M-6  | F6  |
| C-*S-*M-7  | F7  |
| C-*S-*M-8  | F8  |
| C-*S-*M-9  | F9  |
| C-*S-*M-10  | F10  |


### C-x prefix mode

| Input  | Translation  | Description  |
|---|---|---|
| C-q  |   | Toggle Emacs mode  |
| C-s  | C-s  | Save  |
| C-f  | C-o  | Open  |
| C-c  | M-F  | Close  |
| u  | C-z  | Undo  |
| h  | C-a  | Select all  |


### Mark selection mode

Backlight is toggled when it is enabled.

| Input  | Translation  | Description  |
|---|---|---|
| C-q  |   | Toggle Emacs mode  |
| C-g  | Right  | Cancel mark selection mode  |
| C-w  | C-x, Left, Right  | Cut  |
| M-w  | C-c, Left  | Copy  |
| C-a  | S-Home  | Beginning  |
| C-e  | S-End  | End  |
| C-f  | S-'->'  | Right  |
| C-b  | S-'<-'  | Left  |
| C-p  | S-'^'  | Up  |
| C-n  | S-'v'  | Down  |
| CS-v  | S-PageUp  | Page up  |
| C-v  | S-PageDown  | Page down  |
| M-F  | SC-'->'  | Next word  |
| M-b  | SC-'<-'  | Previous word  |
| SM-,  | SC-Home  | Top  |
| SM-.  | SC-End  | Bottom  |
| <-  | S-'<-'  | Left  |
| -> | S-'->'  | Right  |
| ^  | S-'^'  | Up  |
| v  | S-'v'  | Down  |
