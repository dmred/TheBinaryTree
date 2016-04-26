
#include "stdafx.h"
#include <memory>
#include "iostream"
using namespace std;


template <class NODETYPE> class Tree;
template <typename NODETYPE>
ostream & operator<<(ostream & output, Tree<NODETYPE> &);

template <typename NODETYPE>
istream & operator >> (istream & input, Tree<NODETYPE> &);

template <typename NODETYPE>
fstream & operator<<(fstream & file, Tree<NODETYPE> &);

template <typename NODETYPE>
fstream & operator >> (fstream & file, Tree<NODETYPE> &);

template <class NODETYPE>
class TreeNode
{
	friend class Tree<NODETYPE>;
public:
	TreeNode(const NODETYPE &a) :data(a), right(nullptr), left(nullptr) {};
	NODETYPE get_data();
protected:
	TreeNode* left;           /* указатель на левого ребенка */
	TreeNode* right;          /* указатель на правого ребенка */
	TreeNode* parent;         /* указатель на родителя */
	NODETYPE data;            /* ключ */
};


template <class NODETYPE>
NODETYPE TreeNode <NODETYPE>::get_data()
{
	return data;
}