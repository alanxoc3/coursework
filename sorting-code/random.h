// Author: Brother Neff

#include <cstdlib>
#include <ctime>

class Random
{
	public:
		/*********************************************************
		 *
		 *    FUNCTION: Random
		 *
		 *  PARAMETERS: None
		 *
		 *     PURPOSE: Random constructor.  Sets the random number
		 *              seed to the current time.  The srand function
		 *              is provided by the cstdlib library and time
		 *              by the ctime library.
		 *
		 *              Passing NULL to the time function returns
		 *              the current time (in clock ticks) and this
		 *              is then passed to the srand function.
		 *
		 *       USAGE: Creates a Random instance (r1) that is used
		 *              to generate random numbers.
		 *              
		 *              Random r1;  
		 *
		 *********************************************************/
		Random()
		{
			srand((int) time(NULL));
		}

		/*********************************************************
		 *
		 *    FUNCTION: nextInt
		 *
		 *  PARAMETERS: low - smallest number in range
		 *              high - largest number in range
		 *
		 *     PURPOSE: This function does the following:
		 *                1. Generate a real number between 0 and 1 
		 *                   by calling rand() and dividing by
		 *                   the constant RAND_MAX + 1
		 *                2. Scale this number to the appropriate range
		 *                   size (high - low)
		 *                3. Truncate the value to an integer
		 *                4. Translate the number to the appropriate
		 *                   starting point.
		 *
		 *        USAGE: Assuming Random object r1 has been created,
		 *               this creates one random number between 1 and 50.
		 *
		 *                  num = r1.nextInt(1, 50);
		 *
		 *********************************************************/
		int nextInt(int low, int high)
		{
			double d  = (double) rand() / ((double) RAND_MAX + 1);
			int k = (int) (d * (high - low + 1));
			return (low + k);
		}
};
