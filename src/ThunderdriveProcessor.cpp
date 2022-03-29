#include "ThunderdriveProcessor.h"

ThunderdriveProcessor::ThunderdriveProcessor()
{

	mParamValues[kGain] = 0.5f;
	mParamValues[kDrive] = 0.0f;

	mParamRanges[kGain][0] = 0.0f;
	mParamRanges[kGain][1] = 1.0f;
	mParamRanges[kDrive][0] = 0.0f;
	mParamRanges[kDrive][1] = 1.0f;

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

void ThunderdriveProcessor::process(float* outBuffer, const float* inBuffer, int iNumSamples)
{
}

bool ThunderdriveProcessor::isParamInRange(ThunderdriveProcessor::Param_t param, float value) const
{
	return (mParamRanges[param][0] < value && value < mParamRanges[param][1]);
}

