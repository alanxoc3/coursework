// Author: Alan Morgan

#ifndef _BUCKET_SORT_HPP
#define _BUCKET_SORT_HPP

#include <vector>
#include <math.h>
#include "insertionsort.hpp"

namespace morg {
	// BUCKET SORT
	template <typename T>
	void bucketSort(int data[], int num, int min, int max, const T & compare) {
		// STEP 1: SETUP (separation, buckets) & STORE
		// If sep is 1, then this algorithm is very fast, but the lower
		// sep is, the more containers are needed.
		int sep = 1; //(max - min) / 2;
		int len = (int) ceil((float) (max + 1 - min) / (float) sep);

		// Want pointers to vectors so we don't need contiguous memory.
		std::vector<int> ** buckets = new std::vector<int> * [len];
		for(int i = 0; i < len; ++i)
			buckets[i] = new std::vector<int>;

		for (int i = 0; i < num; ++i) {
			int spot = (data[i] - min) / sep;
			buckets[spot]->push_back(data[i]);
		}

		// STEP 2: EXTRACT
		int count = 0;
		for (int i = 0; i < len; ++i)
			for (int j = 0; j < buckets[i]->size(); ++j)
				data[count++] = (*buckets[i])[j];

		// STEP 3: INSERTION SORT
		if (sep != 1)
			insertionSort(data, num, compare);

		// STEP 4: CLEANUP
		for(int i = 0; i < len; ++i)
			delete buckets[i];

		delete [] buckets;
	}
}

#endif // _BUCKET_SORT_HPP
