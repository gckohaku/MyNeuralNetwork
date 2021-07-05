#ifndef XOR_SHIFT_128

#define XOR_SHIFT_128

#include "XorShift128.h"

void XorShifts::XorShift128::SetSeed(
	uint32_t w,
	uint32_t x,
	uint32_t y,
	uint32_t z
) {
	x = x != NULL ? x : w << 13;
	y = y != NULL ? y : (w >> 9) ^ (x << 6);
	z = z != NULL ? z : y >> 7;
	seeds = { x,y,z,w };
	this->w = w; this->x = x; this->y = y; this->z = z;
}

uint32_t XorShifts::XorShift128::Rand() {
	randCount++;
	uint32_t t = x ^ (x << 11);
	x = y;
	y = z;
	z = w;
	return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

int XorShifts::XorShift128::RandInt(int min = 0, int max = 0x7FFFFFFF) {
	return Rand() % (max - min + 1) + min;
}

float XorShifts::XorShift128::RandFloat(float min = 0, float max = 1) {
	return (float)(Rand() % 0xFFFF) / 0xFFFF * (max - min) + min;
}

#endif