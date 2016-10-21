#include <iostream>
#include "helper.hpp"

std::unique_ptr<AVL::Node<int>> createNode(int key)
{
	return std::make_unique<AVL::Node<int>>(key);
}

// Returns a full BST of height 2 with min key 0
std::unique_ptr<AVL::Node<int>> generateTree()
{
	auto root = createNode(3);
	root->left = createNode(1);
	root->right = createNode(5);
	root->left->left = createNode(0);
	root->right->right = createNode(6);
	root->left->right = createNode(2);
	root->right->left = createNode(4);
	root->height = 2;
	root->left->height = 1;
	root->right->height = 1;
	return root;
}