#ifndef __TOKEN_H
#define __TOKEN_H 1


#define PAR_OUV 11
#define PAR_FER 12
#define OP_BI   13
#define OP_UN   14 
#define VAL     15

struct token {
	int type_token; // prend une des 4 valeurs :
					// PAR_OUV, PAR_FER, OP, VAL
	char *op;//opérateur ".", "+", "<=>", "=>"
	int val;//valeur 0 ou 1
	struct token *suiv;
	struct token *prec;
};
typedef struct token* liste_token;

liste_token token_ajouter_fin_liste (liste_token t, liste_token e);
liste_token string_to_token (char *string);
void token_afficher_suite (liste_token t);
void libere_liste(liste_token t);

#endif
