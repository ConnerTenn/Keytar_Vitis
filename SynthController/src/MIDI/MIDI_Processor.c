
#include "MIDI.h"

void *StateAddr = 0;
void *RunAddr = 0;

u8 RunStatus = 0;

u8 ParamStack[32];
u8 ParamStackFill = 0;


void Midi_ProcessByte(u8 byte)
{
    if ((byte & 0x80) != 0)
    {
        //Status byte received

        //Reset state
        ParamStackFill = 0;
        StateAddr = 0;
    }
    else
    {
        //Push value onto stack
        ParamStack[ParamStackFill++] = byte;

        //== Jump to State ==
        if (StateAddr)
        {
            goto *StateAddr;
        }

        //== Run Message ==
        if (RunAddr)
        {
            goto *RunAddr;
        }
    }



    //== Channel Voice Messages ==
    //Note Off
    if ((byte & 0xF0) == 0x80)
    {
        RunStatus = byte;
        StateAddr = &&controllerNoteOff1;
        RunAddr = &&controllerNoteOff1;
        return;
controllerNoteOff1:
        if (byte <= 0x7F)
        {
            StateAddr = &&controllerNoteOff2;
            return;
controllerNoteOff2:
            if (byte <= 0x7F)
            {
                Midi_ChannelNoteOff(RunStatus&0x0F, ParamStack[0], ParamStack[1]);
                StateAddr = 0; //Reset
                return;
            }
            //Error State (Ignored)
            return;
        }
        //Error State (Ignored)
        return;
    }
    //Note On
    else if ((byte & 0xF0) == 0x90)
    {
        RunStatus = byte;
        StateAddr = &&ControllerNoteOn1;
        RunAddr = &&ControllerNoteOn1;
        return;
ControllerNoteOn1:
        if (byte <= 0x7F)
        {
            StateAddr = &&ControllerNoteOn2;
ControllerNoteOn2:
            if (byte <= 0x7F)
            {
                Midi_ChannelNoteOn(RunStatus&0x0F, ParamStack[0], ParamStack[1]);
                return;
            }
            //Error State (Ignored)
            return;
        }
        //Error State (Ignored)
        return;
    }
    //Controller Change
    else if ((byte & 0xF0) == 0xB0)
    {
        RunStatus = byte;
        StateAddr = &&ControllerChange1;
        RunAddr = &&ControllerChange1;
        return;
ControllerChange1:
        if (byte <= 0x7F)
        {
            StateAddr = &&ControllerChange2;
            return;
ControllerChange2:
            if (byte <= 0x7F)
            {
                Midi_ChannelControllerChange(RunStatus&0x0F, ParamStack[0], ParamStack[1]);
                return;
            }
            //Error State (Ignored)
            return;
        }
        //Error State (Ignored)
        return;
    }
    //Program Change
    else if ((byte & 0xF0) == 0xC0)
    {
        RunStatus = byte;
        StateAddr = &&ProgramChange1;
        RunAddr = &&ProgramChange1;
        return;
ProgramChange1:
        if (byte <= 0x7F)
        {
            Midi_ChannelProgramChange(RunStatus&0x0F, ParamStack[0]);
            return;
        }
        //Error State (Ignored)
        return;
    }
    //Pitch Bend
    else if ((byte & 0xF0) == 0xE0)
    {
        RunStatus = byte;
        StateAddr = &&PitchBend1;
        RunAddr = &&PitchBend1;
        return;
PitchBend1:
        if (byte <= 0x7F)
        {
            StateAddr = &&PitchBend2;
            return;
PitchBend2:
            if (byte <= 0x7F)
            {
                Midi_ChannelPitchBend(RunStatus&0x0F, ParamStack[0], ParamStack[1]);
                return;
            }
            //Error State (Ignored)
            return;
        }
        //Error State (Ignored)
        return;
    }
}

void Midi_ProcessPacket(u8 *data, u32 dataLen)
{
    while (dataLen--)
    {
        Midi_ProcessByte(*(data++));
    }
}

