// Author: Alan Morgan
// test_algs.cpp

#include <iostream>
#include <cstring>
#include "sorts.hpp"
#include "testinghelper.hpp"
#include "compare.hpp"

using namespace std;
using namespace morg;

int main(int argc, char ** argv)
{
	enum {
		PIPE      = 1,
		TIM       = 2,
		QUICK     = 4,
		INSERTION = 8,
		COCKTAIL  = 16,
		BUCKET    = 32,
		BUBBLE    = 64
	};

	int min = 0, max = 1000, comp = 0, start = 10000, end = 50000, inc = 5000;
	int options = 0;

	// For piping the input.
	for (int i = 1; i < argc; ++i) {
		for (char * ptr = argv[i]; *ptr; ++ptr) *ptr = tolower(*ptr);
		if (!strcmp(argv[i], "-p")) options = options | PIPE;
		else if (!strcmp(argv[i], "tim")) options = options | TIM;
		else if (!strcmp(argv[i], "quick")) options = options | QUICK;
		else if (!strcmp(argv[i], "insertion")) options = options | INSERTION;
		else if (!strcmp(argv[i], "cocktail")) options = options | COCKTAIL;
		else if (!strcmp(argv[i], "bucket")) options = options | BUCKET;
		else if (!strcmp(argv[i], "bubble")) options = options | BUBBLE;
	}

	if (options & PIPE) {
		cin >> min;
		cin >> max;
		cin >> comp;
	} else {
		cout << "Welcome Bro Neff, or TA, to the sorting algorithm tester program.\n";
		min =  promptVal("MIN NUM: ", "Sorry, enter a real number: ");
		max =  promptVal("MAX NUM: ", "Hey, grader!!! Give me a real number: ");
		comp = promptVal("CMP NUM: ", "I said I wanted a number bro! Try again: ");
	}

	cout << "MIN: " << min << endl;
	cout << "MAX: " << max << endl;
	cout << "CMP: " << comp << endl;

	if (options & TIM) {
		cout << endl;
		testCombos(start, end, inc, min, max, comp, &testTim,       "TIM SORT");
	}
	if (options & QUICK) {
		cout << endl;
		testCombos(start, end, inc, min, max, comp, &testQuick,     "QUICK SORT");
	}
	if (options & INSERTION) {
		cout << endl;
		testCombos(start, end, inc, min, max, comp, &testInsertion,  "INSERTION SORT");
	}
	if (options & COCKTAIL) {
		cout << endl;
		testCombos(start, end, inc, min, max, comp, &testCocktail,  "COCKTAIL SORT");
	}
	if (options & BUCKET) {
		cout << endl;
		testCombos(start, end, inc, min, max, comp, &testBucket,    "BUCKET SORT");
	}
	cout << endl;

	return 0;
}
