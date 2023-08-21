#include"ecu_button.h"


/**
 * 
 * @param btn
 * @return 
 */
Std_ReturnType button_initialize (const button_t *btn)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == btn)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = btn->port_name, .pin = btn->pin,
                        .direction = GPIO_DIRECTION_INPUT, .logic = btn->button_connection};
        ret = gpio_pin_direction_inializtion(&pin_obj);
    }

    return ret;    
    
}

/**
 * 
 * @param btn
 * @param btn_state
 * @return 
 */
Std_ReturnType button_read_state (const button_t *btn,button_state_t *btn_state)
{
    Std_ReturnType ret = E_OK;
    logic_t pin_logic_status = GPIO_LOW;
    pin_config_t pin_obj = {.port = btn->port_name, .pin = btn->pin,
                        .direction = GPIO_DIRECTION_INPUT, .logic = btn->button_connection};
    
    if((NULL == btn) || (NULL == btn_state))
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_raed_logic(&pin_obj,&pin_logic_status);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection)
        {
            if(GPIO_HIGH == pin_logic_status)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection)
        {
            if(GPIO_HIGH == pin_logic_status)
            {
                *btn_state = BUTTON_RELEASED;
            }
            else
            {
                *btn_state = BUTTON_PRESSED;
            }            
        }
        else
        {
            /*****    NOTHING    *****/
        }
    }

    return ret;       
}