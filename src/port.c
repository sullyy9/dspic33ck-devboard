/*----------------------------------------------------------------------------*/
/*
 *  Ryan Sullivan
 *
 *  Module Name     : port.c
 *  Description     : pin functions
 */
/*----------------------------------------------------------------------------*/

#include "types.h"

#include "port.h"

/*----------------------------------------------------------------------------*/
/*-constant-definitions-------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-exported-variables---------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-static-variables-----------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*-forward-declarations-------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

void    set_pin_output(uint16_t port_pin);
void    set_pin_input(uint16_t port_pin);

/*----------------------------------------------------------------------------*/
/*-exported-functions---------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*
 * @brief           initialise a pin to the specified mode
 * @param port_pin: port and pin to be initialised. refer to port.h for
 *                  possible arguments
 * @param mode:     mode pin is to be initialised to. refer to port.h
 *                  for possible arguments
 * @retval          none
 */
void port_initialise_pin(uint16_t port_pin, uint16_t mode)
{
    switch( mode )
    {
        case PORT_MODE_ANALOG:
        {
            break;
        }

        case PORT_MODE_FLOATING:
        {
            set_pin_input(port_pin);
            break;
        }

        case PORT_MODE_OPEN_DRAIN:
        {

            break;
        }

        case PORT_MODE_PUSH_PULL:
        {
            set_pin_output(port_pin);
            break;
        }

        case PORT_MODE_ALT_OPEN_DRAIN:
        {

            break;
        }

        case PORT_MODE_ALT_OUTPUT:
        {

            break;
        }

        default:
        {

            break;
        }
    }
}

/*----------------------------------------------------------------------------*/

/*
 * @brief set a pin
 * 
 * @param port_pin  port and pin to set
 */
void port_set(uint16_t port_pin)
{
    *(PORT_MASK(port_pin) + LAT) = *(PORT_MASK(port_pin) + LAT) | (1 << PIN_MASK(port_pin));
}

/*----------------------------------------------------------------------------*/

/*
 * @brief clear a pin
 * 
 * @param port_pin  port and pin to read
 */
void port_clear(uint16_t port_pin)
{
    *(PORT_MASK(port_pin) + LAT) = *(PORT_MASK(port_pin) + LAT) & ~(1 << PIN_MASK(port_pin));
}

/*----------------------------------------------------------------------------*/

/*
 * @brief read a pin
 * 
 * @param port_pin  port and pin to read from
 * @return uint8_t  1 if pin is high, 0 if low
 */
uint8_t port_read(uint16_t port_pin)
{
    return(0);
}

/*----------------------------------------------------------------------------*/
/*-static-functions-----------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

void set_pin_output(uint16_t port_pin)
{
    *(PORT_MASK(port_pin) + TRIS) = *(PORT_MASK(port_pin) + TRIS) & ~(1 << PIN_MASK(port_pin));
}

/*----------------------------------------------------------------------------*/

void set_pin_input(uint16_t port_pin)
{
    *(PORT_MASK(port_pin) + TRIS) = *(PORT_MASK(port_pin) + TRIS) | (1 << PIN_MASK(port_pin));
}

/*----------------------------------------------------------------------------*/
/*-end-of-module--------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
