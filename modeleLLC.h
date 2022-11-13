#ifndef     MODELE_LLC_H
#define     MODELE_LLC_H	1

#define NB_MAX 20
#define NB_MIN 1

// D�claration de la structure de donn�es "maillon"
typedef struct maillon maillon;
typedef struct maillon
{
    int val;
    maillon* adr;
};


// D�finition du nouveau type PtrMaillon (pointeur vers un maillon)
typedef maillon* PtrMaillon;

// Proc�dure qui alloue un maillon et retourne son adresse dans p
void Allouer(PtrMaillon* p);

// Proc�dure qui d�truit le maillon point� par p
void Liberer (PtrMaillon p);

// Proc�dure qui affecte v dans le champ (val)du maillon point� par p
void Aff_val(PtrMaillon p, int v);

// Proc�dure qui affecte q dans le champ (adr) du maillon point� par p
void Aff_adr(PtrMaillon p, PtrMaillon q);

// Fonction qui retourne le contenu du champ (val) du maillon point� par p
int Valeur (PtrMaillon p);

// Fonction qui retourne le contenu du champ (adr) du maillon point� par p
PtrMaillon Suivant (PtrMaillon p);

#endif /* modeleLLC.h  */
