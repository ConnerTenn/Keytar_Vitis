
#include "MIDI.h"


u8 RunStatus = 0;

u8 ParamStack[2];
u8 ParamStackFill = 0;


void Midi_ProcessByte(u8 byte)
{
    if ((byte & 0x80) != 0)
    {
        //Status byte received
        RunStatus = byte;

        //Reset state
        ParamStackFill = 0;
    }
    else if (ParamStackFill<sizeof(ParamStack))
    {
        //Push value onto stack
        ParamStack[ParamStackFill++] = byte;
    }



    //== Channel Voice Messages ==
    switch (RunStatus & 0xF0)
    {
    //Note Off
    case 0x80:
        if (ParamStackFill==2)
        {
            Midi_ChannelNoteOff(RunStatus&0x0F, ParamStack[0], ParamStack[1]);
            RunStatus = 0; //Reset
        }
        break;

    //Note On
    case 0x90:
        if (ParamStackFill==2)
        {
            Midi_ChannelNoteOn(RunStatus&0x0F, ParamStack[0], ParamStack[1]);
            RunStatus = 0; //Reset
        }
        break;

    //Controller Change
    case 0xB0:
        if (ParamStackFill==2)
        {
            Midi_ChannelControllerChange(RunStatus&0x0F, ParamStack[0], ParamStack[1]);
            RunStatus = 0; //Reset
        }
        break;

    //Program Change
    case 0xC0:
        if (ParamStackFill==1)
        {
            Midi_ChannelProgramChange(RunStatus&0x0F, ParamStack[0]);
            RunStatus = 0; //Reset
        }
        break;

    //Pitch Bend
    case 0xE0:
        if (ParamStackFill==2)
        {
            Midi_ChannelPitchBend(RunStatus&0x0F, ParamStack[0], ParamStack[1]);
            RunStatus = 0; //Reset
        }
        break;
    }
}

void Midi_ProcessPacket(u8 *data, u32 dataLen)
{
    while (dataLen--)
    {
        Midi_ProcessByte(*(data++));
    }
}

