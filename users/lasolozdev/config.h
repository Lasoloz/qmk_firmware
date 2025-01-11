#pragma once

#ifdef OLED_ENABLE
#   undef OLED_FONT_H
#   define OLED_FONT_H "users/lasolozdev/src/glcdfont.c"
#endif

#ifdef RGB_MATRIX_ENABLE
#   define SPLIT_LED_STATE_ENABLE
#endif

#ifdef SUPER_RAISE_ENABLE
#   define SPLIT_TRANSACTION_IDS_USER USER_SYNC_LAYER_LOCK
#endif
