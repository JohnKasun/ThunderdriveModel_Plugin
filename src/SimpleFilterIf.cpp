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
	case FilterType::kLowpass:
		mFilter = new SimpleLowPass();
		break;
	default:
		mFilter = new SimpleHighPass();
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
	mFilterType = FilterType::kNoFilter;

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