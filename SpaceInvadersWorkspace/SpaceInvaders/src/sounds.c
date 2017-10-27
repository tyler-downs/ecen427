/*
 * sounds.c
 *
 *  Created on: Oct 27, 2017
 *      Author: superman
 */
#include "sounds.h"
#include <stdint.h>
#include "xac97_l.h"
#include "xparameters.h"

//#include "soundfiles/alienKilledSound.c"

extern int32_t alienKilledSound_soundData[];
extern int32_t alienKilledSound_sampleRate;
extern int32_t alienKilledSound_numSamples;

extern int tankFireSoundRate;
extern int tankFireSoundFrames;
extern int tankFireSound[];




void accessSounds()
{
	xil_printf("Sample rate: %d\n\r", alienKilledSound_soundData[0]);
}


void init_sound()
{
	//call audio_init

	//call hard reset
	XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);
	XAC97_AwaitCodecReady(XPAR_AXI_AC97_0_BASEADDR);
	XAC97_mSetControl(AC97_ExtendedAudioStat, AC97_EXTENDED_AUDIO_CONTROL_VRA);
	XAC97_mSetControl(AC97_PCM_DAC_Rate, tankFireSoundRate);
	uint32_t i;
	while(1)
	{
		XAC97_PlayAudio(XPAR_AXI_AC97_0_BASEADDR, &tankFireSound[0], &tankFireSound[tankFireSoundFrames-1]);
		while(i < 5000000)
		{
			i++;
		}
		i = 0;
	}


}