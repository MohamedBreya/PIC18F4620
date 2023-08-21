/* 
 * File:   ecu_relay.h
 * Author: moham
 *
 * Created on May 29, 2023, 11:36 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section : Includes */
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"ecu_relay_cfg.h"


/* Section : Macro Declarations */
//#define RELAY_ON_STATUS    0X01U
//#define RELAY_OFF_STATUS   0X00U


/* Section : Macro Functions Declarations */



/* Section : Data Type Declarations */

typedef enum {
    RELAY_OFF = 0,
    RELAY_ON
}relay_status_t;

typedef struct {
    uint8 port_name :4;
    uint8 pin : 3;
    uint8 relay_status : 1;
}relay_t;


/* Section : Functions Declarations */


Std_ReturnType relay_initialize (const relay_t *relay);
Std_ReturnType relay_turn_on (const relay_t *relay);
Std_ReturnType relay_turn_off (const relay_t *relay);
Std_ReturnType relay_turn_toggle (const relay_t *relay);

#endif	/* ECU_RELAY_H */

