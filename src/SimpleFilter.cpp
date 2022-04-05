#include "SimpleFilter.h"

SimpleFilter::SimpleFilter(float sampleRate) :
	mSampleRate(sampleRate)
{

	for (int i = 0; i < SimpleFilterIf::kNumFilterParams; i++)
		mParamValues[i] = 0;

	mParamRanges[SimpleFilterIf::FilterParam::kCutoff][0] = 0;
	mParamRanges[SimpleFilterIf::FilterParam::kCutoff][1] = 20000;

	mInputDelayLine.setWriteIdx(1);
	mOutputDelayLine.setWriteIdx(1);

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
	float prevOut = mOutputDelayLine.getPostInc();
	float out = mParamValues[SimpleFilterIf::FilterParam::kCutoff] * prevOut + (1 - mParamValues[SimpleFilterIf::FilterParam::kCutoff]) * in;

	mOutputDelayLine.putPostInc(out);

	return out;
}

float SimpleHighPass::process(float in)
{
	float prevIn = mInputDelayLine.getPostInc();
	float out = in - mParamValues[SimpleFilterIf::FilterParam::kCutoff] * prevIn;

	mInputDelayLine.putPostInc(in);

	return out;
}