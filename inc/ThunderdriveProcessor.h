#pragma once

#include <cassert>
#include <limits>
#include "ErrorDef.h"
#include "SimpleFilterIf.h"

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

	Error_t setParam(ThunderdriveProcessor::Param_t param, float value);
	float getParam(ThunderdriveProcessor::Param_t param) const;

	Error_t process(float* outBuffer, const float* inBuffer, int iNumSamples);

private:

	float mParamValues[ThunderdriveProcessor::kNumParams];
	float mParamRanges[ThunderdriveProcessor::kNumParams][2];

	bool isParamInRange(ThunderdriveProcessor::Param_t param, float value) const;

	void applyInputGain(float& value) const;
	void applyDiodeClipping(float& value) const;

	// Raw circuitry values
	const float mR1RangesInOhms[2]{ 0, 14925 };
	const float mR2InOhms = 2400.0f;
	const float mInputMaxVoltage = 0.120f;
	const float mDiodeMaxVoltage = 0.591f;
	const float mDiodeCutoffVoltage = 0.325f;

	// Circuitry values converted to gain format
	const float mInputMaxGain = 0.8f;
	const float mDiodeMaxGain = mDiodeMaxVoltage / mInputMaxVoltage;
	const float mDiodeCutoffGain = mDiodeCutoffVoltage / mInputMaxVoltage;

	SimpleFilterIf mFilter;
};