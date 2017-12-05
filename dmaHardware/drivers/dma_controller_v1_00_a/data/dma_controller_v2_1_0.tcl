##############################################################################
## Filename:          C:\Users\superman\Documents\TylerBondGithub\ecen427\dmaHardware/drivers/dma_controller_v1_00_a/data/dma_controller_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Mon Dec 04 15:38:29 2017 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "dma_controller" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
