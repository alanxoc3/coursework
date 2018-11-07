#ifndef _TESTING_HELPER_HPP
#define _TESTING_HELPER_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include "random.h"

#define MIX_PERCENTAGE 10
#define TIME_PRECISION 5
#define TIME_WIDTH 8

namespace morg {
	typedef void (*ArrayCreation) (int * &, int, int, int);

	void displayTime(const clock_t & sortTime);
	void deallocArray(int * & array);
	void createAlmostReversedArray(int * & array, int size, int min, int max);
	void createAlmostOrderedArray(int * & array, int size, int min, int max);
	void createOrderedArray(int * & array, int size, int min, int max);
	void createReversedArray(int * & array, int size, int min, int max);
	void createRandomArray(int * & array, int size, int min, int max);
	void createXVector(std::vector<int> & array, int size, int min, int max,
			ArrayCreation arrayCreation);
	void displayVector(std::vector<int> data, char const * text);
	void displayArray(int * data, int num, char const * text);
	int promptVal(char const * text, char const * badText);

	int promptVal(char const * text, char const * badText) {
		int val;
		std::cout << text;
		std::cin >> val;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(256,'\n');
			return promptVal(badText, badText);
		}

		return val;
	}

	void displayArray(int * data, int num, char const * text) {
		std::cerr << text;
		for (int i = 0; i < num; ++i)
			std::cerr << data[i] << ((i == num - 1) ? "\n" : " ");
		std::cerr << std::endl;
	}

	void displayVector(std::vector<int> data, char const * text) {
		std::cerr << text;
		for (int i = 0; i < data.size(); ++i)
			std::cerr << data[i] << ((i == data.size() - 1) ? "\n" : " ");
		std::cerr << std::endl;
	}

// VECTOR
	void createXVector(std::vector<int> & array, int size, int min, int max,
			ArrayCreation arrayCreation) {
		int * arr = NULL;
		arrayCreation(arr, size, min, max);
		array.clear();
		for (int i = 0; i < size; ++i)
			array.push_back(arr[i]);
		deallocArray(arr);
	}

// RANDOM
	void createRandomArray(int * & array, int size, int min, int max) {
		Random r;
		array = new int[size];
		for (int i = 0; i < size; ++i)
			array[i] = r.nextInt(min, max);
	}

// REVERSE
	void createReversedArray(int * & array, int size, int min, int max) {
		array = new int[size];
		for (int i = 0; i < size; ++i)
			array[i] = (1.0f - (float) i / (float) size) * (max + min) - min;
	}

// ORDERED
	void createOrderedArray(int * & array, int size, int min, int max) {
		array = new int[size];
		for (int i = 0; i < size; ++i)
			array[i] = ((float) i / (float) size) * (max + min) - min;
	}

// ALMOST ORDERED
	void createAlmostOrderedArray(int * & array, int size, int min, int max) {
		createOrderedArray(array, size, min, max);

		Random r;
		int spot1 = 0;
		int spot2 = 0;
		int tmpNum = 0;
		int numOfTimes = size / MIX_PERCENTAGE;
		if (!numOfTimes) numOfTimes = 1;

		for (int i = 0; i < numOfTimes; ++i) {
			spot1 = r.nextInt(0, size - 1);
			spot2 = r.nextInt(0, size - 1);
			tmpNum = array[spot1];
			array[spot1] = array[spot2];
			array[spot2] = tmpNum;
		}
	}

// ALMOST REVERSED
	void createAlmostReversedArray(int * & array, int size, int min, int max) {
		createReversedArray(array, size, min, max);

		Random r;
		int spot1 = 0;
		int spot2 = 0;
		int tmpNum = 0;
		int numOfTimes = size / MIX_PERCENTAGE;

		for (int i = 0; i < numOfTimes; ++i) {
			spot1 = r.nextInt(0, size - 1);
			spot2 = r.nextInt(0, size - 1);
			tmpNum = array[spot1];
			array[spot1] = array[spot2];
			array[spot2] = tmpNum;
		}
	}

	void displayTime(const clock_t & sortTime) {
		std::cout << std::fixed << std::setprecision(TIME_PRECISION) <<
			std::setw(TIME_WIDTH) <<
			sortTime / (double) CLOCKS_PER_SEC;
	}

	void deallocArray(int * & array) {
		delete [] array;
		array = NULL;
	}
}

#endif // _TESTING_HELPER_HPP
