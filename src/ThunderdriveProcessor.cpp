#include "ThunderdriveProcessor.h"

ThunderdriveProcessor::ThunderdriveProcessor()
{

	mParamValues[ThunderdriveProcessor::kGain] = 0.5f;
	mParamValues[ThunderdriveProcessor::kDrive] = 0.0f;

	mParamRanges[ThunderdriveProcessor::kGain][0] = 0.0f;
	mParamRanges[ThunderdriveProcessor::kGain][1] = 1.0f;
	mParamRanges[ThunderdriveProcessor::kDrive][0] = 0.0f;
	mParamRanges[ThunderdriveProcessor::kDrive][1] = 1.0f;

	mR1Ranges[0] = 750.0f;
	mR1Ranges[1] = 14925.0f;

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
		
		// Convert To Voltage
		float valueAsVoltage = inBuffer[sample] * 0.12;

		// Input Gain Stage
		float R1 = (mR1Ranges[1] - mR1Ranges[0]) * mParamValues[ThunderdriveProcessor::kDrive] + mR1Ranges[0];
		float driveGain = (1 + (R1 / mR2));
		valueAsVoltage *= driveGain;

		// Diode Clipping Stage
		if (valueAsVoltage > mDiodeCutoff)
			applyDiodeClipping(valueAsVoltage);

		// Normalize between -1 and 1
		float sampleValue = valueAsVoltage / mDiodeMax;

		outBuffer[sample] = mParamValues[ThunderdriveProcessor::kGain] * sampleValue;
	}
}
 
bool ThunderdriveProcessor::isParamInRange(ThunderdriveProcessor::Param_t param, float value) const
{
	return (mParamRanges[param][0] <= value && value <= mParamRanges[param][1]);
}

void ThunderdriveProcessor::applyDiodeClipping(float& value) const
{
	if (value > mDiodeMax)
		value = mDiodeMax;
	else
	{
		value * 0.5f;
	}
}


