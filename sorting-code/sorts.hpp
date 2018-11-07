#ifndef _SORTS_HPP
#define _SORTS_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include "testinghelper.hpp"
#include "compare.hpp"
#include "timsort.hpp"
#include "quicksort.hpp"
#include "cocktailshakersort.hpp"
#include "bucketsort.hpp"
#include "insertionsort.hpp"

namespace morg {
	typedef clock_t (*TestSort) (int * &, int, int, int, int);

	clock_t testInsertion(int * & arr, int size, int min, int max, int comp) {
		clock_t start;
		clock_t finish;

		start  = clock();
		insertionSort(arr, size, CompareLoop<int>(comp));
		finish = clock();

		return finish - start;
	}

	clock_t testCocktail(int * & arr, int size, int min, int max, int comp) {
		clock_t start;
		clock_t finish;

		start  = clock();
		cocktailShakerSort(arr, size, CompareLoop<int>(comp));
		finish = clock();

		return finish - start;
	}

	clock_t testBucket(int * & arr, int size, int min, int max, int comp) {
		clock_t start;
		clock_t finish;

		start  = clock();
		bucketSort(arr, size, min, max, CompareLoop<int>(comp));
		finish = clock();

		return finish - start;
	}

	clock_t testQuick(int * & arr, int size, int min, int max, int comp) {
		clock_t start;
		clock_t finish;

		start  = clock();
		quicksort(arr, 0, size - 1, CompareLoop<int>(comp));
		finish = clock();

		return finish - start;
	}

	clock_t testTim(int * & arr, int size, int min, int max, int comp) {
		// Copy to vector.
		std::vector<int> array;
		for (int i = 0; i < size; ++i) array.push_back( arr[i] );

		clock_t start;
		clock_t finish;

		start  = clock();
		gfx::timsort(array.begin(), array.end(), CompareLoop<int>(comp));
		finish = clock();

		for (int i = 0; i < size; ++i) arr[i] = array[i];

		return finish - start;
	}

	// A way to use the above algorithms
	void testAlgorithms(int beginLen, int endLen, int inc, int min, int max, int comp, TestSort testSort, ArrayCreation arrayCreation) {
		int * array = NULL;

		for (int size = beginLen; size <= endLen; size+= inc)
		{
			arrayCreation(array, size, min, max);
		
			std::cout << "| ";
			displayTime(testSort(array, size, min, max, comp));
			std::cout << " ";

			deallocArray(array);
		}

		std::cout << "|" << std::endl;
	}

	void testCombos(int beginLen, int endLen, int inc, int min, int max, int comp, TestSort testSort, const char * name) {
		std::cout << name << " table\n";
		
		std::cout << "| starting array  ";
		for (int size = beginLen; size <= endLen; size+= inc) std::cout << "| " << std::setw(TIME_WIDTH) << size << " ";
		std::cout << "|\n";
		std::cout << "|-----------------";
		for (int size = beginLen; size <= endLen; size+= inc) std::cout << "+----------";
		std::cout << "|\n";

		std::cout << "| random          "; testAlgorithms(beginLen, endLen, inc, min, max, comp, testSort, &createRandomArray);
		std::cout << "| ordered         "; testAlgorithms(beginLen, endLen, inc, min, max, comp, testSort, &createOrderedArray);
		std::cout << "| reversed        "; testAlgorithms(beginLen, endLen, inc, min, max, comp, testSort, &createReversedArray);
		std::cout << "| almost ordered  "; testAlgorithms(beginLen, endLen, inc, min, max, comp, testSort, &createAlmostOrderedArray);
		std::cout << "| almost reversed "; testAlgorithms(beginLen, endLen, inc, min, max, comp, testSort, &createAlmostReversedArray);
	}
}

#endif // _SORTS_HPP
