#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// štruktúra jednej vetvy stromu
struct tree { 
	int var; 								// položka int (číslo) štruktúty - hodbnota izolácie 
	struct tree *l; 							// smerník na ľavú vetvu (tá istá štruktúra)
	struct tree *r; 							// smerník na pravú vetvu (tá istá štruktúra)
	struct tree *prev; };							// smerník na predchádzajúcu vetvu (tá istá štruktúra)

bool check(struct tree *n1, struct tree *n2);					// funkcia na púorovnanie dvoch stromov - vracia true ak sú rovnaké

// hlavná funkcia	
int main() {
    int treesPocet, nodes;							// int premennné počet stromov a položku int štruktúry
    scanf("%d %d", &treesPocet, &nodes);					// zadajme vstup - počet stromov a položku int štruktúry
    int whole[treesPocet][nodes];						// dvojrovmerné pole - riadok ja strom a stlpce sú položky int stromu (štruktúry)
    struct tree *trees[treesPocet];						// deklarujeme toľko stromov (štruktúr trees) koľko je prvý vstup
										
    // naplname dvojrozmernú maticu  								
    for (int i = 0; i < treesPocet; i++) {					// vonkajší cyklus - riadok teda strom
        for (int j = 0; j < nodes; j++) {					// vnútorný cyklus - stlpec teda položka (hodnota izolácie) 
            scanf("%d", &whole[i][j]);						// načítaj zo vstupu položku					
        }
    }

    // vytvárame strom  
    for (int i = 0; i < treesPocet; i++) {					// vonkajší cyklus - riadok teda strom
        for (int j = 0; j < nodes; j++) {					// vnútorný cyklus - stlpec teda položka (hodnota izolácie)
            int number = whole[i][j];						// zoberieme položku z poľa
	    // ak je to koreň			
            if (j == 0) {							// ak je stlpec 0 je to prvá položka a teda koren
                trees[i] = (struct tree *)malloc(sizeof(struct tree));		// alokujeme poamať
                trees[i]->var = number;						// strom "i" hodnota izolácie 
                trees[i]->r = NULL;						// koren nemá pravú vetvu
                trees[i]->l = NULL;						// koren nemá ľavú vetvu
                trees[i]->prev = NULL;						// koren nemá hornú vetvu
										//
	      // ak to nie je koreň	
            } else {
                while (1) { 							// budujem,e strom ďalej
                    if (number >= trees[i]->var) {				// hodnota ďalšej izolácie je väčšia alebo rovná ako tej aktuálnej
                        //skontroluje pravu stranu
                        if (!trees[i]->r) { 					// ak neexistuje ďalšia pravá vetva (aktuálne sme na poslednej štruktúre tak tam môžeme pridať)
				trees[i]->r = (struct tree *)malloc(sizeof(struct tree)); 	// alokujem pamať
				trees[i]->r->var = number; 			// pridávame do stromu ďalší prvok 		
				trees[i]->r->prev = trees[i]; 			// ak sme ho pridali musíme naviazať na predchádzajúcu štruktúru
				trees[i]->r->r = NULL; 				// ďalej vpravo ž nič nie je
				trees[i]->r->l = NULL;				// ďalej vľavo ž nič nie je
                            	while (trees[i]->prev) {
                                	trees[i] = trees[i]->prev;		// musíme sa vracať na začiatok lebo pri pridávaní ďalšej izolácie porovnávame od začiatku 
                            	}
                           	 break;
                        }
                        trees[i] = trees[i]->r;					// smerujeme na pravú vetvu
                    } else {
                        //skontroluje lavu stranu
			// opakujeme to isté ako v pravej vetcve ale na ľavú stranu 				
                        if (!trees[i]->l) { 
				trees[i]->l = (struct tree *)malloc(sizeof(struct tree)); 
				trees[i]->l->var = number; 
				trees[i]->l->prev = trees[i]; 
				trees[i]->l->r = NULL; 
				trees[i]->l->l = NULL;
                           	 while (trees[i]->prev) {
                                	trees[i] = trees[i]->prev;
                            	} break;
                        }
                        trees[i] = trees[i]->l;
                     }
                }
            }
       }
    }

    // porovnávanie či máme nejaké stromy rovnaké cez binárne vyľadávanie
    int count = 0;								// premenná typu int
    for (int i = treesPocet - 1; i >= 0; i--) {					// stromy porovnávame od konca
        bool same = false;							// default je false (žiadne porovnávené stromym nie sú rovnaké)	
        // skontroluje a skonci
	// najprv porovnáme posledný s predposledým, potom posledný s predpredposledným a tak nakoniec posledný s prvým
	// potom porovnávame predposledný, ale ten nemusíme porovnávať s posledným (to smem už robili) tak ideme len dopredu (nazad) 
	// preto máme i=j
        for (int j = i; j >= 0; j--) {						// 
            if (i != j) { 							// sám so sebou neporovnávam
		if (check(trees[i], trees[j])) { 				// ak sú rovnaké	
			same = true; 						// true nezvýš počet lebo len rozdielne stromy máš spočítať
			break; 							// ukonči
		}
        }
        if (same == false) {							// ak nie su rovnaké zvýš počet  
		count++; 

	}									// opa
    }

    printf("%d\n", count);							// vypíš počet rozdielnych stromov teda rozdielnych izolácií 
    return 0;									// ukonči program
    }
 }

// funkcia na porovnávanie
bool check(struct tree *n1, struct tree *n2) {
        if (n2 == NULL && n1 == NULL) {                                         // prázdne smerníky neporovnávam vrát true teda nepripocítavaj
                return true;
        }
        if ((n2 == NULL && n1) || (n2 && n1 == NULL)) {                         // ak sú rovnaké vraciam false teda zvýš počet
                return false;
        }
        return check(n1->l, n2->l) && check(n1->r, n2->r);                      // rekurzívne volaj funkciu a posielaj ľavú vetvo dvoch stromov aj pravú vetvu tých istých stromov
}


