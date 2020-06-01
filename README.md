# qmk_ergodash_emacs_keymap

## Summary

This is a personal keymap (Japanese) for ergodash/rev1.

This also implements an Emacs key-binding mode for Windows.

The emacs part is provided in separate files:
- process_emacs.c
- process_emacs.h

so that they can be used in other keymaps.


## Limitation

* This module does not support tapping features such as LT, MT etc, nor the oneshot modifiers.
In fact, this module does not work with such non-basic keycodes that are used to generate other basic keycodes as a result of their processing.
Because such features are handled in the later stage of process_record_* chain, there is no chance for this module to handle those generated keycodes.
In order to use such features like LT, MT, however, a method similar to the one used in `keymap.c` can be employed, where tapping is handled within `process_record_user()` and the generated keycodes are passed to `process_record_emacs()` to allow for this module to handle them.
A limitation of this method is that it cannot support keyrepeat by OS because the tapping will only be sent when the key is released.

* If this module is used, Windows' ALT-(key) menu (a single tap of ALT) will be disabled. However, 'ALT tap + (key)' should still be available.


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


## Supported Emacs key bindings

In the following tables, '*' means that the modifier key that follows the asterisk will be kept pressed/released during the translation.
For example, C-m will be translated to Enter as shown in the fifth row of the default mode table. In this case, Shift and Alt will be kept released.
Likewise, if Alt(Meta) key was pressed at the same time, C-M-m will be translated to M-Enter: Shift will be kept released, and Alt pressed.

### Default mode

| Input  | Translation  | Description  |
|---|---|---|
| C-q  |   | Toggle Emacs mode  |
| C-x  |   | C-x prefix key  |
| C-' ' |   | Enter mark selection mode  |
| C-g  | Esc  | Cancel  |
| C-*S-*M-m  | *S-*M-Enter  | Enter  |
| C-*S-*M-a  | *S-*M-Home  | Beginning  |
| C-*S-*M-e  | *S-*M-End  | End  |
| C-*S-*M-f  | *S-*M-->  | Right  |
| C-*S-*M-b  | *S-*M-<-  | Left  |
| C-*S-*M-p  | *S-*M-^  | Up  |
| C-*S-*M-n  | *S-*M-v  | Down  |
| C-*S-*M-r  | *S-*M-PageUp  | Page up  |
| C-*S-*M-v  | *S-*M-PageDown  | Page down  |
| M-*S-f  | *S-C-'->'  | Next word  |
| M-*S-b  | *S-C-'<-'  | Previous word  |
| C-*S-d  | *S-Del  | Delete  |
| C-h  | BS  | Backspace  |
| C-s  | C-f  | Forward search -> Find  |
| C-o  | Ent, Up, End  | Open line  |
| C-k  | S-End, C-x  | Kill line  |
| C-t  | S-Right, C-x, Left, C-v, Right  | Swap chars  |
| M-d  | CS-Right, C-x  | Kill word  |
| C-*S-i  | *S-Tab  | Tab  |
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

<!---
Extra : Function keys for convenience.
| Input  | Translation  |
|---|---|
| C-*S-*M-1  | *S-*M-F1  |
| C-*S-*M-2  | *S-*M-F2  |
| C-*S-*M-3  | *S-*M-F3  |
| C-*S-*M-4  | *S-*M-F4  |
| C-*S-*M-5  | *S-*M-F5  |
| C-*S-*M-6  | *S-*M-F6  |
| C-*S-*M-7  | *S-*M-F7  |
| C-*S-*M-8  | *S-*M-F8  |
| C-*S-*M-9  | *S-*M-F9  |
| C-*S-*M-10  | *S-*M-F10  |
-->

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

If backlight is enabled by `rules.mk`, the backlight will be toggled to show that this module is in the mark selection mode.

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
