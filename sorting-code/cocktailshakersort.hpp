// Author: Alan Morgan

#ifndef _COCKTAIL_SHAKER_SORT_HPP
#define _COCKTAIL_SHAKER_SORT_HPP

namespace morg {
	// COCKTAIL SHAKER SORT
	template <typename T, template <typename> class C>
	void cocktailShakerSort(T data[], int n, const C<T> & compare) {
		// Start and end.
		T tmp;
		int beg = 0;
		int end = n - 1;
		int inc = beg;
		int sign = 1;
		int noneCount = n;

		while (end != beg) {
			if (compare(data[inc+1], data[inc]))
			{
				--noneCount;
				tmp = data[inc];
				data[inc] = data[inc + 1];
				data[inc + 1] = tmp;
			}

			inc += sign;
			if (inc == end) {
				if (noneCount == end - beg)
					break;

				sign = -1;
				--end;
				--inc;

				noneCount = end - beg;
			} else if (inc == beg - 1) {
				if (noneCount == end - beg)
					break;

				sign = 1;
				++beg;
				++inc;

				noneCount = end - beg;
			}
		}
	}
}

#endif // _COCKTAIL_SHAKER_SORT_HPP
