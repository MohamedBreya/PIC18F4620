/* 
 * File:   hal_gpio.h
 * Author: moham
 *
 * Created on May 23, 2023, 10:45 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

//#include"proc\pic18f4620.h"
#include"C:\Program Files\Microchip\MPLABX\v6.10\packs\Microchip\PIC18Fxxxx_DFP\1.4.151\xc8\pic\include\proc\pic18f4620.h"
#include"../mcal_std_types.h"
#include"../device_config.h"
#include "hal_gpio_cfg.h"


/* Section : Includes */



/* Section : Macro Declarations */

#define BIT_MASK               ((uint8)1)
#define PORT_PIN_MAX_NUMBER    8
#define PORT_MAX_NUMBER        5
#define PORT_MASK              0XFF

#define _XTAL_FREQ             4000000




/* Section : Macro Functions Declarations */



#define HWREG8(_X)        (*((volatile uint8 *)(_X)))


#define SET_BIT(REG,BIT_POSN)         (REG |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)       (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)      (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG,BIT_POSN)        ((REG >> BIT_POSN) & BIT_MASK)




/* Section : Data Type Declarations */
typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef uint8 port_logic_t;


typedef enum {
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;


typedef uint8 port_direction_t;



        
        
typedef enum {
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,	
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;



typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}port_index_t;



typedef struct {
    uint8 port : 3 ;        /*@ref port_index_t */
    uint8 pin : 3 ;         /*@ref pin_index_t  */
    uint8 direction : 1 ;   /*@ref direction_t  */
    uint8 logic : 1 ;       /*@ref logic_t      */
}pin_config_t;


/* Section : Functions Declarations */
Std_ReturnType gpio_pin_direction_inializtion(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_c_pin_configonfig,direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic);
Std_ReturnType gpio_pin_raed_logic(const pin_config_t *_pin_config,logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_inialization(const pin_config_t *_pin_config);




Std_ReturnType gpio_port_direction_inializtion(port_index_t port,port_direction_t direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port,port_direction_t *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, port_logic_t logic);
Std_ReturnType gpio_port_raed_logic(port_index_t port, port_logic_t *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);








#endif	/* HAL_GPIO_H */

