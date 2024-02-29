#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pile.h"

//initialise toutes les cases d'une pile 0 et son sommet à -1 ce qui signifie que le pile est vide
PILE initialise_pile(){
PILE p;
p.sommet=-1;
for(int i=0; i<Nmax ;i++){
p.T[i]=0;
}
return p;
}

//vérifie si une pile est vide ou non
int pile_vide(struct pile p){
if(p.sommet==-1) return 0;
return 1; 
}

//permet d'inserer 1 a la case d'indice sommet, ce qui signifie qu'on lit une parenthèse ouvrante
PILE insertion(PILE p){
  p.sommet++; p.T[p.sommet]=1;
  return p;
}

//permet vider la case d'indice sommet et de le reculer d'1
PILE suppression(PILE p){
  if(pile_vide(p)){p.T[p.sommet]=0;p.sommet--;}
  return p;
}

//permet de vérifier si une liste de token est une expression booléenne appartenant au langage
int verif_token(liste_token t){
  PILE p=initialise_pile();
  liste_token e=t;
  int verif=1;
  //vrif permet détecter dès qu'un problème survient dans la liste de token ce qui permet de sortir de la boucle while mais aussi de ne pas entrer le if
  while(e!=NULL && e->suiv!=NULL && verif==1){
    //si  e contient parenthèse ouvrante alors e suivant contient:
    //- une constante 
    //      ou
    //-une parenthèse ouvrante 
    //      ou
    //-l'opérateur unaire NON
    if(e->type_token==PAR_OUV && (e->suiv->type_token==PAR_OUV || e->suiv->type_token==VAL || (e->suiv->type_token==OP_UN ))){
    p=insertion(p);
    e=e->suiv;
  }

  //si  e contient opérateur unaire NON alors e suivant contient:
  //- une constante 
  //      ou
  //-une parenthèse ouvrante 
  //      ou
  //-l'opérateur unaire NON
  else if((e->type_token==OP_UN) && (e->suiv->type_token==VAL || e->suiv->type_token==PAR_OUV || (e->suiv->type_token==OP_UN))){
    e=e->suiv;
  }

  //si  e contient une constante alors e suivant contient:
  //-un opérateur binaire 
  //        ou 
  //-une parenthèse fermante
  else if(e->type_token==VAL && ((e->suiv->type_token==OP_BI) || e->suiv->type_token==PAR_FER)){
    e=e->suiv;  
  }  

  //si  e contient opérateur binaire alors e suivant contient:
  //- une constante 
  //      ou
  //-une parenthèse ouvrante 
  //      ou
  //-l'opérateur unaire NON
  else if(e->type_token==OP_BI && (e->suiv->type_token==PAR_OUV || e->suiv->type_token==VAL ||(e->suiv->type_token==OP_UN))){
    e=e->suiv;
  }
  //si  e contient parenthèse fermante NON alors e suivant contient:
  //-une parenthèse fermante
  //      ou
  //-l'opérateur binaire
  else if(e->type_token==PAR_FER && pile_vide(p) &&((e->suiv->type_token==OP_BI )||e->suiv->type_token==PAR_FER)){
    p=suppression(p);
    e=e->suiv;
    }
  else{verif=0;}
  }
  //permet d'analyser le dernier token qui peut être:
  //-une parenthèse fermante  
  //          ou 
  //-une constante
  // si aucun problème n'est survenu durant les tokens précédents, c'est à dire si vérif est toujurs égal à 1
  if(verif==1){ 
  if (e->type_token==PAR_FER || e->type_token==VAL) 
  {
    if(e->type_token==PAR_FER && pile_vide(p)) 
      p=suppression(p);}
  else verif=0;
  }
  return verif && pile_vide(p)==0; 
  //la pile permet de vérifier si le mot est correctement parenthésé, verif vérifie que l'ordre des tokens a un sens
}