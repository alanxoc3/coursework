#ifndef _QUICK_SORT_HPP
#define _QUICK_SORT_HPP

#include "compare.hpp"

namespace morg {
	// QUICK SORT
	template<typename C>
		void quicksort(int data[], int left, int right, C compare) {
			int i;
			int j;
			int pivot;
			int temp;

			if (left <= right)
			{
				pivot = data[(left + right) / 2];

				i = left;
				j = right;

				do
				{
					while (compare(data[i], pivot))
						i++;

					while (compare(pivot, data[j]))
						j--;

					if (i <= j)
					{
						temp = data[i];
						data[i] = data[j];
						data[j] = temp;
						i++;
						j--;
					}
				} while (i < j);

				quicksort(data, left, j,     compare);
				quicksort(data, i,    right, compare);
			}
		}
}

#endif // _QUICK_SORT_HPP
