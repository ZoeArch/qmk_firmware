 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

//Sets up what the OLED screens display.

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        28, 28, 56, 56,112,240,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,112, 56, 56, 28,252,252, 14, 14, 14, 14,254, 14, 14, 14, 14,254,254, 28, 28, 56, 56,240,240,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,112, 56, 56, 28, 28, 28, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 28, 28, 56, 56,112,240,224,192,128,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,248, 56, 28, 28, 14,254,254,  7,  7,  7,  7,255,  7,  7,  7,  7,255,255, 14, 14, 28, 28,248,120,240,224,192,128,  0,  0,
        0,  0,  0,  0,224,  0,  1,  3,  7, 15, 30,124,240,224,128,  8, 62, 15,  7,  3,  1,255,  0,  0,  0,  0,255,255,  0,  0,  0,  0,255,  0,  0,  0,  0,255,255,  0,  0,  0,  0,255,  0,  1,  3,  7, 15, 30,124,240,224,128,  8, 62, 15,  7,  3,  1,224,  0,  0,  0,  0,254,254,  0,  0,  0,  0,255,  0,  0,  0,  0,254,254,  0,  0,  0,  0,224,  0,  1,  3,  7, 15, 30,124,240,192,  4, 31,  7,  3,  1,  0,255,  0,  0,  0,  0,255,255,  0,  0,  0,  0,255,  0,  0,  0,  0,255,255,  0,  0,  0,  0,255,  0,  0,  1,  3,  7, 15, 62, 
        0,  0,  0,  0,255,  0,128,192,224,240,120, 56,  1,  3, 15, 30,124,240,224,192,128,  7,  0,  0,  0,  0,127,127,  0,  0,  0,  0,255,  0,  0,  0,  0,127,127,  0,  0,  0,  0,  7,  0,128,192,224,240,120, 56,  1,  3, 15, 30,124,240,224,192,128,255,  0,  0,  0,  0,255,255,  0,  0,  0,  0,255,  0,  0,  0,  0,255,255,  0,  0,  0,  0,255,  0,128,192,224,240,120, 56,  1,  7, 15, 62,120,240,224,192,131,  0,  0,  0,  0, 63, 63,  0,  0,  0,  0,127,  0,  0,  0,  0, 63, 63,  0,  0,  0,  0,  3,128,192,224,240,120, 60, 28,
        56, 56, 28, 28, 15, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 14, 28, 28, 56, 56, 56,112,112,112,112,112,112,112,112,112,112,112, 56, 56, 28, 28, 14, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 14, 28, 28, 56, 63, 63,112,112,112,112,127,112,112,112,112,127,127, 56, 56, 28, 28, 15, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7,  7, 14, 14, 28, 28, 28, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 28, 28, 14, 14,  7,  7,  3,  1,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}


static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Game"), false);
            break;
        default:
            oled_write_P(PSTR("Mod\n"), false);
            break;
    }
    oled_write_P(PSTR("\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
        case 1:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Raise"), false);
            break;
        case 3:
            oled_write_P(PSTR("Lower"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n"), false);

    oled_write_P(PSTR("WPM:\n"), false);
    oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);
    
    oled_write_P(PSTR("\n"), false);

    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif
