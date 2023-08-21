/* 
 * File:   hal_ccp1.h
 * Author: moham
 *
 * Created on June 26, 2023, 8:18 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* Section : Includes */

#include"hal_ccp1_cfg.h"
#include"../GPIO/hal_gpio.h"
#include"../Interrupt/mcal_intenal_interrupt.h"

/* Section : Macro Declarations */

#define CCP1_MODULE_DISABLE                 0x00
#define CCP1_CAPTURE_MODE_1_FALLING_EDGE    0x04
#define CCP1_CAPTURE_MODE_1_RISING_EDGE     0x05
#define CCP1_CAPTURE_MODE_4_RISING_EDGE     0x06
#define CCP1_CAPTURE_MODE_16_RISING_EDGE    0x07
#define CCP1_COMPARE_MODE_SET_PIN_LOW       0x08
#define CCP1_COMPARE_MODE_SET_PIN_HIGH      0x09
#define CCP1_COMPARE_MODE_TOGGLE_ON_MATCH   0x02
#define CCP1_COMPARE_MODE_GEN_SW_INTERRUPT  0x0A
#define CCP1_COMPARE_MODE_GEN_EVENT         0x0B
#define CCP1_PWM_MODE                       0x0c


#define CCP1_CAPTURE_NOT_READY 0x00
#define CCP1_CAPTURE_READY     0x01

#define CCP1_COMPARE_NOT_READY 0x00
#define CCP1_COMPARE_READY     0x01


/* Section : Macro Functions Declarations */

#define CCP1_SET_MODE(_CONFIG)  (CCP1CONbits.CCP1M = _CONFIG)

/* Section : Data Type Declarations */

typedef enum
{
    CCP1_CAPTURE_MODE_SELECTED = 0,
    CCP1_COMPARE_MODE_SELECTED,
    CCP1_PWM_MODE_SELECTED        
}ccp1_mode_t;

typedef struct
{
    ccp1_mode_t ccp1_mode;
    
}ccp1_t;


/* Section : Functions Declarations */


#endif	/* HAL_CCP1_H */

