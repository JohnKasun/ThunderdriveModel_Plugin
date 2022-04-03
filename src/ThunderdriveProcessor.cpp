#include "ThunderdriveProcessor.h"

ThunderdriveProcessor::ThunderdriveProcessor()
{

	mParamValues[ThunderdriveProcessor::kGain] = 0.5f;
	mParamValues[ThunderdriveProcessor::kDrive] = 0.0f;

	mParamRanges[ThunderdriveProcessor::kGain][0] = 0.0f;
	mParamRanges[ThunderdriveProcessor::kGain][1] = 1.0f;
	mParamRanges[ThunderdriveProcessor::kDrive][0] = 0.0f;
	mParamRanges[ThunderdriveProcessor::kDrive][1] = 1.0f;

}

ThunderdriveProcessor::~ThunderdriveProcessor()
{
}

Error_t ThunderdriveProcessor::setParam(ThunderdriveProcessor::Param_t param, float value)
{
	if (!isParamInRange(param, value))
		return Error_t::kFunctionInvalidArgsError;

	mParamValues[param] = value;
	return Error_t::kNoError;
}

float ThunderdriveProcessor::getParam(ThunderdriveProcessor::Param_t param) const
{
	return mParamValues[param];
}

Error_t ThunderdriveProcessor::process(float* outBuffer, const float* inBuffer, int iNumSamples) const
{
	for (int sample = 0; sample < iNumSamples; sample++)
	{
		float currentValue = inBuffer[sample];

		applyInputGain(currentValue);
		applyDiodeClipping(currentValue);

		// Normalize between -1 and 1
		currentValue /= mDiodeMaxGain;

		assert(abs(currentValue) <= 1.0f);

		outBuffer[sample] = mParamValues[ThunderdriveProcessor::kGain] * currentValue;
	}
	return Error_t::kNoError;
}
 
bool ThunderdriveProcessor::isParamInRange(ThunderdriveProcessor::Param_t param, float value) const
{
	return (mParamRanges[param][0] <= value && value <= mParamRanges[param][1]);
}

void ThunderdriveProcessor::applyInputGain(float& value) const
{
	float R1InOhms = (mR1RangesInOhms[1] - mR1RangesInOhms[0]) * mParamValues[ThunderdriveProcessor::kDrive] + mR1RangesInOhms[0];
	float driveGain = (1 + (R1InOhms / mR2InOhms));
	value *= driveGain;
}

void ThunderdriveProcessor::applyDiodeClipping(float& value) const
{
	if (abs(value) > mDiodeMaxGain)
	{
		float phase = (value < 0) ? -1.0f : 1.0f;
		value = phase * mDiodeMaxGain;
	}
	else if (value > mDiodeCutoffGain)
	{
		value *= 0.75;
	}
}


