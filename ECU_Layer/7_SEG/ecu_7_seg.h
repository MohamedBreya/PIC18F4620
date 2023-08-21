/* 
 * File:   ecu_7_seg.h
 * Author: moham
 *
 * Created on May 30, 2023, 10:48 AM
 */

#ifndef ECU_7_SEG_H
#define	ECU_7_SEG_H



/* Section : Includes */
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
#include"ecu_7_seg_cfg.h"


/* Section : Macro Declarations */

#define SEGGMENT_PIN0   0
#define SEGGMENT_PIN1   1
#define SEGGMENT_PIN2   2
#define SEGGMENT_PIN3   3


/* Section : Macro Functions Declarations */



/* Section : Data Type Declarations */

typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;


//typedef struct {
//    uint8 seven_seg_port_name : 3 ;
//    uint8 seven_seg_pin : 3 ;
//    uint8 reserved : 2;
//}seven_seg_pin_cfg;


typedef struct {
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;
/* Section : Functions Declarations */


Std_ReturnType seven_segment_initialize (const segment_t *segment);
Std_ReturnType seven_segment_write_number (const segment_t *segment, uint8 number);



#endif	/* ECU_7_SEG_H */

