// Author: Brother Neff and Alan Morgan
#ifndef _INSERTION_SORT_HPP
#define _INSERTION_SORT_HPP

namespace morg {
	// INSERTION SORT
	template <typename T, template <typename> class C>
	void insertionSort(T data[], int num, const C<T> & compare) {
		int tmp, j;
		for (int i = 0; i < num; ++i) {
			j = i;

			while (j > 0 && compare(data[j], data[j - 1])) {
				tmp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = tmp;
				--j;
			}
		}
	}
}

#endif // _INSERTION_SORT_HPP
