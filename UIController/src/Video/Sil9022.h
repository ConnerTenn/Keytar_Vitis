
#include "../../../Synth_system/Common.h"


#define SIL9022_I2C_ADDR 0x3B

#define PICOS2KHZ(a) (1000000000UL/(a))
#define KHZ2PICOS(a) (1000000000UL/(a))


#define TPI_AUDIO_HANDING_REG   0x25
#define TPI_AUDIO_INTF_REG      0x26
#define TPI_AUDIO_FREQ_REG      0x27
#define TPI_SET_PAGE_REG        0xBC
#define TPI_SET_OFFSET_REG      0xBD
#define TPI_RW_ACCESS_REG       0xBE
#define TPI_TRANS_MODE_REG      0xC7

#define TPI_INBUS_CLOCK_RATIO_1         (1 << 6)
#define TPI_INBUS_FULL_PIXEL_WIDE       (1 << 5)
#define TPI_INBUS_RISING_EDGE           (1 << 4)
#define TPI_INPUT_CLR_DEPTH_8BIT        (0 << 6)
#define TPI_INPUT_VRANGE_EXPAN_AUTO     (0 << 2)
#define TPI_INPUT_CLR_RGB               (0 << 0)
#define TPI_OUTPUT_CLR_DEPTH_8BIT       (0 << 6)
#define TPI_OUTPUT_VRANGE_COMPRE_AUTO   (0 << 2)
#define TPI_OUTPUT_CLR_HDMI_RGB         (0 << 0)
#define TPI_SYS_TMDS_OUTPUT             (0 << 4)
#define TPI_SYS_AV_NORAML               (0 << 3)
#define TPI_SYS_AV_MUTE                 (1 << 3)
#define TPI_SYS_DVI_MODE                (0 << 0)
#define TPI_SYS_HDMI_MODE               (1 << 0)
#define TPI_PWR_STAT_MASK               (3 << 0)
#define TPI_PWR_STAT_D0                 (0 << 0)
#define TPI_AUDIO_PASS_BASIC            (0 << 0)
#define TPI_AUDIO_INTF_I2S              (2 << 6)
#define TPI_AUDIO_INTF_NORMAL           (0 << 4)
#define TPI_AUDIO_INTF_MUTE             (0 << 4)
#define TPI_AUDIO_TYPE_PCM              (1 << 0)
#define TPI_AUDIO_SAMP_SIZE_16BIT       (1 << 6)
#define TPI_AUDIO_SAMP_FREQ_44K         (2 << 3)
#define TPI_AUDIO_SAMP_FREQ_96K         (5 << 3)
#define TPI_SET_PAGE_SII9022A           0x01
#define TPI_SET_OFFSET_SII9022A         0x82
#define TPI_RW_EN_SRC_TERMIN            (1 << 0)
#define TPI_TRANS_MODE_ENABLE           (0 << 7)


int Sil9022Init();


