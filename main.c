////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

void lireCommande(char commande[29]);
void cherche (int ref, char* label[50], float* prix);
int stockage(int ref, int nombre);

int lireProchaineCommande() //pour lire l'int contenu dans nextFact
{
FILE *f;
int N;
f=fopen("nextFact","r");
fread(&N,sizeof(int),1,f);
fclose(f);
//printf("\n--->lu N=%d",N);
return N;
}

void convertirNenChaine4(int N,char *N4) //convertit l'int N en une chaine de 4 caracteres
{ // si N=1234 alors N4 sera égal à "1234"
int m,c,d,u;
char cm,cc,cd,cu;
m=N/1000;cm=48+m;
N%=1000;
c=N/100;cc=48+c;
N%=100;
d=N/10;cd=48+d;
u=N%10;
cu=48+u;
N4[0]=cm;N4[1]=cc;N4[2]=cd;N4[3]=cu;N4[4]='\0';
}


void lireLesCommandes() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
FILE *ficCommande=NULL;
int FINI=0;
int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
char NNNN[5];
char nomCommande[29];

do //ce do while prend fin dès que fichier commandeXXXX.txt est absent 
	{
	strcpy(nomCommande,"./commandes/commande");
	convertirNenChaine4(N,NNNN); 
	//printf("\n==>%s<==",NNNN);
	ficCommande=NULL;
	strcat(nomCommande,NNNN);
	strcat(nomCommande,".txt");
	
	//printf("\n traitement de  %s",nomCommande);
	
	ficCommande=fopen(nomCommande,"rt");
	if (ficCommande!=NULL)
		{ // le fichier commandeNNNN.txt existe
			//printf("\nFichier %s présent\n",nomCommande);
			lireCommande(nomCommande); // à vous de coder cette fonction lors de ce TP9
			fclose(ficCommande);
		}
	else
		{
			printf("\nToutes les commandes présentes ont été traitées.\n");
			FILE *f=fopen("nextFact","w"); // on va ecrire la valeur de N dans enxtFact 
			// pour 
			fwrite(&N,1,sizeof(int),f);
			fclose(f);
			FINI=1;			
		}

	N++;
	}while(FINI==0);		

}

void lireCommande(char commande[29]){

	int i;
	int ref, number;
	char nom[30];
	char label [50];
	float prix;
	float total=0;
	char fact[29] = "./factures/factureXXXX.txt";
	
	for(i=18; i<22; i++) fact[i] = commande[i+2];
	
	FILE *g=fopen(fact, "w");
	
	//printf("%s Yo \n",commande);
	FILE *f=fopen(commande,"r");
	//fread(&nom,sizeof(nom),1,f);
	fscanf(f, "%s\n", &nom);
	
	fprintf(g,"Client : %s\n\n", nom);
	
	do {
		ref = 0;
		fscanf(f, "%d %d\n", &ref, &number);
		
		if (!stockage(ref, number)){
			FILE *h=fopen("./alertes.txt", "a");
			fprintf(h, "%d\n", ref);
			fclose(h);
		}
		
		if (ref){
			cherche(ref, &label, &prix);
			//printf("Nom : %s\n", &label);
			//printf("Prix : %f\n", prix*number);
			total += prix*number;
			
			fprintf(g,"%d %s (PU = %.2f€) :: %.2f€\n", number, label, prix, prix*number);
		}
		//printf("Le total est de : %f\n", total);
	} while (ref);
	
	fprintf(g,"\nTOTAL = %.2f\n", total);
	
	fclose(f);
	fclose(g);
}

void cherche (int ref, char* label[50], float* prix){
	int prod=0;
	FILE *f=fopen("./produits.txt", "r");
	while(prod!=ref){
		fscanf(f, "%d %s %f\n", &prod, label, prix);
	}
}

int stockage(int ref, int nombre){
	int prod;
	int stock;
	int out = 0;
	FILE *f=fopen("./stock.txt", "r");
	FILE *g=fopen("./stock2.txt", "w");
	do{
		prod = 0;
		fscanf(f, "%d %d\n", &prod, &stock);
		if (prod == ref){
			if (stock >= nombre){
				stock -= nombre;
				out = 1;
			} else out = 0;
			
			
		}
		if (prod) fprintf(g, "%d %d\n", prod, stock);
	} while(prod);
	
	fclose(f);
	fclose(g);
	
	system("cp stock2.txt stock.txt");
	
	return out;
	
}

int main()
{
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 
	
	
	/*FILE *f;int N=1;
	f=fopen("nextFact","w");
	fwrite(&N,1,sizeof(int),f);
	fclose(f);*/

	//PARTIE 1 du TP : sans Gestion de stock
	lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	

	//PARTIE 2 du TP : avec Gestion de stock
	//copiez coller votre travail précédent puis modifiez le  
	//lireLesCommandes2(); 	

	return 0;
}
