#pragma once

#include <cmath>

#include "ErrorDef.h"

class DiodeClipper
{
public:
	DiodeClipper();
	DiodeClipper(float cutoffGain, float maxGain);
	~DiodeClipper();

	Error_t setCutoffGain(float cutoffGain);
	Error_t setMaxGain(float maxGain);

	float getCutoffGain() const;
	float getMaxGain() const;

	float process(float sample);

private:

	float mCutoffGain = 0;
	float mMaxGain = 0;

};