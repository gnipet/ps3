#include<stdio.h>

int vypocet_cisla(int cislo){
   while(cislo>9){
     int vysledok=0;
         while(cislo>0){
            vysledok = vysledok + cislo % 10;
            cislo = cislo / 10;
         }
   cislo =vysledok;
   }

   return cislo;
}
int main(){
   int cislo=0;
   //printf("zadaj cislo:");
   scanf("%d",&cislo);
   if (cislo<1) return 0;
   if (cislo>0 && cislo<10){
      printf("%d",cislo);
      return 0;
   }
   int vysledok=vypocet_cisla(cislo);
   printf("%d",vysledok);
return 0;
}


