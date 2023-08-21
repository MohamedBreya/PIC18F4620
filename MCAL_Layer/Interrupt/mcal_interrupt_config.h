/* 
 * File:   mcal_interrupt_config.h
 * Author: moham
 *
 * Created on June 12, 2023, 1:44 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section : Includes */
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"mcal_interrupt_gen_cfg.h"

/* Section : Macro Declarations */

#define INTERRUPT_ENABLE             1
#define INTERRUPT_DISABLE            0
#define INTERRUPT_OCCUR              1
#define INTERRUPT_NOT_OCCUR          0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0

/* Section : Macro Functions Declarations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_Priority_LevelsEnable()        (RCONbits.IPEN=1)
#define INTERRUPT_PriorityLevelsDisable()        (RCONbits.IPEN=0)
#define INTERRUPT_GlobalInterruptHighEnable()    (INTCONbits.GIEH=1)
#define INTERRUPT_GlobalInterruptHighDisable()   (INTCONbits.GIEH=0)
#define INTERRUPT_GlobalInterruptLowEnable()     (INTCONbits.GIEL=1)
#define INTERRUPT_GlobalInterruptLowDisable()    (INTCONbits.GIEL=0)

#else
#define INTERRUPT_GlobalInterruptEnable()    (INTCONbits.GIE=1)
#define INTERRUPT_GlobalInterruptDisable()   (INTCONbits.GIE=0)
#define INTERRUPT_PeripheralInterruptEnable()    (INTCONbits.PEIE=1)
#define INTERRUPT_PeripheralInterruptDisable()   (INTCONbits.PEIE=0)

#endif

/* Section : Data Type Declarations */
typedef enum
{
 INTERRUPT_LOW_PRIORITY=0,
 INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;

typedef void (*InterruptHandeler)(void);


/* Section : Functions Declarations */

//Std_ReturnType button_initialize (const button_t *btn);

#endif	/* MCAL_INTERRUPT_CONFIG_H */

