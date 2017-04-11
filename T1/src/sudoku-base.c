#include <stdio.h>
#include <stdlib.h>

/* grid size = 9x9 */
#define SIZE 9
#define MAX 362880 // 9!

int grid[9][9];
int max_threads;
int *thread_number;
int *jobs;


/* Funcao que le um grid do arquivo "filename" e o armazena em uma matriz */
int load_grid(char *filename) {
	FILE *input_file = fopen(filename, "r");

	if (input_file != NULL) {
		for(int i = 0; i < SIZE; i++)
			for(int j = 0; j < SIZE; j++)
				fscanf(input_file, "%d", &grid[i][j]);
		fclose(input_file);
		return 1;
	}

	return 0;
}

/**
*	It looks for sudoku errors
**/
void verify_line(int *t_number) {
	int mult_line = 1;

	int t_number_count = t_number;

	for(int i = t_number_count*9; i < (t_number_count+1)*9 ; i++) {

		mult_line *= grid[i/SIZE][i%SIZE]; // grid[x][y] x = position/9, y = position%9 ... position [0 .. 80] //*(grid[0]+i)//

		if((i+1)%SIZE == 0){
			if( mult_line != MAX)
				printf("erro na linha %d\n", (i-1)/SIZE);
			mult_line = 1;
		}
	}
}

void verify_column() {
	int mult_column = 1;

	for(int i = 0; i < 81; i++) {
		mult_column *= grid[i%SIZE][i/SIZE]; // grid[x][y] x = position/9, y = position%9 ... position [0 .. 80] //*(grid[0]+i)//		

		if((i+1)%SIZE == 0){
			if( mult_column != MAX)
				printf("erro na coluna %d\n", (i-1)/SIZE);
			mult_column = 1;
		}
	}
}

void verify_region() {
	int mult_region = 1;

	//int region[SIZE] = {[0 ... (SIZE-1)] = 1};
	for(int i = 0; i < 9; i++) {
		int initial_point = ((int)(i/3)*27)+((i%3)*3);
		for(int j = 0; j < 3; j++){
			mult_region *= *(grid[0]+initial_point);
			mult_region *= *(grid[0]+initial_point+1);
			mult_region *= *(grid[0]+initial_point+2);

			initial_point += 9;
		}
		if( mult_region != MAX)
				printf("erro na regiao %d\n", i);
		mult_region = 1;
	}

}

void calculate(){
	pthread_t threads[max_threads];

	switch(max_threads%3){
		case 0: //9 LINHAS DIVIDIAS PARA 1/3 DAS THREADS
		for(int i = 0; i < max_threads/3; i++){
			pthread_create(&threads[i], NULL, verify_line, (void*)(&thread_number[i]));
		}
		
		break;
		case 1:


		break;
		case 2:


		break;
	}
	for(int i = 0; i < max_threads; i++){
		while
	}

	for (int i = 0; i < 9; i++) {
		pthread_create(&threads[i], NULL, verify_line, (void*)(&thread_number[i]));
	}

	for (int i = 0; i < max_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	for(int i = 0; i < 9; i++){
		printf("%d\n", thread_number[i%max_threads]);

	}
}

int main(int argc, char *argv[]) {


	if(argc != 3) {
		printf("Erro: informe o arquivo de entrada e o número de threads!\nUso: %s <arquivo de entrada>\n\n", argv[0]);
		return 1;
	}

	max_threads = atoi(argv[2]);
	thread_number = malloc(sizeof(int)*max_threads);
	jobs = malloc(sizeof(int)*27);

	for(int i = 0; i < max_threads; i++){
		thread_number[i] = i;
	}

	for(int i = 0; i < 27; i++){
		jobs[i] = i;
	}

	calculate();

	/* Le o grid do arquivo, armazena na matriz grid e imprime */

	if(load_grid(argv[1])) {
		printf("Quebra-cabecas fornecido:\n");
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++)
				printf("%d ", grid[i][j]);
			printf("\n");
		}
		printf("\n");
		verify_line(grid);
		verify_column(grid);
		verify_region(grid);
	}

	return 0;
}
