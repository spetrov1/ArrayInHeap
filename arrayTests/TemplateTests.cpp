
// ASK if the following line is ok
// #pragma once


#include "../array/array.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


// ASK why not working CONCAT as expected when CONCAT(a, b) a ## b
#define CONCAT2(a, b) a ## b
#define CONCAT(a, b) CONCAT2(a, b)


// TESTs FOR ALL THE TYPES
TEST_CLASS(CONCAT(TYPE_TO_TEST, _EmptyArray))
{
private:
	array<TYPE_TO_TEST> testArray;

	int capacity;
public:

	/// testArray is inited with capacity by default (10)
	CONCAT(TYPE_TO_TEST, _EmptyArray)() : capacity(10), testArray() {}



	TEST_METHOD(CONCAT(
		TYPE_TO_TEST, _size_ExpectedSizeIsZero))
	{
		Assert::AreEqual(testArray.size(), (size_t)0);
	}



	TEST_METHOD(CONCAT(
		TYPE_TO_TEST, _empty_ExpectedEmptyArray)) {
		Assert::IsTrue(testArray.isEmpty());
	}



	TEST_METHOD(CONCAT(
		TYPE_TO_TEST, _fill_FillArrayExpectedSizeIs10)) {
		testArray.fill(1);

		Assert::AreEqual((size_t)capacity, testArray.size());
	}



	TEST_METHOD( CONCAT(
		TYPE_TO_TEST, _operatorEquality_CompareObjectsWithJustDifferentCapacityExpectedTrue) ) {
		int otherCapacity = 100;
		array<TYPE_TO_TEST> otherArray(otherCapacity);

		Assert::IsTrue(testArray == otherArray);
	}



	TEST_METHOD( CONCAT(
		TYPE_TO_TEST, _copyConstructor_WorkingAsExpected) ) {
		array<TYPE_TO_TEST> otherArray = testArray;

		Assert::IsTrue(testArray == otherArray);
	}



	TEST_METHOD( CONCAT(
		TYPE_TO_TEST, _operatorEquals_WorkingAsExpected) ) {
		array<TYPE_TO_TEST> otherArray;
		otherArray = testArray;

		Assert::IsTrue(otherArray == testArray);
	}



	TEST_METHOD( CONCAT(
		TYPE_TO_TEST, _operatorEquality_CompareToSameTestArrayExpectedTrue) ) {
		Assert::IsTrue(testArray == testArray);
	}



	TEST_METHOD( CONCAT(
		TYPE_TO_TEST, _pop_back_invokingPopBackOnEmptyArrayExceptionIsExpected) ) {
		try {
			testArray.pop_back();
			Assert::Fail();
		}
		catch (std::exception) {

		}
	}



	TEST_METHOD( CONCAT(
		TYPE_TO_TEST, _back_invokingBackOnEmptyArrayExceptionIsExpected) ) {
		try {
			testArray.back();
			Assert::Fail();
		}
		catch (std::exception) {

		}
	}



	TEST_METHOD( CONCAT(
			TYPE_TO_TEST, _at_invokingAtOnEmptyExceptionOutOfRangeIsExpected) ) {
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




