#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\ThomasWasAlone\Portal.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
		//Portal p;
	public:

		TEST_METHOD(TestMethod)
		{
			Assert::AreEqual(100, 100);
		}
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(100, 0);
		}
	};
}