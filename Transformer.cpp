#include "Transformer.h"
#include <ctime>

namespace DLSS {

Transformer::Transformer(Sudoku& problem)
{
	matrix_ = new bool*[729];
	for (int i = 0; i < 729; ++i)
		matrix_[i] = new bool[324];
	for (int i = 0; i < 729; ++i)
		for (int j = 0; j < 324; ++j)
			matrix_[i][j] = 0;

	generate_matrix(problem);
	DL dl(matrix_, 729, 324);
	clock_t start = clock();
	dl.Solve();
	clock_t end = clock();
	time_ = (double)(end - start) / CLOCKS_PER_SEC;
	std::vector<int> sol;
	dl.GetSolution(sol);
	generate_ans(sol);
}

Transformer::~Transformer()
{
	delete[] matrix_;
}

void Transformer::GetAnswer(Sudoku& ans)
{
	ans.SetArray(ans_);
}

double Transformer::GetTime()
{
	return time_;
}

void Transformer::set(int r, int c, int num)
{
	// row index: (r, c) fills num
	int row = (r * 9 + c) * 9 + num - 1;

	// column index: 4 conditions
	// 1. (r, c) fills a number
	matrix_[row][r * 9 + c] = 1;
	// 2. row r fills a number num
	matrix_[row][81 + r * 9 + num - 1] = 1;
	// 3. column c fills a number num
	matrix_[row][162 + c * 9 + num - 1] = 1;
	// 4. square s fills a number num
	int s = (r / 3) * 3 + (c / 3);
	matrix_[row][243 + s * 9 + num - 1] = 1;
}

void Transformer::generate_matrix(Sudoku& problem)
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			int num = problem.Get(i, j);
			if (num != 0)
				set(i, j, num);
			else
			{
				for (int n = 1; n < 10; ++n)
					set(i, j, n);
			}
		}
	}
}

void Transformer::generate_ans(std::vector<int> selected)
{
	for (int i = 0; i < 81; ++i)
	{
		int index = selected[i] / 9;
		int num = selected[i] % 9;
		ans_[index] = num;
	}
}

}	// namespace DLSS