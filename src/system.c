/*----------------------------------------------------------------------------*/
/*
 *  Ryan Sullivan
 *
 *  Module Name     : system.c
 *  Description     : system functions
 */
/*----------------------------------------------------------------------------*/

#include "types.h"

#include "system.h"

/*----------------------------------------------------------------------------*/
/*-constant-definitions-------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

#define PRIMARY_OSCILLATOR_HZ      8000000
#define PLL_MULTIPLIER             32
#define PLL_OUT_HZ                 (PRIMARY_OSCILLATOR_HZ * PLL_MULTIPLIER)

#define SYSTEM_CLOCK_HZ            (PLL_OUT_HZ / 2)            //Fosc
#define PERIPHERAL_CLOCK_HZ        (SYSTEM_CLOCK_HZ / 2)       //Fp
#define CPU_CLOCK_HZ               (SYSTEM_CLOCK_HZ / 2)       //Fcy

/*
 * @brief:  memory configuration bits
 * @FSEC
 */
#pragma config AIVTDIS = OFF, CSS = DISABLED, CWRP = OFF, GSS = DISABLED, GWRP = OFF, BSEN = OFF, BSS = DISABLED, BWRP = OFF


/*
 * @brief:  Clock configuration bits
 * @FOSC
 * @FOSCSEL
 */
#pragma config XTBST = DISABLE, XTCFG = G0, PLLKEN = OFF, FCKSM = CSECME, OSCIOFNC = ON, POSCMD = XT
#pragma config IESO = ON, FNOSC = PRI

/*
 * @brief:  Watchdog configuration bits
 * @FWDT
 */
#pragma config FWDTEN = ON_SW, SWDTPS = PS1, WDTWIN = WIN75, WINDIS = OFF, RCLKSEL = LPRC, RWDTPS = PS1

#pragma config BISTDIS = DISABLED

/*
 * @brief:  Debug configuration bits
 * @FICD JTAG
 */
#pragma config NOBTSWP = DISABLED, JTAGEN = ON, ICS = PGD3

#pragma config DMTDIS = OFF

/*
 * @brief:  comms configuration bits 
 * @FDEVOPT
 */
#pragma config SPI2PIN = DEDICATED, SMBEN = STANDARD, ALTI2C3 = OFF, ALTI2C2 = OFF, ALTI2C1 = OFF

/*
 * @brief:  alt register configuration bits 
 * @FALTREG
 */
#pragma config CTXT4 = OFF, CTXT3 = OFF, CTXT2 = OFF, CTXT1 = OFF

/*
 * @brief:  boot configuration bits 
 * @FBTSEQ
 * @FBOOT
 */
#pragma config IBSEQ = IBSEQ, BSEQ = BSEQ 
#pragma config BTMODE = SINGLE

/*----------------------------------------------------------------------------*/
/*-exported-variables---------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-static-variables-----------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-forward-declarations-------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-exported-functions---------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*
 * @brief:      Setup clocks
 * @param:      None
 * @retval:     None
 */
void system_initialise(void)
{
    /* Relevent registers:
    * OSCCON:       OSCILLATOR CONTROL REGISTER
    * CLKDIV:       CLOCK DIVIDER REGISTER
    * PLLFBD:       PLL FEEDBACK DIVIDER REGISTER
    * OSCTUN:       FRC OSCILLATOR TUNING REGISTER
    * PLLDIV:       PLL OUTPUT DIVIDER REGISTER
    * ACLKCON1:     AUXILIARY CLOCK CONTROL REGISTER
    * APLLFBD1:     APLL FEEDBACK DIVIDER REGISTER
    * APLLDIV1:     APLL OUTPUT DIVIDER REGISTER
    * CANCLKCON:    CAN CLOCK CONTROL REGISTER
    * REFOCONL:     REFERENCE CLOCK CONTROL LOW REGISTER
    * REFOCONH:     REFERENCE CLOCK CONTROL HIGH REGISTER
    * REFOTRIMH:    REFERENCE OSCILLATOR TRIM REGISTER
    */

    /*
    * Configure PLL to output 256Mhz.
    * Configure the ratio between Fp and the periphreal clocks to be 1:1
    * Switch clock source to the primary oscillator with PLL.
    * Fout = Fin * (PLLFBDIV / (PLLPRE * POST1DIV * POST2DIV))
    */
    CLKDIVbits.PLLPRE = 1;
    PLLFBDbits.PLLFBDIV = 64;
    PLLDIVbits.POST1DIV = 2;
    PLLDIVbits.POST2DIV = 1;

    CLKDIVbits.DOZEN = 0;
    CLKDIVbits.DOZE = 0;

    __builtin_write_OSCCONH(0b011);
    __builtin_write_OSCCONL(OSCCON | 1);
    while(OSCCONbits.OSWEN == 1);
    while(OSCCONbits.LOCK == 0);
}

/*----------------------------------------------------------------------------*/
/*-static-functions-----------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-end-of-module--------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
