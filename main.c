#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
typedef struct maillon maillon;
typedef struct maillon
{
    int val;
    maillon* adr;
};
typedef maillon* PtrMaillon;
struct sclient
{
    char nom[15];
    char prenom[15];
    int code;
    char tel[15];
    char IN[15];
};
struct facture {
    int numchambre;
    int codecli;
    int identres;
    int nmbrnuits;
    float montant;
};
struct factli{
 struct facture facture;
 struct factli *ptrfactli;
};
typedef struct factli factli;
typedef struct factli* ptrfactli;

struct date {
    int jour ;
    int mois;
    int annee;
};
typedef struct date date;
struct res
{
    int  nchambre;
    char nom[15];
    char prenom[15];
    int NmbrNuit;
    date date;
    date datesejour;
    int nombrepers;
    int idres;
};
void Allouer(PtrMaillon* p)
{
    *p = (PtrMaillon)malloc(sizeof(maillon));
}

// Procédure qui détruit le maillon pointé par p
void Liberer (PtrMaillon p)
{
    free(p);
}

// Procédure qui affecte v dans le champ (val) du maillon pointé par p
void Aff_val(PtrMaillon p, int v)
{
    p->val = v;     // (p->val) est l'équivalent de (*p.val)
}

// Procédure qui affecte q dans le champ (adr) du maillon pointé par p
void Aff_adr(PtrMaillon p, PtrMaillon q)
{
    p->adr = q;     // (p->adr) est l'équivalent de (*p.adr)
}

// Fonction qui retourne le contenu du champ (val) du maillon pointé par p
int Valeur (PtrMaillon p)
{
    return p->val;
}

// Fonction qui retourne le contenu du champ (adr) du maillon pointé par p
PtrMaillon Suivant (PtrMaillon p)
{
    return p->adr;
}

/*------------------------------ les maillons-------------------------------------------------------------------------------------------*/
struct schambre
{
    int num;
    char typechambre[15];
    float prix;
    int TV;
    char Etat[15];

};
typedef struct schambre chambre;
typedef chambre *ptrch ;
struct clientli{
   struct sclient client;
   struct clientli* ptrcl;
};
typedef struct clientli clientli;
typedef struct clientli* ptrclientli;
struct resli{
   struct res reserve;
   struct resli *ptres;

};
typedef struct resli resli;
typedef struct resli* ptresli;
/*--------------------------------------------machine abstraite de djennane mohamed el ostori -----------------------------------------------------------------*/
void Allouer_n(ptrclientli* p)
{
    *p = (ptrclientli)malloc(sizeof(clientli));
}
void Liberer_n (ptrclientli p)
{
    free(p);
}
ptrclientli Suivant_n (ptrclientli p)
{
    return p->ptrcl;
}
void Aff_adr_n(ptrclientli p, ptrclientli q)
{
    p->ptrcl = q;     // (p->adr) est l'équivalent de (*p.adr)
}
void Allouer_res(ptresli* p)
{
    *p = (ptresli)malloc(sizeof(resli));
}
void Liberer_res (ptresli p)
{
    free(p);
}
void Aff_adr_res(ptresli p, ptresli q)
{
    p->ptres = q;     // (p->adr) est l'équivalent de (*p.adr)
}
ptresli Suivant_res (ptresli p)
{
    return p->ptres;
}
/*--------------------------------------llc_factures------------------------------*/
void allouer_fact(ptrfactli* p)
{
    *p=malloc(sizeof(factli));
}
void aff_adr_fact(ptrfactli p,ptrfactli q)
{
    p->ptrfactli=q;
}
ptrfactli suivant_fact(ptrfactli p)
{
    return p->ptrfactli;
}


/*---------------------------------------------------------les fonction utilisable --------------------------------------------------------------------------------*/
void LLc_client(ptrclientli *t ,ptrclientli *d){

    ptrclientli p;
    ptrclientli k;
    Allouer_n(&p);
    FILE *fp;
    fp = fopen("client.txt","r");
    fscanf(fp,"%s %s %d %s %s ", p->client.nom ,p->client.prenom , &p->client.code ,p->client.IN ,p->client.tel);
    *t=p;
    while(!feof(fp)){
      Allouer_n(&k);
      Aff_adr_n(p,k);
      p=Suivant_n(p);
      fscanf(fp,"%s %s %d %s %s ", p->client.nom ,p->client.prenom , &p->client.code ,p->client.IN ,p->client.tel);
    }
    Aff_adr_n(p,NULL);
    (*d)=p;
}
void ajouterclient(ptrclientli *d){
    FILE *fp;
    ptrclientli p;
    Allouer_n(&p);
    printf("entrer votre nom : ");
    gets(p->client.nom);
    printf("entrer votre prenom : ");
    gets(p->client.prenom);
    printf("entrer votre nemuro tel : " );
    gets(p->client.tel);
    printf("entrer votre id : ");
    gets(p->client.IN);
    p->client.code=((*d)->client.code)+1;
    printf("votre code est : %d \n ",p->client.code);
    Aff_adr_n((*d),p);
    Aff_adr_n(p,NULL);
    fp=fopen("client.txt","a");
    fprintf(fp,"%s %s %d %s %s\n", p->client.nom ,p->client.prenom , p->client.code ,p->client.IN ,p->client.tel);

}
void modifierclient(int code, ptrclientli *t){
    ptrclientli p=(*t);
    FILE *fp;
    while (p != NULL){
        if(p->client.code == code){
            printf("**** reentrer votre donnee ***** \n");
             printf("entrer votre nom : ");
            gets(p->client.nom);
            printf("entrer votre prenom : ");
            gets(p->client.prenom);
            printf("entrer votre nemuro tel : " );
            gets(p->client.tel);
            printf("entrer votre id : ");
            gets(p->client.IN);
        }
     p=Suivant_n(p);
    }
     fp=fopen("client.txt","w");

    ptrclientli z=(*t);

    while(z!=NULL){

        fprintf(fp,"%s %s %d %s %s \n", z->client.nom ,z->client.prenom , z->client.code ,z->client.IN ,z->client.tel);
        z=Suivant_n(z);
    }
}
void acces_code(ptrclientli t,int code, ptrclientli *p,ptrclientli *q){
    int trouv=0;
    (*p)=t;
    (*q)=NULL;
    while(((*p) != NULL)&&(trouv==0)){
          if ((*p)->client.code==code){
            trouv=1;
          }
          else {
            (*q)=(*p);
            (*p)=Suivant_n((*p));
        }
}
}
int compte(FILE *fichier){
	int c;
	int nLignes = 0;
	int c2 = '\0';

	while((c=fgetc(fichier)) != EOF)
	{
		if(c=='\n')
			nLignes++;
		c2 = c;
	}

	/* Ici, c2 est égal au caractère juste avant le EOF. */
	if(c2 != '\n')
		nLignes++; /* Dernière ligne non finie */

	return nLignes;
}
void supprclient(ptrclientli *t, int code){
    ptrclientli p,q;
    FILE *fp;
    acces_code(*t,code,&p,&q);
    if(p!=NULL){
            if(q==NULL){
                (*t)=Suivant_n(p);
            }
            else{
                Aff_adr_n(q,Suivant_n(p));
            }
            Liberer_n(p);
    }
    else{
        printf("valeur non existance \n");
    }
    fp=fopen("client.txt","w");

    ptrclientli z=(*t);

    while(z!=NULL){

        fprintf(fp,"%s %s %d %s %s \n", z->client.nom ,z->client.prenom , z->client.code ,z->client.IN ,z->client.tel);
        z=Suivant_n(z);
    }
}
void LLc_res(ptresli *t ,ptresli *d){
    ptresli p;
    ptresli k;
    Allouer_res(&p);
    FILE *fp;
    fp = fopen("reservations.txt","r");
    fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %d",p->reserve.nom , p->reserve.prenom ,&p->reserve.NmbrNuit, &p->reserve.date.jour, &p->reserve.date.mois, &p->reserve.date.annee, &p->reserve.datesejour.jour, &p->reserve.datesejour.mois, &p->reserve.datesejour.annee, &p->reserve.nombrepers, &p->reserve.nchambre,&p->reserve.idres);
    (*t)=p;
      while(!feof(fp)){
      Allouer_res(&k);
      Aff_adr_res(p,k);
      p=Suivant_res(p);
      fscanf(fp,"%s %s %d %d %d %d %d %d %d %d %d %d ",p->reserve.nom , p->reserve.prenom ,&p->reserve.NmbrNuit, &p->reserve.date.jour, &p->reserve.date.mois, &p->reserve.date.annee, &p->reserve.datesejour.jour, &p->reserve.datesejour.mois, &p->reserve.datesejour.annee,&p->reserve.nombrepers, &p->reserve.nchambre, &p->reserve.idres);
    }
    Aff_adr_res(p,NULL);
            (*d)=p;

    }
void tab_chambre(ptrch t){
    int i;
    FILE *fp;
    fp=fopen("chambre.txt","r");
    i = 0;
    while(!feof(fp)){
            fscanf(fp," %d %s %d %s %f ", &(t[i].num) , t[i].typechambre , &(t[i].TV) ,t[i].Etat , &(t[i].prix) );
            i=i+1;
    }
}
int rechercheclient(ptrclientli *t , ptresli q ){
    ptrclientli p=*t;
    while(p!=NULL){
        if(strcmp(p->client.nom,q->reserve.nom)==0){
            if(strcmp(p->client.prenom,q->reserve.prenom)==0){
                return 1;
            }
            }

       p=Suivant_n(p);

    }
}
void change(date p , ptresli t ,ptrch ch){
    ptresli q=t;
    char occupe[15]="occupe";
    int i=0;
    int trouv=0;
    while(i<27){
        if (strcmp(occupe,ch[i].Etat)==0){
                while (q != NULL){
                    if (q->reserve.nchambre==i+1){
                        if (calcul_date_sortie(q->reserve.datesejour,q->reserve.NmbrNuit)<p.annee*10000+p.mois*100+p.jour){
                            system("pause");
                            trouv=1;
                        }
                    }
                    q=Suivant_res(q);
                }
        }
        if (trouv==1){
            strcpy(ch[i].Etat,"libre");
        }
        i=i+1;
    }
}
int choix_chambre(ptrch ch,char type[15]){
    char libre[15]="libre";
    int i=0;
    int trouv=0;
    while (i<27 && trouv==0){
        if (strcmp(type,ch[i].typechambre)==0){
            if(strcmp(ch[i].Etat,libre)==0){
                trouv=i+1;
            }
        }
        i=i+1;
    }

    return trouv;
}
void ajouteres(ptresli *d ,ptresli *y, ptrclientli *t, ptrclientli *dernier, ptrch ch){
    FILE *fp;
    ptresli p;
    char type[15];
    Allouer_res(&p);
    printf("entrer votre nom : ");
    gets(p->reserve.nom);
    printf("entrer votre prenom : ");
    gets(p->reserve.prenom);
    if (rechercheclient(t,p)!= 1){
            printf("*******Avant de reserver il faut inscrit merci d'avance ******** \n");
        ajouterclient(&dernier);
    }
    printf("entrer nbr de nuits : ");
    scanf("%d",&(p->reserve.NmbrNuit));
    printf("entrer la date de reservation selon la forme (jour/mois/annee) : \n");
    scanf("%d",&(p->reserve.date.jour));
    scanf("%d",&(p->reserve.date.mois));
    scanf("%d",&(p->reserve.date.annee));
    printf("entrer la date de sejour selon la forme (jour/mois/annee) : \n");
    scanf("%d" , &(p->reserve.datesejour.jour));
    scanf("%d" , &(p->reserve.datesejour.mois));
    scanf("%d" , &(p->reserve.datesejour.annee));
    printf("entrer le nombre de personne : \n");
    scanf("%d", &(p->reserve.nombrepers));
    p->reserve.idres=(*d)->reserve.idres+1;
    printf("-----------------------------veuillez entrer le type de chambre s'il vous plait : ---------------------------------\n");
    scanf("%s",type);
    tab_chambre(ch);
    date da;
    da.jour=p->reserve.datesejour.jour;
    da.annee=p->reserve.datesejour.annee;
    da.mois=p->reserve.datesejour.mois;
    change(da,*y,ch);
    p->reserve.nchambre=choix_chambre(ch,type);
    FILE *fch;
    fch=fopen("chambre.txt","w");
    int i=0;
    char chaine[15]="occupe";
    while (i<27){
        if(i==p->reserve.nchambre-1){
            fprintf(fch,"%d %s %d %s %f \n",ch[i].num , ch[i].typechambre ,ch[i].TV, chaine,ch[i].prix);
        }

        else{
                fprintf(fch,"%d %s %d %s %f \n",ch[i].num , ch[i].typechambre ,ch[i].TV ,ch[i].Etat,ch[i].prix);
        }
        i=i+1;
    }

    Aff_adr_res((*d),p);
    Aff_adr_res(p,NULL);
    fp=fopen("reservations.txt","a");
    fprintf (fp,"%s %s %d %d %d %d %d %d %d %d %d %d \n ",p->reserve.nom , p->reserve.prenom ,p->reserve.NmbrNuit, p->reserve.date.jour, p->reserve.date.mois, p->reserve.date.annee, p->reserve.datesejour.jour, p->reserve.datesejour.mois, p->reserve.datesejour.annee,p->reserve.nombrepers, p->reserve.nchambre,p->reserve.idres);

}
void modifier_res(char nom[15],char prenom[15],ptresli *t ,ptrch ch ){
    ptresli p=(*t);
    FILE *fp;
    char type[15];
    int a=0;
    while (p!=NULL && a==0){
        if (strcmp(p->reserve.nom,nom)+strcmp(p->reserve.prenom,prenom)==0){
            printf("VOUS VOULLEZ MODIFIER SES DONNEES ? \n");
            printf("%s %s %d %d %d %d %d %d %d %d %d \n ",p->reserve.nom , p->reserve.prenom ,p->reserve.NmbrNuit, p->reserve.date.jour, p->reserve.date.mois, p->reserve.date.annee, p->reserve.datesejour.jour, p->reserve.datesejour.mois, p->reserve.datesejour.annee,p->reserve.nombrepers, p->reserve.nchambre);
            printf("ENTRER (1) / SINON (0) : ");
            scanf("%d",&a);
            if(a==1){
                printf("---------------------------REENTRER VOTRE DONNEES---------------------------\n");
                printf("entrer votre nom  : \n");
                gets(p->reserve.nom);
                printf("entrer votre prenom : ");
                gets(p->reserve.prenom);
                printf("entrer nbr de nuits : ");
                scanf("%d",&(p->reserve.NmbrNuit));
                printf("entrer la date de reservation selon la forme (jour/mois/annee) : \n");
                scanf("%d",&(p->reserve.date.jour));
                scanf("%d",&(p->reserve.date.mois));
                scanf("%d",&(p->reserve.date.annee));
                printf("entrer la date de sejour selon la forme (jour/mois/annee) : \n");
                scanf("%d" , &(p->reserve.datesejour.jour));
                scanf("%d" , &(p->reserve.datesejour.mois));
                scanf("%d" , &(p->reserve.datesejour.annee));
                printf("entrer le nombre de personne : \n");
                scanf("%d", &(p->reserve.nombrepers));
                printf("---------------------------------ENTRER LE TYPE DE CHAMBRE-----------------------------------------\n");
                scanf("%s",type);
                tab_chambre(ch);
                if ((p->reserve.datesejour.mois==12) || (p->reserve.datesejour.mois==1) || (p->reserve.datesejour.mois==2)){
                    ch[p->reserve.nchambre-1].prix=ch[p->reserve.nchambre-1].prix*0.8*p->reserve.NmbrNuit;

                }
                if (p->reserve.datesejour.mois==3 || p->reserve.datesejour.mois==4 || p->reserve.datesejour.mois==5){
                    ch[p->reserve.nchambre-1].prix=ch[p->reserve.nchambre-1].prix*1*p->reserve.NmbrNuit;

                }
                if (p->reserve.datesejour.mois==6 || p->reserve.datesejour.mois==7 || p->reserve.datesejour.mois==8){
                    ch[p->reserve.nchambre-1].prix=ch[p->reserve.nchambre-1].prix*1.4*p->reserve.NmbrNuit;

                }
                if (p->reserve.datesejour.mois==9 || p->reserve.datesejour.mois==10 || p->reserve.datesejour.mois==11){
                    ch[p->reserve.nchambre-1].prix=ch[p->reserve.nchambre-1].prix*1.1*p->reserve.NmbrNuit;

                }
                printf("----------------------------- le prix est -----------------------------------\n ");
                printf("%d",ch[p->reserve.nchambre-1].prix);
                FILE *fch;
                fch=fopen("chambre.txt","w");
                int i=0;
                char chaine[15]="occupe";
                FILE *fichier = fopen("chambre.txt", "r");
                while (i<compte(fichier)){
                if(i==p->reserve.nchambre-1){
                fprintf(fch,"%d %s %d %s %d \n",ch[i].num , ch[i].typechambre ,ch[i].TV, chaine,ch[i].prix);
                }

                else{
                fprintf(fch,"%d %s %d %s %d \n",ch[i].num , ch[i].typechambre ,ch[i].TV ,ch[i].Etat,ch[i].prix);
                }
                i=i+1;
                }


                }
        }
        p=Suivant_res(p);
    }
    fp=fopen("reservations.txt","w");

    ptresli z=(*t);

    while(z!=NULL){

        fprintf(fp,"%s %s %d %d %d %d %d %d %d %d %d %d \n ",z->reserve.nom , z->reserve.prenom ,z->reserve.NmbrNuit, z->reserve.date.jour, z->reserve.date.mois, z->reserve.date.annee, z->reserve.datesejour.jour, z->reserve.datesejour.mois, z->reserve.datesejour.annee,z->reserve.nombrepers, z->reserve.nchambre,z->reserve.idres);
        z=Suivant_res(z);
    }

}
void history_res(ptresli t , char nom[15], char prenom[15]){
    ptresli p=t;
    while(p !=NULL){
        if (strcmp(p->reserve.nom,nom)==0){
                if(strcmp(p->reserve.prenom,prenom)==0){
            printf("-------------------------------------------------------------------------------- \n");
            printf("%s %s %d %d %d %d %d %d %d %d %d %d \n ",p->reserve.nom , p->reserve.prenom ,p->reserve.NmbrNuit, p->reserve.date.jour, p->reserve.date.mois, p->reserve.date.annee, p->reserve.datesejour.jour, p->reserve.datesejour.mois, p->reserve.datesejour.annee,p->reserve.nombrepers, p->reserve.nchambre,p->reserve.idres);
            }
        }
            p=Suivant_res(p);


    }
}
int nmbr_type(ptresli t,ptresli d , ptrch ch , char type[15]){
    ptresli p=t;
    int i=0;
    do{
        if (strcmp(ch[p->reserve.nchambre-1].typechambre,type)==0){
            i=i+1;
        }

        p=Suivant_res(p);
    }
    while (p!=d);
    if(strcmp(ch[d->reserve.NmbrNuit-1].typechambre,type)==0){
        i=i+1;
         }
    return i;
}
float prix(float prixx,ptresli p){
    if(p->reserve.datesejour.mois==12 || p->reserve.datesejour.mois==1 || p->reserve.datesejour.mois==2){
        prixx=prixx*0.8*p->reserve.NmbrNuit;
    }
    if(p->reserve.datesejour.mois==3 || p->reserve.datesejour.mois==4 || p->reserve.datesejour.mois==5){

        prixx=prixx*1*p->reserve.NmbrNuit;
    }
    if(p->reserve.datesejour.mois==6 || p->reserve.datesejour.mois==7 || p->reserve.datesejour.mois==8){
        prixx=prixx*1.4*p->reserve.NmbrNuit;
    }
    if(p->reserve.datesejour.mois==9 || p->reserve.datesejour.mois==10 || p->reserve.datesejour.mois==11){
        prixx=prixx*1.1*p->reserve.NmbrNuit;
    }
    return prixx;

}
float ch_aff_chambre(int nmbrch,ptresli t, ptrch ch){
    tab_chambre(ch);
    char simple[15]="simple";
    char doble[15]="double";
    char triple[15]="triple";
    ptresli p=t;
    float cmp;
    float total=0;
    int i=0;
    FILE *fichier = fopen("reservations.txt", "r");
    while(i<compte(fichier)){
        if(p->reserve.nchambre==nmbrch){
            if(nmbrch%3==1){
               cmp=4500;
               total = total+prix(cmp,p);
            }
             if(nmbrch%3==2){
               cmp=6000;
               total = total+prix(cmp,p);
            }
             if(nmbrch%3==0){
               cmp=6500;
               total = total+prix(cmp,p);
            }

        }
        i=i+1;


        p=Suivant_res(p);
            }
            return total;

}
float ch_aff_session(char session[15] , ptresli t ){
    ptresli p=t;
    char hiver[15]="hiver";
    char ete[15]="ete";
    char automne[15]="automne";
    char printemps[15]="printemps";
    float total=0;
    float prix;
    int i=0;
        FILE *fich = fopen("reservations.txt", "r");
    while(i<compte(fich)){
            prix=0;
        if (strcmp(session, hiver)==0){

        if(p->reserve.datesejour.mois==12 || p->reserve.datesejour.mois==1 || p->reserve.datesejour.mois==2){
            if (p->reserve.nchambre %3 ==1){
                prix=4500*0.8*p->reserve.NmbrNuit;
            }
            if (p->reserve.nchambre%3==2){
                prix=6000*0.8*p->reserve.NmbrNuit;
            }
            if (p->reserve.nchambre%3==0){
                prix=6500*0.8*p->reserve.NmbrNuit;
            }
    }
        }
     if (strcmp(session, ete)==0){
        if(p->reserve.datesejour.mois==6 || p->reserve.datesejour.mois==7 || p->reserve.datesejour.mois==8){
            if (p->reserve.nchambre%3==1){
                prix=4500*1.4*p->reserve.NmbrNuit;
            }
            if (p->reserve.nchambre%3==2){
                prix=6000*1.4*p->reserve.NmbrNuit;
            }
            if (p->reserve.nchambre%3==0){
                prix=6500*1.4*p->reserve.NmbrNuit;
            }
    }
     }
     if (strcmp(session, printemps)==0){
        if(p->reserve.datesejour.mois==3 || p->reserve.datesejour.mois==4 || p->reserve.datesejour.mois==5){
            if (p->reserve.nchambre%3==1){
                prix=4500*p->reserve.NmbrNuit;
            }
            if (p->reserve.nchambre%3==2){
                prix=6000*p->reserve.NmbrNuit;
            }
            if (p->reserve.nchambre%3==0){
                prix=6500*p->reserve.NmbrNuit;
            }
    }
     }
     if (strcmp(session, automne)==0){
        if(p->reserve.datesejour.mois==9 || p->reserve.datesejour.mois==10 || p->reserve.datesejour.mois==11){
            if (p->reserve.nchambre%3==1){
                prix=4500*1.1*p->reserve.NmbrNuit;
            }
            if (p->reserve.nchambre%3==2){
                prix=6000*1.1*p->reserve.NmbrNuit;
            }
            if (p->reserve.nchambre%3==0){
                prix=6500*1.1*p->reserve.NmbrNuit;
            }
    }
     }

     total=total+prix;
     p=Suivant_res(p);
     i=i+1;

    }
    return total;
}
void acces_idres(ptresli t, int code , ptresli *p , ptresli *q){
    int  trouv=0;
    (*p)=t;
    (*q)=NULL;
    while(((*p) != NULL) && (trouv==0)){
        if ((*p)->reserve.idres==code){
            trouv=1;
        }
        else{
            (*q)=(*p);
            (*p)=Suivant_res((*p));
        }
    }
}
void suppres(ptresli *t, int code){
    ptresli p,q;
    FILE *fp;
    acces_idres(*t,code,&p,&q);
    if(p!=NULL){
            if(q==NULL){
                (*t)=Suivant_res(p);
            }
            else{
                Aff_adr_res(q,Suivant_res(p));
            }
            Liberer_res(p);
    }
    else{
        printf("valeur non existance \n");
    }
    fp=fopen("reservations.txt","w");

    ptresli z=(*t);

    while(z!=NULL){

        fprintf (fp,"%s %s %d %d %d %d %d %d %d %d %d %d \n",z->reserve.nom , z->reserve.prenom ,z->reserve.NmbrNuit, z->reserve.date.jour, z->reserve.date.mois, z->reserve.date.annee, z->reserve.datesejour.jour, z->reserve.datesejour.mois, z->reserve.datesejour.annee,z->reserve.nombrepers, z->reserve.nchambre,z->reserve.idres);
        z=Suivant_res(z);
    }
}
void History_chambre(int n ,date datedonnee,resli *p,resli *d){
int dated,dater; /**Afficher l'historique d'une chambre (toutes les réservations précédentes à une date donnée)**/
dated=(datedonnee.annee*10000+datedonnee.mois*100+datedonnee.jour);/*on ecrit les dates sous la forme annee,mois,jour pour donner une priorite de l annee sur le moois et le mois sur le jour*/

    while(p!= d){/*on parcours la liste des reservations jusqu au dernier element*/
                  if (p->reserve.nchambre==n) {  /*on cherche les reservations de la chambre donnee*/
                                               dater=(p->reserve.date.annee*10000+p->reserve.date.mois*100+p->reserve.date.jour);
                                               if(dater<dated){/*on compare si la datedonnee est superieurs a la  la date de reservation,on affiche la reservation*/
                                                                 printf("%s  %s  date de reservation:%d/%d/%d  date de sejour:%d/%d/%d  nombres de nuits:%d  nombre de personnes:%d\n",p->reserve.nom,p->reserve.prenom,p->reserve.date.jour,p->reserve.date.mois,p->reserve.date.annee,p->reserve.datesejour.jour,p->reserve.datesejour.mois,p->reserve.datesejour.annee,p->reserve.NmbrNuit,p->reserve.nombrepers);
                                                               }
                                              }
                  p=Suivant_res(p);
              }

    if (p->reserve.nchambre==n){/*on traite la derniere reservation de la meme faacon*/
                                dater=(p->reserve.date.annee*10000+p->reserve.date.mois*100+p->reserve.date.jour);

                                if(dater<dated){

                                                printf("%s  %s  date de reservation:%d/%d/%d  date de sejour:%d/%d/%d  nombres de nuits:%d  nombre de personnes:%d\n",p->reserve.nom,p->reserve.prenom,p->reserve.date.jour,p->reserve.date.mois,p->reserve.date.annee,p->reserve.datesejour.jour,p->reserve.datesejour.mois,p->reserve.datesejour.annee,p->reserve.NmbrNuit,p->reserve.nombrepers);
                                               }
                               }

}
/************* Exercice1: GenLLC ***************/
void GenLLC (PtrMaillon* L,ptresli t,int anne1, int anne2){
    PtrMaillon p = NULL, q = NULL;
    ptresli rs=t;
    int i=0;
    int nb=0;
    while (nb==0){
    if (rs->reserve.datesejour.annee>=anne1){
        if(rs->reserve.datesejour.annee<=anne2){

    nb = rs->reserve.nchambre;
    Allouer (&p);
    Aff_val (p, nb);
    *L = p;
    q = p;
        }
    }
    rs=Suivant_res(rs);
    i=i+1;
    }
    while(i<7)                // Après chaque passage q contiendra l'adresse du derier maillon alloué
    {
       if (rs->reserve.datesejour.annee>=anne1){
        if(rs->reserve.datesejour.annee<=anne2){

        nb =rs->reserve.nchambre ;
        Allouer (&p);
        Aff_val (p, nb);
        Aff_adr (q, p);
        q = p;
    }
       }
       i=i+1;
       rs=Suivant_res(rs);
    }
    Aff_adr (q, NULL);      // Affecter NIL dans le champ (adr) de la queue de la liste

}
/************* Exercice3: MaxOccLLC ***************/
void MaxOccLLC (PtrMaillon L, PtrMaillon* L2, int* maxOcc){
    int cpt;
    PtrMaillon q, p = L;
    bool trouv;

    *maxOcc = 0;        // Initialisation du plus grand nombre d’occurrences à 0
    while (p != NULL)
    {
        cpt = 0;    // Remise à 0 du compteur qui va contenir le nombre d’occurrences de l’élément en cours dans la LLC
        q = L;
        // Recherche du nbre d’occurrences de l’élément pointé par p
        while (q != NULL)
        {
            if (Valeur(p)==Valeur(q))
            {
                cpt++;
            }
            q = Suivant (q);
        }
        if (cpt > *maxOcc)      // Mise à jour du plus grand nbre d’occurrences d’une valeur dans la liste L
        {
            *maxOcc = cpt;
        }
        p = Suivant (p);
    }

    p = L;
    *L2 = NULL;
    while (p != NULL)
    {
        cpt = 0;
        q = L;
        // Recherche du nbre d’occurrences de l’élément pointé par p
        while (q != NULL)
        {
            if (Valeur(p) == Valeur(q))
            {
                cpt++;
            }
            q = Suivant (q);
        }

        // Si le nombre d’occurrence de l’élément en cours = maxOcc, l’insérer dans L2 (s'il n'existe pas)
        if (cpt == *maxOcc)
        {
            q = *L2;
            trouv = false;
            while ((q!= NULL) && (!trouv))
            {
                if (Valeur (q) == Valeur(p))
                {
                    trouv = true;   // L'élément est déjà inséré dans L2
                }
                else
                {
                    q = Suivant (q);
                }
            }
            if (!trouv)     // L’élément n’existe pas dans L2
            {
                Allouer (&q);
                Aff_val (q, Valeur(p));       // Insertion en tête de liste L2
                Aff_adr (q, *L2);
                *L2 = q;
            }
        }
        p = Suivant (p);
    }
}
/************* Exercice4: AccesValLLC ***************/
void AccesValLLC (PtrMaillon L, int val, PtrMaillon* p, PtrMaillon* q){
    bool trouv = false;	// booléen indiquant la fin du parcours

	*p = L;
	*q = NULL;
    while ((*p != NULL) && (!trouv))
    {
        if (Valeur (*p) == val)
            trouv = true;
        else
        {
            *q = *p;              // On sauvegarde dans q adr du maillon
            *p = Suivant (*p);    // avant de passer au prochain avec p
        }
    }
}
/*Exercice suppression par valeur */
void SuppValLLC (PtrMaillon* L, int val){
    PtrMaillon p, q;

	AccesValLLC (*L, val, &p, &q);
    if (p != NULL)
    {
        if (q == NULL) 	        // S’il n’existe aucun maillon qui précède p :
            *L = Suivant(*L);	    // on met à jour de la tête de la liste
        else
            Aff_adr (q, Suivant(p));
        Liberer (p);            // Libération mémoire
    }
}
/************   Procédure AffichLLC  ****************/
void AffichLLC (PtrMaillon L){
    PtrMaillon p = L;
    while (p != NULL)
    {
        printf("| %d ", Valeur(p));
        p = Suivant(p);
    }
    printf("|\n");
}
void MAIN_FOCNTION_12(){PtrMaillon p ,q;
    ptresli t , d;
    int a;
    int a1,a2;
    int i=0;
    printf("entrer les deux annees \n");
    scanf("%d",&a1);
    scanf("%d",&a2);
    printf("les trois chambres le plus reserve sont : ");
    LLc_res(&t,&d);
    GenLLC(&p,t,a1,a2);
    MaxOccLLC(p,&q,&a);
    printf("%d",q->val);
    while(i<6){
    SuppValLLC(&p,q->val);
    i=i+1;
    }
    MaxOccLLC(p,&q,&a);
    printf(" %d",q->val);
    i=0;
    FILE *fp;
    fp=fopen("reservations.txt","r");
    while(i<compte(fp)){
    SuppValLLC(&p,q->val);
    i=i+1;
    }
    MaxOccLLC(p,&q,&a);
    printf(" %d",q->val);
    }
int calcul_nmbr_jour(date datedonne){/*calculer le nombre de jour depuid debut d annee*/
    int nbj[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int i=0,nmbrjour=0;
    for (i=0;i<(datedonne.mois-1);i++){
     nmbrjour=nmbrjour+nbj[i];
    }
    nmbrjour=nmbrjour+datedonne.jour;
    if(((datedonne.annee%4)== 0)&&(datedonne.mois>2)){nmbrjour++;}
    return nmbrjour;
}
void Res_Perc_Chambre(date datedonne,int nchambre,resli *t,resli *d){
    float cpt=0;
    float prct;
    int dated=(datedonne.annee*10000+datedonne.mois*100+datedonne.jour);
    int dates,j;
    while(t != d){
            if((t->reserve.nchambre==nchambre)&&(t->reserve.datesejour.annee==datedonne.annee)){
                    if (calcul_date_sortie(t->reserve.datesejour,t->reserve.NmbrNuit)<=dated){cpt=cpt+(t->reserve.NmbrNuit);}
                       else{dates=t->reserve.datesejour.annee*10000+t->reserve.datesejour.mois*100+t->reserve.datesejour.jour;
                         if((calcul_date_sortie(t->reserve.datesejour,t->reserve.NmbrNuit)>dated)&&(dates<=dated)){j=0;
                            while(calcul_date_sortie(t->reserve.datesejour,j)<=dated){j++;}
                            cpt=cpt+j;
                         }}
                      }
     t=Suivant_res(t);
    }
    if((t->reserve.nchambre==nchambre)&&(t->reserve.datesejour.annee==datedonne.annee)){
                    if (calcul_date_sortie(t->reserve.datesejour,t->reserve.NmbrNuit)<=dated){cpt=cpt+(t->reserve.NmbrNuit);}
                       else{dates=t->reserve.datesejour.annee*10000+t->reserve.datesejour.mois*100+t->reserve.datesejour.jour;
                         if((calcul_date_sortie(t->reserve.datesejour,t->reserve.NmbrNuit)>dated)&&(dates<=dated)){j=0;
                            while(calcul_date_sortie(t->reserve.datesejour,j)<=dated){j++;}
                            cpt=cpt+j;
                         }}}
    prct=(cpt/(calcul_nmbr_jour(datedonne))*100);
    printf("le pourcentage de reservation de la chambre %d est : %f\n",nchambre,prct);


}
int calcul_date_sortie(date datesejour,int nmbrnuits){ /*calculer la date de sortie selon la date de sejour et nombre de nuits*/
 int nbj[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 date datesortie=datesejour;
 int nuits=nmbrnuits;
 while (nuits>=nbj[datesortie.mois-1]){if ((datesortie.annee%4)== 0){nbj[1]=29;}else{nbj[1]=28;}
    nuits=nuits-nbj[datesortie.mois-1];
    if(datesortie.mois==12){
        datesortie.mois=1;
        datesortie.annee++;}
    else{datesortie.mois=datesortie.mois+1;}
 }
    if ((datesortie.annee%4)== 0){nbj[1]=29;}else{nbj[1]=28;}

    if((nuits+datesortie.jour)>nbj[datesortie.mois-1]){
             if(datesortie.mois==12){datesortie.annee++;
               datesortie.mois=1;
               datesortie.jour=(nuits+datesortie.jour)%31;
             }
             else{
               datesortie.jour=(nuits+datesortie.jour)%nbj[datesortie.mois-1];
               datesortie.mois++;}

    }else{datesortie.jour=datesortie.jour+nuits;}
           if ((datesortie.annee%4)== 0){
            if((datesortie.mois==2) && (datesortie.jour==30)){datesortie.jour=1;
             datesortie.mois=3;}
           }else{
             if((datesortie.mois==2) && (datesortie.jour==29)){datesortie.jour=1;
             datesortie.mois=3;}
             if((datesortie.mois==2) && (datesortie.jour==30)){datesortie.jour=2;
             datesortie.mois=3;}
            }
            if (datesortie.jour==0){datesortie.jour=30;}

    return datesortie.annee*10000+datesortie.mois*100+datesortie.jour;

}
void Cli_ocp_mtype(char type[10],resli *t,resli *d,date dateactuelle,chambre *ch){
     int datesej,dateactu,datesor;
     dateactu=(dateactuelle.annee*10000+dateactuelle.mois*100+dateactuelle.jour);
    while(t != d){datesej=t->reserve.datesejour.annee*10000+t->reserve.datesejour.mois*100+t->reserve.datesejour.jour;
                  datesor=calcul_date_sortie(t->reserve.datesejour,t->reserve.NmbrNuit);
       if((strcasecmp(type,ch[t->reserve.nchambre-1].typechambre)==0)&&(ch[t->reserve.nchambre-1].TV==1)&&(dateactu<datesor)&&(dateactu>=datesej))/*pour que une chambre soit occupee il faut que la date de sejour soit inferieure ou egale a la date d aujourdhui et la date de sortie soit superieure a la date d aujourdui*/
       {printf("%s,%s\n",t->reserve.nom,t->reserve.prenom);}                                                                                      /*on verifie le type de la chambre et la disponibilite dune tv en utilisant ch[numero de la chambre-1]care les informations de la chambre n se trouve a la case numero n-1 dans le tableau des chambres*/
       t=Suivant_res(t);
    }
    datesej=t->reserve.datesejour.annee*10000+t->reserve.datesejour.mois*100+t->reserve.datesejour.jour;
                  datesor=calcul_date_sortie(t->reserve.datesejour,t->reserve.NmbrNuit);
       if((strcasecmp(type,ch[t->reserve.nchambre-1].typechambre)==0)&&(ch[t->reserve.nchambre-1].TV==1)&&(dateactu<datesor)&&(dateactu>=datesej))
       {printf("%s,%s\n",t->reserve.nom,t->reserve.prenom);}


}
float montant_res(resli *p,chambre *ch){
 int datesej=p->reserve.datesejour.mois*100+p->reserve.datesejour.jour;
 float total=0;
 char type1[10]="simple",type2[10]="double",type3[10]="triple";
 if (strcasecmp(ch[p->reserve.nchambre-1].typechambre,type1)==0){total=4500;}/*on initialise le total selon le type de la chambre*/
 if (strcasecmp(ch[p->reserve.nchambre-1].typechambre,type2)==0){total=6000;}
 if (strcasecmp(ch[p->reserve.nchambre-1].typechambre,type3)==0){total=6500;}
 if ((datesej>=1221)||(datesej<321)){total=total*0.8;}/*on decide le prix finale dune nuit selon la saison du debut de sejour en comparant les mois et les jours*/
 if ((datesej>=621)&&(datesej<921)){total=total*1.4;}
 if ((datesej>=921)&&(datesej<1221)){total=total*1.1;}
 return total*p->reserve.NmbrNuit;/* on renvoie le total en multipliyant le prix d une nuit par le nombe total de nuits*/
}
void Factures_Res(int nombrechambres,resli *t,resli *d,clientli *ct,chambre *ch,ptrfactli *tf,ptrfactli*df){
int i=0;
resli *p;
clientli *cp;
cp=ct;
p=t;
int cpt;
ptrfactli k;
 for (i=1;i<=nombrechambres;i++){
        t=p;/*on varie i de 1 au nombre de chambre pour trier les facture sselon le num de la chambre*/
       while(t != d){
               if(t->reserve.nchambre==i){/*on parcours les reservations si on trouve le meme numero de chambre ,on parcours la listes des clients pour trouver le client avec le meme nom et prenom de la reservation pour recuperer le code de ce client*/
                    ct=cp;

                   while((strcmp(ct->client.nom,t->reserve.nom)!=0)||(strcmp(ct->client.prenom,t->reserve.prenom)!=0)){ct=Suivant_n(ct);}
                   printf("numero de chambre:%d  code du client:%d  identifiant de la reservation:%d  nombre de nuits:%d  montant:%f\n",i,ct->client.code,t->reserve.idres,t->reserve.NmbrNuit,montant_res(t,ch));
              if(cpt==0){
                    allouer_fact(&k);
                    *tf=k;
                    *df=k;
                    (*df)->facture.numchambre=i;
                    (*df)->facture.codecli=ct->client.code;
                    (*df)->facture.identres=t->reserve.idres;
                    (*df)->facture.nmbrnuits=t->reserve.NmbrNuit;
                    (*df)->facture.montant=montant_res(t,ch);
                    cpt++;
                   }
                   else{allouer_fact(&k);
                    *df=k;
                    (*df)->facture.numchambre=i;
                    (*df)->facture.codecli=ct->client.code;
                    (*df)->facture.identres=t->reserve.idres;
                    (*df)->facture.nmbrnuits=t->reserve.NmbrNuit;
                    (*df)->facture.montant=montant_res(t,ch);}
                    }
               t=Suivant_res(t);
       }
       if(t->reserve.nchambre==i){ct=cp;

                   while((strcmp(ct->client.nom,t->reserve.nom)!=0)||(strcmp(ct->client.prenom,t->reserve.prenom)!=0)){ct=Suivant_n(ct);}
                   printf("numero de chambre:%d  code du client:%d  identifiant de la reservation:%d  nombre de nuits:%d  montant:%f\n",i,ct->client.code,t->reserve.idres,t->reserve.NmbrNuit,montant_res(t,ch));
              if(cpt==0){
                    allouer_fact(&k);
                    *tf=k;
                    *df=k;
                    (*df)->facture.numchambre=i;
                    (*df)->facture.codecli=ct->client.code;
                    (*df)->facture.identres=t->reserve.idres;
                    (*df)->facture.nmbrnuits=t->reserve.NmbrNuit;
                    (*df)->facture.montant=montant_res(t,ch);
                    cpt++;
                   }
                   else{allouer_fact(&k);
                    *df=k;
                    (*df)->facture.numchambre=i;
                    (*df)->facture.codecli=ct->client.code;
                    (*df)->facture.identres=t->reserve.idres;
                    (*df)->facture.nmbrnuits=t->reserve.NmbrNuit;
                    (*df)->facture.montant=montant_res(t,ch);}
                     }
 }

}
void create_res_type(resli *p,resli *d,ptresli *t1,ptresli *d1,char type[10],chambre *ch){
    ptresli k;
*t1=NULL;

while (*t1 == NULL){
    if (strcmp(type,ch[p->reserve.nchambre-1].typechambre)==0){
        Allouer_res(&k);
        *t1=k;
        *d1=k;
        (*t1)->reserve=p->reserve;

    }
    p=Suivant_res(p);
}
if (t1!=NULL){
        while(p!=d){
            if (strcmp(type,ch[p->reserve.nchambre-1].typechambre)==0){
                Allouer_res(&k);
                Aff_adr_res(*d1,k);
                *d1=Suivant_res(*d1);
                (*d1)->reserve=p->reserve;
            }
            p=Suivant_res(p);
        }
        if (strcmp(type,ch[p->reserve.nchambre-1].typechambre)==0){
                Allouer_res(&k);
                Aff_adr_res(*d1,k);
                *d1=Suivant_res(*d1);
                (*d1)->reserve=p->reserve;}



}}
void tri_liste_montant(resli *t1 , resli *d1,chambre *ch){
    bool permut=1;
    resli tmp;
    resli*p=t1;
    while(permut==1){
        permut=0;

        while(Suivant_res(p) != d1){
          if(montant_res(p,ch)>montant_res(Suivant_res(p),ch)){
           tmp.reserve=p->reserve;
           t1->reserve=Suivant_res(p)->reserve;
           Suivant_res(p)->reserve=tmp.reserve;
           permut=1;

          }
          t1=Suivant_res(p);
        }
        if(montant_res(p,ch)>montant_res(Suivant_res(p),ch)){
           tmp.reserve=p->reserve;
           p->reserve=Suivant_res(p)->reserve;
           Suivant_res(p)->reserve=tmp.reserve;
           permut=1;}
    }



}
void fusionner_2listes(resli *t1,resli *d1,resli *t2,resli *d2,ptresli *ft1,ptresli *fd1,chambre *ch){
resli *p1;
resli *p2;
resli *q;
p1=t1;
p2=t2;
Aff_adr_res(d1,NULL);
Aff_adr_res(d2,NULL);

     if(montant_res(p1,ch)<=montant_res(p2,ch)){*ft1=p1;
                                            p1=Suivant_res(p1); }
    else{*ft1=p2;
         p2=Suivant_res(p2);}
     q=*ft1;
    while((p1!=NULL)&&(p2!=NULL)){
        if(montant_res(p1,ch)<=montant_res(p2,ch)){Aff_adr_res(q,p1);
                                                   q=p1;
                                                   p1=Suivant_res(p1); }
        else{Aff_adr_res(q,p2);
             q=p2;
            p2=Suivant_res(p2);}
    }
    if(p1==NULL){Aff_adr_res(q,p2);
                 *fd1=d2;}
    else{Aff_adr_res(q,p1);
          *fd1=d1;}

    }
void fusionner_3listes(resli *t1,resli *d1,resli *t2,resli *d2,resli *t3,resli *d3,ptresli *ft2,ptresli *fd2,chambre *ch){
        resli *ft1;
        resli *fd1;
        fusionner_2listes(t1,d1,t2,d2,&ft1,&fd1,ch);
        fusionner_2listes(ft1,fd1,t3,d3,ft2,fd2,ch);
        while(*ft2 != *fd2){
            printf("%f",montant_res(*ft2,ch));
            *ft2=Suivant_res(*ft2);
          }

        printf("%f",montant_res(*ft2,ch));
    }


int main(){
    ptresli p,d,t1,d1,d2,t2,d3,ft2,fd2;
    chambre ch[100];
    create_res_type(&p,&d,&t1,&d,"simple",ch);

    return 0;
 }
