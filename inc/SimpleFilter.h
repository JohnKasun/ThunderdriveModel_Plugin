#pragma once

#include "ErrorDef.h"
#include "RingBuffer.h"

class SimpleFilter
{
public:

	enum FilterParam {
		kCutoff,

		kNumFilterParams
	};

	SimpleFilter();
	~SimpleFilter();

	Error_t setParam(SimpleFilter::FilterParam filterParam, float value);
	float getParam(SimpleFilter::FilterParam filterParam) const;

	virtual float process(float in) = 0;

protected:

	float mParamValues[kNumFilterParams]{};
	float mParamRanges[kNumFilterParams][2]{};

	CRingBuffer<float> mInputDelayLine{ 2 };

	bool isInParamRange(SimpleFilter::FilterParam, float value) const;

};

class SimpleLowPass : public SimpleFilter
{
public:

	float process(float in) override;
};

class SimpleHighPass : public SimpleFilter
{
public:

	float process(float in) override;
		
private:

	CRingBuffer<float> mOutputDelayLine{ 2 };

};