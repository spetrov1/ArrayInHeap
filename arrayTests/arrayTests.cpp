#include "CppUnitTest.h"
#include "../array/array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace arrayTests
{
	TEST_CLASS(EmptyArray)
	{
	private:
		array<int> testArray;

		int capacity;
	public:

		/// testArray is inited with capacity by default (10)
		EmptyArray() : capacity(10), testArray() {}
		
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

		TEST_METHOD(push_back_PushBackToFullArrayExceptionIsExpected) {
			testArray.fill(1);
			try {
				testArray.push_back(1);
				Assert::Fail();
			}
			catch (std::exception) {

			}
		}

	};


	TEST_CLASS(ArrayWithFirstFiveNaturalNumbers) {
	private:
		array<int> testArray;
		size_t capacity = 10; /// capacity to init testArray
	public:
		ArrayWithFirstFiveNaturalNumbers() : testArray(10) {
			for (int i = 0; i <= 4; ++i)
				testArray.push_back(i);
		}

		TEST_METHOD(copyConstructorWorkingAsExpected) {
			array<int> otherArray = testArray;

			Assert::IsTrue(testArray == otherArray);
		}

		TEST_METHOD(operatorEquals_WorkingAsExpected) {
			array<int> otherArray;
			otherArray = testArray;

			Assert::IsTrue(otherArray == testArray);
		}

		TEST_METHOD(fill_maintainsCorrectSize) {
			testArray.fill( rand() );

			Assert::AreEqual(capacity, testArray.size());
		}

		TEST_METHOD(fill_fillWithCorrectElem) {
			int elemToFillWith = rand();
			testArray.fill(elemToFillWith);

			for (int i = 0; i < 9; ++i) {
				if (testArray[i] != elemToFillWith)
					Assert::Fail();
			}
		}

		TEST_METHOD(operatorBrackets_workingAsExpected) {
			for (int i = 0; i <= 4; ++i) {
				if (testArray[i] != i)
					Assert::Fail();
			}
		}

		// TODO operatorBrackets_changing array elem
		// TODO at_changing array elem

		TEST_METHOD(isEmpty_ExpectedNotEmptyArray) {
			Assert::IsFalse(testArray.isEmpty());
		}

		TEST_METHOD(size_ExpectedSizeIsFive) {
			Assert::AreEqual((size_t)5, testArray.size());
		}

		TEST_METHOD(push_back_ExpectedSizeIsSix) {
			testArray.push_back(rand());

			Assert::AreEqual((size_t)6, testArray.size());
		}

		TEST_METHOD(push_back_CorrectElementsAreInArray) {
			testArray.push_back(5);

			for (int i = 0; i <= 5; ++i) {
				if (testArray[i] != i)
					Assert::Fail();
			}
		}

		TEST_METHOD(pop_back_ExpectedSizeIsFour) {
			testArray.pop_back();

			Assert::AreEqual((size_t)4, testArray.size());
		}

		TEST_METHOD(pop_back_CorrectElementsAreLeftInArray) {
			testArray.pop_back(); // testArray = {0, 1 ,2 ,3 }

			for (int i = 0; i <= 3; ++i) {
				if (testArray[i] != i)
					Assert::Fail();
			}
		}

		TEST_METHOD(back_ExpectedFourToBeReturned) {

			Assert::AreEqual(4, testArray.back());
		}

		TEST_METHOD(at_WorkingForAllInsertedElems) {
			for (int i = 0; i <= 4; ++i) {
				if (testArray[i] != i)
					Assert::Fail();
			}
		}

		TEST_METHOD(at_AccessingInvalidPositionsInArrayExceptionIsExpected) {
			for (int i = 5; i < 10; ++i) {
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
