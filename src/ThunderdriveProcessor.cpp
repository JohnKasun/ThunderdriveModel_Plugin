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

void ThunderdriveProcessor::setParam(ThunderdriveProcessor::Param_t param, float value)
{
	assert(isParamInRange(param, value));

	mParamValues[param] = value;

}

float ThunderdriveProcessor::getParam(ThunderdriveProcessor::Param_t param) const
{
	return mParamValues[param];
}

void ThunderdriveProcessor::process(float* outBuffer, const float* inBuffer, int iNumSamples) const
{
	for (int sample = 0; sample < iNumSamples; sample++)
	{
		outBuffer[sample] = mParamValues[ThunderdriveProcessor::kGain] * inBuffer[sample];
	}
}
 
bool ThunderdriveProcessor::isParamInRange(ThunderdriveProcessor::Param_t param, float value) const
{
	return (mParamRanges[param][0] <= value && value <= mParamRanges[param][1]);
}

