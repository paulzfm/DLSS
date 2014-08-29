#include "Sudoku.h"
#include <fstream>
#include <iostream>

namespace DLSS {

Sudoku::Sudoku(std::string file_name)
{
	std::ifstream in(file_name);
	if (!in)
	{
		std::cerr << "File ["  << file_name << "] loading failed.\n";
		exit(1);
	}
	for (int i = 0; i < 81; ++i)
		in >> array_[i];
	in.close();
}

void Sudoku::SaveToFile(std::string file_name)
{
	std::ofstream out(file_name);
	if (!out)
	{
		std::cerr << "File ["  << file_name << "] loading failed.\n";
		exit(1);
	}
	for (int i = 0; i < 81; ++i)
		out << array_[i];
	out.close();
}

void Sudoku::Print()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			std::cout << Get(i, j);
			if (j == 8)
				std::cout << "\n";
			else
				std::cout << " ";
		}
	}
}

void Sudoku::SetArray(int* array)
{
	for (int i = 0; i < 81; ++i)
		array_[i] = array[i];
}

int Sudoku::Get(int index)
{
	return array_[index];
}

int Sudoku::Get(int r, int c)
{
	return array_[r * 9 + c];
}

void Sudoku::Set(int index, int num)
{
	array_[index] = num;
}

void Sudoku::Set(int r, int c, int num)
{
	array_[r * 9 + c] = num;
}

}	// DLSS