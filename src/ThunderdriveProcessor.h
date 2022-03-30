#pragma once

#include <cassert>
#include <limits>

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

	void process(float* outBuffer, const float* inBuffer, int iNumSamples) const;

private:

	float mParamValues[ThunderdriveProcessor::kNumParams];
	float mParamRanges[ThunderdriveProcessor::kNumParams][2];

	bool isParamInRange(ThunderdriveProcessor::Param_t param, float value) const;

};