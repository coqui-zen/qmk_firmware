/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD,
};

enum planck_keycodes { QWERTY = SAFE_RANGE };

// Define a type containing as many tapdance states as you need
typedef enum { TD_NONE, TD_UNKNOWN, TD_SINGLE_TAP, TD_SINGLE_HOLD, TD_DOUBLE_SINGLE_TAP } td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

// Create a global instance of the tapdance state type
static td_tap_t al_tap_state = {.is_press_action = true, .state = TD_NONE};

enum { A_LOWER };

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void altlower_finished(qk_tap_dance_state_t *state, void *user_data);
void altlower_reset(qk_tap_dance_state_t *state, void *user_data);

enum combos {
    SUP_2,
    SUP_3,
};

const uint16_t PROGMEM sup2_combo[] = {KC_CIRC, KC_2, COMBO_END};
const uint16_t PROGMEM sup3_combo[] = {KC_CIRC, KC_3, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {[SUP_2] = COMBO(sup2_combo, UC(0x00B9)), [SUP_3] = COMBO(sup3_combo, UC(0x00B3))};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define TD_LWR TD(A_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS]
                              [MATRIX_COLS] = {
//    ┌──────┬──────┬──────┬──────┬────────┬─────┬─────┬───────┬──────┬──────┬────┬──────┐
//    │ tab  │  q   │  w   │  e   │   r    │  t  │  y  │   u   │  i   │  o   │ p  │ bspc │
//    ├──────┼──────┼──────┼──────┼────────┼─────┼─────┼───────┼──────┼──────┼────┼──────┤
//    │ esc  │  a   │  s   │  d   │   f    │  g  │  h  │   j   │  k   │  l   │ ;  │ "'"  │
//    ├──────┼──────┼──────┼──────┼────────┼─────┼─────┼───────┼──────┼──────┼────┼──────┤
//    │ lsft │  z   │  x   │  c   │   v    │  b  │  n  │   m   │  ,   │  .   │ /  │ ent  │
//    ├──────┼──────┼──────┼──────┼────────┼─────┼─────┼───────┼──────┼──────┼────┼──────┤
//    │ lctl │ lgui │ lalt │ aLGR │ TD_LWR │ spc │ spc │ RAISE │ left │ down │ up │ rght │
//    └──────┴──────┴──────┴──────┴────────┴─────┴─────┴───────┴──────┴──────┴────┴──────┘
[_QWERTY] = LAYOUT_planck_grid(
  KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R   , KC_T   , KC_Y   , KC_U  , KC_I    , KC_O    , KC_P    , KC_BSPC,
  KC_ESC  , KC_A    , KC_S    , KC_D    , KC_F   , KC_G   , KC_H   , KC_J  , KC_K    , KC_L    , KC_SCLN , KC_QUOT,
  KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V   , KC_B   , KC_N   , KC_M  , KC_COMM , KC_DOT  , KC_SLSH , KC_ENT ,
  KC_LCTL , KC_LGUI , KC_LALT , KC_ALGR , TD_LWR , KC_SPC , KC_SPC , RAISE , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬───────┬──────────┬─────────────┬──────┬─────┐
//    │  `  │  1  │  2  │  3  │  4  │  5  │  6  │   7   │    8     │      9      │  0   │ del │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼───────┼──────────┼─────────────┼──────┼─────┤
//    │ del │ f1  │ f2  │ f3  │ f4  │ f5  │ f6  │   -   │    =     │      [      │  ]   │ '\' │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼───────┼──────────┼─────────────┼──────┼─────┤
//    │     │ f7  │ f8  │ f9  │ f10 │ f11 │ f12 │ iso-- │ www_back │ www_forward │      │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼───────┼──────────┼─────────────┼──────┼─────┤
//    │     │     │     │     │     │     │     │       │   home   │    pgdn     │ pgup │ end │
//    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴───────┴──────────┴─────────────┴──────┴─────┘
[_LOWER] = LAYOUT_planck_grid(
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_DEL ,
  KC_DEL  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_MINS , KC_EQL  , KC_LBRC , KC_RBRC , KC_BSLS,
  _______ , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_NUHS , KC_WBAK , KC_WFWD , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_HOME , KC_PGDN , KC_PGUP , KC_END
),

//    ┌─────┬─────┬─────┬──────┬─────┬─────┬─────┬──────────┬──────┬──────┬──────┬─────┐
//    │  ~  │  !  │  @  │ '--' │  $  │  %  │  ^  │    &     │  *   │  (   │  )   │ del │
//    ├─────┼─────┼─────┼──────┼─────┼─────┼─────┼──────────┼──────┼──────┼──────┼─────┤
//    │ del │ f1  │ f2  │  f3  │ f4  │ f5  │ f6  │    _     │  +   │  {   │  }   │  |  │
//    ├─────┼─────┼─────┼──────┼─────┼─────┼─────┼──────────┼──────┼──────┼──────┼─────┤
//    │     │ f7  │ f8  │  f9  │ f10 │ f11 │ f12 │ S(iso--) │ mprv │ mnxt │ mply │     │
//    ├─────┼─────┼─────┼──────┼─────┼─────┼─────┼──────────┼──────┼──────┼──────┼─────┤
//    │     │     │     │      │     │     │     │          │ mute │ vold │ volu │     │
//    └─────┴─────┴─────┴──────┴─────┴─────┴─────┴──────────┴──────┴──────┴──────┴─────┘
[_RAISE] = LAYOUT_planck_grid(
  KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR    , KC_ASTR , KC_LPRN , KC_RPRN , KC_DEL ,
  KC_DEL  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_UNDS    , KC_PLUS , KC_LCBR , KC_RCBR , KC_PIPE,
  _______ , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , S(KC_NUHS) , KC_MPRV , KC_MNXT , KC_MPLY , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______    , KC_MUTE , KC_VOLD , KC_VOLU , _______
),

//    ┌─────┬─────────┬────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬──────┬──────┬─────┐
//    │     │ QK_BOOT │ DEBUG  │ RGB_TOG │ RGB_MOD │ RGB_HUI │ RGB_HUD │ RGB_SAI │ RGB_SAD │      │ pscr │ del │
//    ├─────┼─────────┼────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────┼──────┼─────┤
//    │     │         │ MU_MOD │  AU_ON  │ AU_OFF  │ AG_NORM │ AG_SWAP │ QWERTY  │         │      │      │     │
//    ├─────┼─────────┼────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────┼──────┼─────┤
//    │     │ MUV_DE  │ MUV_IN │  MU_ON  │ MU_OFF  │  MI_ON  │ MI_OFF  │         │  bRID   │ bRIU │      │     │
//    ├─────┼─────────┼────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────┼──────┼─────┤
//    │     │         │        │         │         │         │         │         │         │      │      │     │
//    └─────┴─────────┴────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴──────┴──────┴─────┘
[_ADJUST] = LAYOUT_planck_grid(
  _______ , QK_BOOT , DEBUG   , RGB_TOG , RGB_MOD , RGB_HUI , RGB_HUD , RGB_SAI , RGB_SAD , _______ , KC_PSCR , KC_DEL ,
  _______ , _______ , MU_MOD  , AU_ON   , AU_OFF  , AG_NORM , AG_SWAP , QWERTY  , _______ , _______ , _______ , _______,
  _______ , MUV_DE  , MUV_IN  , MU_ON   , MU_OFF  , MI_ON   , MI_OFF  , _______ , KC_BRID , KC_BRIU , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌──────┬──────┬──────┬──────┬──────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
//    │ kp_* │ kp_1 │ kp_2 │ kp_3 │ kp_- │     │     │     │     │     │     │     │
//    ├──────┼──────┼──────┼──────┼──────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │ kp_/ │ kp_4 │ kp_5 │ kp_6 │ kp_+ │     │     │     │     │     │     │     │
//    ├──────┼──────┼──────┼──────┼──────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │      │ kp_7 │ kp_8 │ kp_9 │ kp_= │     │     │     │     │     │     │     │
//    ├──────┼──────┼──────┼──────┼──────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │      │ kp_0 │      │ kp_. │      │     │     │     │     │     │     │     │
//    └──────┴──────┴──────┴──────┴──────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
[_NUMPAD] = LAYOUT_planck_grid(
  KC_PAST , KC_P1 , KC_P2   , KC_P3   , KC_PMNS , _______ , _______ , _______ , _______ , _______ , _______ , _______,
  KC_PSLS , KC_P4 , KC_P5   , KC_P6   , KC_PPLS , _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_P7 , KC_P8   , KC_P9   , KC_PEQL , _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_P0 , _______ , KC_PDOT , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
)
} layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        default:
            break;
    }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo += 1;
            } else {
                muse_tempo -= 1;
            }
        }
    } else {
        if (clockwise) {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_DOWN);
#else
            tap_code(KC_PGDN);
#endif
        } else {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_UP);
#else
            tap_code(KC_PGUP);
#endif
        }
    }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
            break;
        default:
            break;
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed)
            return TD_SINGLE_TAP;
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2)
        return TD_DOUBLE_SINGLE_TAP;
    else
        return TD_UNKNOWN;
}

void altlower_finished(qk_tap_dance_state_t *state, void *user_data) {
    al_tap_state.state = cur_dance(state);
    switch (al_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(_LOWER);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_NUMPAD)) {
                // If already set, then switch it off
                layer_off(_NUMPAD);
                PLAY_SONG(layerswitch_song);
            } else {
                // If not already set, then switch the layer on
                layer_on(_NUMPAD);
                PLAY_SONG(layerswitch_song);
            };
            break;
        default:
            break;
    }
}

void altlower_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (al_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_LOWER);
    }
    al_tap_state.state = TD_NONE;
}

// Associate tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {[A_LOWER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlower_finished, altlower_reset)};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}
