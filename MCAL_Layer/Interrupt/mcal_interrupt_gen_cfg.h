/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: moham
 *
 * Created on June 14, 2023, 6:09 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_FEATURE_ENABLE  1U
#define INTERRUPT_FEATURE_DISABLE 0U

//#define INTERRUPT_PRIORITY_LEVELS_ENABLE             INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_INTX_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE   INTERRUPT_FEATURE_ENABLE

//ADC
#define ADC_INTERRUPT_FEATURE INTERRUPT_FEATURE_ENABLE

//TIMER0
#define TIMER0_INTERRUPT_FEATURE INTERRUPT_FEATURE_ENABLE

//TIMER1
#define TIMER1_INTERRUPT_FEATURE INTERRUPT_FEATURE_ENABLE

//TIMER2
#define TIMER2_INTERRUPT_FEATURE INTERRUPT_FEATURE_ENABLE

//TIMER3
#define TIMER3_INTERRUPT_FEATURE INTERRUPT_FEATURE_ENABLE

//EUSART ---> TX
#define EUSART_TX_INTERRUPT_FEATURE INTERRUPT_FEATURE_ENABLE
//EUSART ---> RX
#define EUSART_RX_INTERRUPT_FEATURE INTERRUPT_FEATURE_ENABLE


//MSSP -----> I2C
#define MSSP_I2C_INTERRUPT_FEATURE INTERRUPT_FEATURE_ENABLE

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

