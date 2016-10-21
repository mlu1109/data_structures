#ifndef DATA_STRUCTURES_HELPER_HPP
#define DATA_STRUCTURES_HELPER_HPP

#include "avl.hpp"

std::unique_ptr<AVL::Node<int>> createNode(int key);
std::unique_ptr<AVL::Node<int>> generateTree();
std::string getTreeString(std::unique_ptr<AVL::Node<int>> &node, int depth);

template<typename T>
int getCalculatedHeight(std::unique_ptr<AVL::Node<T>> &node)
{
	if (!node)
		return -1;

	return 1 + std::max(getCalculatedHeight(node->left), getCalculatedHeight(node->right));
}

template<typename T>
int getCalculatedBalance(std::unique_ptr<AVL::Node<T>> &node)
{
	if (!node)
		return 0;

	return getCalculatedHeight(node->left) - getCalculatedHeight(node->right);
}

template<typename T>
bool isTreeBalanced(std::unique_ptr<AVL::Node<T>> &node)
{
	if (!node)
		return true;

	return std::abs(getCalculatedBalance(node)) < 2 && isTreeBalanced(node->left) && isTreeBalanced(node->right);
}

#endif //DATA_STRUCTURES_HELPER_HPP
