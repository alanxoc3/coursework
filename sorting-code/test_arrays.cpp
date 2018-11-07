#include <iostream>
#include <vector>
#include "testinghelper.hpp"

using namespace std;
using namespace morg;

int main() {
	vector<int> array;
	
	createXVector(array, 100, 0, 200, &createOrderedArray);
	displayVector(array, "Ordered:\n ");
	
	createXVector(array, 100, 0, 200, &createReversedArray);
	displayVector(array, "Reversed:\n ");

	createXVector(array, 100, 0, 200, &createRandomArray);
	displayVector(array, "Random:\n ");

	createXVector(array, 100, 0, 200, &createAlmostOrderedArray);
	displayVector(array, "Almost Ordered:\n ");

	createXVector(array, 100, 0, 200, &createAlmostReversedArray);
	displayVector(array, "Almost Reversed:\n ");

/*
	int * array = nullptr;
	
	createOrderedArray(array, 100, 0, 200);
	displayArray(array, 100, "Ordered:\n ");
	
	createReversedArray(array, 100, 0, 200);
	displayArray(array, 100, "Reversed:\n ");

	createRandomArray(array, 100, 0, 200);
	displayArray(array, 100, "Random:\n ");

	createAlmostOrderedArray(array, 100, 0, 200);
	displayArray(array, 100, "Almost Ordered:\n ");

	createAlmostReversedArray(array, 100, 0, 200);
	displayArray(array, 100, "Almost Reversed:\n ");
*/

	return 0;
}
