/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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
#include <stdbool.h>
#include <stdint.h>

extern bool is_drag_scroll;
bool is_key_held = false;
uint16_t scroll_mode_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRAG_SCROLL:  // Replace DRAG_SCROLL with the actual keycode you're using
#ifdef PLOOPY_DRAGSCROLL_CUSTOM
            if (record->event.pressed) {
                scroll_mode_timer = timer_read();
                is_key_held = true;
                is_drag_scroll = true; // Enable scroll mode on key press
            } else {
                if (timer_elapsed(scroll_mode_timer) < SCROLL_MODE_TOGGLE_DELAY) {
                    // Toggle scroll mode on tap (press-and-release)
                    if (!is_key_held) {
                        is_drag_scroll = !is_drag_scroll;
                    }
                }
                is_key_held = false;
                is_drag_scroll = false; // Disable scroll mode on key release
            }
            return false; // Disable behavior for DRAG_SCROLL defined on keyboard level.
#else
            return true;
#endif
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN1, DRAG_SCROLL, KC_BTN4, KC_BTN2, KC_BTN5
    ),
};
