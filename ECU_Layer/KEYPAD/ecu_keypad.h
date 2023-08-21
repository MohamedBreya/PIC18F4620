/* 
 * File:   ecu_keypad.h
 * Author: moham
 *
 * Created on May 30, 2023, 5:47 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H




/* Section : Includes */
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"ecu_keypad_cfg.h"


/* Section : Macro Declarations */

#define ECU_KEYPAD_ROWS      4
#define ECU_KEYPAD_COLUMNS      4


/* Section : Macro Functions Declarations */



/* Section : Data Type Declarations */

typedef struct {
   pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS]; 
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS]; 

}keypad_t;



/* Section : Functions Declarations */


Std_ReturnType keypad_initialize (const keypad_t *_keypad_opj);
Std_ReturnType keypad_get_value (const keypad_t *_keypad_opj, uint8 *value);






#endif	/* ECU_KEYPAD_H */

