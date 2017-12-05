/*****************************************************************************
* Filename:          C:\Users\superman\Documents\TylerBondGithub\ecen427\SpaceInvaderTestHW2/drivers/dma_controller_v1_00_a/src/dma_controller_selftest.c
* Version:           1.00.a
* Description:       Contains a diagnostic self-test function for the dma_controller driver
* Date:              Mon Dec 04 14:36:43 2017 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "dma_controller.h"
#include "stdio.h"
#include "xio.h"
#include "xparameters.h"


/************************** Constant Definitions ***************************/

#define READ_WRITE_MUL_FACTOR 0x10
#define DMA_CONTROLLER_SELFTEST_BUFSIZE  4 /* Size of buffer (n bytes) is fixed to 4 for lite Master */
#define DMA_CONTROLLER_USER_NUM_REG  7/* Number of registers in slave */

/************************** Variable Definitions ****************************/

static Xuint8 __attribute__((aligned (128))) SrcBuffer[DMA_CONTROLLER_SELFTEST_BUFSIZE];   /* Source buffer      */
static Xuint8 __attribute__((aligned (128))) DstBuffer[DMA_CONTROLLER_SELFTEST_BUFSIZE];   /* Destination buffer */

/************************** Function Definitions ***************************/

/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the DMA_CONTROLLER instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus DMA_CONTROLLER_SelfTest(void * baseaddr_p)
{
  Xuint32 baseaddr;
  int write_loop_index;
  int read_loop_index;
  int Index;
  
  /*
   * Check and get the device address
   */
  /*
   * Base Address maybe 0. Up to developer to uncomment line below.
  XASSERT_NONVOID(baseaddr_p != XNULL);
   */
  baseaddr = (Xuint32) baseaddr_p;

  xil_printf("******************************\n\r");
  xil_printf("* User Peripheral Self Test\n\r");
  xil_printf("******************************\n\n\r");

  /*
   * Write to user logic slave module register(s) and read back
   */
  xil_printf("User logic slave module test...\n\r");

  for (write_loop_index = 0 ; write_loop_index < DMA_CONTROLLER_USER_NUM_REG; write_loop_index++)
    DMA_CONTROLLER_mWriteSlaveReg0 (baseaddr, write_loop_index*4, (write_loop_index+1)*READ_WRITE_MUL_FACTOR);
  for (read_loop_index = 0 ; read_loop_index < DMA_CONTROLLER_USER_NUM_REG; read_loop_index++)
    if ( DMA_CONTROLLER_mReadSlaveReg0 (baseaddr, read_loop_index*4) != (read_loop_index+1)*READ_WRITE_MUL_FACTOR){
      xil_printf ("Error reading register value at address %x", (int)baseaddr + read_loop_index*4);
      return XST_FAILURE;
    }

  xil_printf("   - slave register write/read passed\n\n\r");

  /* Read the registers at the base address to ensure that this is indeed working */
  if ( (DMA_CONTROLLER_mReadSlaveReg0 (baseaddr, 0)) != 0x0){
    xil_printf("   - soft reset failed\n\n\r");
    return XST_FAILURE;
  }

  xil_printf("   - soft reset passed\n\n\r");

  /*
   * Setup user logic master module to receive/send data from/to remote memory
   */
  xil_printf("User logic master module test...\n\r");
  xil_printf("   - source buffer address is 0x%08x\n\r", SrcBuffer);
  xil_printf("   - destination buffer address is 0x%08x\n\r", DstBuffer);
  xil_printf("   - initialize the source buffer bytes with a pattern\n\r");
  xil_printf("   - initialize the destination buffer bytes to zero\n\r");
  /*
  *  Initialize the buffer to be used for testing. Note that this
  * buffer should be accessible from both processor as well as
  * Master */

  for ( Index = 0; Index < DMA_CONTROLLER_SELFTEST_BUFSIZE; Index++ )
  {
    SrcBuffer[Index] = Index;
    DstBuffer[Index] = 0;
  }
  xil_printf("   - start user logic master module to receive one word from the source\n\r");
  DMA_CONTROLLER_MasterRecvWord(baseaddr, (Xuint32) SrcBuffer);
  while ( ! DMA_CONTROLLER_mMasterDone(baseaddr) ) {}
  xil_printf("   - transfer completed\n\r");
  xil_printf("   - start user logic master module to send onw word to the destination\n\r");
  DMA_CONTROLLER_MasterSendWord(baseaddr, (Xuint32) DstBuffer);
  while ( ! DMA_CONTROLLER_mMasterDone(baseaddr) ) {}
  xil_printf("   - transfer completed\n\r");

  /* Compare the source and destination buffers */

  for ( Index = 0; Index < DMA_CONTROLLER_SELFTEST_BUFSIZE; Index++ )
  {
    if ( DstBuffer[Index] != SrcBuffer[Index] )
    {
      xil_printf("   - destination buffer byte %d is different from the source buffer\n\r", Index);
      xil_printf("   - master module data transfer failed\n\r");
      return XST_FAILURE;
    }
  }
  xil_printf("   - destination buffer's contents are same as the source buffer\n\r");
  xil_printf("   - master module data transfer passed\n\n\r");

  return XST_SUCCESS;
}
