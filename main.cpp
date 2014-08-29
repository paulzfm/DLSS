#include "Sudoku.h"
#include "Transformer.h"
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./dlss sudoku_file_name\n";
		exit(1);
	}

	std::string pro_file = argv[1];
	DLSS::Sudoku problem(pro_file);
	DLSS::Sudoku answer;

	std::cout << "Problem\n=======\n";
	problem.Print();

	DLSS::Transformer trans(problem);
	trans.GetAnswer(answer);

	std::cout << "Answer\n======\n";
	answer.Print();

	double time = 1000 * trans.GetTime();
	printf("Time cost: %.2lf ms\n", time);

	return 0;
}