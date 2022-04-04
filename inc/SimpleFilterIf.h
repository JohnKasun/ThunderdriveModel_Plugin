#pragma once

#include "SimpleFilter.h"

class SimpleFilterIf
{
public:
	enum FilterType {
		kLowpass,
		kHighpass,

		kNumFilterTypes
	};

	SimpleFilterIf(SimpleFilterIf::FilterType filterType) :
		mFilterType(filterType),
		mFilter(nullptr)
	{
		switch (filterType)
		{
		case FilterType::kLowpass:
			mFilter = new SimpleLowPass();
		default:
			mFilter = new SimpleHighPass();
		}
	}

	~SimpleFilterIf()
	{
		delete mFilter;
		mFilter = nullptr;
	}

	Error_t setParam(SimpleFilter::FilterParam filterParam, float value)
	{
		return mFilter->setParam(filterParam, value);
	}

	float getParam(SimpleFilter::FilterParam filterParam) const
	{
		return mFilter->getParam(filterParam);
	}

	FilterType getFilterType() const
	{
		return mFilterType;
	}

	float process(float in)
	{
		return mFilter->process(in);
	}

private:

	FilterType mFilterType;
	SimpleFilter* mFilter;

};