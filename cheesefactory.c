#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double getpi() {
    long double cele = 3.000000000000000000000000;
    long double desatine = 0.141592653589793238462643;
    long double pi = cele + desatine;
    return pi;
}

long double objem(unsigned int radius) {
    long double pi = getpi();
    long double vysledok = pi * ((4 * powl(radius, 3)) / 3);
    return vysledok;
}

//dettis is used as a reference to calculate the remaining volume
long double reset_objem(int size, unsigned int arr[size][2]) {
    long double zvysok = 0;
    long double dettis = 100000.0 * 100000.0 * 100000.0;
    for (int i = 0; i < size; i++) {
        zvysok += objem(arr[i][0]);
    }
    long double rst = dettis - zvysok;
    return rst;
}

long double recurse(int size, unsigned int arr[size][2], long double min, long double max, long double hoal) {
    long double result = (min + max) / 2;
    long double tis = 100000.0 * 100000.0;
    long double guess = tis * result;
    long double pi = getpi();
    for (int i = 0; i < size; i++) {
        if (result > (arr[i][0] + arr[i][1])) { guess -= objem(arr[i][0]); }
        else if (result >= (arr[i][1] - arr[i][0])) {
            double H = result - arr[i][1];
            guess -= (pi * (powl(arr[i][0], 2) * H - powl(H, 3) / 3.0 + 2.0 / 3.0 * powl(arr[i][0], 3)));
        }
    }
    if (fabsl(hoal - guess) < 0.1) { return result; }
    if (guess < hoal) { return recurse(size, arr, result, max, hoal); }
    else { return recurse(size, arr, min, result, hoal); }
}

int main() {
    int y, cast;
    scanf("%d %d", &y, &cast);
    unsigned int array[y][2];
    for (int i = 0; i < y; i++) {
        int util;
        scanf("%d", &array[i][0]);
        scanf("%d", &util);
        scanf("%d", &util);
        scanf("%d", &array[i][1]);
    }
    long double p = 0;
    long double sobjem = reset_objem(y, array);
    for (int i = 1; i < cast + 1; i++) {
        long double slice = recurse(y, array, 0, 100000, (sobjem / cast) * i);
        printf("%.9Lf\n", (slice - p)/1000.0);
        p = slice;
    }
    return 0;
}

