#pragma once
#include "quantum.h"
/*
typedef enum {
    DISABLE_OVERRIDE,
    US_KEY_ON_JP_OS_OVERRIDE,
    JP_KEY_ON_US_OS_OVERRIDE,
} OVERRIDE_MODE;

typedef union {
    uint32_t raw;
    struct {
        uint8_t override_mode;
    };
} keyboard_config_t;

enum kb_keycodes {
    DISABLE_KEY_OVERRIDES = KC_FN0,
    ENABLE_US_KEY_ON_JP_OS_OVERRIDE,
    ENABLE_JP_KEY_ON_US_OS_OVERRIDE,
};

void set_key_override(OVERRIDE_MODE mode);
void eeconfig_init_kb(void);
*/
void matrix_init_kb(void);
