#include <stdio.h>
#include <stdlib.h>

#include "pile.h"
#include "val.h"


int main (int argc, char *argv[]) {
	liste_token t = NULL;
  arbre_token a = NULL;
  for(int i=1; i<argc;i++){
  
    t=string_to_token(argv[i]);
    //token_afficher_suite(t);
    if(verif_token(t)){
      printf("la chaine de caractère est une expression boolénne\n");
      a = token_to_EB(t);
	    at_afficher(a);
      /*printf("\n");
      printf("infixe:\n");
      afficher_ABR_infixe(a);*/
      printf("\n");
      affiche_resultat(a);
      libere_ABR(a);
    }
    else {printf("la chaine de caractère n'est pas une expression boolénne\n");
    libere_liste(t);
    }
    printf("\n");
  }	 
  return 0;
}