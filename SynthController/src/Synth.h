

#define SYNTH_ADDR (0x40000000)
#define SYNTH_ACCESS_RAW() (*(uint32_t *)(SYNTH_ADDR))
#define SYNTH_ACCESS(reg) (*(uint32_t *)(SYNTH_ADDR + 4*(reg)))

#define CHANNEL_OFFSET (0x00000000)

