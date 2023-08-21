#include"ecu_7_seg.h"



/**
 * 
 * @param segment
 * @return 
 */
Std_ReturnType seven_segment_initialize (const segment_t *segment)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == segment)
    {
        ret = E_NOT_OK;
    }
    else
    {
//        pin_config_t pin_obj = {.port = relay->port_name, .pin = relay->pin,
//                                .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status};
        ret = gpio_pin_inialization(&(segment->segment_pins[SEGGMENT_PIN0]));
        ret = gpio_pin_inialization(&(segment->segment_pins[SEGGMENT_PIN1]));
        ret = gpio_pin_inialization(&(segment->segment_pins[SEGGMENT_PIN2]));
        ret = gpio_pin_inialization(&(segment->segment_pins[SEGGMENT_PIN3]));

    }

    return ret;      
}

/**
 * 
 * @param segment
 * @param number
 * @return 
 */
Std_ReturnType seven_segment_write_number (const segment_t *segment, uint8 number)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL == segment) || (9 < number))
    {
        ret = E_NOT_OK;
    }
    else
    {
//        pin_config_t pin_obj = {.port = relay->port_name, .pin = relay->pin,
//                                .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status};
//        ret = gpio_pin_inialization(&pin_obj);
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGGMENT_PIN0]),(number&0x01) );
		ret = gpio_pin_write_logic(&(segment->segment_pins[SEGGMENT_PIN1]),((number>>1)&0x01) );
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGGMENT_PIN2]),((number>>2)&0x01) );
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGGMENT_PIN3]),((number>>3)&0x01) );

    }

    return ret;     
}
