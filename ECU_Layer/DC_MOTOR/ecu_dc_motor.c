#include"ecu_dc_motor.h"





/**
 * 
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _dc_motor)
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
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _dc_motor)
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
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _dc_motor)
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
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _dc_motor)
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
