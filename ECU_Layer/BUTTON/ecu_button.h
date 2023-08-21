/* 
 * File:   ecu_button.h
 * Author: moham
 *
 * Created on May 29, 2023, 9:15 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H


/* Section : Includes */
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"ecu_button_cfg.h"


/* Section : Macro Declarations */



/* Section : Macro Functions Declarations */



/* Section : Data Type Declarations */

typedef enum {
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;


typedef enum {
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct {
    uint8 port_name : 3;
    uint8 pin : 3;
    uint8 button_state : 1;
    uint8 button_connection : 1;
}button_t;



/* Section : Functions Declarations */

Std_ReturnType button_initialize (const button_t *btn);
Std_ReturnType button_read_state (const button_t *btn,button_state_t *btn_state);




#endif	/* ECU_BUTTON_H */

