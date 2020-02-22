/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>

string calcSum(int* sequence, int size)
{
    string output = "";

    int sum[size];
    fill_n(sum, size, 999);
    int min, minIndex;

    for (int m = 1; m <= size; m++) {
        min = 9999;
        // Calcular as somas
        for (int i = 0; i <= size - m; i++) {
            if (m == 1)
                sum[i] = sequence[i + m - 1];
            else
                sum[i] = sum[i] + sequence[i + m - 1];
            if (sum[i] < min) {
                min = sum[i];
                minIndex = i;
            }
        }

        output += to_string(sum[minIndex]) + "," + to_string(minIndex) + ";";
    }

    return output;
}

