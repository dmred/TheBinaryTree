#include "node.h"
template <class NODETYPE>
class Tree
{
public:
	Tree() :root(nullptr) {};
	int count;
	Tree(int k) : root(nullptr), count(k) {};/* конструктор */
	int insert_node(const NODETYPE &);                         /* вставляет узел */
	TreeNode<NODETYPE>* delete_node(TreeNode<NODETYPE> *);     /* удаляет узел */
	TreeNode<NODETYPE>* find(TreeNode<NODETYPE>*, const NODETYPE &);	/*поиск */
	TreeNode<NODETYPE> *get_root();                            /* возвращает указатель на корень дерева */
	void inorder_walk(TreeNode<NODETYPE>*);                    /* печатает все ключи в неубывающем порядке */
	TreeNode<NODETYPE>* find_succsessor(const NODETYPE &);     /* находит элемент с ключем, следующим за данным числом */
	TreeNode<NODETYPE>* find_max(TreeNode<NODETYPE>*);         /* находит узел с минимальным значением ключа и возвращает указатель на него */
	TreeNode<NODETYPE>* find_min(TreeNode<NODETYPE>*);

	friend	ostream & operator << <>(ostream &output, Tree &);
	friend	istream & operator >> <>(istream &input, Tree &);
	friend	fstream & operator << <>(fstream &file, Tree<NODETYPE> &);
	friend	fstream & operator >> <>(fstream &file, Tree<NODETYPE> &);

private:
	TreeNode<NODETYPE> *root;                                  /*корень */
	bool print(const TreeNode<NODETYPE>&, ostream &);
};


template<class NODETYPE>
int Tree<NODETYPE>::insert_node(const NODETYPE &x)
{
	TreeNode<NODETYPE>* n = new TreeNode<NODETYPE>(x);  /* создаем новый узел, его мы будем вставлять */
	TreeNode<NODETYPE>* ptr;
	TreeNode<NODETYPE>* ptr1 = 0;

	n->parent = n->left = n->right = 0;          /* он - лист */
	ptr = root;
	while (ptr != 0)                     /* идем от корня и ищем подходящее место для нашего нового элемента, оно должно быть свободно */
	{
		ptr1 = ptr;                 /* будущий родитель нового узла */
		if (x < ptr->get_data())  /* по определению нашего дерева - слева значение ключа меньше родителя, */
			ptr = ptr->left;
		else
			ptr = ptr->right;   /* справа - больше */
	}
	n->parent = ptr1;
	if (ptr1 == 0)
		root = n;
	else
	{
		if (x < ptr1->get_data())
			ptr1->left = n;
		else
			ptr1->right = n;
	}
	return 0;
}



template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::delete_node(TreeNode<NODETYPE> *z)
{
	TreeNode<NODETYPE>* y;
	TreeNode<NODETYPE>* x;

	if (z->left == 0 || z->right == 0)               /* в этой и следующих двух строках ищем вершину y, которую мы потом вырежем из дерева. Это либо z, либо следующий за z */
		y = z;
	else
		y = find_succsessor(z->get_data());

	if (y->left != 0)                                  /* x - указатель на существующего ребенка y или 0 если таковых нет */
		x = y->left;
	else
		x = y->right;
	if (x != 0)                                        /* эта и следующие 9 строк - вырезание y */
		x->parent = y->parent;
	if (y->parent == 0)
		root = x;
	else
	{
		if (y == (y->parent)->left)
			(y->parent)->left = x;
		else
			(y->parent)->right = x;
	}
	if (y != z)                                        /* если мы вырезали вершин, отличную от z, то ее данные перемещаем в z */
		z->data = y->get_data();
	return y;
}

template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::find(TreeNode<NODETYPE>* n, const NODETYPE & val)
{
	if (n == 0 || val == n->get_data())
		return n;
	if (val > n->get_data())
		return find(n->right, val);
	else
		return find(n->left, val);
}
template<class NODETYPE>
void Tree<NODETYPE>::inorder_walk(TreeNode<NODETYPE>* n)
{
	if (n != 0)
	{
		inorder_walk(n->left);
		cout << n->get_data() << endl;
		inorder_walk(n->right);
	}
}
template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::get_root()
{
	return root;
}


template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::find_succsessor(const NODETYPE & val)
{
	TreeNode<NODETYPE>* x = find(root, val);                     /* получим указатель на ноду с ключем val */
	TreeNode<NODETYPE>* y;
	if (x == 0)
		return 0;
	if (x->right != 0)                                                /* если у нее есть правые дети, то следующий элемент - минимальный в правом поддереве */
		return find_min(x->right);
	y = x->parent;
	while (y != 0 && x == y->right)                                   /* иначе - идем вверх и ищем первый элемент, являющийся левым
																	  потомком своего родителя */
	{
		x = y;
		y = y->parent;
	}
	return y;
}
template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::find_max(TreeNode<NODETYPE>* x)
{
	while (x->right != 0)                              /* здесь все очевидно - самыое максимальное значение у самого правого */
		x = x->right;
	return x;
}

template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::find_min(TreeNode<NODETYPE>* x)
{
	while (x->left != 0)
		x = x->left;
	return x;
}


template <typename NODETYPE>
ostream & operator <<(ostream & os, const Tree<NODETYPE> & x) {

	x.print(x.get_root(), os);

	return os;
}

template <typename NODETYPE>
istream & operator >> (istream & input, Tree<NODETYPE> & x) {
	Tree<NODETYPE> temp;


	for (int i = 0; i < x.count; ++i) {

		if (input >> temp) {
			x.insert_node(temp);
		}
	}
	return input;
}


template <typename NODETYPE>
fstream & operator <<(fstream &file, Tree<NODETYPE> & x) {

	x.print(x.get_root(), file);

	return file;
}
template <typename NODETYPE>
fstream & operator >> (fstream &file, Tree<NODETYPE> & x) {
	Tree<NODETYPE> temp;

	for (size_t i = 0; i < x.count; ++i) {

		if (file >> temp) {
			x.insert_node(temp);

		}
		return file;
	}
}

template <typename NODETYPE>
bool Tree<NODETYPE>::print(const TreeNode<NODETYPE> &m_node, ostream & os) {
	if (m_node == nullptr) {
		return true;
	}
	print(m_node->left, os);
	os << m_node->data << endl;
	print(m_node->right, os);
}
