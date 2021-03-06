/*
 * sounds.c
 *
 *  Created on: Oct 27, 2017
 *      Author: superman
 */
#include "sounds.h"
#include <stdint.h>
#include "xparameters.h"

//#include "soundfiles/alienKilledSound.c"

extern int32_t alienKilledSound_soundData[]; //alien killed explosion sound
extern int32_t alienKilledSound_sampleRate;
extern int32_t alienKilledSound_numSamples;

extern int32_t shootSound_sampleRate; //tank bullet shoot sound
extern int32_t shootSound_numSamples;
extern int32_t shootSound_soundData[];

extern int32_t explosionSound_sampleRate; //tank death sound
extern int32_t explosionSound_numSamples;
extern int32_t explosionSound_soundData[];

//alien move sounds
extern int32_t alienMoveSound4_sampleRate;
extern int32_t alienMoveSound4_numSamples;
extern int32_t alienMoveSound4_soundData[];

extern int32_t alienMoveSound3_sampleRate;
extern int32_t alienMoveSound3_numSamples;
extern int32_t alienMoveSound3_soundData[];

extern int32_t alienMoveSound2_sampleRate;
extern int32_t alienMoveSound2_numSamples;
extern int32_t alienMoveSound2_soundData[];

extern int32_t alienMoveSound1_sampleRate;
extern int32_t alienMoveSound1_numSamples;
extern int32_t alienMoveSound1_soundData[];

//saucer flying sounds
extern int32_t UFOLowPitchSound_sampleRate;
extern int32_t UFOLowPitchSound_numSamples;
extern int32_t UFOLowPitchSound_soundData[];

extern u8 saucerLaunched; //true if the saucer is alive on screen


#define NUM_SAMPLES_PER_INTERRUPT 100 //how many samples to write to the FIFO at a time
#define ALIEN_MOVE_PITCH_HIGHEST 4 //first alien move sound
#define ALIEN_MOVE_PITCH_HIGH 3 //second alien move sound
#define ALIEN_MOVE_PITCH_LOW 2 //third alien move sound
#define ALIEN_MOVE_PITCH_LOWEST 1 //fourth alien move sound

#define SAUCER_SOUND_HIGH 1 //the high pitch saucer sound
#define SAUCER_SOUND_LOW 0 //the low pitch saucer sound

#define DELTA_VOLUME 8 //how much to change the volume by on every button press

uint8_t playShootSound = FALSE; //flag to signal to play the shoot sound
uint8_t playTankDeathSound = FALSE; //flag to signal to play the tank death sound
uint8_t playAlienKilledSound = FALSE; //flag to signal to play the alien killed sound
uint8_t playAlienMoveSound = FALSE; //flag to signal to play the alien move sound
uint8_t alienMoveSoundNumber = ALIEN_MOVE_PITCH_LOWEST; //4 is the highest pitch, 1 is the lowest
uint32_t sounds_currentIndex = 0;

uint16_t currentVolume = AC97_VOL_MID; //the current volume

//writes zeros to the FIFO
void writeZeros()
{
	uint32_t i;
	for( i = 0; i < NUM_SAMPLES_PER_INTERRUPT; i++ )
		XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, 0);
}

//writes a sound to the FIFO, or 0's if reached the end of the sound
void writeSound(uint8_t* soundFlag, int32_t* soundData, int32_t numSamples)
{
	uint32_t start_point = sounds_currentIndex;
	for ( ; sounds_currentIndex < (start_point + NUM_SAMPLES_PER_INTERRUPT); sounds_currentIndex++) //load 100 samples from wherever we are
	{
		if (sounds_currentIndex < numSamples - 1) //if we haven't reached the end of the sound array
		{
			XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, *(soundData + sounds_currentIndex)); //write sound sample to fifo
		}
		else //reached end of sound
		{
			writeZeros();
			*soundFlag = FALSE; //disable the flag
			return; //we're done here
		}
	}
}

//fill the fifo, either with a sound or 0's
void sounds_fillFifo()
{
	if (playTankDeathSound)
	{
		writeSound(&playTankDeathSound, explosionSound_soundData, explosionSound_numSamples); //write the tank death sound to the fifo
	}
	else if (playShootSound)
	{
		writeSound(&playShootSound, shootSound_soundData, shootSound_numSamples); //write the tank bullet shoot sound to the fifo
	}
	else if (playAlienKilledSound)
	{
		writeSound(&playAlienKilledSound, alienKilledSound_soundData, alienKilledSound_numSamples); //write the alien killed explosion sound to the fifo
	}
	else if (playAlienMoveSound)
	{
		switch (alienMoveSoundNumber) //select which alien pitch to play
		{
		case ALIEN_MOVE_PITCH_HIGHEST: //4
			writeSound(&playAlienMoveSound, alienMoveSound4_soundData, alienMoveSound4_numSamples); //write the highest alien move sound to the FIFO
			break;
		case ALIEN_MOVE_PITCH_HIGH: //3
			writeSound(&playAlienMoveSound, alienMoveSound3_soundData, alienMoveSound3_numSamples); //write the high alien move sound to the FIFO
			break;
		case ALIEN_MOVE_PITCH_LOW: //2
			writeSound(&playAlienMoveSound, alienMoveSound2_soundData, alienMoveSound2_numSamples); //write the low alien move sound to the FIFO
			break;
		case ALIEN_MOVE_PITCH_LOWEST: //1
			writeSound(&playAlienMoveSound, alienMoveSound1_soundData, alienMoveSound1_numSamples); //write the lowest alien move sound to the FIFO
			break;
		default: //shouldn't ever happen
			xil_printf("error playing alien move sound!");
			return;
		}
	}
	else //play saucer sound if it's on screen. Otherwise no sound needs to be played right now
	{
		if (saucerLaunched) //true if the saucer is on the screen
		{
			writeSound(NULL, UFOLowPitchSound_soundData, UFOLowPitchSound_numSamples);
		}
		writeZeros();
	}
}

void sounds_playShootSound() //signal to play the shoot sound
{
	playShootSound = TRUE; //set the flag to play the shoot sound
	if (!playTankDeathSound) //if a higher priority sound is not playing
		sounds_currentIndex = 0; //start at the beginning of the sound
}

void sounds_playTankDeathSound() //signal to play the tank death sound
{
	playTankDeathSound = TRUE; //set the flag to play the tank death sound
	sounds_currentIndex = 0; //start at the beginning of the sound
}

void sounds_playAlienKilledSound() //signal to play the alien killed explosion sound
{
	playAlienKilledSound = TRUE; //set the flag to play the alien killed explosion sound
	if (!playTankDeathSound && !playShootSound) //if a higher priority sound is not playing
		sounds_currentIndex = 0; //start at the beginning of the sound
}

void sounds_playAlienMoveSound() //signal to play the alien move sound
{
	playAlienMoveSound = TRUE; //set the flag to play the alien move sound
	if (!playTankDeathSound && !playShootSound && !playAlienKilledSound) //if a higher priority sound is not playing
		sounds_currentIndex = 0; //start at the beginning of the sound

	//update the next pitch to play
	if (alienMoveSoundNumber == ALIEN_MOVE_PITCH_LOWEST)
		alienMoveSoundNumber = ALIEN_MOVE_PITCH_HIGHEST; //start over at the top pitch
	else
		alienMoveSoundNumber--; //move down a pitch
}

//write a new volume to the registers
void writeVol(u16 newVolume) {
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, newVolume);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_AuxOutVol, newVolume);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVolMono, newVolume);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCBeepVol, newVolume);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCMOutVol, newVolume);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_LineInVol, newVolume);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MicVol, newVolume);
}

void sounds_volumeDown() //decrease the volume
{
	u32 newVolume = currentVolume + DELTA_VOLUME; //decrease the volume
	if (newVolume > AC97_VOL_MIN) //if we passed the min volume
		newVolume = AC97_VOL_MIN;
	writeVol(newVolume); //update the volume registers
	currentVolume = newVolume; //update the global
}

void sounds_volumeUp() //increase the volume
{

	u32 newVolume;
	if(currentVolume < DELTA_VOLUME) //if the next decrease will put the volume below zero (max)
		newVolume = AC97_VOL_MAX; //set the volume to 0 (max)
	else
		newVolume = currentVolume - DELTA_VOLUME; //decrease the volume
	writeVol(newVolume); //update the volume registers
	currentVolume = newVolume; //update the global
}

void sounds_init_sound()
{
	//call audio_init

	//call hard reset
	XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);
	XAC97_InitAudio(XPAR_AXI_AC97_0_BASEADDR, 0);
	XAC97_AwaitCodecReady(XPAR_AXI_AC97_0_BASEADDR);
	//set VRA
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, AC97_EXTENDED_AUDIO_CONTROL_VRA);
	//set frequency DAC
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, shootSound_sampleRate); //assuming the sample rate is the same for all sounds
	//set volumes
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCMOutVol, AC97_VOL_MID);
	//clear FIFO
	XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);
	//set control bit to cause IN_FIFO interrupts
	XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
}
