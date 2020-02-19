/*
 * Change.cpp
 */

#include "Change.h"

/* ALINEA A
 * Ir dividindo o montante pela maior moeda, guarda-se o número de moedas desse tipo e fica-se com o resto.
 */

/* ALINEA B
 * Slide 12 - Formulação recursiva - Programação Dinamica
 */

/* ALINEA C
 *      i   |   k           0   1   2   3   4   5   6   7   8   9
 *          |
 *      0   |   minCoins    0   0   0   0   0   0   0   0   0   0
 *          |   lastCoin    0   0   0   0   0   0   0   0   0   0
 *          |
 *      1   |   minCoins    0   1   2   3   4   5   6   7   8   9
 *          |   lastCoin    0   1   1   1   1   1   1   1   1   1
 *          |
 *      2   |   minCoins    0   1   1   2   2   3   3   4   4   5
 *          |   lastCoin    0   1   2   1   2   1   2   1   2   1
 *          |
 *      3   |   minCoins    0   1   1   2   2   1   2   2   3   3
 *          |   lastCoin    0   1   2   1   2   5   1   2   1   2
 */


string calcChange(int m, int numCoins, int *coinValues)
{
    if (m == 0)
        return "";

    int minCoins[m + 1];
    int lastCoin[m + 1];

    fill_n(minCoins, m+1, 0);
    fill_n(lastCoin, m+1, 0);

    for (int i = 1; i <= numCoins; i++ ) {
        for (int k = coinValues[i-1]; k <= m; k++) {
            if (minCoins[k] == 0 || 1 + minCoins[k - coinValues[i-1]] < minCoins[k]) {
                minCoins[k] = 1 + minCoins[k - coinValues[i-1]];
                lastCoin[k] = coinValues[i - 1];
            }
        }
    }

    string output = "";
    int temp = m;

    if (minCoins[m] == 0)
        return "-";

    for (int i = 0; i < minCoins[m]; i++) {
        output += to_string(lastCoin[temp]) + ";";
        temp -= lastCoin[temp];
    }

    return output;
}



