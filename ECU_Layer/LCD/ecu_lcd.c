#include"ecu_lcd.h"




static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column);






/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_4bit_initialize (const chr_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 l_data_pin_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= gpio_pin_inialization(&(lcd->lcd_rs));
        ret &= gpio_pin_inialization(&(lcd->lcd_en));
        for(l_data_pin_counter = ZERO_INIT;l_data_pin_counter < 4;l_data_pin_counter++)
        {
            ret &= gpio_pin_inialization(&(lcd->lcd_data[l_data_pin_counter]));
        }
        __delay_ms(20);
        ret &= lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret &= lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret &= lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret &= lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret &= lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret &= lcd_4bit_send_command(lcd, _LCD_ENTERY_MODE);
        ret &= lcd_4bit_send_command(lcd, _LCD_CURSOR_ON_BLINK_OFF);       
        ret &= lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret &= lcd_4bit_send_command(lcd, 0x80);        
    }

    return ret; 
}


/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_4bit_send_command (const chr_lcd_4bit_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
        ret &= lcd_send_4bits(lcd,(command >> 4));
        ret &= lcd_4bit_send_enable_signal(lcd);
        ret &= lcd_send_4bits(lcd, command);
        ret &= lcd_4bit_send_enable_signal(lcd);
    }

    return ret;     
}


/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data (const chr_lcd_4bit_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
        ret &= lcd_send_4bits(lcd,(data >> 4));
        ret &= lcd_4bit_send_enable_signal(lcd);
        ret &= lcd_send_4bits(lcd, data);
        ret &= lcd_4bit_send_enable_signal(lcd);
    }

    return ret;     
}


/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data_pos (const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= lcd_4bit_set_cursor(lcd,row,column);
        ret &= lcd_4bit_send_char_data(lcd,data);
    }

    return ret;     
}


/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string (const chr_lcd_4bit_t *lcd, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd || NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret &= lcd_4bit_send_char_data(lcd,*str++);
        }
    }

    return ret;     
}


/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string_pos (const chr_lcd_4bit_t *lcd,uint8 row, uint8 column,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd || NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= lcd_4bit_set_cursor(lcd,row,column);
        while(*str)
        {
            ret &= lcd_4bit_send_char_data(lcd,*str++);
        }
    }

    return ret;     
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_4bit_send_custom_char (const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,const uint8 _chr[],uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= lcd_4bit_send_command(lcd,(_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = ZERO_INIT;lcd_counter < 7;lcd_counter++)
        {
            ret &= lcd_4bit_send_char_data(lcd,_chr[lcd_counter]);
        }
        ret &= lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
    }

    return ret;     
}

/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 l_data_pin_cpounter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= gpio_pin_inialization(&(lcd->lcd_rs));
        ret &= gpio_pin_inialization(&(lcd->lcd_en));
        for(l_data_pin_cpounter = ZERO_INIT;l_data_pin_cpounter < 8;l_data_pin_cpounter++)
        {
            ret &= gpio_pin_inialization(&(lcd->lcd_data[l_data_pin_cpounter]));
        }
        __delay_ms(20);
        ret &= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret &= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret &= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret &= lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret &= lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret &= lcd_8bit_send_command(lcd, _LCD_ENTERY_MODE);
        ret &= lcd_8bit_send_command(lcd, _LCD_CURSOR_ON_BLINK_OFF);       
        ret &= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret &= lcd_8bit_send_command(lcd, 0x80);

    }

    return ret;     
}



/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = ZERO_INIT ; 
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
        
        for(l_pin_counter = ZERO_INIT;l_pin_counter<8;l_pin_counter++)
        {
            ret &= gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]),((command>>l_pin_counter)& BIT_MASK));
        }
        ret &= lcd_8bit_send_enable_signal(lcd);
    }

    return ret;     
}


/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
        
        for(l_pin_counter = ZERO_INIT;l_pin_counter<8;l_pin_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]),((data>>l_pin_counter)& BIT_MASK));
        }
        ret &= lcd_8bit_send_enable_signal(lcd);
    }

    return ret;     
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= lcd_8bit_set_cursor(lcd, row, column);
        ret &= lcd_8bit_send_char_data(lcd, data);
    }

    return ret;     
}




/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd || NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            lcd_8bit_send_char_data(lcd,*str++);
        }
    }

    return ret;     
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd || NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= lcd_8bit_set_cursor(lcd, row, column);
        while(*str)
        {
            lcd_8bit_send_char_data(lcd,*str++);
        }        
    }

    return ret;     
}


/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,const uint8 _chr[],uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= lcd_8bit_send_command(lcd,(_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = ZERO_INIT;lcd_counter < 7;lcd_counter++)
        {
            ret &= lcd_8bit_send_char_data(lcd,_chr[lcd_counter]);
        }
        ret &= lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
    }

    return ret;     
}

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &=gpio_pin_write_logic(&(lcd->lcd_data[0]),((_data_command>>0) & BIT_MASK ));
        ret &=gpio_pin_write_logic(&(lcd->lcd_data[1]),((_data_command>>1) & BIT_MASK ));
        ret &=gpio_pin_write_logic(&(lcd->lcd_data[2]),((_data_command>>2) & BIT_MASK ));
        ret &=gpio_pin_write_logic(&(lcd->lcd_data[3]),((_data_command>>3) & BIT_MASK ));
    }
    return ret;
}


static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
        __delay_us(5);
        ret &= gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
    }
    return ret;
}


static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= gpio_pin_write_logic (&(lcd->lcd_en),GPIO_HIGH);
        __delay_us(5);
        ret &= gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
    }
    
    return ret;
}


static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_OK;
    column--;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (row)
        {
                    case ROW_1 :
            ret &= lcd_8bit_send_command(lcd,(0x80 + column));
            break;
        case ROW_2 : 
            ret &= lcd_8bit_send_command(lcd,(0xc0 + column));
            break;        
        case ROW_3 :
            ret &= lcd_8bit_send_command(lcd,(0x94 + column));
            break;        
        case ROW_4 :
            ret &= lcd_8bit_send_command(lcd,(0xd4 + column));
            break; 
        default :
            ret = E_NOT_OK;
        }

    }
    
    return ret;
}



static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_OK;
    column--;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (row)
        {
            case ROW_1 :
            ret &= lcd_4bit_send_command(lcd,(0x80 + column));
            break;
        case ROW_2 : 
            ret &= lcd_4bit_send_command(lcd,(0xc0 + column));
            break;        
        case ROW_3 :
            ret &= lcd_4bit_send_command(lcd,(0x94 + column));
            break;        
        case ROW_4 :
            ret &= lcd_4bit_send_command(lcd,(0xd4 + column));
            break; 
        default :
            ret = E_NOT_OK;
        }

    }
    
    return ret;
}


Std_ReturnType convert_uint8_to_string (uint8  value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str,'\0',4);
        sprintf(str,"%i",value);
    }

    return ret;     
}
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str,'\0',6);
        sprintf(str,"%i",value);
    }

    return ret;     
}
Std_ReturnType convert_uint32_to_string  (uint32 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str,'\0',11);
        sprintf(str,"%i",value);
    }

    return ret;     
}












 
