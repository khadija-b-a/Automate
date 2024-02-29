#include "token.h"
#define EST_VAL 1
#define EST_OP  2

struct noeud {
int type_var; //prend une des 2 valeurs selon le type de la valeur prise par le token
							//EST_VAl, EST_OP
char * op;
int val;
struct noeud * sad; //pointe vers le noeud en fils droit
struct noeud * sag;	//pointe vers le neoud en fils gauche
}; 
typedef struct noeud * arbre_token;


arbre_token token_to_EB (liste_token t);

void at_afficher(arbre_token e);
void afficher_ABR_prefixe(arbre_token A);
void afficher_ABR_infixe(arbre_token A);

void libere_ABR(arbre_token A );