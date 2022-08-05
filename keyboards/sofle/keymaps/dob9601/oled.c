#include "raw_hid.h"
#include "print.h"

static char current_screen[] = {
        0,  0,  0,  0,  0,  0,  0,  0,128,192, 96, 48, 16, 16,  8,  8,  8,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  8,  8, 16, 16, 16, 16, 32, 96,192,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 64,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,128,  0,  0,  0,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,248,135,  1,  0,  0,  0,128, 96, 32, 16,  8,  8,  4,  4,  4,  4,  4,  4,  4,  4,  4, 12,152,112,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  3,  6,  4, 12,  8, 24, 16, 16, 32, 64,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,140,133,133,  7,  0,  0,  0,  0,  0, 31, 49, 32, 32, 63, 48, 48, 24, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  3, 14,120,192,  0,  3,  4,  8,  8, 16, 32, 32, 64,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  2,  2,  2,  2,  2,  2,  2,  2,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  1,  3, 30,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 12, 31, 35, 66, 67, 70,124, 48,  0,  0,  0,  0,  0,  0,  7, 13, 24, 16, 59, 62, 16, 24,  7,  0,  0,  0, 12, 24, 48, 32, 32, 32, 56, 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  2,  6,  4,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32, 32, 32, 16, 16, 16, 16,  8,  8, 12,  7,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  9, 25, 21, 22,  6,  6,  4,  0,  0,  0,  0,  0,  0,  0, 28, 18, 35, 33, 35, 34, 44, 56,  0,  0,  0,  0,  8,  8,  8,  4,  4,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
};

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uprintf("Data received: %s", data);
    // Receive packet
    // Overwrite current_screen with contents
}


static void render_logo(void) {
    oled_write_raw_P(current_screen, sizeof(current_screen));
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_ln_P(PSTR("MODE"), true);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("Mac"), false);
    } else {
        oled_write_ln_P(PSTR("Win"), false);
    }
    oled_write_ln_P(PSTR(""), false);

    oled_write_P(PSTR("ROTAR"), true);
    switch (rotary_mode) {
        case 0:
            oled_write_ln_P(PSTR("Vol."), false);
            break;
        case 1:
            oled_write_P(PSTR("Media"), false);
            break;
        case 2:
            oled_write_P(PSTR("Mouse"), false);
            break;

    }

    oled_write_ln_P(PSTR(""), false);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("Clmk"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), true);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
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
