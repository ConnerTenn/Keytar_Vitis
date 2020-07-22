
#include "sil9022.h"

#include "xiicps.h"

XIicPs I2CPS;
int InitI2C()
{
    PRINT("CPU1: Init I2C\n");
    XIicPs_Config *Config = XIicPs_LookupConfig(XPAR_PS7_I2C_0_DEVICE_ID);
    if (Config == NULL) { return XST_FAILURE; }

    if (XIicPs_CfgInitialize(&I2CPS, Config, Config->BaseAddress) != XST_SUCCESS)
    {
        PRINT("CPU1: Failed to Set I2C Baud Rate\n");
        return XST_FAILURE;
    }

    //100 KHz
    if (XIicPs_SetSClk(&I2CPS, 100000) != XST_SUCCESS)
    {
        PRINT("CPU1: Failed to Set I2C Baud Rate\n");
        return XST_FAILURE;
    }

    if (XIicPs_SetOptions(&I2CPS, XIICPS_7_BIT_ADDR_OPTION) != XST_SUCCESS)
    {
        PRINT("CPU1: Failed to Set I2C Baud Rate\n");
        return XST_FAILURE;
    }

    PRINT("CPU1: I2C Clk Frequency %d[Hz]\n", XIicPs_GetSClk(&I2CPS));

    return XST_SUCCESS;
}

//https://www.kernel.org/doc/html/latest/i2c/smbus-protocol.html
void Sil9022WriteByte(u8 command, u8 val)
{
    u8 msg[2] = {command, val};
    XIicPs_MasterSendPolled(&I2CPS, msg, 2, SIL9022_I2C_ADDR);
}

u8 Sil9022ReadByte(u8 command)
{
    XIicPs_MasterSendPolled(&I2CPS, &command, 1, SIL9022_I2C_ADDR);

    u8 data;
    XIicPs_MasterRecvPolled(&I2CPS, &data, 1, SIL9022_I2C_ADDR);
    return data;
}

int Sil9022Init()
{
    InitI2C();


    Sil9022WriteByte(0xC7, 0x00);

    u8 id = Sil9022ReadByte(0x1B);
    if (id == 0xb0) 
    {
        PRINT("CPU1: Sil9022 ID: 0x%02X-0x%02X-0x%02X-0x%02X\n", 
            id, 
            Sil9022ReadByte(0x1C),
            Sil9022ReadByte(0x1D),
            Sil9022ReadByte(0x30));
    }
    else { PRINT("CPU1: Error: Sil9022 ID not recognized: 0x%02X\n", id); }

    //Power up
    Sil9022WriteByte(0x1E, 0x00);

    // {
    //     u16 data[4];

    //     data[0] = PICOS2KHZ(6667/*pixclock*/) / 10;
	//     data[2] = 44/*hsync_len*/ + 148/*left_margin*/ + 1920/*xres*/ + 88/*right_margin*/;
	//     data[3] = 5/*vsync_len*/ + 36/*upper_margin*/ + 1080/*yres*/ + 4/*lower_margin*/;
	//     u32 refresh = data[2] * data[3];
    //     refresh = (PICOS2KHZ(6667/*pixclock*/) * 1000) / refresh;
    //     data[1] = refresh * 100;
	//     for (u32 i = 0; i < 4*2; i++)
    //     {
	// 	    Sil9022WriteByte(i, ((u8 *)data)+i);
    //     }
    // }
    

    //input bus/pixel: full pixel wide (24bit), rising edge
	Sil9022WriteByte(0x08, 0x70);
	//Set input format to RGB
	Sil9022WriteByte(0x09, 0x00);
	//set output format to RGB
	Sil9022WriteByte(0x0A, 0x00);

    //Power on
    Sil9022WriteByte(0x1A, 0x01);
    
    return XST_SUCCESS;
}

