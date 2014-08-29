#include "DL.h"
#include <iostream>

namespace DLSS {

DL::DL(bool** matrix, int row, int col)
{
	// roots
	init_roots(row, col);

	// other nodes
	list_ = new Node[row * col];
	count_ = 0;
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (matrix[i][j])
				add(i, j);

	// ready to search
	solution_ = new int[row];
	sol_count_ = 0;
}

DL::~DL()
{
	delete[] root_c;
	delete[] root_r;
	delete[] list_;
}

void DL::Solve()
{
	solve(0);
}

void DL::GetSolution(std::vector<int>& solution)
{
	solution.clear();
	for (int i = 0; i < sol_count_; ++i)
		solution.push_back(solution_[i]);
}

void DL::init_roots(int row, int col)
{
	// column
	// root & row are NOT used
	root_c = new Node[col + 1];
	for (int i = 0; i <= col; ++i)
	{
		root_c[i].up = root_c[i].down = root_c + i;
		root_c[i].left = root_c + ((i + col) % (1 + col));
		root_c[i].right = root_c + ((i + 1) % (1 + col));
		root_c[i].count = 0;
	}

	// head
	head_ = root_c + col;

	// row
	// ONLY left & right are used, leave root as the head, and up & down itself
	root_r = new Node[row];
	for (int i = 0; i < row; ++i)
	{
		root_r[i].left = root_r[i].right = root_r + i;
		root_r[i].up = root_r[i].down = root_r + i;
		root_r[i].root = head_;
	}
}

void DL::add(int r, int c)
{
	// change neighbors
	list_[count_].up = root_c[c].up;
	list_[count_].down = root_c + c;
	list_[count_].left = root_r[r].left;
	list_[count_].right = root_r + r;
	root_c[c].up = root_c[c].up->down = root_r[r].left = root_r[r].left->right = list_ + count_;

	// change roots
	list_[count_].root = root_c + c;
	list_[count_].row = r;
	root_c[c].count++;

	count_++;
}

void DL::cover(Node* node)
{
	if (node == head_)
		return;

	node->left->right = node->right;
	node->right->left = node->left;
	for (Node* p = node->down; p != node; p = p->down)
	{
		for (Node* q = p->right; q != p; q = q->right)
		{
			q->up->down = q->down;
			q->down->up = q->up;
			q->root->count--;
		}
	}
}

void DL::resume(Node* node)
{
	if (node == head_)
		return;

	for (Node* p = node->up; p != node; p = p->up)
	{
		for (Node* q = p->left; q != p; q = q->left)
		{
			q->up->down = q->down->up = q;
			q->root->count++;
		}
	}
	node->left->right = node->right->left = node;
}

bool DL::solve(int process)
{
	if (head_->right == head_)
	{
		sol_count_ = process;
		return true;
	}

	// find the column with least nodes
	Node* min = head_->right;
	for (Node* p = min; p != head_; p = p ->right)
		if (p->count < min->count)
			min = p;

	// cover this column
	cover(min);

	for (Node* p = min->down; p != min; p = p->down)
	{
		// try selecting this row
		solution_[process] = p->row;
		// cover all columns whose nodes are on the selected row
		for (Node* q = p->right; q != p; q = q->right)
			cover(q->root);

		// test
		if (solve(process + 1))
			return true;
		// else: backtrace
		for (Node* q = p->left; q != p; q = q->left)
			resume(q->root);
	}

	// undo: covering the column
	resume(min);
	return false;
}

}	// namespace DLSS