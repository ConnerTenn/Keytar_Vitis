
#ifndef _USB_CONTROLLER_H_
#define _USB_CONTROLLER_H_

#include "../../../Synth_system/Common.h"
#include "xusbps_ch9.h"



typedef struct 
{
	USB_STD_CFG_DESC  stdCfg;
	USB_STD_IF_DESC   ifCfg;
} __attribute__((__packed__))USB_CONFIG;



void InitUSB();

#endif
