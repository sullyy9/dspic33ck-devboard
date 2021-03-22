/*----------------------------------------------------------------------------*/
/*
 *  Ryan Sullivan
 *
 *  Module Name     : port.h
 *  Description     : header file
 */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-constant-definitions-------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

enum
{
    PORT_A0,
    PORT_A1,
    PORT_A2,
    PORT_A3,
    PORT_A4,

    PORT_A5,    // Not implemented on this device
    PORT_A6,    // Not implemented on this device
    PORT_A7,    // Not implemented on this device
    PORT_A8,    // Not implemented on this device
    PORT_A9,    // Not implemented on this device
    PORT_A10,   // Not implemented on this device
    PORT_A11,   // Not implemented on this device
    PORT_A12,   // Not implemented on this device
    PORT_A13,   // Not implemented on this device
    PORT_A14,   // Not implemented on this device
    PORT_A15,   // Not implemented on this device

    PORT_B0,
    PORT_B1,
    PORT_B2,
    PORT_B3,
    PORT_B4,
    PORT_B5,
    PORT_B6,
    PORT_B7,
    PORT_B8,
    PORT_B9,
    PORT_B10,
    PORT_B11,
    PORT_B12,
    PORT_B13,
    PORT_B14,
    PORT_B15,

    PORT_C0,
    PORT_C1,
    PORT_C2,
    PORT_C3,
    PORT_C4,
    PORT_C5,
    PORT_C6,
    PORT_C7,
    PORT_C8,
    PORT_C9,
    PORT_C10,
    PORT_C11,
    PORT_C12,
    PORT_C13,
    PORT_C14,
    PORT_C15,

    PORT_D0,
    PORT_D1,
    PORT_D2,
    PORT_D3,
    PORT_D4,
    PORT_D5,
    PORT_D6,
    PORT_D7,
    PORT_D8,
    PORT_D9,
    PORT_D10,
    PORT_D11,
    PORT_D12,
    PORT_D13,
    PORT_D14,
    PORT_D15,

    PORT_E0,
    PORT_E1,
    PORT_E2,
    PORT_E3,
    PORT_E4,
    PORT_E5,
    PORT_E6,
    PORT_E7,
    PORT_E8,
    PORT_E9,
    PORT_E10,
    PORT_E11,
    PORT_E12,
    PORT_E13,
    PORT_E14,
    PORT_E15

};

enum PIN_MODES
{
    PORT_MODE_PUSH_PULL,
    PORT_MODE_FLOATING,
    PORT_MODE_ALT_OUTPUT,
    PORT_MODE_ANALOG,
    PORT_MODE_ALT_OPEN_DRAIN,
    PORT_MODE_OPEN_DRAIN
};

#define GPIOA_BASE  &ANSELA
#define GPIOB_BASE  &ANSELB
#define GPIO_DIFF   (GPIOB_BASE - GPIOA_BASE)
enum PORT_REGISTER_OFFSETS
{
    ANSEL,
    TRIS,
    PORT,
    LAT,
    ODC,
    CNPU,
    CNPD,
    CNCON,
    CNEN0,
    CNSTSAT,
    CNEN1,
    CNF
};

#define PORT_MASK(port_pin) (GPIOA_BASE + ((port_pin / 16) * GPIO_DIFF))
#define PIN_MASK(port_pin)  (port_pin % 16)

/*----------------------------------------------------------------------------*/
/*-exported-variables---------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-exported-functions---------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

void    port_initialise_pin(uint16_t port_pin, uint16_t mode);

void    port_set(uint16_t port_pin);
void    port_clear(uint16_t port_pin);

/*----------------------------------------------------------------------------*/
/*-end-of-module--------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
