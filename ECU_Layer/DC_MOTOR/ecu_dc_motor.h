/* 
 * File:   ecu_dc_motor.h
 * Author: moham
 *
 * Created on May 30, 2023, 2:01 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H


/* Section : Includes */
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"ecu_dc_motor_cfg.h"


/* Section : Macro Declarations */
//#define DC_MOTOR_ON_STATUS    0X01U
//#define DC_MOTOR_OFF_STATUS   0X00U


/* Section : Macro Functions Declarations */



/* Section : Data Type Declarations */

typedef enum {
    motor_OFF = 0,
    motor_ON
}motor_status_t;

typedef struct {
    uint8 dc_motor_port_name :4;
    uint8 dc_motor_pin : 3;
    uint8 dc_motor_status : 1;
}dc_motor_pin_t;

typedef struct{
   dc_motor_pin_t dc_motor[2]; 
}dc_motor_t;

/* Section : Functions Declarations */


Std_ReturnType dc_motor_initialize   (const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right   (const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left    (const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop         (const dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

