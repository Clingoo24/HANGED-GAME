//abbiamo delle parole in un file di testo e le vogliamo identificare con un numero e memorizzare
#include "prot.h"

int main(){

	srand(time(NULL));
	FILE *fp;
	struct Frase *vect;
	
	char frase_pc[SIZE];
	
	int dim;

	fp = apertura();

	dim = conta_righe(fp);
	
	vect = alloc_vect(dim);
	
	fp = apertura();
	
	init_vect(fp, vect, dim);
	
	strcpy( frase_pc, pick_random_frase(vect, dim) );
	
	inizio_gioco(frase_pc, SIZE);
	
	free((void *)vect);
	return 0;
}
