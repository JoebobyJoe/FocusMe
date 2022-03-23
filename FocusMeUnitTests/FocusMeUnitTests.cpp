#include "pch.h"
#include "CppUnitTest.h"

#include "../FocusMe/src/timeSet.h"
#include <stdio.h>
#include <fstream>

static std::ofstream g_log("log.txt");

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FocusMeUnitTests
{
	/*
	* test all the methods related to time.h
	*/
	TEST_CLASS(FocusMeUnitTestsTime)
	{
	public:
		
		/*
		* test the getTime
		*/
		TEST_METHOD(TimeTestGetTime)
		{
			int hour = 10;
			int min = 30;
			Time time1 = Time();
			Time time2 = Time(hour, min);

			int* getTime = time1.getTime();
			Assert::IsTrue(getTime[0] == 0 && getTime[1] == 0);

			getTime = time2.getTime();
			Assert::IsTrue(getTime[0] == hour && getTime[1] == min);
		}

		/*
		* test the == operator
		*/
		TEST_METHOD(TimeTestBoolEqu)
		{
			int hour = 10;
			int min = 30;
			Time time1 = Time();
			Time time2 = Time();

			Assert::IsTrue(time1 == time2);

			time1 = Time(hour, min);
			Assert::IsFalse(time1 == time2);

			time2 = Time(hour, min);
			Assert::IsTrue(time1 == time2);
		}

		/*
		* test the to_string function
		*/
		TEST_METHOD(TimeTestToString)
		{
			Time time1 = Time();

			Assert::IsTrue(time1.to_string() == "00:00");

			time1 = Time(11, 33);
			Assert::IsTrue(time1.to_string() == "11:33");

			time1 = Time(1, 8);
			Assert::IsTrue(time1.to_string() == "01:08");

			time1 = Time(1, 21);
			Assert::IsTrue(time1.to_string() == "01:21");

			time1 = Time(12, 8);
			Assert::IsTrue(time1.to_string() == "12:08");
		}
	};

	/*
	* test all the methods related to timeSet.h
	*/
	TEST_CLASS(FocusMeUnitTestsTimeSet)
	{
	public:

		/*
		* test the == operator
		*/
		TEST_METHOD(TimeTestBoolEqu)
		{
			int shour = 10;
			int smin = 30;
			int ehour = 2;
			int emin = 45;
			Time time1 = Time(shour, smin);
			Time time2 = Time(ehour, emin);

			TimeSet timeSet1 = TimeSet();
			TimeSet timeSet2 = TimeSet();

			Assert::IsTrue(timeSet1 == timeSet2);

			timeSet2 = TimeSet(time1, time2);
			Assert::IsFalse(timeSet1 == timeSet2);

			timeSet1 = TimeSet(time1, time2);
			Assert::IsTrue(timeSet1 == timeSet2);
		}

		/*
		* test the to_string function
		*/
		TEST_METHOD(TimeTestToString)
		{
			Time time1 = Time();
			Time time2 = Time();

			TimeSet timeSet = TimeSet();

			Assert::IsTrue(timeSet.to_string() == "00:00 - 00:00");

			time1 = Time(11, 33);
			time2 = Time(12, 21);
			timeSet = TimeSet(time1, time2);
			Assert::IsTrue(timeSet.to_string() == "11:33 - 12:21");

			time1 = Time(1, 8);
			time2 = Time(2, 7);
			timeSet = TimeSet(time1, time2);
			Assert::IsTrue(timeSet.to_string() == "01:08 - 02:07");

			time1 = Time(1, 21);
			time2 = Time(2, 44);
			timeSet = TimeSet(time1, time2);
			Assert::IsTrue(timeSet.to_string() == "01:21 - 02:44");

			time1 = Time(12, 8);
			time2 = Time(11, 4);
			timeSet = TimeSet(time1, time2);
			Assert::IsTrue(timeSet.to_string() == "12:08 - 11:04");
		}

		/*
		* test the to_string function and conversion to c string
		*/
		TEST_METHOD(TimeTestToStringToCString)
		{
			Time time1 = Time();
			Time time2 = Time();

			TimeSet timeSet = TimeSet();

			//const char * tmep = timeSet.to_string().c_str();
			//const char* tmep = &(timeSet.to_string()[0]);
			const char* tmep = timeSet.to_string().c_str();
			g_log << "tempvar c string" << tmep << std::endl;

			std::string temp = timeSet.to_string();
			g_log << "tempvar string" << temp << std::endl;

			g_log << "direct c string" << timeSet.to_string().c_str() << std::endl;
			g_log << "direct string" << timeSet.to_string() << std::endl;


			Assert::IsTrue(timeSet.to_string().c_str() == "00:00 - 00:00");

			

			time1 = Time(11, 33);
			time2 = Time(12, 21);
			timeSet = TimeSet(time1, time2);
			Assert::IsTrue(timeSet.to_string().c_str() == "11:33 - 12:21");

			time1 = Time(1, 8);
			time2 = Time(2, 7);
			timeSet = TimeSet(time1, time2);
			Assert::IsTrue(timeSet.to_string().c_str() == "01:08 - 02:07");

			time1 = Time(1, 21);
			time2 = Time(2, 44);
			timeSet = TimeSet(time1, time2);
			Assert::IsTrue(timeSet.to_string().c_str() == "01:21 - 02:44");

			time1 = Time(12, 8);
			time2 = Time(11, 4);
			timeSet = TimeSet(time1, time2);
			Assert::IsTrue(timeSet.to_string().c_str() == "12:08 - 11:04");
		}
	};
}
