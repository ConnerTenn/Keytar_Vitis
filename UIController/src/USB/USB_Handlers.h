
#include "../../../Synth_system/Common.h"

void USB_CtrlRxHandler(void *callbackRef, u8 endpointNum, u8 eventType, void *data);
void USB_CtrlTxHandler(void *callbackRef, u8 endpointNum, u8 eventType, void *data);


void USB_SynthEventRxHandler(void *callbackRef, u8 endpointNum, u8 eventType, void *data);
void USB_SynthEventTxHandler(void *callbackRef, u8 endpointNum, u8 eventType, void *data);

