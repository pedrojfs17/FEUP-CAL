/*
 * Partioning.cpp
 */

#include "Partitioning.h"


int s_recursive(int n,int k)
{
    if (k == 1)
        return 1;
    else if (k == n)
        return 1;
    else
        return s_recursive(n-1, k-1) + k * s_recursive(n-1, k);
}

int s_dynamic(int n,int k)
{
    int s[k];
    // Initialize the array with 1's
    fill_n(s, k, 1);

    for (int i = 0; i < n - k; i++) {
        for (int j = 1; j < k; j++) {
            s[j] = (j + 1) * s[j] + s[j - 1];
        }
    }

    return s[k - 1];
}


int b_recursive(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; k++)
        sum += s_recursive(n, k);
    return sum;
}

int b_dynamic(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; k++)
        sum += s_dynamic(n, k);
    return sum;
}


