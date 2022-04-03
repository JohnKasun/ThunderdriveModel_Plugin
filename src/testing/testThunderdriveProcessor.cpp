#pragma once

#include "catch.hpp"
#include "../src/ThunderdriveProcessor.h"
#include "Synthesis.h"
#include "Util.h"
#include <fstream>

void CHECK_ARRAY_CLOSE(float* buffer1, float* buffer2, int iNumSamples, float tolerance = 0)
{
	for (int i = 0; i < iNumSamples; i++)
	{
		float diff = abs(buffer1[i] - buffer2[i]);
		REQUIRE(diff <= tolerance);
	}
}

TEST_CASE("Parameter Setting", "[Thunderdrive]")
{
	ThunderdriveProcessor thunderdrive;

	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 0.0f) == Error_t::kNoError);
	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kGain, 0.0f) == Error_t::kNoError);
	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 1.0f) == Error_t::kNoError);
	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kGain, 1.0f) == Error_t::kNoError);
	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 0.5f) == Error_t::kNoError);
	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kGain, 0.5f) == Error_t::kNoError);

	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 2.0f) == Error_t::kFunctionInvalidArgsError);
	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kGain, 6.0f) == Error_t::kFunctionInvalidArgsError);
	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, -1.5f) == Error_t::kFunctionInvalidArgsError);
	REQUIRE(thunderdrive.setParam(ThunderdriveProcessor::Param_t::kGain, -345.5f) == Error_t::kFunctionInvalidArgsError);

	REQUIRE(thunderdrive.getParam(ThunderdriveProcessor::Param_t::kDrive) == 0.5f);
	REQUIRE(thunderdrive.getParam(ThunderdriveProcessor::Param_t::kGain) == 0.5f);

}

TEST_CASE("Processes Correctly", "[Thunderdrive]")
{
	ThunderdriveProcessor thunderdrive;

	int iNumSamples = 1000;
	float* inBuffer = new float[iNumSamples];
	float* outBuffer = new float[iNumSamples];
	float* groundBuffer = new float[iNumSamples];

	SECTION("Zero Input")
	{
		CSynthesis::generateDc(groundBuffer, iNumSamples, 0);
		CSynthesis::generateDc(inBuffer, iNumSamples, 0);

		thunderdrive.process(outBuffer, inBuffer, iNumSamples);

		CHECK_ARRAY_CLOSE(outBuffer, groundBuffer, iNumSamples, 0);
	}

	SECTION("Below-Threshold Input Stays Unchanged")
	{

		thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 0);
		thunderdrive.setParam(ThunderdriveProcessor::Param_t::kGain, 1);

		CSynthesis::generateDc(groundBuffer, iNumSamples, 0.5);
		CSynthesis::generateDc(inBuffer, iNumSamples, 0.5);

		thunderdrive.process(outBuffer, inBuffer, iNumSamples);

		CHECK_ARRAY_CLOSE(outBuffer, groundBuffer, iNumSamples, 0);
	}

	SECTION("Print Sinusoid")
	{
		thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 1);
		thunderdrive.setParam(ThunderdriveProcessor::Param_t::kGain, 1);

		CSynthesis::generateSine(inBuffer, 440, 44100, iNumSamples);
		thunderdrive.process(outBuffer, inBuffer, iNumSamples);

		std::ofstream out_file;
		out_file.open("C:/Users/JohnK/Desktop/out.txt");
		REQUIRE(out_file);

		for (int i = 0; i < iNumSamples; i++)
		{
			out_file << outBuffer[i] << std::endl;
		}

		out_file.close();
	}

	delete[] inBuffer;
	delete[] outBuffer;
	delete[] groundBuffer;

}