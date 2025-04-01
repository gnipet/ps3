#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// funkcia mení int na char, int vstupuje ako num a výsledok je smerník na pole char
void numtostr(char * str, unsigned long int num) {
    const int maxlen = 10;						// premená int
    unsigned long int tmpnum = num;					// dočasná premenná
    int strPos;
    for(strPos = 0; strPos < maxlen && tmpnum != 0; ++strPos) {		// prechádzame všetky číslice (max 10)
        char newchar = '0' + (tmpnum % 10);				// urobíme z int číslice char 
        str[strPos] = newchar;						// uložíme do poľa (smerník)
        tmpnum = tmpnum / 10;						// oddelíme posledný znak
    }			
    str[strPos] = '\0';							// char musí byť ukončený ukončovacím znakom tak ho prihodíme na koniec 
}


// funkcia na sčítanie číslic a výsledok je jedno jednociferné číslo 
int mighty_method(char* input) {					
    unsigned long int sum = 0;						// výsledok nastavíme na nulu
    for(int i = 0; i < strlen(input); i++) {				// ideme po jednotlivých číslicách (znakoch)
        char msum = input[i];						// zoberieme znak (číslicu)
        sum = sum + (msum - ('0'));					// msum - ('0') je prevod char -> int a sučet znamená, že spočítavame číslice
    }
    if(sum > 9) {							// ak je to viacciferné číslo
        const int maxChars = 100;					// premenná int
        char * input = malloc(maxChars*sizeof(char));			// alokujeme pamäť (lebo je to char)
        numtostr(input, sum);						// ak je to viacciferné číslo tak výsledok sučtu cifier je int ale my potrebujeme char
        int output = mighty_method(input);				// rekurzívne voláme finkciu mm až pokiaľ nemáme jednociferný výsledok
        free(input);							// uvoľníme alokovanú pamäť
        return output;							// vraciame súčet cifier - výsledok	
    }
    return sum;								// vraciame výsledok
}

//hlavcná funkcia
int main() {					
    const int maxChars = 100000;					// maximalny počet číslic 
    char * input = malloc(maxChars*sizeof(char));			// alokácia pamate na cislo
    scanf("%s", input);							// čakanie na vstup čísla
    int output = mighty_method(input);					// volanie funkcie
    printf("%d\n", output);						// vypísanie výsledku 
    free(input);							// uvoľnenie pamäte
    return 0;								// ukonenie programu 
}



