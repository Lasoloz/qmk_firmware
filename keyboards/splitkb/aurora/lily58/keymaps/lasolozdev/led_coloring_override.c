#include "quantum.h"

#include "layers.h"
#include "../../../../../../users/lasolozdev/src/features/led_coloring.h"

int keycode_to_led_category(uint8_t layer, uint16_t keycode) {
    if (keycode == KC_NO) {
        return LED_IRRELEVANT;
    }

    if (keycode >= TG(0) && keycode <= TG(15)) {
        return LED_ALT_2;
    }

    if (layer == _LOWER) {
        switch (keycode) {
            case KC_UP:
            case KC_LEFT:
            case KC_DOWN:
            case KC_RIGHT:
            case KC_CAPS:
            case KC_ESC:
                return LED_ALT_1;
            case KC_HOME:
            case KC_END:
            case KC_PGUP:
            case KC_PGDN:
            case KC_DEL:
            case KC_INS:
            case KC_PSCR:
            case KC_PAUS:
                return LED_ALT_2;
        }
    } else if (layer == _RAISE) {
        led_t led_usb_state = host_keyboard_led_state();
        switch (keycode) {
            case KC_P0:
            case KC_P1:
            case KC_P2:
            case KC_P3:
            case KC_P4:
            case KC_P5:
            case KC_P6:
            case KC_P7:
            case KC_P8:
            case KC_P9:
                if (!led_usb_state.num_lock) {
                    return LED_NORMAL;
                }
            case KC_MSTP:
            case KC_MPLY:
            case KC_FIND:
            case KC_VOLU:
            case KC_CUT:
            case KC_COPY:
            case KC_PSTE:
            case KC_VOLD:
            case KC_MPRV:
            case KC_MNXT:
                return LED_ALT_1;
            case KC_PENT:
            case KC_PSLS:
            case KC_PAST:
            case KC_PMNS:
            case KC_PDOT:
            case KC_PPLS:
            case KC_CAPS:
            case KC_TAB:
                return LED_ALT_2;
            case KC_NUM:
                if (!host_keyboard_led_state().num_lock) {
                    return LED_ALT_1;
                }
                return LED_ALT_2;
        }
    } else if (layer == _ADJUST) {
        if (keycode == KC_SLEP || keycode == KC_PWR) {
            return LED_ALT_1;
        }
        if (keycode >= TO(0) && keycode <= TO(15)) {
            return LED_ALT_2;
        }
        if (keycode >= RM_HUEU && keycode <= RM_VALD) {
            return LED_HANDLER_FALLTHROUGH;
        }
        return LED_NORMAL;
    } else if (layer == _GAMING_1) {
        switch (keycode) {
            case KC_UP:
            case KC_LEFT:
            case KC_DOWN:
            case KC_RIGHT:
            case KC_MPLY:
            case KC_VOLU:
            case KC_VOLD:
                return LED_ALT_1;
        }
    }

    return LED_NORMAL;
}

bool layer_led_enabled_as_highest(uint8_t layer) {
    return layer == _ADJUST || layer == _GAMING_1;
}
