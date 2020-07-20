
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


#include "common.h"

#include "xil_mmu.h"

#include "sleep.h"

#include "xuartps.h"
#include "xil_printf.h"

#define UART_DEVICE_ID  XPAR_XUARTPS_0_DEVICE_ID



int main()
{
    uint32_t *buzzer = (uint32_t *)0x40000000;

    //Disable cache on OCM
    Xil_SetTlbAttributes(0xFFFF0000,0x14de2);           // S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0

    PRINT("CPU1: Start!\n");


    uint32_t count = 0;
    while (1)
    {
        xil_printf("CPU1: %lu\n", count++);
        *buzzer = count*2;
        usleep(500*1000); //500ms

    }

    return 0;
}


