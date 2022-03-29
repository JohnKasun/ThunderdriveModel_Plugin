#pragma once

#include <cassert>

class ThunderdriveProcessor
{
public:

	enum Param_t
	{
		kGain,
		kDrive,

		kNumParams
	};

	ThunderdriveProcessor();
	~ThunderdriveProcessor();

	void setParam(ThunderdriveProcessor::Param_t param, float value);
	float getParam(ThunderdriveProcessor::Param_t param) const;

	void process(float* outBuffer, const float* inBuffer, int iNumSamples);

private:

	float mParamValues[kNumParams];
	float mParamRanges[kNumParams][2];

	bool isParamInRange(ThunderdriveProcessor::Param_t param, float value) const;

};