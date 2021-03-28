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

#define FAST_RC_HZ                 8000000
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
void system_clocks_initialise(void)
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
    * Configure the ratio between Fp and the peripheral clocks to be 1:1
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

/*
 * @brief:  configure timer 1 as a counter
 * 
 * @param:  time interval at which the timer interupt will trigger
 */
void system_timer_initialise(uint16_t time_ms)
{
    /*
     * Set clock to Fp
     * Calculate prescaler
     * Calculate period
     * Enable the timer
     */
    T1CONbits.TCS = 0;      //use peripheral clock (Fp)

    uint16_t prescale_count = 0;
    uint16_t prescale_value[4] = {1, 8, 64, 256};
    while((((prescale_value[prescale_count] * 65535 * 1000) / PERIPHERAL_CLOCK_HZ) < time_ms) && (prescale_count < 3))
    {
        prescale_count++;
    }
    T1CONbits.TCKPS = prescale_count;   //set the prescale level(1:1, 1:8, 1:64, 1:256)

    uint16_t period = 1;
    while((((period * prescale_value[prescale_count] * 1000) / PERIPHERAL_CLOCK_HZ ) < time_ms) && (period < 65535))
    {
        period++;
    }
    PR1 = period;

    T1CONbits.TON = 1;      //enable timer 1

    /*
     * Configure the timer 1 interupt.
     */
    IPC0bits.T1IP = 4;      //Set priority to middleish
    IFS0bits.T1IF = 0;      //clear interupt flag
    IEC0bits.T1IE = 1;      //enable the interupt
}

/*----------------------------------------------------------------------------*/
/*-static-functions-----------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-end-of-module--------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
