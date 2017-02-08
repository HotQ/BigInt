#include "stdafx.h"
#include "CppUnitTest.h"
#include "Integer.h"
#include "test_config.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(Arithmetic)
	{
	public:

		TEST_METHOD(Arithmetic_Times_Integer_IntegerR_IntegerR)
		{
			Integer z("0x707fffff03"), l("0xff70207fffff02");
			testIntS(Times(z, l), "34740628695596179551592446726")

			Logger::WriteMessage("What's up,Test?");
		}

	};
}