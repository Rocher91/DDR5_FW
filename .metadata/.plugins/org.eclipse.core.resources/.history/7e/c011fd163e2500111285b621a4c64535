/*
 * nhd0420_i2c.h
 *
 *  Created on: Mar 21, 2026
 *      Author: Xavi
 */

#ifndef SRC_NHD0420_I2C_H_
#define SRC_NHD0420_I2C_H_

#include "stm32h5xx.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 7-bit default address from datasheet: 0x28
 * Datasheet also states 0x50 when counting the R/W bit.
 */
#define NHD0420_I2C_ADDR_7BIT      0x28U

/* Command prefix */
#define NHD0420_PREFIX             0xFEU

/* Commands */
#define NHD0420_CMD_DISPLAY_ON     0x41U
#define NHD0420_CMD_DISPLAY_OFF    0x42U
#define NHD0420_CMD_SET_CURSOR     0x45U
#define NHD0420_CMD_HOME           0x46U
#define NHD0420_CMD_UNDERLINE_ON   0x47U
#define NHD0420_CMD_UNDERLINE_OFF  0x48U
#define NHD0420_CMD_CURSOR_LEFT    0x49U
#define NHD0420_CMD_CURSOR_RIGHT   0x4AU
#define NHD0420_CMD_BLINK_ON       0x4BU
#define NHD0420_CMD_BLINK_OFF      0x4CU
#define NHD0420_CMD_BACKSPACE      0x4EU
#define NHD0420_CMD_CLEAR          0x51U
#define NHD0420_CMD_CONTRAST       0x52U
#define NHD0420_CMD_BRIGHTNESS     0x53U
#define NHD0420_CMD_CUSTOM_CHAR    0x54U
#define NHD0420_CMD_SHIFT_LEFT     0x55U
#define NHD0420_CMD_SHIFT_RIGHT    0x56U
#define NHD0420_CMD_SHOW_FW        0x70U
#define NHD0420_CMD_SHOW_I2C_ADDR  0x72U

typedef struct
{
    I2C_TypeDef *i2c;
    uint8_t addr_7bit;
    void (*delay_ms)(uint32_t ms);
} nhd0420_t;

int nhd0420_init(nhd0420_t *lcd, I2C_TypeDef *i2c, uint8_t addr_7bit,
                 void (*delay_ms_fn)(uint32_t ms));

int nhd0420_display_on(nhd0420_t *lcd);
int nhd0420_display_off(nhd0420_t *lcd);
int nhd0420_clear(nhd0420_t *lcd);
int nhd0420_home(nhd0420_t *lcd);

int nhd0420_set_cursor_pos(nhd0420_t *lcd, uint8_t pos);
int nhd0420_set_cursor_rc(nhd0420_t *lcd, uint8_t row, uint8_t col);

int nhd0420_write_char(nhd0420_t *lcd, char c);
int nhd0420_write_data(nhd0420_t *lcd, const uint8_t *data, size_t len);
int nhd0420_write_string(nhd0420_t *lcd, const char *s);

int nhd0420_write_line(nhd0420_t *lcd, uint8_t row, const char *s);

int nhd0420_set_contrast(nhd0420_t *lcd, uint8_t contrast_1_to_50);
int nhd0420_set_backlight(nhd0420_t *lcd, uint8_t brightness_1_to_8);

int nhd0420_underline_on(nhd0420_t *lcd);
int nhd0420_underline_off(nhd0420_t *lcd);
int nhd0420_blink_on(nhd0420_t *lcd);
int nhd0420_blink_off(nhd0420_t *lcd);

int nhd0420_shift_left(nhd0420_t *lcd);
int nhd0420_shift_right(nhd0420_t *lcd);

int nhd0420_load_custom_char(nhd0420_t *lcd, uint8_t addr_0_to_7,
                             const uint8_t bitmap[8]);

#ifdef __cplusplus
}
#endif

#endif /* SRC_NHD0420_I2C_H_ */
