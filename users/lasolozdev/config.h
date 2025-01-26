#pragma once

// Redefine font using userspace font
#ifdef OLED_ENABLE
#   undef OLED_FONT_H
#   define OLED_FONT_H "users/lasolozdev/src/glcdfont.c"
#endif

// Enable split led state for Num/Caps/Scroll lock checking on slave side
// Enable layer state checking on the slave side
#ifdef RGB_MATRIX_ENABLE
#   define SPLIT_LED_STATE_ENABLE
#   define SPLIT_LAYER_STATE_ENABLE
#endif

// Define user transaction IDs, that might or might not be used
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_LAYER_LOCK
