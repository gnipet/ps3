#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Výpočet objemu gule- vstup ej polomer vystup je objem 
long double objem(unsigned int radius) {
    long double vysledok = M_PI * ((4 * powl(radius, 3)) / 3); //powl je na výpočet tretej mocniny
    return vysledok;					
}

//dettis is used as a reference to calculate the remaining volume
long double reset_objem(int size, unsigned int arr[size][2]) {
    long double zvysok = 0;
    long double dettis = 100000.0 * 100000.0 * 100000.0;							// celkový objem syra
    for (int i = 0; i < size; i++) {
        zvysok += objem(arr[i][0]);										// sčítanie objemov všetkých dier
    }
    long double rst = dettis - zvysok;										// zvyšný objem syra po odčítaní dier
    return rst;
}


// Rekurzívne hľadanie optimálnych plátkov
// Vstupy:
// size → počet dier
// arr → súradnice dier
// min, max → rozsah binárneho vyhľadávania
// hoal → cieľový objem rezu
long double recurse(int size, unsigned int arr[size][2], long double min, long double max, long double hoal) {
    long double result = (min + max) / 2;									// stredná hodnota pre binárne vyhľadávanie
    long double tis = 100000.0 * 100000.0;									// objem plátku syra bez dier
    long double guess = tis * result;										// predpokladaný objem rezu
    for (int i = 0; i < size; i++) {
        if (result > (arr[i][0] + arr[i][1])) { 
		guess -= objem(arr[i][0]);									// ak celý rez pokrýva dieru, odpočítame celý objem 
	}
        else if (result >= (arr[i][1] - arr[i][0])) {
            double H = result - arr[i][1];									// výška vrchlíka vnútri syra
            guess -= (M_PI * (powl(arr[i][0], 2) * H - powl(H, 3) / 3.0 + 2.0 / 3.0 * powl(arr[i][0], 3)));
        }
    }
    if (fabsl(hoal - guess) < 0.1) { return result; }								// ak je objem blízko požadovanému, vrátime výsledok
    
    if (guess < hoal) { 
	    return recurse(size, arr, result, max, hoal);							// príliš malý objem → zvýšime min
    }
    else { return recurse(size, arr, min, result, hoal); }							// Príliš veľký objem → znížime max
}

int main() {
    int y, cast;
    scanf("%d %d", &y, &cast);											// načítanie počtu dier a počtu plátkov
    unsigned int array[y][2];											// dvojrozmerné pole na uloženie polomerov a súradníc
    for (int i = 0; i < y; i++) {
        int util;
        scanf("%d", &array[i][0]);										// načítanie polomeru diery
        scanf("%d", &util);											// súradnica X (nepoužitá)
        scanf("%d", &util);											// súradnica Y (nepoužitá)
        scanf("%d", &array[i][1]);										// súradnica Z
    }
    long double p = 0;
    long double sobjem = reset_objem(y, array);									// výpočet objemu syra bez dier
    for (int i = 1; i < cast + 1; i++) {
        long double slice = recurse(y, array, 0, 100000, (sobjem / cast) * i);					// výpočet hrúbky i-teho plátku
        printf("%.9Lf\n", (slice - p)/1000.0);									// výpis hrúbky plátku v milimetroch
        p = slice;												// aktualizácia pre ďalší rez
    }
    return 0;
}

