

#include "common.h"

#include "xiicps.h"


void Init()
{
    XIicPs_Config *Config = XIicPs_LookupConfig(XPAR_PS7_I2C_0_DEVICE_ID);
    if (Config == NULL) { return XST_FAILURE; }

    XIicPs I2CPS;
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
}


