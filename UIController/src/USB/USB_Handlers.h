
#include "../../../Synth_system/Common.h"

void USB_CtrlRxHandler(void *callbackRef, u8 endpointNum, u8 eventType, void *data);
void USB_CtrlTxHandler(void *callbackRef, u8 endpointNum, u8 eventType, void *data);


void USB_SynthEventIsoRxHandler(void *callbackRef, u32 requestedBytes, u32 bytesTXed);
void USB_SynthEventIsoTxHandler(void *callbackRef, u32 requestedBytes, u32 bytesTXed);

