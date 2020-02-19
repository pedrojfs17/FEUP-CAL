/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
	if (n <= 1)
	    return 1;
	else
	    return n * factorialRecurs(n - 1);

}

int factorialDinam(int n)
{
    int fact = 1;

    while (n > 1) {
        fact *= n;
        n--;
    }

    return fact;
}
