#pragma once

#include "SimpleFilter.h"

class SimpleFilterIf
{
public:
	enum FilterType {
		kLowpass,
		kHighpass,

		kNumFilterTypes,

		kNoFilter
	};

	SimpleFilterIf() {}

	~SimpleFilterIf()
	{
		reset();
	}

	Error_t init(SimpleFilterIf::FilterType filterType)
	{
		if (mFilter)
			return Error_t::kMemError;

		switch (filterType)
		{
		case FilterType::kLowpass:
			mFilter = new SimpleLowPass();
			break;
		default:
			mFilter = new SimpleHighPass();
		}

		return Error_t::kNoError;
	}

	Error_t reset()
	{
		delete mFilter;
		mFilter = nullptr;
		mFilterType = FilterType::kNoFilter;

		return Error_t::kNoError;
	}

	Error_t setParam(SimpleFilter::FilterParam filterParam, float value)
	{
		if (!mFilter)
			return Error_t::kMemError;

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
		if (!mFilter)
			return 0;

		return mFilter->process(in);
	}

private:

	FilterType mFilterType = FilterType::kNoFilter;
	SimpleFilter* mFilter = nullptr;

};