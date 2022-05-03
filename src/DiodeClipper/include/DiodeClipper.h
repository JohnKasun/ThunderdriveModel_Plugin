#pragma once

#include <cmath>

#include "ErrorDef.h"

class DiodeClipper
{
public:
	DiodeClipper();
	~DiodeClipper();

	Error_t setCutoffGain(float negativeCutoff, float positiveCutoff);
	Error_t setMaxGain(float negativeMax, float positiveMax);

	Error_t process(float& sample);

private:

	float mCutoffGainLowerBound = 0;
	float mCutoffGainUpperBound = 0;
	float mMaxGainLowerBound = 0;
	float mMaxGainUpperBound = 0;

};