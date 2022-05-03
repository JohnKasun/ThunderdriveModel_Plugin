#include "DiodeClipper.h"

DiodeClipper::DiodeClipper()
{

}

DiodeClipper::~DiodeClipper()
{

}

Error_t DiodeClipper::setCutoffGain(float negativeCutoff, float positiveCutoff)
{
	if (negativeCutoff > 0 || positiveCutoff < 0)
		return Error_t::kFunctionInvalidArgsError;

	mCutoffGainLowerBound = negativeCutoff;
	mCutoffGainUpperBound = positiveCutoff;
	return Error_t::kNoError;
}

Error_t DiodeClipper::setMaxGain(float negativeMax, float positiveMax)
{
	if (negativeMax > 0 || positiveMax < 0)
		return Error_t::kFunctionInvalidArgsError;

	mMaxGainLowerBound = negativeMax;
	mMaxGainUpperBound = positiveMax;
	return Error_t::kNoError;
}

/* Credit for clipping stage:
* https://github.com/JanosGit/Schrammel_OJD
*/

Error_t DiodeClipper::process(float& sample)
{
	float in = sample;

	if (in <= mMaxGainLowerBound)
	{
		sample = -1.0f;
	}
	else if ((in > mMaxGainLowerBound) && (in < mCutoffGainLowerBound))
	{
		in += abs(mCutoffGainLowerBound);
		sample = in + (in * in) / (4 * (1 + mCutoffGainLowerBound)) + mCutoffGainLowerBound;
	}
	else if ((in > mCutoffGainUpperBound) && (in < mMaxGainUpperBound))
	{
		in -= mCutoffGainUpperBound;
		sample = in - (in * in) / (4 * (1 - mCutoffGainUpperBound)) + mCutoffGainUpperBound;
	}
	else if (mMaxGainUpperBound > 1.1f)
	{
		sample = 1.0f;
	}
	
	return Error_t::kNoError;
}
