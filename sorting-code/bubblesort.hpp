// Author: Brother Neff and Alan Morgan

#ifndef _BUBBLE_SORT_HPP
#define _BUBBLE_SORT_HPP

#include "compare.h"

namespace morg {
	// BUBBLE SORT
	void bubbleSort(int data[], int n) {
		bool notsorted = true;
		int temp;
		int i;

		while (notsorted)
		{
			notsorted = false;
			for (i = 0; i < n; ++i)
			{
				if (slowCompare(data[i+1], data[i]))
				{
					temp = data[i];
					data[i] = data[i + 1];
					data[i + 1] = temp;
					notsorted = true;
				}
			}
		}
	}
}

#endif // _BUBBLE_SORT_HPP
