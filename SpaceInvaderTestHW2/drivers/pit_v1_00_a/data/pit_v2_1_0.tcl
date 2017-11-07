##############################################################################
## Filename:          C:\Users\superman\Documents\TylerBondGithub\ecen427\SpaceInvaderTestHW2/drivers/pit_v1_00_a/data/pit_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Mon Nov 06 17:52:38 2017 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "pit" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
