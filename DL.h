#ifndef DLSS_DL_H_
#define DLSS_DL_H_

#include <vector>

namespace DLSS {

struct Node
{
	Node* up;
	Node* down;
	Node* left;
	Node* right;
	Node* root;		// column root
	int row;		// row No.
	int count;		// element count for the column
};

class DL
{
public:
	DL(bool** matrix, int row, int col);
	virtual ~DL();

	void Solve();
	// void SolveAll(int max = 0);
	void GetSolution(std::vector<int>& solution);

private:
	Node* head_;	// root for all
	Node* root_c;	// roots for columns
	Node* root_r;	// roots for rows
	Node* list_;	// other nodes
	int count_;		// count for list_

	int* solution_;	// rows should be selected
	int sol_count_;	// rows selected

	void init_roots(int row, int col);
	void add(int r, int c);

	void cover(Node* node);
	void resume(Node* node);
	bool solve(int process);
};

}

#endif // DLSS_DL_H_