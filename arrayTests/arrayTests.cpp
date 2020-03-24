#include "CppUnitTest.h"
#include "../array/array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace arrayTests
{
	TEST_CLASS(EmptyArrayTests)
	{
	private:
		array<int> array;
	public:
		
		TEST_METHOD(ExpectedSizeIsZero)
		{
			Assert::AreEqual(array.size(), (size_t)0);
		}

		TEST_METHOD(ExpectedEmptyArray) {
			Assert::IsTrue(array.isEmpty());
		}

		

	};
}
