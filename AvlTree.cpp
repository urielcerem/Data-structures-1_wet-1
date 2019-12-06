#include <iostream>
#include <algorithm>
#include "AVLTree.h"

template <class T>
AVLNode<T>::~AVLNode() {
	delete left;
	delete right;
}

/* AVL class definition */
template <class T>
void AVLTree<T>::FixBalance(AVLNode<T> *n) {
	SetBalance(n);

	if (n->balance == -2) {
		if (GetHeight(n->left->left) >= GetHeight(n->left->right))
			n = RotateRight(n);
		else
			n = RotateLeftRight(n);
	}
	else if (n->balance == 2) {
		if (GetHeight(n->right->right) >= GetHeight(n->right->left))
			n = RotateLeft(n);
		else
			n = RotateRighLeft(n);
	}

	if (n->parent != NULL) {
		FixBalance(n->parent);
	}
	else {
		root = n;
	}
}

template <class T>
AVLNode<T>* AVLTree<T>::RotateLeft(AVLNode<T> *a) {
	AVLNode<T> *b = a->right;
	b->parent = a->parent;
	a->right = b->left;

	if (a->right != NULL)
		a->right->parent = a;

	b->left = a;
	a->parent = b;

	if (b->parent != NULL) {
		if (b->parent->right == a) {
			b->parent->right = b;
		}
		else {
			b->parent->left = b;
		}
	}

	SetBalance(a);
	SetBalance(b);
	return b;
}

template <class T>
AVLNode<T>* AVLTree<T>::RotateRight(AVLNode<T> *a) {
	AVLNode<T> *b = a->left;
	b->parent = a->parent;
	a->left = b->right;

	if (a->left != NULL)
		a->left->parent = a;

	b->right = a;
	a->parent = b;

	if (b->parent != NULL) {
		if (b->parent->right == a) {
			b->parent->right = b;
		}
		else {
			b->parent->left = b;
		}
	}

	SetBalance(a);
	SetBalance(b);
	return b;
}

template <class T>
AVLNode<T>* AVLTree<T>::RotateLeftRight(AVLNode<T> *n) {
	n->left = RotateLeft(n->left);
	return RotateRight(n);
}

template <class T>
AVLNode<T>* AVLTree<T>::RotateRighLeft(AVLNode<T> *n) {
	n->right = RotateRight(n->right);
	return RotateLeft(n);
}

template <class T>
int AVLTree<T>::GetHeight(AVLNode<T> *n) {
	if (n == NULL)
		return -1;
	return 1 + std::max(GetHeight(n->left), GetHeight(n->right));
}

template <class T>
void AVLTree<T>::SetBalance(AVLNode<T> *n) {
	n->balance = GetHeight(n->right) - GetHeight(n->left);
}

template <class T>
AVLTree<T>::AVLTree(void) : root(NULL) {}

template <class T>
AVLTree<T>::~AVLTree(void) {
	delete root;
}

template <class T>
bool AVLTree<T>::InsertData(T key) {
	if (root == NULL) {
		root = new AVLNode<T>(key, NULL);
	}
	else {
		AVLNode<T>
			*n = root,
			*parent;

		while (true) {
			if (n->key == key)
				return false;

			parent = n;

			bool goLeft = n->key > key;
			n = goLeft ? n->left : n->right;

			if (n == NULL) {
				if (goLeft) {
					parent->left = new AVLNode<T>(key, parent);
				}
				else {
					parent->right = new AVLNode<T>(key, parent);
				}

				FixBalance(parent);
				break;
			}
		}
	}

	return true;
}

template <class T>
void AVLTree<T>::DeleteData(const T delKey) {
	if (root == NULL)
		return;

	AVLNode<T>
		*n = root,
		*parent = root,
		*delNode = NULL,
		*child = root;

	while (child != NULL) {
		parent = n;
		n = child;
		child = delKey >= n->key ? n->right : n->left;
		if (delKey == n->key)
			delNode = n;
	}

	if (delNode != NULL) {
		delNode->key = n->key;

		child = n->left != NULL ? n->left : n->right;
		if (root->key == delKey) {
			root = child;
		}
		else {
			if (parent->left == n) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
			FixBalance(parent);

		}
	}
}

template <class T>
void AVLTree<T>::PrintInOrder() {
	PrintInOrder(root);
	std::cout << std::endl;
}

template <class T>
void AVLTree<T>::PrintInOrder(AVLNode<T> *n) {
	if (n != NULL) {
		PrintInOrder(n->left);
		std::cout << n->key << std::endl;
		PrintInOrder(n->right);
	}
}

