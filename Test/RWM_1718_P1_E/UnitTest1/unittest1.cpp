#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\ThomasWasAlone\GameOverScreen.h"
#include "..\ThomasWasAlone\Renderer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	
	TEST_CLASS(UnitTest1)
	{
		

	public:
	
		
		TEST_METHOD(TestMethod)
		{

			Assert::IsTrue(1);
		}

		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(100, 0);
		}
	};
}