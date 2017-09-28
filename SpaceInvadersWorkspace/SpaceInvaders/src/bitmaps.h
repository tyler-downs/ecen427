/*
 * bitmaps.h
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#ifndef BITMAPS_H_
#define BITMAPS_H_

#include <stdio.h>
#include <stdint.h>

// Packs each horizontal line of the figures into a single 32 bit word.
#define packword32(b31,b30,b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b31 << 31) | (b30 << 30) | (b29 << 29) | (b28 << 28) | (b27 << 27) | (b26 << 26) | (b25 << 25) | (b24 << 24) |						  \
 (b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 24 bit word.
#define packword24(b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 20 bit word.
#define packword20(b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 18 bit word.
#define packword18(b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b17 << 17) | (b16 << 16) |  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 16 bit word.
#define packword16(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 15 bit word.
#define packword15(b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |	\
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 12 bit word.
#define packword12(b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 6 bit word.
#define packword6(b5,b4,b3,b2,b1,b0) \
((b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 5 bit word.
#define packword5(b4,b3,b2,b1,b0) \
((b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Packs each horizontal line of the figures into a single 3 bit word.
#define packword3(b2,b1,b0) \
((b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Must define packword for each of the different bit-widths.
static const uint32_t saucer_16x7[] =
{
packword16(0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0),
packword16(0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0),
packword16(0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
packword16(0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0),
packword16(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
packword16(0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0),
packword16(0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0)
};

static const uint32_t alien_explosion_12x10[] =
{
packword12(0,0,0,0,0,0,1,0,0,0,0,0),
packword12(0,0,0,1,0,0,1,0,0,0,1,0),
packword12(1,0,0,1,0,0,0,0,0,1,0,0),
packword12(0,1,0,0,1,0,0,0,1,0,0,0),
packword12(0,0,0,0,0,0,0,0,0,0,1,1),
packword12(1,1,0,0,0,0,0,0,0,0,0,0),
packword12(0,0,0,1,0,0,0,1,0,0,1,0),
packword12(0,0,1,0,0,0,0,0,1,0,0,1),
packword12(0,1,0,0,0,1,0,0,1,0,0,0),
packword12(0,0,0,0,0,1,0,0,0,0,0,0)
};

static const uint32_t alien_top_in_12x8[] =
{
packword12(0,0,0,0,0,1,1,0,0,0,0,0),
packword12(0,0,0,0,1,1,1,1,0,0,0,0),
packword12(0,0,0,1,1,1,1,1,1,0,0,0),
packword12(0,0,1,1,0,1,1,0,1,1,0,0),
packword12(0,0,1,1,1,1,1,1,1,1,0,0),
packword12(0,0,0,1,0,1,1,0,1,0,0,0),
packword12(0,0,1,0,0,0,0,0,0,1,0,0),
packword12(0,0,0,1,0,0,0,0,1,0,0,0)
};

static const uint32_t alien_top_out_12x8[] =
{
packword12(0,0,0,0,0,1,1,0,0,0,0,0),
packword12(0,0,0,0,1,1,1,1,0,0,0,0),
packword12(0,0,0,1,1,1,1,1,1,0,0,0),
packword12(0,0,1,1,0,1,1,0,1,1,0,0),
packword12(0,0,1,1,1,1,1,1,1,1,0,0),
packword12(0,0,0,0,1,0,0,1,0,0,0,0),
packword12(0,0,0,1,0,1,1,0,1,0,0,0),
packword12(0,0,1,0,1,0,0,1,0,1,0,0)
};

static const uint32_t alien_middle_in_12x8[] =
{
packword12(0,0,0,1,0,0,0,0,0,1,0,0),
packword12(0,0,0,0,1,0,0,0,1,0,0,0),
packword12(0,0,0,1,1,1,1,1,1,1,0,0),
packword12(0,0,1,1,0,1,1,1,0,1,1,0),
packword12(0,1,1,1,1,1,1,1,1,1,1,1),
packword12(0,1,1,1,1,1,1,1,1,1,1,1),
packword12(0,1,0,1,0,0,0,0,0,1,0,1),
packword12(0,0,0,0,1,1,0,1,1,0,0,0)
};

static const uint32_t alien_middle_out_12x8[] =
{
packword12(0,0,0,1,0,0,0,0,0,1,0,0),
packword12(0,1,0,0,1,0,0,0,1,0,0,1),
packword12(0,1,0,1,1,1,1,1,1,1,0,1),
packword12(0,1,1,1,0,1,1,1,0,1,1,1),
packword12(0,1,1,1,1,1,1,1,1,1,1,1),
packword12(0,0,1,1,1,1,1,1,1,1,1,0),
packword12(0,0,0,1,0,0,0,0,0,1,0,0),
packword12(0,0,1,0,0,0,0,0,0,0,1,0)
};

static const uint32_t alien_bottom_in_12x8[] =
{
packword12(0,0,0,0,1,1,1,1,0,0,0,0),
packword12(0,1,1,1,1,1,1,1,1,1,1,0),
packword12(1,1,1,1,1,1,1,1,1,1,1,1),
packword12(1,1,1,0,0,1,1,0,0,1,1,1),
packword12(1,1,1,1,1,1,1,1,1,1,1,1),
packword12(0,0,1,1,1,0,0,1,1,1,0,0),
packword12(0,1,1,0,0,1,1,0,0,1,1,0),
packword12(0,0,1,1,0,0,0,0,1,1,0,0)
};

static const uint32_t alien_bottom_out_12x8[] =
{
packword12(0,0,0,0,1,1,1,1,0,0,0,0),
packword12(0,1,1,1,1,1,1,1,1,1,1,0),
packword12(1,1,1,1,1,1,1,1,1,1,1,1),
packword12(1,1,1,0,0,1,1,0,0,1,1,1),
packword12(1,1,1,1,1,1,1,1,1,1,1,1),
packword12(0,0,0,1,1,0,0,1,1,0,0,0),
packword12(0,0,1,1,0,1,1,0,1,1,0,0),
packword12(1,1,0,0,0,0,0,0,0,0,1,1)
};

static const uint32_t tank_15x8[] =
{
packword15(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0),
packword15(0,0,0,0,0,0,1,1,1,0,0,0,0,0,0),
packword15(0,0,0,0,0,0,1,1,1,0,0,0,0,0,0),
packword15(0,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
packword15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
packword15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
packword15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
packword15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)
};


// Shape of the entire bunker.
static const uint32_t bunker_24x18[] =
{
packword24(0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0),
packword24(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
packword24(0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)
};

// These are the blocks that comprise the bunker and each time a bullet
// strikes one of these blocks, you erode the block as you sequence through
// these patterns.
static const uint32_t bunkerDamage0_6x6[] = {
packword6(0,1,1,0,0,0),
packword6(0,0,0,0,0,1),
packword6(1,1,0,1,0,0),
packword6(1,0,0,0,0,0),
packword6(0,0,1,1,0,0),
packword6(0,0,0,0,1,0)
};

static const uint32_t bunkerDamage1_6x6[] = {
packword6(1,1,1,0,1,0),
packword6(1,0,1,0,0,1),
packword6(1,1,0,1,1,1),
packword6(1,0,0,0,0,0),
packword6(0,1,1,1,0,1),
packword6(0,1,1,0,1,0)
};

static const uint32_t bunkerDamage2_6x6[] = {
packword6(1,1,1,1,1,1),
packword6(1,0,1,1,0,1),
packword6(1,1,0,1,1,1),
packword6(1,1,0,1,1,0),
packword6(0,1,1,1,0,1),
packword6(1,1,1,1,1,1)
};

static const uint32_t bunkerDamage3_6x6[] = {
packword6(1,1,1,1,1,1),
packword6(1,1,1,1,1,1),
packword6(1,1,1,1,1,1),
packword6(1,1,1,1,1,1),
packword6(1,1,1,1,1,1),
packword6(1,1,1,1,1,1)
};

static const uint32_t lives_18x5[] = {
packword18(1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1),
packword18(1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0),
packword18(1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0),
packword18(1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1),
packword18(1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0)
};

static const uint32_t score_20x5[] = {
packword20(0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1),
packword20(1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0),
packword20(0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0),
packword20(0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0),
packword20(1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1)
};

static const uint32_t zero_5x5[] = {
packword5(0, 1, 1, 0, 0),
packword5(1, 0, 0, 1, 0),
packword5(1, 0, 0, 1, 0),
packword5(1, 0, 0, 1, 0),
packword5(0, 1, 1, 0, 0)
};

static const uint32_t one_3x5[] = {
packword3(1, 1, 0),
packword3(0, 1, 0),
packword3(0, 1, 0),
packword3(0, 1, 0),
packword3(0, 1, 0)
};

static const uint32_t two_5x5[] = {
packword5(1, 1, 1, 0, 0),
packword5(0, 0, 0, 1, 0),
packword5(0, 1, 1, 1, 0),
packword5(1, 0, 0, 0, 0),
packword5(1, 1, 1, 1, 0)
};

static const uint32_t three_5x5[] = {
packword5(1, 1, 1, 0, 0),
packword5(0, 0, 0, 1, 0),
packword5(1, 1, 1, 1, 0),
packword5(0, 0, 0, 1, 0),
packword5(1, 1, 1, 0, 0)
};

static const uint32_t four_5x5[] = {
packword5(1, 0, 0, 1, 0),
packword5(1, 0, 0, 1, 0),
packword5(1, 1, 1, 1, 0),
packword5(0, 0, 0, 1, 0),
packword5(0, 0, 0, 1, 0)
};

static const uint32_t five_5x5[] = {
packword5(1, 1, 1, 1, 0),
packword5(1, 0, 0, 0, 0),
packword5(1, 1, 1, 0, 0),
packword5(0, 0, 0, 1, 0),
packword5(1, 1, 1, 0, 0)
};

static const uint32_t six_5x5[] = {
packword5(0, 1, 1, 0, 0),
packword5(1, 0, 0, 0, 0),
packword5(1, 1, 1, 0, 0),
packword5(1, 0, 0, 1, 0),
packword5(0, 1, 1, 0, 0)
};

static const uint32_t seven_5x5[] = {
packword5(1, 1, 1, 1, 0),
packword5(0, 0, 0, 1, 0),
packword5(0, 0, 0, 1, 0),
packword5(0, 0, 1, 0, 0),
packword5(0, 0, 1, 0, 0)
};

static const uint32_t eight_5x5[] = {
packword5(0, 1, 1, 0, 0),
packword5(1, 0, 0, 1, 0),
packword5(0, 1, 1, 0, 0),
packword5(1, 0, 0, 1, 0),
packword5(0, 1, 1, 0, 0)
};

static const uint32_t nine_5x5[] = {
packword5(0, 1, 1, 0, 0),
packword5(1, 0, 0, 1, 0),
packword5(0, 1, 1, 1, 0),
packword5(0, 0, 0, 1, 0),
packword5(0, 1, 1, 0, 0)
};

#endif /* BITMAPS_H_ */
