// ConsoleApplication28.cpp: определяет точку входа для консольного приложения.
//


#include "Tree.h"

int main()
{

	Tree<int> intTree(10);
	int a;
	cout << "10 numbers:" << endl;
	for (int i = 0; i<10; i++)
	{
		cin >> a;
		intTree.insert_node(a);
	}

	intTree.inorder_walk(intTree.get_root());
	cout << "choose the one node u'd like to delete:";
	cin >> a;
	intTree.delete_node(intTree.find(intTree.get_root(), a));
	cout << endl << "The actual tree:" << endl;
	intTree.inorder_walk(intTree.get_root());
	system("pause");
}
