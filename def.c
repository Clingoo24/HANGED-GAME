#include "prot.h"

FILE* apertura(){

	FILE* fp;
	
	fp = fopen("diz.txt", "r");
	
	if (fp == NULL) gest_err(APER);

	return fp;
}

int conta_righe(FILE *fp){

	char frase[SIZE];
	int count = 0;

	while(fgets(frase, SIZE, fp) != NULL)
		count++;
		
	fclose(fp);
	
	return count;
}

struct Frase* alloc_vect(int dim){

	struct Frase *vect;
	
	vect = (struct Frase *)malloc(dim * sizeof(struct Frase));
	
	if (vect == NULL) gest_err(ALLOC);

	return vect;
}

void init_vect(FILE *fp, struct Frase *vect, int dim){

	for (unsigned int i = 0; i < dim; i++){
	
		(*(vect + i)).identificativo = i;
		
		if ( fgets( (*(vect + i)).frase, SIZE, fp) == NULL) gest_err(LTR);
	}
}

char* pick_random_frase(struct Frase *vect, int dim){

	int pick = rand() % (dim - 1);

	return (*(vect + pick)).frase;
}


void inizio_gioco(char *frase_pc, int dim){

	void frase_utente_asterischi(char *frase_utente);
	int corrispondenze(char *frase_utente, char *frase_pc, char lettera);
	int soluzione(char *frase_completa, char *frase_pc); 

	char frase_utente[dim];
	char frase_completa[dim];
	
	strcpy( frase_utente, frase_pc );
	
	frase_utente_asterischi(frase_utente);
	
	int fermati = -1;
	char lettera;
	int tentativi = 5;
	int flag = 0;
	
	while((fermati != 0) && (tentativi > 0)){
	
		printf("%s\n",frase_utente);
		printf("Tentativi residui: %d\n", tentativi);
		printf("Scegli:\n");
		printf("1) do una lettera\n");
		printf("2) provo a dare la soluzione\n");
		printf("0) esci\n\n");
		
		if ((scanf("%d",&fermati) != 1) || (fermati < 0) || (fermati > 2)) gest_err(DATI);
		
		if (fermati == 0){
		
			printf("\n\nStai uscendo dal gioco, arresto...\n");
			exit(-1);
		}
		
		if (fermati == 1){
			
			printf("Inserisci una lettera: ");
			if (scanf(" %c",&lettera) != 1) gest_err(DATI);
			
			if (corrispondenze(frase_utente, frase_pc, lettera))
				printf("lettera %c presente!\n\n",lettera);
			else { 
			
				printf("lettera non presente\n\n");
				tentativi--;
			}
		}
		
		if (fermati == 2){
		
			printf("prova a darmi la soluzione: ");
			
			if (scanf("%s",frase_completa) != 1) gest_err(DATI);
			
			flag = soluzione(frase_completa, frase_pc);
			
			if (flag == (((dim - flag) - dim) * (-1))){
			
				printf("Hai inserito la frase \"%s\"\n",frase_completa);
				printf("Hai vinto!\n");
				printf("La frase era %s\n", frase_pc);
				exit(-1);
				
			} else {
			
				printf("Hai inserito la frase \"%s\"\n", frase_completa);
				printf("La frase non corrisponde! riprova.\n");
				tentativi--;
			}
		}
	}
	
	printf("\n\n\nTentativi esauriti, arresto...\n");
	exit(-1);
}

void frase_utente_asterischi(char *frase_utente){

	int i = 0;

	while(*(frase_utente + i) != '\0'){
	
		if ( ( (*(frase_utente + i) >= 65) && (*(frase_utente + i) <= 90) ) || ( (*(frase_utente + i) >= 97) && (*(frase_utente + i) <= 122) )) *(frase_utente + i) = '*';
		i++;
	}
}

int corrispondenze(char *frase_utente, char *frase_pc, char lettera){

	int i = 0;
	int count = 0;

	while(*(frase_pc + i) != '\0'){
	
		if (*(frase_pc + i) == lettera){
		
			*(frase_utente + i) = lettera;
			++count;
		}
	
		i++;
	}
	
	return count;
}

int soluzione(char *frase_completa, char *frase_pc){

	int count = 0;
	int i = 0;
	
	while(*(frase_pc + i) != '\0'){
	
		if (*(frase_pc + i) == *(frase_completa + i))
			++count;
		
		i++;
	}
	
	return count;
}

void stampa(struct Frase *vect, int dim){

	for (unsigned int i = 0; i < dim; i++){
	
		printf("Frase: %s\n", (*(vect + i)).frase);
		printf("Idx: %d\n\n", (*(vect + i)).identificativo);
	}
}

void gest_err(int err){

	switch(err){
	
		case 0:		printf("Errore inserimento dati, uscita...\n");
				exit(-1);
			break;
			
		case 1:		printf("Errore Allocazione, uscita...\n");
				exit(-1);
			break;
			
		case 2:		printf("Errore apertura file, uscita...\n");
				exit(-1);
			break;
			
		case 3:		printf("Errore lettura dati da file, uscita...\n");
				exit(-1);
			break;	
	}
}
