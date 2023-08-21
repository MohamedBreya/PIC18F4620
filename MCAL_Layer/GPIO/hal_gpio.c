#include "hal_gpio.h"

static volatile uint8 *tris_registers[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
static volatile uint8 *lat_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};
static volatile uint8 *port_registers[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};



/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_inializtion(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(_pin_config->direction)
        {
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
                break;
            default:
                ret=E_NOT_OK;
        }
    }

    return ret;
}


/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return 
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config,direction_t *direction_status)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PORT_PIN_MAX_NUMBER-1 )
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;
}

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(logic)
        {
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}


/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
Std_ReturnType gpio_pin_raed_logic(const pin_config_t *_pin_config,logic_t *logic)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PORT_PIN_MAX_NUMBER-1 )
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;
}


/**
 * 
 * @param _pin_config
 * @return 
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;
}
Std_ReturnType gpio_pin_inialization(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_inializtion(_pin_config);
        ret = gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }
    
    return ret;
}

#endif

#if GPIO_PORT_CONFIGRATIONS == CONFIG_ENABLE

Std_ReturnType gpio_port_direction_inializtion(port_index_t port, port_direction_t direction)
{
    Std_ReturnType ret = E_OK;
    if( port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *tris_registers[port] = direction;
    }
    return ret;
}
Std_ReturnType gpio_port_get_direction_status(port_index_t port, port_direction_t *direction_status)
{
    Std_ReturnType ret = E_OK;
    if( (port > PORT_MAX_NUMBER-1) || (NULL == direction_status) )
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = *tris_registers[port];
    }
    return ret;
}
Std_ReturnType gpio_port_write_logic(port_index_t port, port_logic_t logic)
{
    Std_ReturnType ret = E_OK;
    if( (port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
       *lat_registers[port] = logic ;
    }
    return ret;
}
Std_ReturnType gpio_port_raed_logic(port_index_t port, port_logic_t *logic)
{
    Std_ReturnType ret = E_OK;
    if( (port > PORT_MAX_NUMBER-1)|| (NULL == logic))
    {
        ret = E_NOT_OK;
    }
    else
    {
       *logic = *port_registers[port] ;
    }
    return ret;
}
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    Std_ReturnType ret = E_OK;
    if( (port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
       *lat_registers[port] ^= PORT_MASK  ;
    }
    return ret;
    
}


#endif


