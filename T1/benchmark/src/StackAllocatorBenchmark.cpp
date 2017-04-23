#include "hayai.hpp"
#include "sudoku-base.c"

class SudokuCheckerBenchmark
	: public ::hayai::Fixture
{
	virtual void SetUp() {

	}

	virtual void TearDown() {
	}
};
int correct_grid[9][9] = {	{5, 3, 4, 6, 7, 8, 9, 1, 2},
							{6, 7, 2, 1, 9, 5, 3, 4, 8},
							{1, 9, 8, 3, 4, 2, 5, 6, 7},
							{8, 5, 9, 7, 6, 1, 4, 2, 3},
							{4, 2, 6, 8, 5, 3, 7, 9, 1},
							{7, 1, 3, 9, 2, 4, 8, 5, 6},
							{9, 6, 1, 5, 3, 7, 2, 8, 4},
							{2, 8, 7, 4, 1, 9, 6, 3, 5},
							{3, 4, 5, 2, 8, 6, 1, 7, 9}};

int wrong_grid[9][9] = {{3, 5, 4, 6, 7, 8, 9, 1, 2},
						{6, 7, 2, 1, 9, 5, 3, 4, 8},
						{1, 9, 8, 3, 4, 2, 5, 6, 7},
						{8, 5, 9, 7, 6, 1, 4, 2, 7},
						{4, 2, 6, 8, 5, 3, 7, 9, 1},
						{7, 1, 3, 9, 2, 4, 8, 5, 6},
						{9, 6, 1, 5, 3, 7, 2, 8, 4},
						{2, 8, 7, 4, 1, 9, 6, 3, 5},
						{3, 4, 5, 2, 8, 6, 1, 7, 9}};

// BENCHMARK(SudokuCheckerBenchmark, Allocator_benchmark, 50, 10000) {
// 	StackAllocator::getInstance().Allocator(sizeof(int));
// }


//Parametized benchmarks
BENCHMARK_P_F(SudokuCheckerBenchmark, correct, 50, 1000, (int m_threads)) {
	initialize_variables(m_threads);
	initialize_grid(correct_grid);
	start_threads();
}

// BENCHMARK_P_F(SudokuCheckerBenchmark, incorrect, 50, 1000, (int m_threads)) {
// 	malloc(bytes);
// }

BENCHMARK_P_INSTANCE(SudokuCheckerBenchmark, correct,(27));
BENCHMARK_P_INSTANCE(SudokuCheckerBenchmark, correct,(3));
BENCHMARK_P_INSTANCE(SudokuCheckerBenchmark, correct, (1));
BENCHMARK_P_INSTANCE(SudokuCheckerBenchmark, correct, (243));

// BENCHMARK_P_INSTANCE(SudokuCheckerBenchmark, malloc, (16ul));
// BENCHMARK_P_INSTANCE(SudokuCheckerBenchmark, malloc, (256ul));
