#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

void libere_liste(liste_token t){
  liste_token tmp;
  while(t!=NULL){ 
  tmp=t->suiv; 
  free(t->op);
  free(t);
  t=tmp;
  }
}

liste_token creer_token( int type_token, char *op, int val) {
	liste_token e;
	e = malloc(sizeof(struct token));
	if (e==NULL) exit(2);
	e->val  = val;
	e->type_token= type_token; 
  e->op = op;   
	e->suiv = NULL;
	e->prec = NULL;
	return e;
}

liste_token token_ajouter_fin_liste (liste_token t, liste_token e) { 
	// Cas de la liste vide
	if (t==NULL) return e;
	// Cas général
	liste_token tdeb = t;
	// Déplacer t pour qu'il pointe 
	// sur le dernier élément de la liste
	while (t->suiv != NULL) {
		t = t->suiv;
	}
	t->suiv = e;
	e->prec = t;
	return tdeb;
}

int est_op(char c, char c1, char c2) {
  if (c=='.') return 1; 	
  if (c=='+') return 1; 
  if(c=='<'&& c1=='=' && c2=='>') return 3;
  if(c=='=' && c1=='>') return 2;	
  if(c=='N' &&c1=='O' && c2=='N')return 3;
  //if (c=='=') return 1; 
  //if (c=='/') return 1; 	
  return 0; 
}

int est_val(char c){
  if (('0'==c) ||(c== '1') )return 1;  
  return 0; 	
}

int est_valide( char c, char c1, char c2) {
  if (est_op(c, c1, c2)) return 1; 
  if(est_val(c)) return 1;  
  if (c=='(') return 1; 
  if (c==')') return 1; 	
  if (c==' ') return 1; 	
  if (c=='\t') return 1; 	
  return 0;
}


liste_token string_to_token (char *string){
  liste_token e;
  liste_token t=NULL;
	while (*string !='\0') { 
		if(!est_valide(*string, *(string+1), *(string+2))){
      fprintf(stderr, "caractere '%c' non valide\n", *string); 
      libere_liste(t);
			exit(3); 
    }
		if(*string=='(') {
      e=creer_token(PAR_OUV,0, 0); 
			t=token_ajouter_fin_liste(t, e);string++;
    }
		else if(*string==')') {
      e=creer_token( PAR_FER, 0, 0); 
			t=token_ajouter_fin_liste(t, e);string++;
    }
    else if(est_val(*string)){ 
      if(*string=='0')e=creer_token( VAL, 0, 0); 
      else e=creer_token( VAL, 0, 1);
			t=token_ajouter_fin_liste(t, e);string++;
    }
		else if(est_op(*string,*(string+1),*(string+2))){	
		  int i=est_op(*string,*(string+1),*(string+2));
      char *operateur = malloc((i+1)*sizeof(char)); 
      for(int j =0; j<i; j++){
        *(operateur+j) = *(string+j); 
      }
      *(operateur+i)= '\0';
      if(strcmp(operateur, "NON")==0)
      e=creer_token(OP_UN,operateur, 0);
      else e=creer_token(OP_BI,operateur, 0);
			t=token_ajouter_fin_liste(t, e);string+=i;
    }
    else string++;
	}
  return t;	
}

//permet d'afficher les liste chainée de tokens
void token_afficher_suite(liste_token t) {
	printf("## DEB ##\n");
	while (t != NULL) {
		if (t->type_token == PAR_OUV) printf("PAR_O\n");
		if (t->type_token == PAR_FER) printf("PAR_F\n");
		if (t->type_token == OP_UN ||t->type_token == OP_BI)    printf("OP    '%s'\n",t->op);
		if (t->type_token == VAL)   printf("VAL   %d\n",t->val);
		t = t->suiv;
	}
	printf("## FIN ##\n");
}