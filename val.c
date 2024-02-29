#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "val.h"

int arbre_to_int(arbre_token A){
if(A->type_var == EST_OP) 
  {if (strcmp(A->op,"<=>")==0) return arbre_to_int(A->sag)==arbre_to_int(A->sad);
    else if(strcmp(A->op,"+")==0) return arbre_to_int(A->sag)&&arbre_to_int(A->sad);
    else if(strcmp(A->op,".")==0) return arbre_to_int(A->sag)||arbre_to_int(A->sad);
    else if(strcmp(A->op,"NON")==0) return !arbre_to_int(A->sad);
    else if(arbre_to_int(A->sag)==1 && arbre_to_int(A->sag)==0) return 0; 
    else return 1;}
else return A->val;

}

void affiche_resultat(arbre_token A){
printf("\n");
printf("////////RESULTAT/////////\n");
if(arbre_to_int(A)) printf("VRAI\n");
else printf("FAUX\n");
printf("/////////////////////////\n");
printf("\n");
}