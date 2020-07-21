
#include "sil9022.h"

#include "xiicps.h"

XIicPs I2CPS;
int InitI2C()
{
    XIicPs_Config *Config = XIicPs_LookupConfig(XPAR_PS7_I2C_0_DEVICE_ID);
    if (Config == NULL) { return XST_FAILURE; }

    if (XIicPs_CfgInitialize(&I2CPS, Config, Config->BaseAddress) != XST_SUCCESS)
    {
        PRINT("CPU1: Failed to Set I2C Baud Rate\n");
        return XST_FAILURE;
    }

    //1 MHz
    if (XIicPs_SetSClk(&I2CPS, 1000000) != XST_SUCCESS)
    {
        PRINT("CPU1: Failed to Set I2C Baud Rate\n");
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}

void Sil9022WriteByte(u8 command, u8 val)
{
    u8 msg[2] = {command, val};
    XIicPs_MasterSend(&I2CPS, msg, 2, SIL9022_I2C_ADDR);
}

u8 Sil9022ReadByte(u8 command)
{
    XIicPs_MasterSend(&I2CPS, &command, 1, SIL9022_I2C_ADDR);

    u8 data;
    XIicPs_MasterRecv(&I2CPS, &data, 1, SIL9022_I2C_ADDR);
    return data;
}

int Sil9022Init()
{
    InitI2C();


    Sil9022WriteByte(0xC7, 0x00);

    //Power up
    Sil9022WriteByte(0x1E, 0x00);

    //set TPI video mode
	// data[0] = PICOS2KHZ(fbi->var.pixclock) / 10;
	// data[2] = fbi->var.hsync_len + fbi->var.left_margin +
	// 	  fbi->var.xres + fbi->var.right_margin;
	// data[3] = fbi->var.vsync_len + fbi->var.upper_margin +
	// 	  fbi->var.yres + fbi->var.lower_margin;
	// refresh = data[2] * data[3];
	// refresh = (PICOS2KHZ(fbi->var.pixclock) * 1000) / refresh;
	// data[1] = refresh * 100;
	// tmp = (u8 *)data;
	// for (i = 0; i < 8; i++)
	// 	i2c_smbus_write_byte_data(sii902x.client, i, tmp[i]);
    u8 id = Sil9022ReadByte(0x1B);
    if (id == 0xb0) 
    {
        PRINT("CPU1: Sil9022 ID: 0x%02X-0x%02X-0x%02X-0x%02X", 
            id, 
            Sil9022ReadByte(0x1C),
            Sil9022ReadByte(0x1D),
            Sil9022ReadByte(0x30));
    }
    else { PRINT("CPU1: Error: Sil9022 ID not recognized: 0x%02X", id); }
    

    //input bus/pixel: full pixel wide (24bit), rising edge
	Sil9022WriteByte(0x08, 0x70);
	//Set input format to RGB
	Sil9022WriteByte(0x09, 0x00);
	//set output format to RGB
	Sil9022WriteByte(0x0A, 0x00);


    Sil9022WriteByte(0x1A, 0x01);
    
    return XST_SUCCESS;
}

