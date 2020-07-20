
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

#include "../../Synth_system/common.h"

#include "xpseudo_asm.h"
#include "xil_mmu.h"

// #include "xil_exception.h"
// #include "xscugic.h"

#include "sleep.h"

#include "xuartps.h"
#include "xil_printf.h"

#include "synth.h"


#define UART_DEVICE_ID  XPAR_XUARTPS_0_DEVICE_ID

#define sev() __asm__("sev")
#define CPU1STARTADR 0xfffffff0
#define CPU1IMAGEADR 0x02000000

int InitCPU1()
{
    print("CPU0: writing startaddress for CPU1\n\r");
    Xil_Out32(CPU1STARTADR, CPU1IMAGEADR);
    dmb();

    print("CPU0: sending the SEV to wake up CPU1\n\r");
    sev();

    return XST_SUCCESS;
}

int InitUart(u16 DeviceId)
{
    int status;

    Out32(PRINT_MUTEX_ADDR, 0);

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
        PRINT("Uartps hello world Example Failed\n");
        return XST_FAILURE;
    }


    //Disable cache on OCM
    Xil_SetTlbAttributes(0xFFFF0000,0x14de2);           // S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0

    
    status = InitCPU1();
    if (status != XST_SUCCESS)
    {
        PRINT("Filed to initialize CPU 1\n");
        return XST_FAILURE;
    }

    usleep(1000);


    uint32_t count = 0;
    while (1)
    {
        PRINT("CPU0: %lu\n", count++);
        
        usleep(500*1000); //500ms
    }

    return 0;
}


