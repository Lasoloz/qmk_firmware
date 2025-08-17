#pragma once

enum led_category_t {
    LED_NORMAL,
    LED_ALT_1,
    LED_ALT_2,
    LED_IRRELEVANT,
    LED_HANDLER_FALLTHROUGH
};

int keycode_to_led_category(uint8_t layer, uint16_t keycode);

#ifdef RGB_MATRIX_ADDITIONAL_LAYERS
bool layer_led_enabled_as_highest(uint8_t layer);
#endif
