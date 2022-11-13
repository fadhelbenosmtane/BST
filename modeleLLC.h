#ifndef     MODELE_LLC_H
#define     MODELE_LLC_H	1

#define NB_MAX 20
#define NB_MIN 1

// Déclaration de la structure de données "maillon"
typedef struct maillon maillon;
typedef struct maillon
{
    int val;
    maillon* adr;
};


// Définition du nouveau type PtrMaillon (pointeur vers un maillon)
typedef maillon* PtrMaillon;

// Procédure qui alloue un maillon et retourne son adresse dans p
void Allouer(PtrMaillon* p);

// Procédure qui détruit le maillon pointé par p
void Liberer (PtrMaillon p);

// Procédure qui affecte v dans le champ (val)du maillon pointé par p
void Aff_val(PtrMaillon p, int v);

// Procédure qui affecte q dans le champ (adr) du maillon pointé par p
void Aff_adr(PtrMaillon p, PtrMaillon q);

// Fonction qui retourne le contenu du champ (val) du maillon pointé par p
int Valeur (PtrMaillon p);

// Fonction qui retourne le contenu du champ (adr) du maillon pointé par p
PtrMaillon Suivant (PtrMaillon p);

#endif /* modeleLLC.h  */
