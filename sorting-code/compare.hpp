// Author: Alan Morgan
#ifndef _COMPARE_HPP
#define _COMPARE_HPP

#define LOOP_LIMIT 1000

namespace morg {
	bool slowCompare(int a, int b) {
		// change the loop limit up or down...
		for (int i = 0; i < LOOP_LIMIT; i++);
		return (a < b);
	}

	// A wonderful FUNCTOR :)
	template <typename T>
		struct CompareLoop {
			CompareLoop(int loopLimit) { this -> loopLimit = loopLimit; };
			inline bool operator() (T a, T b) const {
				for (int i = 0; i < loopLimit; i++);
				return (a < b);
			}

			private:
			int loopLimit;
		};
}

#endif // _COMPARE_HPP
