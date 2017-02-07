#include "stdafx.h"
#include "CppUnitTest.h"
#include "Integer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Integer_TimesF_IntegerR_IntegerR)
		{
			Integer z("0x707fffff03"), l("0xff70207fffff02"),result("34740628695596179551592446726");
			bool a = (Times(z, l) == result);
			Assert::AreEqual(a, true);
			Logger::WriteMessage("What's up,Test?");
		}

	};
}