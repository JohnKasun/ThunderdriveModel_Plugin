#pragma once

#include "ErrorDef.h"

class SimpleFilter;

class SimpleFilterIf
{
public:
	enum FilterType {
		kLowPass,
		kHighPass,

		kNumFilterTypes,

		kUninitialized
	};

	enum FilterParam {
		kCutoff,

		kNumFilterParams
	};

	SimpleFilterIf();
	~SimpleFilterIf();

	Error_t init(SimpleFilterIf::FilterType filterType);
	Error_t reset();

	Error_t setParam(SimpleFilterIf::FilterParam filterParam, float value);
	float getParam(SimpleFilterIf::FilterParam filterParam) const;

	FilterType getFilterType() const;

	float process(float in);

private:

	FilterType mFilterType = FilterType::kUninitialized;
	SimpleFilter* mFilter = nullptr;

};