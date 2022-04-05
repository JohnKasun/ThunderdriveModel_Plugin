#include "SimpleFilter.h"

SimpleFilter::SimpleFilter()
{

	for (int i = 0; i < SimpleFilterIf::kNumFilterParams; i++)
		mParamValues[i] = 0;

	mParamRanges[SimpleFilterIf::FilterParam::kCutoff][0] = 0;
	mParamRanges[SimpleFilterIf::FilterParam::kCutoff][1] = 20000;

}

SimpleFilter::~SimpleFilter()
{

}

Error_t SimpleFilter::setParam(SimpleFilterIf::FilterParam filterParam, float value)
{
	if (!isInParamRange(filterParam, value))
		return Error_t::kFunctionInvalidArgsError;

	mParamValues[filterParam] = value;
}

float SimpleFilter::getParam(SimpleFilterIf::FilterParam filterParam) const
{
	return mParamValues[filterParam];
}

bool SimpleFilter::isInParamRange(SimpleFilterIf::FilterParam filterParam, float value) const
{
	return (mParamRanges[filterParam][0] <= value && value <= mParamRanges[filterParam][1]);
}

float SimpleLowPass::process(float in)
{
	float prevIn = mInputDelayLine.getPostInc();
	float out	 = in - prevIn;

	mInputDelayLine.putPostInc(in);

	return out;
}

float SimpleHighPass::process(float in)
{
	float prevIn  = mInputDelayLine.getPostInc();
	float prevOut = mOutputDelayLine.getPostInc();
	float out = in - prevIn + prevOut;

	mInputDelayLine.putPostInc(in);
	mOutputDelayLine.putPostInc(out);

	return out;
}