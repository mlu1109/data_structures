#ifndef DATA_STRUCTURES_HELPER_HPP
#define DATA_STRUCTURES_HELPER_HPP

#include "avl.hpp"

std::unique_ptr<AVL::Node<int>> createNode(int key);
std::unique_ptr<AVL::Node<int>> generateTree();

#endif //DATA_STRUCTURES_HELPER_HPP
