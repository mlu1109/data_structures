#ifndef DATA_STRUCTURES_AVL_H
#define DATA_STRUCTURES_AVL_H

#include <memory>
#include <iostream>
#include <random>

namespace AVL
{
	template<typename T>
	struct Node
	{
		std::unique_ptr<Node<T>> left;
		std::unique_ptr<Node<T>> right;
		int height;
		T key;

		Node(const T& key) : left(nullptr), right(nullptr), height(0), key(key) {}
	};

	template<typename T>
	int getHeight(std::unique_ptr<Node<T>> &node)
	{
		if (!node)
			return -1;

		return 1 + std::max(getHeight(node->left), getHeight(node->right));
	}

	template<typename T>
	std::unique_ptr<Node<T>> &getMinNode(std::unique_ptr<Node<T>> &node)
	{
		if (node->left)
			return getMinNode(node->left);

		return node;
	}

	template<typename T>
	int getSize(std::unique_ptr<Node<T>> &node)
	{
		if (!node)
			return 0;

		return 1 + getSize(node->left) + getSize(node->right);
	}

	template<typename T>
	void rotateLeft(std::unique_ptr<Node<T>> &root)
	{
		std::swap(root->key, root->right->key);
		std::swap(root->left, root->right);

		if (root->left)
		{
			std::swap(root->left->left, root->left->right);
			std::swap(root->left->left, root->right);
		}
	}

	template<typename T>
	void rotateRight(std::unique_ptr<Node<T>> &root)
	{
		std::swap(root->key, root->left->key);
		std::swap(root->left, root->right);

		if (root->right)
		{
			std::swap(root->right->left, root->right->right);
			std::swap(root->left, root->right->right);
		}
	}

	template<typename T>
	int getBalance(std::unique_ptr<Node<T>> &node)
	{
		if (!node)
			return 0;

		return getHeight(node->left) - getHeight(node->right);
	}

	template<typename T>
	void balanceNode(std::unique_ptr<Node<T>> &root)
	{
		if (getBalance(root) == 2)
		{
			if (getBalance(root->left) == -1)
				rotateLeft(root->left);

			rotateRight(root);
		}
		else if (getBalance(root) == -2)
		{
			if (getBalance(root->right) == 1)
				rotateRight(root->right);

			rotateLeft(root);
		}
	}

	template<typename T>
	void insertNode(std::unique_ptr<Node<T>> &node, const T &key)
	{
		if (!node)
			node = std::make_unique<Node<T>>(key);
		else if (key < node->key)
			insertNode(node->left, key);
		else if (key > node->key)
			insertNode(node->right, key);
		else
			return;

		balanceNode(node);
	}

	template<typename T>
	void removeNode(std::unique_ptr<Node<T>> &node, const T &key)
	{
		if (!node)
			return;
		else if (node->key > key)
			removeNode(node->left, key);
		else if (node->key < key)
			removeNode(node->right, key);
		else if (node->right && node->left)
		{
			auto &min_node = getMinNode(node->right);
			node->key = min_node->key;
			removeNode(node->right, node->key);
		}
		else if (node->left)
			node = std::move(node->left);
		else if (node->right)
			node = std::move(node->right);
		else
			node = nullptr;

		balanceNode(node);
	}

	template<typename T>
	bool isTreeBalanced(std::unique_ptr<Node<T>> &root)
	{
		if (!root)
			return true;

		return std::abs(getBalance(root)) < 2 && isTreeBalanced(root->left) && isTreeBalanced(root->right);
	}

	template<typename T>
	void getTreeArray(std::unique_ptr<Node<T>> &node, T *arr, int &i)
	{
		if (node->left)
			getTreeArray(node->left, arr, i);

		arr[i++] = node->key;

		if (node->right)
			getTreeArray(node->right, arr, i);
	}
}

#endif //DATA_STRUCTURES_AVL_H