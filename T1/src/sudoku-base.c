#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* grid size = 9x9 */
#define SIZE 9
#define MAX 362880 // 9!

int (*grid)[9];
int max_threads;
char *filename;
int *thread_number;
int errors;
pthread_mutex_t mutex_error;

/* Funcao que le um grid do arquivo "filename" e o armazena em uma matriz */
int load_grid(char *filename) {
	grid = (int (*)[9])malloc(sizeof(*grid)*9);

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

void *calculate(void *t_number) {
	int tn = *(int*)t_number;
	int mult_line, mult_column, mult_region, initial_point;

	for(int i = tn; i < 27; i = i+max_threads){

		switch(i/9){
		case 0:
			mult_line = 1;
			for(int j = 0; j < 9; j++)
			{
				mult_line *= grid[i][j]; // grid[x][y] x = position/9, y = position%9 ... position [0 .. 80] //*(grid[0]+i)//

				if(j == 8){
					if( mult_line != MAX){
						printf("Thread %d: erro na linha %d.\n", tn+1, i+1);
						pthread_mutex_lock(&mutex_error);
						errors += 1;
						pthread_mutex_unlock(&mutex_error);
					}
				}
			}

			break;

		case 1:
			mult_column = 1;
			for(int j = 0; j < 9; j++){

				mult_column *= grid[j][i-9]; // grid[x][y] x = position/9, y = position%9 ... position [0 .. 80] //*(grid[0]+i)//

				if(j == 8){
					if( mult_column != MAX){
						printf("Thread %d: erro na coluna %d.\n", tn+1, i-8);
						pthread_mutex_lock(&mutex_error);
						errors += 1;
						pthread_mutex_unlock(&mutex_error);
					}
				}
			}

			break;

		case 2:
			mult_region = 1;
			initial_point = ((int)((i-18)/3)*27)+(((i-18)%3)*3);

			for(int j = 0; j < 3; j++){
				mult_region *= *(grid[0]+initial_point);
				mult_region *= *(grid[0]+initial_point+1);
				mult_region *= *(grid[0]+initial_point+2);
				initial_point += 9;
			}
			if( mult_region != MAX){
				printf("Thread %d: erro na regiao %d.\n", tn+1, i-17);
				pthread_mutex_lock(&mutex_error);
				errors += 1;
				pthread_mutex_unlock(&mutex_error);
			}

			break;
		}
	}
	return NULL;
}

static void start_threads(void){
	pthread_t threads[max_threads];
	for (int i = 0; i < max_threads; i++) {
		pthread_create(&threads[i], NULL, calculate, (void*)(&thread_number[i]));
	}
	for (int i = 0; i < max_threads; i++) {
		pthread_join(threads[i], NULL);
	}
}

void initialize_variables(int m_threads){
	thread_number = (int*)malloc(m_threads*sizeof(int));

	pthread_mutex_init(&mutex_error, NULL); // It protects the errors variable
	errors = 0;

	for(int i = 0; i < max_threads; i++){
		thread_number[i] = i;
	}

	/* Le o grid do arquivo, armazena na matriz grid e imprime */


}

void initialize_grid(int (*p_grid)[9]){
	grid = p_grid;
}

int initialize_grid_file(){
	if(load_grid(filename)) {
		printf("Quebra-cabecas fornecido:\n");
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++)
				printf("%d ", grid[i][j]);
			printf("\n");
		}
		printf("\n");
		return 1;
	}
	return 0;
}

#ifndef BENCH
int main(int argc, char *argv[]) {

	if(argc != 3) {
		printf("Erro: informe o arquivo de entrada e o número de threads!\nUso: %s <arquivo de entrada>\n\n", argv[0]);
		return 1;
	}

	max_threads = atoi(argv[2]);
	filename = argv[1];

	initialize_variables(max_threads);
	int grid_p[9][9] = {{3, 5, 4, 6, 7, 8, 9, 1, 2},
						{6, 7, 2, 1, 9, 5, 3, 4, 8},
						{1, 9, 8, 3, 4, 2, 5, 6, 7},
						{8, 5, 9, 7, 6, 1, 4, 2, 7},
						{4, 2, 6, 8, 5, 3, 7, 9, 1},
						{7, 1, 3, 9, 2, 4, 8, 5, 6},
						{9, 6, 1, 5, 3, 7, 2, 8, 4},
						{2, 8, 7, 4, 1, 9, 6, 3, 5},
						{3, 4, 5, 2, 8, 6, 1, 7, 9}};
	initialize_grid(grid_p);
	// initialize_grid_file();

	start_threads(); // May the war begin
	printf("Erros encontrados: %d.\n", errors);


	return 0;
}
#endif //BENCH
