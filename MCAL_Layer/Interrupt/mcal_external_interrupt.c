#include"mcal_external_interrupt.h"




static InterruptHandeler INT0_Interrupt_Handeler = NULL;
static InterruptHandeler INT1_Interrupt_Handeler = NULL;
static InterruptHandeler INT2_Interrupt_Handeler = NULL;


/*=============================================================================*/

static InterruptHandeler RB4_Interrupt_Handeler_High = NULL;
static InterruptHandeler RB4_Interrupt_Handeler_Low = NULL;

static InterruptHandeler RB5_Interrupt_Handeler_High = NULL;
static InterruptHandeler RB5_Interrupt_Handeler_Low = NULL;

static InterruptHandeler RB6_Interrupt_Handeler_High = NULL;
static InterruptHandeler RB6_Interrupt_Handeler_Low = NULL;
 
static InterruptHandeler RB7_Interrupt_Handeler_High = NULL;
static InterruptHandeler RB7_Interrupt_Handeler_Low = NULL;


/*=============================================================================*/



static Std_ReturnType Interrupt_INTX_Enable(const interrupt_INTX_t *intr_obj);
static Std_ReturnType Interrupt_INTX_Disable(const interrupt_INTX_t *intr_obj);
static Std_ReturnType Interrupt_INTX_Priority_Init(const interrupt_INTX_t *intr_obj);
static Std_ReturnType Interrupt_INTX_Edge_Init(const interrupt_INTX_t *intr_obj);
static Std_ReturnType Interrupt_INTX_Pin_Init(const interrupt_INTX_t *intr_obj);
static Std_ReturnType Interrupt_INTX_Clear_Flag(const interrupt_INTX_t *intr_obj);


static Std_ReturnType INT0_Set_Interrupt_Handeler(void (*InterruptHandeler)(void));
static Std_ReturnType INT1_Set_Interrupt_Handeler(void (*InterruptHandeler)(void));
static Std_ReturnType INT2_Set_Interrupt_Handeler(void (*InterruptHandeler)(void));
static Std_ReturnType INTX_Set_Interrupt_Handeler(const interrupt_INTX_t *intr_obj);




static Std_ReturnType Interrupt_RBX_Enable(const interrupt_RBX_t *intr_obj);
static Std_ReturnType Interrupt_RBX_Disable(const interrupt_RBX_t *intr_obj);
static Std_ReturnType Interrupt_RBX_Priority_Init(const interrupt_RBX_t *intr_obj);
static Std_ReturnType Interrupt_RBX_Pin_Init(const interrupt_RBX_t *intr_obj);


/**
 * 
 * @param intr_obj
 * @return 
 */
Std_ReturnType Interrupt_INTX_Init (const interrupt_INTX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
       ret &= Interrupt_INTX_Disable(intr_obj);
       ret &= Interrupt_INTX_Clear_Flag(intr_obj);
       ret &= Interrupt_INTX_Edge_Init(intr_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE       
       ret &= Interrupt_INTX_Priority_Init(intr_obj);
#endif
       ret &= Interrupt_INTX_Pin_Init(intr_obj);
       ret &= INTX_Set_Interrupt_Handeler(intr_obj);
       ret &= Interrupt_INTX_Enable(intr_obj);
    }
    
    return ret;
}

/**
 * 
 * @param intr_obj
 * @return 
 */
Std_ReturnType Interrupt_INTX_DeInit (const interrupt_INTX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;    
}


/**
 * 
 * @param intr_obj
 * @return 
 */
Std_ReturnType Interrupt_RBX_Init (const interrupt_RBX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXT_RBX_InterruptDisable();
        
        EXT_RBX_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        
        INTERRUPT_Priority_LevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == intr_obj->priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            
            EXT_RBX_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == intr_obj->priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            
            EXT_RBX_LowPrioritySet(); 
        }
        else
        {
            ret = E_NOT_OK;
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        
#endif
        
        ret &= gpio_pin_direction_inializtion(&(intr_obj->mcu_pin));
        
        
        switch(intr_obj->mcu_pin.pin)
        {
            case GPIO_PIN4 :
                RB4_Interrupt_Handeler_High = intr_obj->EXT_InterruptHandeler_High;
                RB4_Interrupt_Handeler_Low = intr_obj->EXT_InterruptHandeler_Low;
                break;
            case GPIO_PIN5 :
                RB5_Interrupt_Handeler_High = intr_obj->EXT_InterruptHandeler_High;
                RB5_Interrupt_Handeler_Low = intr_obj->EXT_InterruptHandeler_Low;
                break;
            case GPIO_PIN6 :
                RB6_Interrupt_Handeler_High = intr_obj->EXT_InterruptHandeler_High;
                RB6_Interrupt_Handeler_Low = intr_obj->EXT_InterruptHandeler_Low;
                break;
            case GPIO_PIN7 :
                RB7_Interrupt_Handeler_High = intr_obj->EXT_InterruptHandeler_High;
                RB7_Interrupt_Handeler_Low = intr_obj->EXT_InterruptHandeler_Low;
                break;
            default:
                ret = E_NOT_OK;
                
        }
        
        EXT_RBX_InterruptEnable();
        
    }
    
    return ret;    
}


/**
 * 
 * @param intr_obj
 * @return 
 */
Std_ReturnType Interrupt_RBX_DeInit (const interrupt_RBX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;    
}



/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Enable(const interrupt_INTX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(intr_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 :
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                EXT_INT2_InterruptEnable();
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    
    return ret;    
}


/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Disable(const interrupt_INTX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(intr_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 :
                EXT_INT0_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                EXT_INT1_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                EXT_INT2_InterruptDisable();
                break;
            default:
                ret = E_NOT_OK;
        }        
    }
    
    return ret;    
}

/**
 * 
 * @param intr_obj
 * @return 
 */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTX_Priority_Init(const interrupt_INTX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)  
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(intr_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT1 :
                
                if(INTERRUPT_LOW_PRIORITY == intr_obj->priority)
                {
                    EXT_INT1_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == intr_obj->priority)
                {
                    EXT_INT1_HighPrioritySet();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
                
            case INTERRUPT_EXTERNAL_INT2 :
                
                if(INTERRUPT_LOW_PRIORITY == intr_obj->priority)
                {
                    EXT_INT2_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == intr_obj->priority)
                {
                    EXT_INT2_HighPrioritySet();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
                
            default:
                ret = E_NOT_OK;
        }        
    }
    
    return ret;    
}
#endif



/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Edge_Init(const interrupt_INTX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
    
        switch(intr_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 :

                if(INTERRUPT_RISING_EDGE == intr_obj->edge)
                {
                    EXT_INT0_RisingEdgeSet();
                }
                else if(INTERRUPT_FALLING_EDGE == intr_obj->edge)
                {
                    EXT_INT0_FallingEdgeSet();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;            
            case INTERRUPT_EXTERNAL_INT1 :


                if(INTERRUPT_RISING_EDGE == intr_obj->edge)
                {
                    EXT_INT1_RisingEdgeSet();
                }
                else if(INTERRUPT_FALLING_EDGE == intr_obj->edge)
                {
                    EXT_INT1_FallingEdgeSet();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;

            case INTERRUPT_EXTERNAL_INT2 :

                if(INTERRUPT_RISING_EDGE == intr_obj->edge)
                {
                    EXT_INT2_RisingEdgeSet();
                }
                else if(INTERRUPT_FALLING_EDGE == intr_obj->edge)
                {
                    EXT_INT2_FallingEdgeSet();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;

            default:
                ret = E_NOT_OK;
        }
    }
    
    return ret;     
     
}



/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Clear_Flag(const interrupt_INTX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(intr_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 :
                EXT_INT0_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                EXT_INT1_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                EXT_INT2_InterruptFlagClear();
                break;
            default:
                ret = E_NOT_OK;
        }        
    }
    
    return ret;     
}


/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Pin_Init(const interrupt_INTX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= gpio_pin_direction_inializtion(&(intr_obj->mcu_pin));
    }
    
    return ret;    
}


/**
 * 
 * @param InterruptHandeler
 * @return 
 */
static Std_ReturnType INT0_Set_Interrupt_Handeler(void (*InterruptHandeler)(void))
{
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandeler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_Interrupt_Handeler = InterruptHandeler;
    }
    
    return ret;       
}

/**
 * 
 * @param InterruptHandeler
 * @return 
 */
static Std_ReturnType INT1_Set_Interrupt_Handeler(void (*InterruptHandeler)(void))
{
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandeler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_Interrupt_Handeler = InterruptHandeler;
    }
    
    return ret;     
}

/**
 * 
 * @param InterruptHandeler
 * @return 
 */
static Std_ReturnType INT2_Set_Interrupt_Handeler(void (*InterruptHandeler)(void))
{
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandeler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_Interrupt_Handeler = InterruptHandeler;
    }
    
    return ret;     
}


/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType INTX_Set_Interrupt_Handeler(const interrupt_INTX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(intr_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 :
                INT0_Set_Interrupt_Handeler(intr_obj->EXT_InterruptHandeler);
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                INT1_Set_Interrupt_Handeler(intr_obj->EXT_InterruptHandeler);                
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                INT2_Set_Interrupt_Handeler(intr_obj->EXT_InterruptHandeler);                
                break;
            default:
                ret = E_NOT_OK;
        }        
    }
    
    return ret;     
}




/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBX_Enable(const interrupt_RBX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;    
}


/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBX_Disable(const interrupt_RBX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;     
}


/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBX_Priority_Init(const interrupt_RBX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;     
}


/**
 * 
 * @param intr_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBX_Pin_Init(const interrupt_RBX_t *intr_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == intr_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;    
}




/*============================== INT1_ISR ==============================*/
void INT0_ISR(void)
{
    EXT_INT0_InterruptFlagClear();
    
    
    if(INT0_Interrupt_Handeler)
    {
        INT0_Interrupt_Handeler();
    }
    else
    {
        /*Nothing*/
    }
}
/*======================================================================*/

/*============================== INT1_ISR ==============================*/
void INT1_ISR(void)
{
    EXT_INT1_InterruptFlagClear();
    
    
    if(INT1_Interrupt_Handeler)
    {
        INT1_Interrupt_Handeler();
    }
    else
    {
        /*Nothing*/
    }
}
/*======================================================================*/

/*============================== INT2_ISR ==============================*/
void INT2_ISR(void)
{
    EXT_INT2_InterruptFlagClear();
    
    
    if(INT2_Interrupt_Handeler)
    {
        INT2_Interrupt_Handeler();
    }
    else
    {
        /*Nothing*/
    }
}
/*=====================================================================*/

/*============================== RB4_ISR ==============================*/
void RB4_ISR(uint8 RB4_Source)
{
    EXT_RBX_InterruptFlagClear();
    
    if(STD_HIGH == RB4_Source)
    {
        
        if(RB4_Interrupt_Handeler_High)
        {
            RB4_Interrupt_Handeler_High();
        }
        else
        {
            /*Nothing*/
        } 
        
    }
    else if(STD_LOW == RB4_Source)
    {
        
        if(RB4_Interrupt_Handeler_Low)
        {
            RB4_Interrupt_Handeler_Low();
        }
        else
        {
            /*Nothing*/
        } 
        
    }
    else
    {
        /*Nothing*/
    }
  
}
/*=====================================================================*/

/*============================== RB5_ISR ==============================*/
void RB5_ISR(uint8 RB5_Source)
{
    EXT_RBX_InterruptFlagClear();
    
    if(STD_HIGH == RB5_Source)
    {
        
        if(RB5_Interrupt_Handeler_High)
        {
            RB5_Interrupt_Handeler_High();
        }
        else
        {
            /*Nothing*/
        } 
        
    }
    else if(STD_LOW == RB5_Source)
    {
        
        if(RB5_Interrupt_Handeler_Low)
        {
            RB5_Interrupt_Handeler_Low();
        }
        else
        {
            /*Nothing*/
        } 
        
    }
    else
    {
        /*Nothing*/
    }
  
}
/*=====================================================================*/

/*============================== RB6_ISR ==============================*/
void RB6_ISR(uint8 RB6_Source)
{
    EXT_RBX_InterruptFlagClear();
    
    if(STD_HIGH == RB6_Source)
    {
        
        if(RB6_Interrupt_Handeler_High)
        {
            RB6_Interrupt_Handeler_High();
        }
        else
        {
            /*Nothing*/
        } 
        
    }
    else if(STD_LOW == RB6_Source)
    {
        
        if(RB6_Interrupt_Handeler_Low)
        {
            RB6_Interrupt_Handeler_Low();
        }
        else
        {
            /*Nothing*/
        } 
        
    }
    else
    {
        /*Nothing*/
    }
  
}
/*=====================================================================*/

/*============================== RB7_ISR ==============================*/
void RB7_ISR(uint8 RB7_Source)
{
    EXT_RBX_InterruptFlagClear();
    
    if(STD_HIGH == RB7_Source)
    {
        
        if(RB7_Interrupt_Handeler_High)
        {
            RB7_Interrupt_Handeler_High();
        }
        else
        {
            /*Nothing*/
        } 
        
    }
    else if(STD_LOW == RB7_Source)
    {
        
        if(RB7_Interrupt_Handeler_Low)
        {
            RB7_Interrupt_Handeler_Low();
        }
        else
        {
            /*Nothing*/
        } 
        
    }
    else
    {
        /*Nothing*/
    }
  
}
/*=====================================================================*/