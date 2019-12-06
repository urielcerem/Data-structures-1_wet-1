#ifndef AVL_TREE_H_
#define AVL_TREE_H_


/* AVL node */
template <class T>
class AVLNode {
public:
	T key;
	AVLNode *parent, *left, *right;
	int balance;

	AVLNode(T k, AVLNode *p) : key(k), balance(0), parent(p),
		left(NULL), right(NULL) {}

	~AVLNode();
};



/* AVL tree */
template <class T>
class AVLTree {
public:
	AVLTree(void);
	~AVLTree(void);
	bool InsertData(T key);
	void DeleteData(const T key);
	void PrintInOrder();
	AVLNode<T> *root;

private:

	AVLNode<T>* RotateLeft(AVLNode<T> *a);
	AVLNode<T>* RotateRight(AVLNode<T> *a);
	AVLNode<T>* RotateLeftRight(AVLNode<T> *n);
	AVLNode<T>* RotateRighLeft(AVLNode<T> *n);
	void FixBalance(AVLNode<T> *n);
	int GetHeight(AVLNode<T> *n);
	void SetBalance(AVLNode<T> *n);
	void PrintInOrder(AVLNode<T> *n);
};



#endif
