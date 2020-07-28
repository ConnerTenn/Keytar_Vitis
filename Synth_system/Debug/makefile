#
# This file was created by Xilinx Vitis tool.
#


#
# tools
#

RM = rm -f
RMDIR = rm -rf



#
# variables
#

SDCARD_GEN = sdcard_gen
GENERATE_BIF = ::scw::generate_bif

XPFM_PATH = Z:/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/ZTurnPlatform.xpfm
SYS_CONFIG = ZTurnPlatform
DOMAINS = core0,core1
BIF_PATH = Z:/Projects/Keytar/VitisWorkspace/Synth_system/Debug/system.bif

BITSTREAM_PATH = Z:/Projects/Keytar/VitisWorkspace/SynthController/_ide/bitstream/system_wrapper.bit
SD_FILES = --elf Z:/Projects/Keytar/VitisWorkspace/SynthController/Debug/SynthController.elf,ps7_cortexa9_0 --elf Z:/Projects/Keytar/VitisWorkspace/UIController/Debug/UIController.elf,ps7_cortexa9_1

#
# primary build targets
#

all: package

package:
	-@echo Generating bif file for the system project
	generate_system_bif.bat 58221 ${XPFM_PATH} ${DOMAINS} ${BIF_PATH}
	${SDCARD_GEN} --xpfm ${XPFM_PATH} --sys_config ${SYS_CONFIG} --bif ${BIF_PATH} --bitstream ${BITSTREAM_PATH} ${SD_FILES}

clean:
	$(RMDIR) ./_sds
	${RMDIR} package
	${RM} system.bif

.PHONY: all package clean


