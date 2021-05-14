
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

#include "xil_cache.h"
#include "xgpiops_hw.h"

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
    //Disable cache on DDR segment
    Xil_SetTlbAttributes(0x30000000, NORM_NONCACHE);


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

    // XGpioPs_WriteReg(XPAR_PS7_GPIO_0_BASEADDR, XGPIOPS_DIRM_OFFSET, 0);

    usleep(500*1000);
    
    PRINT("CPU0: Begin\n");

    for (u8 k=0; k<sizeof(KeyState); k++)
    {
        KeyState[k] = 0;
        KeyBankChannel[k][0] = (u8)-1;
        KeyBankChannel[k][1] = (u8)-1;
    }

    for (u8 b=0; b<MAX_BANKS; b++)
    {
        SYNTH_WAVETYPE_REG(b) = 1;
        SYNTH_PULSEWIDTH_REG(b) = 0;

        SYNTH_ATTACK_REG(b) = 1000;
        SYNTH_DECAY_REG(b) = 50;
        SYNTH_SUSTAIN_REG(b) = 0xFFFFFF;
        SYNTH_RELEASE_REG(b) = 50;

        SYNTH_LFOINCR_REG(b) = 100;
        SYNTH_LFOAMP_REG(b) = 0x000100u;
        SYNTH_LFORUN_REG(b) = 1;
        SYNTH_LFOWAVETYPE_REG(b) = 2;
        SYNTH_LFOSELECTION_STRUCT(b) = (LfoSelection){.Increment=1,.PulseWidth=0};
    }


    u8 clear = 0;

    u32 count = 0;
    while (1)
    {
        //Keyboard
        for (u8 i=0; i<8; i++)
        {
            KEYBOARD_DRIVE_REG = (1<<i);
            dsb(); //Wait for write to complete
            usleep(5);
            u8 keys = KEYBOARD_SENSE_REG;
            dsb(); //Wait for Read to complete

            // PRINT("0x%02X:0x%02X  ", KEYBOARD_DRIVE_REG, keys); dmb(); //Wait for Read to complete

            KEYBOARD_DRIVE_REG = 0;
            // dsb(); //Wait for write to complete
            

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
        }

        for (u8 b=0; b<MAX_BANKS; b++)
        {
            if (KeyState[0] == 1) { SYNTH_WAVETYPE_REG(b) = 0; }
            else if (KeyState[1] == 1) { SYNTH_WAVETYPE_REG(b) = 1; }
            else if (KeyState[2] == 1) { SYNTH_WAVETYPE_REG(b) = 2; }
            else if (KeyState[3] == 1) { SYNTH_WAVETYPE_REG(b) = 3; }
        }
        for (u8 k=4; k<sizeof(KeyState); k++)
        {
            if (KeyState[k] == 1) //KeyDown
            {
                u8 bank = 0;
                u8 channel = 0;
                u8 found = 0;

                while (bank<MAX_BANKS && channel<MAX_CHANNELS && !found)
                {
                    if (SYNTH_RUNNING_REG(bank,channel)==0)
                    {
                        found = 1;
                    }
                    else
                    {
                        channel++;
                        if (channel==MAX_CHANNELS)
                        {
                            bank++;
                            channel=0;
                        }
                    }
                }

                if (bank<MAX_BANKS && channel<MAX_CHANNELS)
                {
                    KeyBankChannel[k][0] = bank;
                    KeyBankChannel[k][1] = channel;

                    SYNTH_INCR_REG(bank,channel) = NoteIncrs[k + KeyOctaveOffset];
                    SYNTH_GATE_REG(bank,channel) = 1;

                    PRINT("CPU0: " TERM_MAGENTA "Gate ON   Bank:%d  Channel:%d  Incr:%d\n" TERM_RESET, bank, channel, NoteIncrs[k + KeyOctaveOffset]);
                    clear = 0;
                }
            }
            else if (KeyState[k] == 3) //KeyUP
            {
                u8 bank = KeyBankChannel[k][0];
                u8 channel = KeyBankChannel[k][1];
                if (bank!=(u8)-1 && channel!=(u8)-1)
                {
                    SYNTH_GATE_REG(bank,channel) = 0;
                    KeyBankChannel[k][0] = (u8)-1;
                    KeyBankChannel[k][1] = (u8)-1;

                    PRINT("CPU0: " TERM_MAGENTA "Gate OFF  Bank:%d  Channel:%d\n" TERM_RESET, bank, channel);
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

            for (u8 b=0; b<MAX_BANKS; b++)
            {
                for (u8 c=0; c<MAX_CHANNELS; c++)
                {
                    if (SYNTH_RUNNING_REG(b,c))
                    {
                        PRINT_NOLOCK("[%d,%2d]:" TERM_CYAN "%d:%d:%6d  " TERM_RESET, b, c, SYNTH_GATE_REG(b,c), SYNTH_ADSR_STATE_REG(b,c), SYNTH_INCR_REG(b,c));
                    }
                    else
                    {
                        PRINT_NOLOCK("[%d,%2d]:OFF         ", b, c);
                    }
                    if (c%8==7)
                    {
                        PRINT_NOLOCK("\n"); nl++;
                    }
                }
                PRINT_NOLOCK("\n"); nl++;
            }

            PRINT_NOLOCK("\n"); nl++;
            
            // u32 high = XGpioPs_ReadReg(XPAR_PS7_GPIO_0_BASEADDR, XGPIOPS_DATA_RO_OFFSET+3*XGPIOPS_DATA_BANK_OFFSET);
            // u32 low = XGpioPs_ReadReg(XPAR_PS7_GPIO_0_BASEADDR, XGPIOPS_DATA_RO_OFFSET+2*XGPIOPS_DATA_BANK_OFFSET);
            // PRINT_NOLOCK("GPIO: AWReady:%d ARReady:%d Val1:%d Val2:%d      \n", 
            //     high>>16, high&0xFFFF, 
            //     low>>16, low&0xFFFF
            //     ); nl++;

            // static u32 val1 = 0, val2 = 400;
            // Out32(0x30000000, val1);
            // Out32(0x30000008, val2);
            // // Xil_DCacheFlushRange(0x30000000, 0x10);
            // // Xil_DCacheInvalidateRange(0x30000010, 0x08);
            // // Xil_DCacheInvalidateRange(0x30000000, 0x28);
            // PRINT_NOLOCK("%d + %d = %d\n", val1, val2, (u32)In32(0x30000010)); nl++;
            // for (u8 i = 0; i < 10; i++) { PRINT_NOLOCK("0x%08X ", (u32)In32(0x30000000+i*4)); } PRINT_NOLOCK("        \n"); nl++;
            // val1++; val2++;
            
            PRINT_NOLOCK("\n"); nl++;
            PRINT_NOLOCK("\n"); nl++;
            
            clear = 1;
            
            PRINT_RELEASELOCK;
        }

        count=count<200?count+1:0;
    }


    return XST_SUCCESS;
}


