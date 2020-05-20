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
In order to realize features similar to LT, MT, however, you can use a method used in `keymap.c` where tapping is handled within `process_record_user()` and the generated keycodes are passed to `process_record_emacs()` to allow for this module to handle them.

* If this module is used, Windows' ALT menu (single tappint of ALT) will be disabled.


## How to use emacs mode

Because QMK is changing actively, this repository is not a fork of the entire qmk_firmware repository, but is a submodule that is expected to be cloned under some specific keymap directory.

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
| C-m  | Enter  | Enter  |
| C-a  | Home  | Beginning  |
| C-e  | End  | End  |
| C-f  | ->  | Right  |
| C-b  | <-  | Left  |
| C-p  | ^  | Up  |
| C-n  | v  | Down  |
| CS-v  | PageUp  | Page up  |
| C-v  | PageDown  | Page down  |
| M-f  | C-'->'  | Next word  |
| M-b  | C-'<-'  | Previous word  |
| C-d  | Del  | Delete  |
| C-h  | BS  | Backspace  |
| C-s  | C-f  | Forward search -> Find  |
| C-o  | Ent, Up, End  | Open line  |
| C-k  | S-End, C-x  | Kill line  |
| C-t  | S-Right, C-x, Left, C-v, Right  | Swap chars  |
| M-d  | CS-Right, C-x  | Kill word  |
| C-i  | Tab  | Tab  |
| C-w  | C-x  | Cut  |
| M-w  | C-c  | Copy  |
| C-y  | C-v  | Paste  |
| M-y  | C-y  | Redo  |
| SM-,  | C-Home  | Top  |
| SM-.  | C-End  | Bottom  |

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
