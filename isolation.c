#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct tree { int var; struct tree *l; struct tree *r; struct tree *prev; };

bool check(struct tree *n1, struct tree *n2);

int main() {
    int treesPocet, nodes;
    scanf("%d %d", &treesPocet, &nodes);
    int whole[treesPocet][nodes];
    struct tree *trees[treesPocet];
    for (int i = 0; i < treesPocet; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &whole[i][j]);
        }
    }
 
    for (int i = 0; i < treesPocet; i++) {
        for (int j = 0; j < nodes; j++) {
            int number = whole[i][j];
            if (j == 0) {
                trees[i] = (struct tree *)malloc(sizeof(struct tree));
                trees[i]->var = number;
                trees[i]->r = NULL;
                trees[i]->l = NULL;
                trees[i]->prev = NULL;
            } else {
                while (1) {
                    if (number >= trees[i]->var) {
                        //skontroluje pravu stranu
                        if (!trees[i]->r) { trees[i]->r = (struct tree *)malloc(sizeof(struct tree)); trees[i]->r->var = number; trees[i]->r->prev = trees[i]; trees[i]->r->r = NULL; trees[i]->r->l = NULL;
                            while (trees[i]->prev) {
                                trees[i] = trees[i]->prev;
                            }
                            break;
                        }
                        trees[i] = trees[i]->r;
                    } else {
                        //skontroluje lavu stranu
                        if (!trees[i]->l) { trees[i]->l = (struct tree *)malloc(sizeof(struct tree)); trees[i]->l->var = number; trees[i]->l->prev = trees[i]; trees[i]->l->r = NULL; trees[i]->l->l = NULL;
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

    int count = 0;
    for (int i = treesPocet - 1; i >= 0; i--) {
        bool same = false;
        //skontroluje a skonci
        for (int j = i; j >= 0; j--) {
            if (i != j) { if (check(trees[i], trees[j])) { same = true; break; } }
        }
        if (same == false) { count++; }
    }

    printf("%d\n", count);
    return 0;
}

bool check(struct tree *n1, struct tree *n2) { if (n2 == NULL && n1 == NULL) { return true; } if ((n2 == NULL && n1) || (n2 && n1 == NULL)) { return false; } return check(n1->l, n2->l) && check(n1->r, n2->r); }




















