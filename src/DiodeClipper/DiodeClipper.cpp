#include "DiodeClipper.h"

DiodeClipper::DiodeClipper()
{

}

DiodeClipper::DiodeClipper(float cutoffGain, float maxGain) :
	mCutoffGain{ cutoffGain },
	mMaxGain{ maxGain }
{

}

DiodeClipper::~DiodeClipper()
{

}

Error_t DiodeClipper::setCutoffGain(float cutoffGain)
{
	if (cutoffGain < 0)
		return Error_t::kFunctionInvalidArgsError;

	mCutoffGain = cutoffGain;
	return Error_t::kNoError;
}

Error_t DiodeClipper::setMaxGain(float maxGain)
{
	if (maxGain < 0 || maxGain < mCutoffGain)
		return Error_t::kFunctionInvalidArgsError;

	mMaxGain = maxGain;
}

float DiodeClipper::getCutoffGain() const
{
	return mCutoffGain;
}

float DiodeClipper::getMaxGain() const
{
	return mMaxGain;
}

float DiodeClipper::process(float sample)
{
	if (abs(sample) > mCutoffGain)
	{
		float phase = (sample < 0) ? -1.0f : 1.0f;
		return (0.0238 * sample + phase * 2.6437);
	}
}
