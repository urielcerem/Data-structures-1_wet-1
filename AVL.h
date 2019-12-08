#ifndef AVL_TREE_H_
#define AVL_TREE_H_


/* AVL node */
template <class T>
class AVLNode {
public:
	T key;
	AVLNode *left, *right;
	int depth;

	AVLNode(T k) : key(k), depth(1), left(NULL), right(NULL) {}
	~AVLNode() {}
};



/* AVL tree */
template <class T>
class AVLTree {
public:
	AVLNode<T>* root;

	AVLTree() : root(NULL) {}
	~AVLTree();

	void InsertKey(T key);
	void DeleteKey(T key);
	AVLNode<T>* Find(T key);

	void PrintInOrder();//for debugging purposes
};



#endif
