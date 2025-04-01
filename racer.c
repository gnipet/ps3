#include <stdio.h>
#include <stdlib.h>


// štruktúra lip ktorá obsahuje prejdenú vzdialenosť (distance), rýchlosť (velocity) a smerník na ďalšiu štruktúru 
struct lip {
	long double distance; 
	long double velocity; 
	struct lip *next; }; 

// rekurzívna funkcia, ktorá uvoľňuje (dealokuje) pamäť pre jednosmerne prepojený zoznam (struct lip)
void rem(struct lip *l, long double size, int i) {
	int max = size - 1;							// Keďže indexy idú od 0, posledný index je size - 1 
	if(i < max) {								// Ak aktuálny index i je menší ako max, rekurzívne sa zavolá rem() s nasledujúcim prvkom (l->next).
		rem(l->next, size, i+=1); 					// rekurzívne voláme funkciu keď ccheme vytvoriť nejaký návezbný zoznam
	} 
	free(l);								// Uvoľni
}

//načítanie prepojeného zoznamu (struct lip) zo vstupu.
void scan(struct lip *lip, int max) {			//lip – ukazovateľ na začiatok prepojeného zoznamu (struct lip),max – maximálny počet prvkov v zozname (koľko hodnôt sa načíta).
    int maxt = max;
    for(int i = 0; i < maxt; i++) {
        scanf("%Le %Le", &lip->distance, &lip->velocity); //Načítaj hodnoty
        if(i < maxt - 1) {				  //Ešte nie som na konci	
            lip->next = (struct lip *)malloc(sizeof(struct lip));	//alokuj pamať na ďalší prvok
            lip = lip->next;						//Presuň sa na ďalší prvok
        }
    }
}

// funkcia na nájdenie tajomnej konštanty
// Parametre:
// lip – ukazateľ na spojkový zoznam obsahujúci úseky jazdy.
// hoal – celkový čas jazdy (zadávaný vstupom).
// left, right – hranice vyhľadávania (dolná a horná).
// lim – maximálny počet iterácií binárneho vyhľadávania.
// iteration – aktuálny počet iterácií (rekurzívne sa zvyšuje).
// size – počet úsekov (veľkosť zoznamu).
long double result(struct lip *lip, long double hoal, long double left, long double right, int lim, int iteration, long double size) {
    long double sample = (left + right) / 2;				// binárne vyhľadávanie nájdeme stred hodnota bude novým kandidátom na výslednú konštantu k
    long double cas = 0;						// čas je nula
    struct lip *l = lip;						// smerník na štruktúru lip na prvý prvok zoznamu Neovplyvňuje pôvodný zoznam lip, pretože sa používa kópia ukazateľa.
    int i = 0;								// i je celé čislo na začiatku 0
    int a = 1;								// a je celé číslo na začiazku 1
    while(a == 1) {							// pokial je a = 1
        if((l->velocity + sample) <= 0.0) {				// ak l->velocity + sample je ≤ 0, znamená to, že tachometer ukazuje nemožnú hodnotu (negatívnu rýchlosť).
		return result(lip, hoal, sample, right, lim, iteration += 1, size); // rekurzivne volaj funkciu ale už len od stredu napravo (left si nahradil sample) 
	}
        cas += (l->distance / (l->velocity + sample));			// výpočet času
        if(i >= size -1) {a = 0;}					// ak sme na konci, nastavíme indikátor/podmienku ukončenia hľadania 
        l = l->next;							// ak nie sme na konci ideme na ďalšiu štruktúru 
        i++;								// koľko úsekov sme spracovali?
    }
    //vrat spravny vysledok						// rekurzívne volanie sa vykonáva, kým nie je dosiahnutý limit iterácií lim
    if(iteration >= lim) {						// ak sme dosiahli limit iterácií, vrátime výsledok
	    return sample; 
    }


    // ak je cas < hoal, to znamená, že skutočný čas je menší ako požadovaný → posúvame hornú hranicu right = sample.
    // ak je čas väčší alebo rovný, posúvame dolnú hranicu left = sample. 
    if(cas < hoal) {
	    return result(lip, hoal, left, sample, lim, iteration += 1, size); 
    }
    else {
	    return result(lip, hoal, sample, right, lim, iteration += 1, size); 
    }
}

int main() {
    long double s, res = 0;						// načítaj hodnoty
    scanf("%Le %Le", &s, &res);						// long double v exponenciálnom tvare 
    struct lip *lip = (struct lip *)malloc(sizeof(struct lip));		// alokuj pamäť
    scan(lip, s);							// volaj funkciu na naplnenie hodnôt a posielaj jej počet jázd a štruktúru na naplnenie
    int min = -10000; int max = 10000; int twoh = 200;			// definícia hodnôt
    long double vl = result(lip, res, min, max, twoh, 0, s);		// volaj funkciu na zistenie tajomnej konštanty
    rem(lip, s, 0);							// uvoľnenie pamati (vytvorenie celej štruktúry záznamov)
    printf("%.9Lf", vl);						// vypisuje hodnotu premennej vl s deviatimi desatinnými miestami ako long double
    return 0;								// ukončenie funkcie main
}

