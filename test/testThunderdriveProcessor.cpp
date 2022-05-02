#pragma once

#include <fstream>

#include "catch.hpp"
#include "ThunderdriveProcessor.h"
#include "Synthesis.h"
#include "Util.h"

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
		std::ofstream drive1, drive2, drive3, drive4;
		drive1.open("C:/Users/JohnK/Desktop/ECE4803/ThunderdriveModel/data/GeneratedData/drive1.txt");
		drive2.open("C:/Users/JohnK/Desktop/ECE4803/ThunderdriveModel/data/GeneratedData/drive2.txt");
		drive3.open("C:/Users/JohnK/Desktop/ECE4803/ThunderdriveModel/data/GeneratedData/drive3.txt");
		drive4.open("C:/Users/JohnK/Desktop/ECE4803/ThunderdriveModel/data/GeneratedData/drive4.txt");
		REQUIRE(drive1);
		REQUIRE(drive2);
		REQUIRE(drive3);
		REQUIRE(drive4);

		auto print = [](std::ofstream& file, const float* buffer, const int iNumSamples)
		{
			for (int i = 0; i < iNumSamples; i++)
			{
				file << buffer[i] << std::endl;
			}
		};

		CSynthesis::generateSine(inBuffer, 440, 44100, iNumSamples);
		thunderdrive.setParam(ThunderdriveProcessor::Param_t::kGain, 1);

		thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 0);
		thunderdrive.process(outBuffer, inBuffer, iNumSamples);
		print(drive1, outBuffer, iNumSamples);

		thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 0.33);
		thunderdrive.process(outBuffer, inBuffer, iNumSamples);
		print(drive2, outBuffer, iNumSamples);

		thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 0.66);
		thunderdrive.process(outBuffer, inBuffer, iNumSamples);
		print(drive3, outBuffer, iNumSamples);

		thunderdrive.setParam(ThunderdriveProcessor::Param_t::kDrive, 1);
		thunderdrive.process(outBuffer, inBuffer, iNumSamples);
		print(drive4, outBuffer, iNumSamples);

		drive1.close();
		drive2.close();
		drive3.close();
		drive4.close();
	}

	delete[] inBuffer;
	delete[] outBuffer;
	delete[] groundBuffer;

}