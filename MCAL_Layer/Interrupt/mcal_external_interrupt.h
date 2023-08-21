/* 
 * File:   mcal_external_interrupt.h
 * Author: moham
 *
 * Created on June 12, 2023, 1:41 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H



/* Section : Includes */

#include"mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */
#if EXTERNAL_INTERRUPT_INTX_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#define EXT_INT0_InterruptEnable()        (INTCONbits.INT0IE=1)
#define EXT_INT0_InterruptDisable()       (INTCONbits.INT0IE=0)
#define EXT_INT0_InterruptFlagClear()     (INTCONbits.INT0IF=0)
#define EXT_INT0_RisingEdgeSet()         (INTCON2bits.INTEDG0=1)
#define EXT_INT0_FallingEdgeSet()        (INTCON2bits.INTEDG0=0)


#define EXT_INT1_InterruptEnable()        (INTCON3bits.INT1IE=1)
#define EXT_INT1_InterruptDisable()       (INTCON3bits.INT1IE=0)
#define EXT_INT1_InterruptFlagClear()     (INTCON3bits.INT1IF=0)
#define EXT_INT1_RisingEdgeSet()         (INTCON2bits.INTEDG1=1)
#define EXT_INT1_FallingEdgeSet()        (INTCON2bits.INTEDG1=0)



#define EXT_INT2_InterruptEnable()        (INTCON3bits.INT2IE=1)
#define EXT_INT2_InterruptDisable()       (INTCON3bits.INT2IE=0)
#define EXT_INT2_InterruptFlagClear()     (INTCON3bits.INT2IF=0)
#define EXT_INT2_RisingEdgeSet()         (INTCON2bits.INTEDG2=1)
#define EXT_INT2_FallingEdgeSet()        (INTCON2bits.INTEDG2=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

#define EXT_INT1_HighPrioritySet()        (INTCON3bits.INT1IP=1)
#define EXT_INT1_LowPrioritySet()         (INTCON3bits.INT1IP=0)

#define EXT_INT2_HighPrioritySet()        (INTCON3bits.INT2IP=1)
#define EXT_INT2_LowPrioritySet()         (INTCON3bits.INT2IP=0)

#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#define EXT_RBX_InterruptEnable()        (INTCONbits.RBIE=1)
#define EXT_RBX_InterruptDisable()       (INTCONbits.RBIE=0)
#define EXT_RBX_InterruptFlagClear()     (INTCONbits.RBIF=0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

#define EXT_RBX_HighPrioritySet()        (INTCON2bits.RBIP=1)
#define EXT_RBX_LowPrioritySet()         (INTCON2bits.RBIP=0)

#endif


#endif

/* Section : Data Type Declarations */



typedef enum
{
 INTERRUPT_FALLING_EDGE =0,
 INTERRUPT_RISING_EDGE         
}interrupt_INTX_edge;

typedef enum
{
 INTERRUPT_EXTERNAL_INT0 =0,
 INTERRUPT_EXTERNAL_INT1,
 INTERRUPT_EXTERNAL_INT2
}interrupt_INTX_src;


typedef struct 
{
  void (* EXT_InterruptHandeler)(void);
  pin_config_t mcu_pin;
  interrupt_INTX_edge edge;
  interrupt_INTX_src source;
  interrupt_priority_cfg priority;
}interrupt_INTX_t;


typedef struct 
{
  void (* EXT_InterruptHandeler_High)(void);    
  void (* EXT_InterruptHandeler_Low)(void); 
  pin_config_t mcu_pin;
  interrupt_priority_cfg priority;  
}interrupt_RBX_t;


/* Section : Functions Declarations */

Std_ReturnType Interrupt_INTX_Init (const interrupt_INTX_t *intr_obj);
Std_ReturnType Interrupt_INTX_DeInit (const interrupt_INTX_t *intr_obj);
Std_ReturnType Interrupt_RBX_Init (const interrupt_RBX_t *intr_obj);
Std_ReturnType Interrupt_RBX_DeInit (const interrupt_RBX_t *intr_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

