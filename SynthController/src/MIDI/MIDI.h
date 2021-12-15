
#ifndef _MIDI_H_
#define _MIDI_H_

#include "../../../Synth_system/Common.h"

void Midi_ProcessPacket(u8 *data, u32 dataLen);

void Midi_ChannelNoteOff(u8 channel, u8 key, u8 velocity);
void Midi_ChannelNoteOn(u8 channel, u8 key, u8 velocity);
void Midi_ChannelControllerChange(u8 channel, u8 controller, u8 value);
void Midi_ChannelProgramChange(u8 channel, u8 program);
void Midi_ChannelPitchBend(u8 channel, u8 lsb, u8 msb);

#endif
