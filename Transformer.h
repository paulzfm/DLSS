// A transformer to:
// a) transfer a sudoku problem to zero-one matrix for Dancing Link
// b) transfer the solution of DL, which is an Integer list to show
//    which rows (should be 81) are selected.

#ifndef DLSS_TRANSFORMER_H_
#define DLSS_TRANSFORMER_H_

#include "DL.h"
#include "Sudoku.h"
#include <vector>

namespace DLSS {

class Transformer
{
public:
	Transformer(Sudoku& problem);
	virtual ~Transformer();

	void GetAnswer(Sudoku& ans);

	double GetTime();

private:
	void generate_matrix(Sudoku& problem);
	void generate_ans(std::vector<int> selected);

	void set(int r, int c, int num);	// num != 0

	bool** matrix_;
	int ans_[81];

	double time_;
};


}


#endif // DLSS_TRANSFORMER_H_