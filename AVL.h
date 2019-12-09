#ifndef AVL_TREE_H_
#define AVL_TREE_H_


/* AVL node */
template <class T>
class AVLNode {
public:
	T data;
	double key;
	AVLNode *left, *right;
	int depth;

	AVLNode(T d , double k) : data(d), key(k), depth(1), left(NULL), right(NULL) {}
	~AVLNode() {}
};



/* AVL tree that sort <T> type of datas by keys*/
template <class T>
class AVLTree {
public:
	AVLNode<T>* root;

	AVLTree() : root(NULL) {}
	~AVLTree();

	void Insert(T data, double key);
	void Delete(double key);
	T* Find(double key);

	void PrintInOrder();//for debugging purposes
};



#endif
