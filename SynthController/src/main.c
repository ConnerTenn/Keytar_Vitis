
/**
* Hello World program using XUartPs driver in polled mode
*
* The example uses the default setting in the XUartPs driver:
*	. baud rate 9600
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

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define UART_DEVICE_ID                  XPAR_XUARTPS_0_DEVICE_ID


int UartPsHelloWorldExample(u16 DeviceId);



int main(void)
{
	int Status;

	/*
	 * Run the Hello World example , specify the the Device ID that is
	 * generated in xparameters.h
	 */
	Status = UartPsHelloWorldExample(UART_DEVICE_ID);

	if (Status == XST_FAILURE) {
		xil_printf("Uartps hello world Example Failed\r\n");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran Uartps hello world Example\r\n");

	while (1)
	{
		xil_printf("Hello World!!!\n");
	}

	return Status;
}


XUartPs Uart_Ps;		/* The instance of the UART Driver */
int UartPsHelloWorldExample(u16 DeviceId)
{
	u8 HelloWorld[] = "Hello World";
	int SentCount = 0;
	int Status;
	XUartPs_Config *Config;

	/*
	 * Initialize the UART driver so that it's ready to use
	 * Look up the configuration in the config table and then initialize it.
	 */
	Config = XUartPs_LookupConfig(DeviceId);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XUartPs_CfgInitialize(&Uart_Ps, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XUartPs_SetBaudRate(&Uart_Ps, 115200);

	while (SentCount < (sizeof(HelloWorld) - 1)) {
		/* Transmit the data */
		SentCount += XUartPs_Send(&Uart_Ps,
					   &HelloWorld[SentCount], 1);
	}

	return SentCount;
}
