/* 
 * File:   ecu_lcd.h
 * Author: moham
 *
 * Created on June 5, 2023, 7:45 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H




/* Section : Includes */
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"ecu_lcd_cfg.h"

/* Section : Macro Declarations */

#define _LCD_CLEAR                            0X01
#define _LCD_RETURN_HOME                      0X02
#define _LCD_ENTERY_MODE                      0X06
#define _LCD_CURSOR_OFF_DISPLAY_ON            0X0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF           0X08
#define _LCD_CURSOR_ON_BLINK_ON               0X0F
#define _LCD_CURSOR_ON_BLINK_OFF              0X0E
#define _LCD_DISPLAY_SHIFT_RIGHT              0X1C
#define _LCD_DISPLAY_SHIFT_LEFT               0X18
#define _LCD_8BIT_MODE_2_LINE                 0X38
#define _LCD_4BIT_MODE_2_LINE                 0X28
#define _LCD_CGRAM_START                      0X40
#define _LCD_DDRAM_START                      0X80


#define ROW_1                                 1
#define ROW_2                                 2
#define ROW_3                                 3
#define ROW_4                                 4



/* Section : Macro Functions Declarations */



/* Section : Data Type Declarations */

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];

}chr_lcd_4bit_t;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];    
}chr_lcd_8bit_t;


/* Section : Functions Declarations */


Std_ReturnType lcd_4bit_initialize (const chr_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command (const chr_lcd_4bit_t *lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char_data (const chr_lcd_4bit_t *lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos (const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data);
Std_ReturnType lcd_4bit_send_string (const chr_lcd_4bit_t *lcd, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos (const chr_lcd_4bit_t *lcd,uint8 row, uint8 column,uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char (const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,const uint8 _chr[],uint8 mem_pos);


Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data);
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column,uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,const uint8 _chr[],uint8 mem_pos);



Std_ReturnType convert_uint8_to_string (uint8  value, uint8 *str);
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);
Std_ReturnType convert_uint32_to_string  (uint32 value, uint8 *str);


#endif	/* ECU_LCD_H */

