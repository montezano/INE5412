#include <stdio.h>

/* grid size = 9x9 */
#define SIZE 9
#define MAX 362880 // 9!

/* Funcao que le um grid do arquivo "filename" e o armazena em uma matriz */
int load_grid(int grid[][SIZE], char *filename) {
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
void verify(int grid[][SIZE]) {
	int mult = 1;
	int columns[SIZE] = {[0 ... (SIZE-1)] = 1}; // it works with gcc
	int region[SIZE] = {[0 ... (SIZE-1)] = 1};

	for(int i = 0; i < 81; i++) {
		int result = grid[i/SIZE][i%SIZE]; // grid[x][y] x = position/9, y = position%9 ... position [0 .. 80]
		columns[i%SIZE] *= result;
		region[((i%SIZE)/3)+(((i/SIZE)/3)*3)] *= result; // Add it to a region

		mult *= result;

		if((i+1)%SIZE == 0){
			if( mult != MAX)
				printf("erro na linha %d\n", (i-1)/SIZE);
			mult = 1;
		}
	}

	for(int i = 0; i < SIZE; i++){
		if(columns[i] != MAX)
			printf("erro na coluna %d\n", i);
		if(region[i] != MAX)
			printf("erro na regiao %d\n", i);
	}

}


int main(int argc, char *argv[]) {

	if(argc != 2) {
		printf("Erro: informe o arquivo de entrada!\nUso: %s <arquivo de entrada>\n\n", argv[0]);
		return 1;
	}

	/* Le o grid do arquivo, armazena na matriz grid e imprime */
	int grid[9][9];
	if(load_grid(grid, argv[1])) {
		printf("Quebra-cabecas fornecido:\n");
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++)
				printf("%d ", grid[i][j]);
			printf("\n");
		}
		printf("\n");
		verify(grid);
	}

	return 0;
}
