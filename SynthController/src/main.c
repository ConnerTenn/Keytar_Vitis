
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

#include "../../Synth_system/Common.h"

#include "xpseudo_asm.h"
#include "xil_mmu.h"

// #include "xil_exception.h"
// #include "xscugic.h"

#include "sleep.h"

#include "Synth.h"



#define sev() __asm__("sev")
#define CPU1STARTADDRREG 0xfffffff0
#define CPU1IMAGEADR 0x02000000

int InitCPU1()
{
    print("CPU0: writing startaddress for CPU1\n\r");
    Xil_Out32(CPU1STARTADDRREG, CPU1IMAGEADR);
    dmb(); //Wait for write to complete

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

int Init()
{
    //Disable cache on OCM
    Xil_SetTlbAttributes(SHARED_ADDR, 0x14de2); //S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0

    if (InitUart(XPAR_XUARTPS_0_DEVICE_ID) != XST_SUCCESS)
    {
        PRINT("CPU0: Failed to initialize UART\n");
        return XST_FAILURE;
    }

    if (InitCPU1() != XST_SUCCESS)
    {
        PRINT("CPU0: Filed to initialize CPU 1\n");
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}

int main()
{
    if (Init() != XST_SUCCESS)
    {
        PRINT("CPU0: Init Failed\n");
        return XST_FAILURE;
    }

    usleep(2000*1000);
    



    uint32_t count = 0;
    while (1)
    {
        if (count % 4 == 0)
        {
            SYNTH_INCR_REG(0) = count*100+1500;//(((u32)rand())%2000)+1000;
            SYNTH_ATTACK_REG(0) = 50;
            SYNTH_WAVETYPE_REG(0) = 0;//1;
            SYNTH_DECAY_REG(0) = 50;
            SYNTH_SUSTAIN_REG(0) = 0x00FFFFFF;
            SYNTH_RELEASE_REG(0) = 50;
            SYNTH_GATE_REG(0) = 1;
        }
        else if (count % 4 == 2)
        {
            SYNTH_GATE_REG(0) = 0;
        }

        // PRINT("CPU0: %lu\n", count++);
        PRINT("CPU0: Synth Incr:%d  ADSRState:%d  Envolope:0x%08X\n", SYNTH_INCR_REG(0), SYNTH_ADSR_STATE_REG(0), SYNTH_ENVELOPE_REG(0));
        
        usleep(100*1000); //100ms
        count = count<4*20 ? count+1 : 0;
    }

    return XST_SUCCESS;
}


