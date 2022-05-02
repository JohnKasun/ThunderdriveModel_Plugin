#pragma once

#include "catch.hpp"
#include "SimpleFilterIf.h"

void CHECK_ARRAY_CLOSE1(float* buffer1, float* buffer2, int iNumSamples, float tolerance = 0)
{
	for (int i = 0; i < iNumSamples; i++)
	{
		float diff = abs(buffer1[i] - buffer2[i]);
		REQUIRE(diff <= tolerance);
	}
}

TEST_CASE("Init and Reset", "[SimpleFilter]")
{
	SimpleFilterIf simpleFilter;

	REQUIRE(simpleFilter.getFilterType() == SimpleFilterIf::FilterType::kUninitialized);
	REQUIRE(simpleFilter.setParam(SimpleFilterIf::FilterParam::kCutoff, 100) == Error_t::kMemError);
	REQUIRE(simpleFilter.getParam(SimpleFilterIf::FilterParam::kCutoff) == 0);
	REQUIRE(simpleFilter.reset() == Error_t::kMemError);

	REQUIRE(simpleFilter.init(SimpleFilterIf::FilterType::kLowPass, 44100) == Error_t::kNoError);

	REQUIRE(simpleFilter.init(SimpleFilterIf::FilterType::kHighPass, 44100) == Error_t::kMemError);

	REQUIRE(simpleFilter.getFilterType() == SimpleFilterIf::FilterType::kLowPass);
	
	REQUIRE(simpleFilter.reset() == Error_t::kNoError);
}

TEST_CASE("LowPass Output", "[SimpleFilter]")
{
	SimpleFilterIf filter;

	filter.init(SimpleFilterIf::FilterType::kLowPass, 44100);
	filter.setParam(SimpleFilterIf::FilterParam::kCutoff, 20000);
	
	float result[] = { 1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f };
	float input[] = { 1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f };
	for (int i = 0; i < 7; i++)
	{
		float val = input[i];
		filter.process(val);
		input[i] = val;
	}
	CHECK_ARRAY_CLOSE1(result, input, 7, 0);
}