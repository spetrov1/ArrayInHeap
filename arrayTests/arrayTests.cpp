#include "CppUnitTest.h"
#include "../array/array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace arrayTests
{
	TEST_CLASS(EmptyArrayTests)
	{
	private:
		array<int> testArray;

		int capacity;
	public:

		/// testArray is inited with capacity by default
		EmptyArrayTests() : capacity(10), testArray() {}
		
		TEST_METHOD(size_ExpectedSizeIsZero)
		{
			Assert::AreEqual(testArray.size(), (size_t)0);
		}

		TEST_METHOD(empty_ExpectedEmptyArray) {
			Assert::IsTrue(testArray.isEmpty());
		}

		TEST_METHOD(fill_FillArrayExpectedSizeIs10) {
			testArray.fill(1);

			Assert::AreEqual((size_t)capacity, testArray.size());
		}

		TEST_METHOD(fill_MaintainsCorrectElementsInserted) {
			int elemToFillWith = 6;
			testArray.fill(elemToFillWith);

			for (int i = 0; i < capacity; ++i) {
				if (testArray[i] != elemToFillWith)
					Assert::Fail();
			}
		}

		TEST_METHOD(operatorEquality_CompareToSameTestArrayExpectedTrue) {
			Assert::IsTrue(testArray == testArray);
		}

		TEST_METHOD(operatorEquality_CompareDifferentObjectsExpectedFalse) {
			array<int> otherArray;
			otherArray.fill(1);

			Assert::IsFalse(testArray == otherArray);
		}

		TEST_METHOD(operatorEquality_CompareObjectsWithJustDifferentCapacityExpectedTrue) {
			int otherCapacity = 100;
			array<int> otherArray(otherCapacity);

			Assert::IsTrue(testArray == otherArray);
		}
	
		TEST_METHOD(copyConstructor_WorkingAsExpected) {
			array<int> otherArray = testArray;

			Assert::IsTrue(testArray == otherArray);
		}
	
		TEST_METHOD(operatorEquals_WorkingAsExpected) {
			array<int> otherArray;
			otherArray = testArray;

			Assert::IsTrue(otherArray == testArray);
		}

		TEST_METHOD(operatorEquals_NoSpaceInArrayForOtherArrayElemsExpectedException) {
			array<int> otherArray(12);
			otherArray.fill(1);

			try {
				testArray = otherArray;
				Assert::Fail();
			}
			catch (std::exception) {
				
			}

		}


		// ? Following two methods to be in one test method ?
		TEST_METHOD(push_back_afterPushBackExpectedSizeIsOne) {
			testArray.push_back(rand());

			Assert::AreEqual((size_t)1, testArray.size());
		}

		TEST_METHOD(push_back_afterPushBackCorrectElementIsInserted) {
			int newElem = rand();
			testArray.push_back(newElem);

			Assert::AreEqual(newElem, testArray[0]);
		}

		TEST_METHOD(pop_back_invokingPopBackOnEmptyArrayExceptionIsExpected) {
			try {
				testArray.pop_back();
				Assert::Fail();
			}
			catch (std::exception) {

			}
		}

		TEST_METHOD(back_invokingBackOnEmptyArrayExceptionIsExpected) {
			try {
				testArray.back();
				Assert::Fail();
			}
			catch (std::exception) {

			}
		}

		TEST_METHOD(at_invokingAtOnEmptyExceptionOutOfRangeIsExpected) {
			for (int i = 0; i < 10; ++i) {
				try {
					testArray.at(i);
					Assert::Fail();
				}
				catch (std::out_of_range) {

				}
			}
		}



	};


	
}
