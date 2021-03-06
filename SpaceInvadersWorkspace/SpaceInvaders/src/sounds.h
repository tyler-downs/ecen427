/*
 * sounds.h
 *
 *  Created on: Oct 27, 2017
 *      Author: superman
 */

#ifndef SOUNDS_H_
#define SOUNDS_H_

#include "xac97_l.h"
//#include "soundfiles/alienKilledSound.c"

//extern int32_t alienKilledSound_soundData[];

void sounds_init_sound(); //init the sound equipment
void sounds_fillFifo(); //fill the fifo, either with a sound or 0's

void sounds_playShootSound(); //signal to play the shoot sound
void sounds_playTankDeathSound(); //signal to play the tank death sound
void sounds_playAlienKilledSound(); //signal to play the alien killed explosion sound
void sounds_playAlienMoveSound(); //signal to play the alien move sound
void sounds_volumeDown(); //decrease the volume
void sounds_volumeUp(); //increase the volume

#endif /* SOUNDS_H_ */
