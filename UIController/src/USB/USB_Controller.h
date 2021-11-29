
#ifndef _USB_CONTROLLER_H_
#define _USB_CONTROLLER_H_

#include "../../../Synth_system/Common.h"
#include "xusbps_ch9.h"



typedef struct 
{
    USB_STD_CFG_DESC  stdCfg;
    USB_STD_IF_DESC   ifCfg;
    USB_STD_EP_DESC   epCfg1;
    USB_STD_EP_DESC   epCfg2;
} __attribute__((__packed__))USB_CONFIG;



void InitUSB();

#endif
