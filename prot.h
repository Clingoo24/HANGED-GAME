#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 255
#define DATI	0
#define ALLOC 	1
#define APER	2
#define	LTR	3

struct Frase{

	char frase[SIZE];
	int identificativo;
};

FILE* apertura(void);

int conta_righe(FILE* fp);

struct Frase* alloc_vect(int dim);

void init_vect(FILE *fp, struct Frase *vect, int dim);

char* pick_random_frase(struct Frase *vect, int dim);

void inizio_gioco(char *frase_pc, int dim);

void stampa(struct Frase *vect, int dim);

void gest_err(int err);
