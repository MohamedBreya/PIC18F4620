/* 
 * File:   mcal_std_types.h
 * Author: moham
 *
 * Created on May 23, 2023, 11:00 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/* Section : Includes */

#include"std_libraries.h"
#include"compilar.h"


/* Section : Data Type Declarations */


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef uint8 Std_ReturnType;



/* Section : Macro Declarations */
#define STD_HIGH        0x01
#define STD_LOW         0x00


#define STD_ON          0x01
#define STD_OFF         0x00


#define STD_ACTIVE      0x01
#define STD_IDEL        0x00

#define CONFIG_ENABLE   0x01
#define CONFIG_DISABLE  0x00

#define E_OK            (Std_ReturnType)0x01
#define E_NOT_OK        (Std_ReturnType)0x00


#define ZERO_INIT       0



/* Section : Macro Functions Declarations */







/* Section : Functions Declarations */






#endif	/* MCAL_STD_TYPES_H */

