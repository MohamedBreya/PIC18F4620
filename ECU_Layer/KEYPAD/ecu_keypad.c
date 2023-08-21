#include"ecu_keypad.h"



/**
 * 
 * @param _keypad_opj
 * @return 
 */
Std_ReturnType keypad_initialize (const keypad_t *_keypad_opj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _keypad_opj)
    {
        ret = E_NOT_OK;
    }
    else
    {
//        pin_config_t pin_obj = {.port = relay->port_name, .pin = relay->pin,
//                                .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status};
//        ret = gpio_pin_inialization(&pin_obj);

    }

    return ret;      
}



/**
 * 
 * @param _keypad_opj
 * @param value
 * @return 
 */
Std_ReturnType keypad_get_value (const keypad_t *_keypad_opj, uint8 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT ;
    
    if((NULL == _keypad_opj) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(rows_counter = ZERO_INIT;rows_counter < ECU_KEYPAD_ROWS;rows_counter++)
        {
            ret = gpio_pin_inialization(&(_keypad_opj->keypad_row_pins[rows_counter]));
        }
        
        for(columns_counter = ZERO_INIT;columns_counter < ECU_KEYPAD_COLUMNS ;columns_counter++)
        {
            ret = gpio_pin_direction_inializtion(&(_keypad_opj->keypad_columns_pins[columns_counter]));
        }

    }

    return ret;    
}
