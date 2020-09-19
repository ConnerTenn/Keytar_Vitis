
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

    usleep(500*1000);
    
    PRINT("CPU0: Begin\n");

    for (u8 k=0; k<sizeof(KeyState); k++)
    {
        KeyState[k] = 0;
        KeyChannel[k] = (u8)-1;
    }


    u8 clear = 0;

    u32 count = 0;
    while (1)
    {
        //Keyboard
        for (u8 i=0; i<8; i++)
        {
            KEYBOARD_DRIVE_REG = (1<<i);
            dmb(); //Wait for write to complete
            usleep(100);
            u8 keys = KEYBOARD_SENSE_REG;
            dmb(); //Wait for Read to complete

            // PRINT("0x%02X:0x%02X  ", KEYBOARD_DRIVE_REG, keys); dmb(); //Wait for Read to complete

            KEYBOARD_DRIVE_REG = 0;
            dmb(); //Wait for write to complete
            
            for (u8 k=0; k<8 && i*8+k<sizeof(KeyState); k++)
            {
                u8 *state = &KeyState[i*8+k];
                u8 pressed = (keys>>k)&1;
                switch (*state)
                {
                case 0: //Unpressed
                    *state = pressed ? 1 : 0;
                    break;
                case 1: //KeyDown
                case 2: //KeyPressed
                    *state = pressed ? 2 : 3;
                    break;
                case 3: //KeyUp
                    *state = pressed ? 1 : 0;
                    break;
                default: //Unknown
                    *state = pressed ? 1 : 3;
                    break;
                }
            }
            usleep(1);
        }

        for (u8 k=0; k<sizeof(KeyState); k++)
        {
            if (KeyState[k] == 1) //KeyDown
            {
                u8 channel = 0;

                while (channel<MAX_CHANNELS && SYNTH_RUNNING_REG(channel)==1)
                {
                    channel++;
                }

                if (channel < MAX_CHANNELS)
                {
                    KeyChannel[k] = channel;

                    SYNTH_INCR_REG(channel) = NoteIncrs[k + KeyOctaveOffset];
                    SYNTH_ATTACK_REG(channel) = 300;
                    SYNTH_WAVETYPE_REG(channel) = 1;
                    SYNTH_DECAY_REG(channel) = 50;
                    SYNTH_SUSTAIN_REG(channel) = 0xAFFFFFFF;
                    SYNTH_RELEASE_REG(channel) = 50;
                    SYNTH_GATE_REG(channel) = 1;

                    PRINT("CPU0: " TERM_MAGENTA "Gate ON   Channel:%d  Incr:%d\n" TERM_RESET, channel, NoteIncrs[k + KeyOctaveOffset]);
                    clear = 0;
                }
            }
            else if (KeyState[k] == 3) //KeyUP
            {
                u8 channel = KeyChannel[k];
                if (channel!=(u8)-1)
                {
                    SYNTH_GATE_REG(channel) = 0;
                    KeyChannel[k] = (u8)-1;

                    PRINT("CPU0: " TERM_MAGENTA "Gate OFF  Channel:%d\n" TERM_RESET, channel);
                    clear = 0;
                }
            }
        }


        if (count == 0)
        {
            PRINT_GETLOCK;

            static u8 nl = 0;
            if (clear) { TERM_MOVE_UP(nl); }
            nl = 0;

            PRINT_NOLOCK("\n"); nl++;
            for (u8 k=0; k<sizeof(KeyState); k++)
            {
                PRINT_NOLOCK("C \0C#\0D \0D#\0E \0F \0F#\0G \0G#\0A \0A#\0B \0"+3*(k%12));
            }
            PRINT_NOLOCK("\n"); nl++;
            for (u8 k=0; k<sizeof(KeyState); k++)
            {
                PRINT_NOLOCK("%s%d ", KeyState[k]?TERM_CYAN:TERM_RESET, KeyState[k]);
            }
            PRINT_NOLOCK(TERM_RESET "\n"); nl++;

            for (u8 c=0; c<MAX_CHANNELS; c++)
            {
                if (SYNTH_RUNNING_REG(c))
                {
                    PRINT_NOLOCK("[%2d]:" TERM_CYAN "%d:%d:%6d  " TERM_RESET, c, SYNTH_GATE_REG(c), SYNTH_ADSR_STATE_REG(c), SYNTH_INCR_REG(c));
                }
                else
                {
                    PRINT_NOLOCK("[%2d]:OFF         ", c);
                }
                if (c%8==7)
                {
                    PRINT_NOLOCK("\n"); nl++;
                }
            }
            PRINT_NOLOCK("\n"); nl++;
            PRINT_NOLOCK("\n"); nl++;
            
            clear = 1;
            
            PRINT_RELEASELOCK;
        }

        count=count<200?count+1:0;
    }


    return XST_SUCCESS;
}


