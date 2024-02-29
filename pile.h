#ifndef __PILE_H
#define __PILE_H 1

#include "token.h"

#define Nmax 30

struct pile {
  int T[Nmax];
  int sommet; // indice du dernier élément inséré dans la pile
};typedef struct pile PILE;

int pile_vide(struct pile p);

PILE initialise_pile();

PILE insertion(struct pile p);

PILE suppression(struct pile p);

int verif_token(liste_token t);

#endif