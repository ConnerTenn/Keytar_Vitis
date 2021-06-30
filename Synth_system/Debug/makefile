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

XPFM_PATH = /NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/ZTurnPlatform.xpfm
SYS_CONFIG = ZTurnPlatform
DOMAINS = standalone_domain,ps7_cortexa9_1
BIF_PATH = /NetDrive/Personal/Projects/Keytar/VitisWorkspace/Synth_system/Debug/system.bif

BITSTREAM_PATH = /NetDrive/Personal/Projects/Keytar/VitisWorkspace/SynthController/_ide/bitstream/system_wrapper.bit
SD_FILES = --elf /NetDrive/Personal/Projects/Keytar/VitisWorkspace/SynthController/Debug/SynthController.elf,ps7_cortexa9_0 --elf /NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/Debug/UIController.elf,ps7_cortexa9_1

GENERATE_BIF_XSCT_CMD = ${GENERATE_BIF} -xpfm ${XPFM_PATH} -domains ${DOMAINS} -bifpath ${BIF_PATH}

#
# primary build targets
#

all: package

package:
	-@echo Generating bif file for the system project
	-@echo Executing command \'${GENERATE_BIF_XSCT_CMD}\' on XSCT
	-@echo "connect -u TCP:localhost:33121; tcf send_command $$::xsdb::curchan xsdb eval s es [list \"${GENERATE_BIF_XSCT_CMD}\"]" | xsct
	${SDCARD_GEN} --xpfm ${XPFM_PATH} --sys_config ${SYS_CONFIG} --bif ${BIF_PATH} --bitstream ${BITSTREAM_PATH} ${SD_FILES}

clean:
	$(RMDIR) ./_sds
	${RMDIR} package
	${RM} system.bif

.PHONY: all package clean


