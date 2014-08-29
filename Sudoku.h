#ifndef DLSS_SUDOKU_H_
#define DLSS_SUDOKU_H_

#include <string>

namespace DLSS {

class Sudoku
{
public:
	Sudoku() {}
	Sudoku(std::string file_name);
	virtual ~Sudoku() {}

	void Print();
	void SaveToFile(std::string file_name);

	void SetArray(int* array);
	
	int Get(int index);
	int Get(int r, int c);
	void Set(int index, int num);
	void Set(int r, int c, int num);

private:
	int array_[81];
};

}	// DLSS

#endif // DLSS_SUDOKU_H_