#include "SimpleFilter.h"
#include "SimpleFilterIf.h"

SimpleFilterIf::SimpleFilterIf()
{

}

SimpleFilterIf::~SimpleFilterIf()
{
	reset();
}

Error_t SimpleFilterIf::init(SimpleFilterIf::FilterType filterType)
{
	if (mFilter)
		return Error_t::kMemError;

	switch (filterType)
	{
	case FilterType::kLowPass:
		mFilter = new SimpleLowPass();
		break;
	case FilterType::kHighPass:
		mFilter = new SimpleHighPass();
		break;
	default:
		return Error_t::kFunctionInvalidArgsError;
	}

	mFilterType = filterType;

	return Error_t::kNoError;
}

Error_t SimpleFilterIf::reset()
{
	if (!mFilter)
		return Error_t::kMemError;

	delete mFilter;
	mFilter = nullptr;
	mFilterType = FilterType::kUninitialized;

	return Error_t::kNoError;
}

Error_t SimpleFilterIf::setParam(SimpleFilterIf::FilterParam filterParam, float value)
{
	if (!mFilter)
		return Error_t::kMemError;

	return mFilter->setParam(filterParam, value);
}

float SimpleFilterIf::getParam(SimpleFilterIf::FilterParam filterParam) const
{
	if (!mFilter)
		return 0;

	return mFilter->getParam(filterParam);
}

SimpleFilterIf::FilterType SimpleFilterIf::getFilterType() const
{
	return mFilterType;
}

float SimpleFilterIf::process(float in)
{
	if (!mFilter)
		return 0;

	return mFilter->process(in);
}