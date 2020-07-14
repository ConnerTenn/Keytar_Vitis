
/**
* Hello World program using XUartPs driver in polled mode
*
* The example uses the default setting in the XUartPs driver:
*	. baud rate 115200
*	. 8 bit data
*	. 1 stop bit
*	. no parity
*
* @note
* This example requires an external SchmartModule connected to the pins for
* the device to display the 'Hello World' message onto a hyper-terminal.
*
*/


#include "xparameters.h"

#include "xil_mmu.h"

#include "sleep.h"

#include "xuartps.h"
#include "xil_printf.h"

#define UART_DEVICE_ID  XPAR_XUARTPS_0_DEVICE_ID



int main()
{
    uint8_t *lock = (uint8_t *)0xFFFF0000;

    //Disable cache on OCM
    Xil_SetTlbAttributes(0xFFFF0000,0x14de2);           // S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0

    xil_printf("Core 2 Start!\n");


    uint32_t count = 0;
    while (1)
    {
        while(*lock == 0) {}
        xil_printf("Hello World Core2! %lu\n", count++);
        *lock = 0;
        usleep(500*1000); //500ms

    }

    return 0;
}


