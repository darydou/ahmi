#include "stdafx.h"
#include"iostream"
#include"vector"
using namespace std;

template<typename Comparable>
class BinarySearchTree
{
public:
	struct BinaryNode{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;
		BinaryNode(const Comparable theElement, BinaryNode *Left, BinaryNode *Right)
			:element(theElement), left(Left), right(Right) { }
	};
public:

	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree &rhs);
	~BinarySearchTree();

	const Comparable &findMin() const;
	const Comparable &findMax() const;
	bool contains(const Comparable &x) const;
	bool isEmpty() const;
	void printTree() const;

	void makeEmpty();
	void insert(const Comparable &x);
	void remove(const Comparable &x);
	const BinarySearchTree & operator=(const BinarySearchTree &rhs);

private:

	BinaryNode  *root;
	void insert(const Comparable &x, BinaryNode  *& t) const;
	void remove(const Comparable &x, BinaryNode  *& t) const;
	BinaryNode * findMax(BinaryNode *t) const;
	BinaryNode * findMin(BinaryNode *t) const;
	bool contains(const Comparable &x, BinaryNode *t)const;
	void makeEmpty(BinaryNode *& t);
	void printTree(BinaryNode *t)const;
	BinaryNode *clone(BinaryNode *t)const;

};

template<typename Comparable> bool  BinarySearchTree<Comparable>::contains(const Comparable &x)const
{
	return contains(x, root);
}

template<typename Comparable> bool  BinarySearchTree<Comparable>::contains(const Comparable &x, BinaryNode *t)const
{
	if (t == NULL)
		return FALSE;
	else if (x < t->element)
		return contains(x, t->left)
	else if (t->element < x)
	return contains(x, t->right);
	else return TRUE;
}

template<typename Comparable> void  BinarySearchTree<Comparable>::insert(const Comparable &x)
{
	insert(x, root);
}

template<typename Comparable> void  BinarySearchTree<Comparable>::remove(const Comparable &x)
{
	remove(x, root);
}

template<typename Comparable>  const Comparable & BinarySearchTree<Comparable>::findMax() const
{
	BinaryNode *t = findMax(root);
	return t->element;
}
//template<typename Comparable> BinaryNode<Comparable>*  BinarySearchTree<Comparable>::findMax(BinaryNode *t) const
template<typename Comparable>  BinaryNode*  BinarySearchTree<Comparable>::findMax(BinaryNode *t) const
{
	if (t == NULL)
		return NULL;
	if (t->right == NULL)
		return t;
	else return findMax(t->right);
}





int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
