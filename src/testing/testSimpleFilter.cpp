#include "catch.hpp"

#include "SimpleFilterIf.h"

TEST_CASE("Init and Reset", "[SimpleFilter]")
{
	SimpleFilterIf simpleFilter;

	REQUIRE(simpleFilter.getFilterType() == SimpleFilterIf::FilterType::kUninitialized);
	REQUIRE(simpleFilter.setParam(SimpleFilterIf::FilterParam::kCutoff, 100) == Error_t::kMemError);
	REQUIRE(simpleFilter.getParam(SimpleFilterIf::FilterParam::kCutoff) == 0);
	REQUIRE(simpleFilter.reset() == Error_t::kMemError);
	REQUIRE(simpleFilter.process(0) == 0);

	REQUIRE(simpleFilter.init(SimpleFilterIf::FilterType::kLowPass, 44100) == Error_t::kNoError);

	REQUIRE(simpleFilter.init(SimpleFilterIf::FilterType::kHighPass, 44100) == Error_t::kMemError);

	REQUIRE(simpleFilter.getFilterType() == SimpleFilterIf::FilterType::kLowPass);
	
	REQUIRE(simpleFilter.reset() == Error_t::kNoError);
}

TEST_CASE("LowPass Output", "[SimpleFilter]")
{
	SimpleFilterIf filter;

	filter.init(SimpleFilterIf::FilterType::kLowPass, 44100);
	
	int result[] = { 1,1,1,1,1,1,1 };
	int input[] = { 1,2,3,4,5,6,7 };
	for (int i = 0; i < 7; i++)
	{
		REQUIRE(result[i] == filter.process(input[i]));
	}
}