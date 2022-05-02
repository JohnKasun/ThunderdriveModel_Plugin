#include "ThunderdriveProcessor.h"

ThunderdriveProcessor::ThunderdriveProcessor()
{

	mParamValues[ThunderdriveProcessor::kGain] = 0.5f;
	mParamValues[ThunderdriveProcessor::kDrive] = 0.0f;
	mParamValues[ThunderdriveProcessor::kTone] = 0.0f;

	mParamRanges[ThunderdriveProcessor::kGain][0] = 0.0f;
	mParamRanges[ThunderdriveProcessor::kGain][1] = 1.0f;
	mParamRanges[ThunderdriveProcessor::kDrive][0] = 0.0f;
	mParamRanges[ThunderdriveProcessor::kDrive][1] = 1.0f;
	mParamRanges[ThunderdriveProcessor::kTone][0] = 0.0f;
	mParamRanges[ThunderdriveProcessor::kTone][1] = 0.99f;

}

ThunderdriveProcessor::~ThunderdriveProcessor()
{
	reset();
}

Error_t ThunderdriveProcessor::init(float sampleRate)
{
	if (sampleRate <= 0)
		return Error_t::kFunctionInvalidArgsError;

	mSampleRate = sampleRate;
	return mFilter.init(SimpleFilterIf::FilterType::kHighPass, sampleRate);
}

Error_t ThunderdriveProcessor::reset()
{
	for (int i = 0; i < Param_t::kNumParams; i++)
		mParamValues[i] = 0;

	mSampleRate = 1.0f;
	mFilter.reset();

	return Error_t::kNoError;
}

Error_t ThunderdriveProcessor::setParam(ThunderdriveProcessor::Param_t param, float value)
{
	if (!isParamInRange(param, value))
		return Error_t::kFunctionInvalidArgsError;

	mParamValues[param] = value;
	if (param == Param_t::kTone)
		return mFilter.setParam(SimpleFilterIf::FilterParam::kCutoff, value);

	return Error_t::kNoError;
}

float ThunderdriveProcessor::getParam(ThunderdriveProcessor::Param_t param) const
{
	return mParamValues[param];
}

Error_t ThunderdriveProcessor::process(float* outBuffer, const float* inBuffer, int iNumSamples)
{
	for (int sample = 0; sample < iNumSamples; sample++)
	{
		float currentValue = inBuffer[sample];

		// Apply input gain from BJT
		applyInputGain(currentValue);

		// Apply distortion from diode stage
		mDiodeClipper.process(currentValue);

		// Apply post distortion filter
		mFilter.process(currentValue);

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

