
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
#include "xuartps.h"
#include "xil_printf.h"


#define UART_DEVICE_ID  XPAR_XUARTPS_0_DEVICE_ID

int InitUart(u16 DeviceId)
{
    int status;

    //Initialize the UART driver so that it's ready to use
    //Look up the configuration in the config table and then initialize it.
    XUartPs_Config *Config = XUartPs_LookupConfig(DeviceId);
    if (Config == NULL) { return XST_FAILURE; }

    XUartPs Uart_Ps; //The instance of the UART Driver
    status = XUartPs_CfgInitialize(&Uart_Ps, Config, Config->BaseAddress);
    if (status != XST_SUCCESS) { return XST_FAILURE; }

    XUartPs_SetBaudRate(&Uart_Ps, 115200);
    if (status != XST_SUCCESS) { return XST_FAILURE; }

    return XST_SUCCESS;
}


int main()
{
    int status;
    status = InitUart(UART_DEVICE_ID);

    if (status != XST_SUCCESS)
    {
        xil_printf("Uartps hello world Example Failed\r\n");
        return XST_FAILURE;
    }


    uint32_t count = 0;
    while (1)
    {
        xil_printf("Hello World Core2! %lu\n", count++);
    }

    return 0;
}


