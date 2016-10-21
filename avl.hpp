#ifndef DATA_STRUCTURES_AVL_H
#define DATA_STRUCTURES_AVL_H

#include <memory>

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
	void updateHeight(std::unique_ptr<Node<T>> &node)
	{
		if (!node)
			return;

		int height_left = node->left ? node->left->height : 0;
		int height_right = node->right ? node->right->height : 0;
		node-> height = node->left || node->right ? std::max(height_left, height_right) + 1 : 0;
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
	void rotateLeft(std::unique_ptr<Node<T>> &node)
	{
		std::swap(node->key, node->right->key);
		std::swap(node->left, node->right);

		if (node->left)
		{
			std::swap(node->left->left, node->left->right);
			std::swap(node->left->left, node->right);
		}

		updateHeight(node->left);
		updateHeight(node);
	}

	template<typename T>
	void rotateRight(std::unique_ptr<Node<T>> &node)
	{
		std::swap(node->key, node->left->key);
		std::swap(node->left, node->right);

		if (node->right)
		{
			std::swap(node->right->left, node->right->right);
			std::swap(node->left, node->right->right);
		}

		updateHeight(node->right);
		updateHeight(node);
	}

	template<typename T>
	int getBalance(std::unique_ptr<Node<T>> &node)
	{
		if (!node)
			return 0;

		int left_height = node->left ? node->left->height : -1;
		int right_height = node->right ? node->right->height : -1;
		return left_height - right_height;
	}

	template<typename T>
	void balanceNode(std::unique_ptr<Node<T>> &node)
	{
		if (getBalance(node) == 2)
		{
			if (getBalance(node->left) == -1)
				rotateLeft(node->left);

			rotateRight(node);
		}
		else if (getBalance(node) == -2)
		{
			if (getBalance(node->right) == 1)
				rotateRight(node->right);

			rotateLeft(node);
		}
	}

	template<typename T>
	void insertKey(std::unique_ptr<Node<T>> &node, const T &key)
	{
		if (!node)
			node = std::make_unique<Node<T>>(key);
		else if (key < node->key)
			insertKey(node->left, key);
		else if (key > node->key)
			insertKey(node->right, key);
		else
			return;

		updateHeight(node);
		balanceNode(node);
	}

	template<typename T>
	void removeKey(std::unique_ptr<Node<T>> &node, const T &key)
	{
		if (!node)
			return;
		else if (node->key > key)
			removeKey(node->left, key);
		else if (node->key < key)
			removeKey(node->right, key);
		else if (node->right && node->left)
		{
			auto &min_node = getMinNode(node->right);
			node->key = min_node->key;
			removeKey(node->right, node->key);
		}
		else if (node->left)
			node = std::move(node->left);
		else if (node->right)
			node = std::move(node->right);
		else
			node = nullptr;

		updateHeight(node);
		balanceNode(node);
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
