#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABR.h"
#include "token.h"
#include "pile.h"


liste_token token_pour_sag (liste_token t, liste_token op) {
  op->prec->suiv = NULL;
	op->prec = NULL;
	return t;
}

liste_token token_pour_sad (liste_token t, liste_token op) {
  t = op->suiv;
	t->prec = NULL;
	op->suiv = NULL;
	return t;
}

//transforme un token en un noeud de l'ABR
arbre_token transforme_un_token_en_eb (liste_token t) {
	arbre_token e;
	e = malloc(sizeof(struct noeud));
	if (!e) exit(34);
	if (t->type_token == PAR_OUV || t->type_token == PAR_FER) {
		fprintf(stderr,"Parenthèse sans partenaire\n");
		exit(35);
	}
	if (t->type_token == OP_UN || t->type_token == OP_BI)  {
		e->type_var = EST_OP;
		e->op = t->op;
	}
	if (t->type_token == VAL) {
		e->type_var = EST_VAL;
		e->val = t->val;
	}
	e->sag = e->sad = NULL;
	free(t);
	return e;
}

liste_token retirer_parenthese_externe(liste_token t) {
	if (t==NULL) return t;
	liste_token e = t;
  liste_token deb=t;
  int nb =0;
	while (e != NULL && e->suiv!=NULL && e->suiv->type_token!=PAR_FER) {
    if(e->type_token==PAR_OUV && nb>0) {nb++;}
    if(e->type_token==PAR_OUV && nb==0) {deb=e;nb++;}
    //printf("nb %d\n", nb); printf("1\n");
    if(e->suiv!=NULL) e=e->suiv;
	}
  while(nb!=0 && e != NULL){
    if(e->type_token==PAR_FER) {nb--;}
    //printf("nb %d\n", nb); 
    if(e->suiv!=NULL && nb !=0) e=e->suiv;
  }
  //printf("%d",deb->type_token ); printf("%d",e->type_token ); printf("%d",e->val );
	if ((deb->type_token == PAR_OUV)&&(e->type_token == PAR_FER))
    {
	//printf("On retire\n");
		// On retire la ( du début
		liste_token pour_le_free;
		pour_le_free = deb;
    if(deb->prec!=NULL)	{deb->prec->suiv = deb->suiv;
    deb->suiv->prec=deb->prec;}
    else {deb=deb->suiv;deb->prec=NULL;t=deb;}
		free(pour_le_free);
		// On retire la ) de la fin
		pour_le_free = e;
    if(e->suiv!=NULL)
	  	{e->prec->suiv = e->suiv; e->suiv->prec=e->prec;}
    else{e=e->prec; e->suiv=NULL;}
		free(pour_le_free);
	  }
	return t;
}

liste_token trouver_op(liste_token t){
  //printf("t entrée %d\n", t->type_token);
  PILE p=initialise_pile();
  liste_token op = NULL;
  liste_token e=t;
  int verif=1;
  while(e!=NULL && e->suiv!=NULL && verif==1){
    //si  e contient parenthèse ouvrante
    if(e->type_token==PAR_OUV){
    p=insertion(p);
    e=e->suiv;
    }

    //si  e contient une constante 
    else if(e->type_token==VAL){
    e=e->suiv;
    }   

    //si  e contient opérateur binaire
    else if(e->type_token==OP_BI || e->type_token==OP_UN){
    if(pile_vide(p)==0){//si c'est vide on peut prendre un opérateur
        //objectif prendre le dernier opérateur qui se trouve au niveau de pile vide.  
        if(e->type_token==OP_BI) op = e;
        if(e->type_token==OP_UN && (op==NULL)) op = e;  // prendre l'opérateur NON au bon moment si on a le choix entre par exemple opérateur binaire ou NON
    }
    //else 
    e=e->suiv;
    }
    //si  e contient parenthèse fermante
    else if(e->type_token==PAR_FER && pile_vide(p)){
    p=suppression(p);
    e=e->suiv;
    }
    else{verif=0;}
    }
    //permet d'analyser le dernier token qui peut être:
    //-une parenthèse fermante  
    //          ou 
    //-une constante
    // si aucun problème n'est survenu durant les tokens précédents,      c'est à dire si vérif est toujurs égal à 1
    if(verif==1){ 
   if (e->type_token==PAR_FER || e->type_token==VAL) 
    {
    if(e->type_token==PAR_FER && pile_vide(p)) 
      p=suppression(p);
      }
    else verif=0;
    }
    //printf("t retourner %d\n", t->type_token);
    if(op!=NULL)t=op;
  return t;//si on n'a pas pu prendre d'opérateur car pile non cide au moment où on est passé sur les opérateurs on retourne ce qu'on a eu en entrée et dans token_to_EA on va supprimer les parenthèses.
}

arbre_token token_to_EB (liste_token t) {
	arbre_token e;
	if (t==NULL) return NULL;
	if ((t->prec==NULL) && (t->suiv==NULL)) {
		if (t->type_token != VAL) {
			fprintf(stderr,"Token de type %d ne doit pas être une feuille\n",t->type_token);
			exit(36);
		}
		e =transforme_un_token_en_eb(t);
		return e;
	}
	
  liste_token op;
  int changement_t; // permet de savoir si on a aplliqué retire parenthèse
  do{
  changement_t = 0;
	op = trouver_op(t); // récupère l'op s'il y en a un lorsque pile vide sinon recupère t
  //token_afficher_suite(t);
  if(op==t && (t->type_token != OP_BI && t->type_token != OP_UN)){ t = retirer_parenthese_externe(t); 
    changement_t = 1;
    }
  }while(changement_t);
	liste_token G, D;
  if(op->type_token==OP_UN){
   G = NULL;
  } 
  else {G = token_pour_sag (t,op);}
  D = token_pour_sad (t,op);
	e = transforme_un_token_en_eb (op);
	e->sag = token_to_EB(G);
	e->sad = token_to_EB(D);
	return e;
}








void at_afficher(arbre_token e){
	if (e==NULL) return;
	if (e->type_var == EST_VAL) printf("%d",e->val);
	else {
		printf("(");
		at_afficher(e->sag);
		printf(" %s ",e->op);
		at_afficher(e->sad);
		printf(")");
		}
}


void afficher_ABR_prefixe(arbre_token A){ // affiche l'ABR de façon préfixe permet de vérifier l'équilibrage 
	if (A==NULL) return;
  if(A->type_var == EST_VAL){printf(" %d |\n",A->val);}
  else printf(" %s |\n",A->op);
	afficher_ABR_prefixe(A->sag);
	afficher_ABR_prefixe(A->sad);
}


void afficher_ABR_infixe(arbre_token A){ // affiche l'ABR de façon préfixe permet de vérifier l'équilibrage 
	if (A==NULL) return;
  afficher_ABR_prefixe(A->sag);
  if(A->type_var == EST_VAL){printf(" %d |\n",A->val);}
  else printf(" %s |\n",A->op);
	afficher_ABR_prefixe(A->sad);
}

void libere_ABR(arbre_token A){
	if (A==NULL) return;
	libere_ABR(A->sad);
	libere_ABR(A->sag);
	if(A->type_var == EST_OP)free(A->op);
	free(A);
}