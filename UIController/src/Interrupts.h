
#include "../../Synth_system/Common.h"

#include "xscugic.h"

void InitializeInterrupt();
void InterruptAttach(u32 interruptID, Xil_InterruptHandler handler, void *callbackRef);


