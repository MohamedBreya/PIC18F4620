#include"hal_eeprom.h"




/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_WriteByte (uint16 bAdd, uint8 bData)
{
    Std_ReturnType ret = E_OK;
    uint8 Global_Interrupt_Status = INTCONbits.GIE;

    
    EEADRH = (uint8)((bAdd >> 8)& 0x03);
    EEADR = (uint8)(bAdd & 0xFF);
    
    
    EEDATA = bData;
    
    
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    
    
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    
    
    
    INTERRUPT_GlobalInterruptDisable();  
    
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    while(EECON1bits.WR);
    
    
    EECON1bits.WREN = INHIBIT_WRITE_CYCLES_FLASH_EEPROM;
    
    
    
    INTCONbits.GIE = Global_Interrupt_Status;
    
    
    
    return ret;     
}



/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_ReadByte (uint16 bAdd, uint8 *bData)
{
    Std_ReturnType ret = E_OK;
    if(NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EEADRH = (uint8)((bAdd >> 8)& 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        
        
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS = 0;
        
        EECON1bits.RD = 1;
        
        NOP();
        NOP();
                
        *bData = EEDATA;
     
    }
    
    return ret;     
}
