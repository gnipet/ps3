#include <stdio.h>
#include <stdlib.h>

struct lip {long double distance; long double velocity; struct lip *next; }; 

void rem(struct lip *l, long double size, int i) {int max = size - 1; if(i < max) {rem(l->next, size, i+=1); } free(l); }

void scan(struct lip *lip, int max) {
    int maxt = max;
    for(int i = 0; i < maxt; i++) {
        scanf("%Le %Le", &lip->distance, &lip->velocity);
        if(i < maxt - 1) {
            lip->next = (struct lip *)malloc(sizeof(struct lip));
            lip = lip->next;
        }
    }
}

long double result(struct lip *lip, long double hoal, long double left, long double right, int lim, int iteration, long double size) {
    long double sample = (left + right) / 2;
    long double cas = 0;
    struct lip *l = lip;
    int i = 0;
    int a = 1;
    while(a == 1) {
        if((l->velocity + sample) <= 0.0) {return result(lip, hoal, sample, right, lim, iteration += 1, size); }
        cas += (l->distance / (l->velocity + sample));
        if(i >= size -1) {a = 0;}
        l = l->next;
        i++;
    }
    //vrat spravny vysledok
    if(iteration >= lim) {return sample; }
    if(cas < hoal) {return result(lip, hoal, left, sample, lim, iteration += 1, size); }
    else {return result(lip, hoal, sample, right, lim, iteration += 1, size); }
}

int main() {
    long double s, res = 0;
    scanf("%Le %Le", &s, &res);
    struct lip *lip = (struct lip *)malloc(sizeof(struct lip));
    scan(lip, s);
    int min = -10000; int max = 10000; int twoh = 200;
    long double vl = result(lip, res, min, max, twoh, 0, s);
    rem(lip, s, 0);
    printf("%.9Lf", vl);
    return 0;
}

