#include "CppUnitTest.h"
#include "../array/array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	

	#define TYPE_TO_TEST int
	#include "TemplateTests.h"
	#undef TYPE_TO_TEST

	#define TYPE_TO_TEST float
	#include "TemplateTests.h"
	#undef TYPE_TO_TEST

	#define TYPE_TO_TEST bool
	#include "TemplateTests.h"
	#undef TYPE_TO_TEST
	
	

	TEST_CLASS(INT_ArrayWithFirstFiveNaturalNumbers) {
	private:
		array<int> testArray;

		size_t capacity = 10; /// capacity to init testArray

	public:

		INT_ArrayWithFirstFiveNaturalNumbers() : testArray(10) {
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
	
	
	
	TEST_CLASS(INT_EmptyArrayAdditionalTests)
	{
	private:
		array<int> testArray;

		int capacity;
	public:

		/// testArray is inited with capacity by default (10)
		INT_EmptyArrayAdditionalTests() : capacity(10), testArray() {}



		TEST_METHOD(fill_MaintainsCorrectElementsInserted) {
			int elemToFillWith = 6;
			testArray.fill(elemToFillWith);

			for (int i = 0; i < capacity; ++i) {
				if (testArray[i] != elemToFillWith)
					Assert::Fail();
			}
		}


		
		TEST_METHOD(operatorEquality_CompareDifferentObjectsExpectedFalse) {
			array<int> otherArray;
			otherArray.fill(1);

			Assert::IsFalse(testArray == otherArray);
		}


		
		TEST_METHOD(operatorEquals_NoSpaceInArrayForOtherArrayElemsExpectedException) {
			array<int> otherArray(12);
			otherArray.fill(1.0);

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

	};


	
	TEST_CLASS(BOOL_EmptyArrayAdditinalTests) {
	private:
		array<bool> testArray; // default inited with capacity = 10

		int capacity = 10;

	public:

		TEST_METHOD(push_back_ExpectedSizeIsOne) {
			testArray.push_back(true);

			Assert::AreEqual((size_t)1, testArray.size());
		}


		TEST_METHOD(push_back_ExpectedValueIsInArray) {
			testArray.push_back(true);

			Assert::AreEqual(true, (bool)testArray[0]);
		}




	};



	TEST_CLASS(BOOL_NotEmptyArrayAdditionalTests) {

	private:
		array<bool> testArray; /// Array used for testing

		int capacity; /// Capacity of the array using for testing

	public:

		/// testArray default inited with capacity = 10
		BOOL_NotEmptyArrayAdditionalTests() : capacity(10), testArray() {
			for (int i = 0; i < 9; ++i) {
				if (i % 2 == 0)
					testArray.push_back(true);
				else
					testArray.push_back(false);
			}

		}

		TEST_METHOD(size_ExpectedSizeIs9) {
			Assert::AreEqual((size_t)9, testArray.size());
		}

		TEST_METHOD(empty_ExpectedNotEmpty) {
			Assert::IsFalse(testArray.isEmpty());
		}

		TEST_METHOD(operatorBrackets_ChangingValueOfArrayElement) {
			// testArray[0] true until now
			testArray[0] = false;

			Assert::IsFalse(testArray[0]);
		}



		TEST_METHOD(push_back_ExpectedSizeIs10) {
			testArray.push_back(true);
			Assert::AreEqual((size_t)10, testArray.size());
		}


		TEST_METHOD(push_back_CorrectElemIsInArray) {
			testArray.push_back(true);
			Assert::AreEqual(true, (bool)testArray.back());
		}


		TEST_METHOD(pop_back_ExpectedSizeIsEight) {
			testArray.pop_back();

			Assert::AreEqual((size_t)8, testArray.size());
		}


		TEST_METHOD(pop_back_ExpectedElementIsReturned) {
			bool expectedValue = true;
			
			Assert::AreEqual(expectedValue, (bool)testArray.pop_back());
		}


		TEST_METHOD(back_ExpectedElemIsReturned) {
			bool expectedValue = true;

			Assert::AreEqual(expectedValue, (bool)testArray.back());
		}


		TEST_METHOD(back_ChangeValueByReturnedReferenceExpectedFalse) {
			testArray.back() = false;

			Assert::AreEqual(false, (bool)testArray.back());
		}
		TEST_METHOD(back_ChangeValueByReturnedReferenceExpectedTrue) {
			testArray.back() = true;

			Assert::AreEqual(true, (bool)testArray.back());
		}

	};



	// TODO Tests when array isFull
