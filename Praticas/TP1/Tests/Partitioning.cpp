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

    for (int i = 1; i <= k; i++) {
        for (int j = i; j <= n - k; j++) {
            s[j] += s[j-1];
            cout << "s[j] = " << s[j] << endl;
        }
    }

    return s[n - k];
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
        sum += s_recursive(n, k);
    return sum;
}


