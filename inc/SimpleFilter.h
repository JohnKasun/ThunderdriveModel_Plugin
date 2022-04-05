#pragma once

#include "ErrorDef.h"
#include "RingBuffer.h"

#include "SimpleFilterIf.h"

class SimpleFilter
{
public:

	SimpleFilter();
	~SimpleFilter();

	Error_t setParam(SimpleFilterIf::FilterParam filterParam, float value);
	float getParam(SimpleFilterIf::FilterParam filterParam) const;

	virtual float process(float in) = 0;

protected:

	float mParamValues[SimpleFilterIf::kNumFilterParams]{};
	float mParamRanges[SimpleFilterIf::kNumFilterParams][2]{};

	CRingBuffer<float> mInputDelayLine{ 2 };
	CRingBuffer<float> mOutputDelayLine{ 2 };

	bool isInParamRange(SimpleFilterIf::FilterParam, float value) const;

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

};