#include <gtest/gtest.h>
#include "avl.hpp"
#include "helper.hpp"

TEST(AVL, getHeight)
{
	auto root = createNode(0);
	EXPECT_EQ(AVL::getHeight(root), 0);

	root->left = createNode(1);
	EXPECT_EQ(AVL::getHeight(root), 1);

	root = generateTree();
	EXPECT_EQ(AVL::getHeight(root), 2);

	root->left->left->right = createNode(3);
	EXPECT_EQ(AVL::getHeight(root), 3);
}


TEST(AVL, getBalance)
{
	auto root = createNode(0);
	EXPECT_EQ(AVL::getBalance(root), 0);

	root->left = createNode(1);
	EXPECT_EQ(AVL::getBalance(root), 1);

	root->right = createNode(1);
	EXPECT_EQ(AVL::getBalance(root), 0);

	root->left = nullptr;
	EXPECT_EQ(AVL::getBalance(root), -1);

	root->right->right = createNode(2);
	root->right->left = createNode(2);
	EXPECT_EQ(AVL::getBalance(root), -2);
}

TEST(AVL, rotateRight)
{
	auto root = createNode(0);
	root->left = createNode(1);
	AVL::rotateRight(root);
	EXPECT_EQ(root->key, 1);
	EXPECT_EQ(root->right->key, 0);
	EXPECT_EQ(root->left, nullptr);

	root = createNode(0);
	root->left = createNode(1);
	root->left->left = createNode(2);
	AVL::rotateRight(root);
	EXPECT_EQ(root->left->key, 2);

	root = createNode(0);
	root->left = createNode(1);
	root->left->left = createNode(2);
	root->left->right = createNode(3);
	root->right = createNode(4);
	AVL::rotateRight(root);
	EXPECT_EQ(root->right->left->key, 3);
	EXPECT_EQ(root->right->right->key, 4);
}

TEST(AVL, rotateLeft)
{
	auto root = createNode(0);
	root->right = createNode(1);
	AVL::rotateLeft(root);
	EXPECT_EQ(root->key, 1);
	EXPECT_EQ(root->left->key, 0);
	EXPECT_EQ(root->right, nullptr);

	root = createNode(0);
	root->right = createNode(1);
	root->right->right = createNode(2);
	AVL::rotateLeft(root);
	EXPECT_EQ(root->right->key, 2);

	root = createNode(0);
	root->right = createNode(1);
	root->right->right = createNode(2);
	root->right->left = createNode(3);
	root->left = createNode(4);
	AVL::rotateLeft(root);
	EXPECT_EQ(root->left->left->key, 4);
	EXPECT_EQ(root->left->right->key, 3);
}

TEST(AVL, insertNode_and_balanceNode)
{
	auto root = createNode(0);

	// Right right imbalance
	AVL::insertNode(root, 5);
	AVL::insertNode(root, 6);
	ASSERT_EQ(root->key, 5);
	ASSERT_EQ(root->left->key, 0);
	ASSERT_EQ(root->right->key, 6);

	// Right left imbalance
	AVL::insertNode(root, 8);
	AVL::insertNode(root, 7);
	ASSERT_EQ(root->key, 5);
	ASSERT_EQ(root->left->key, 0);
	ASSERT_EQ(root->right->key, 7);
	ASSERT_EQ(root->right->left->key, 6);
	ASSERT_EQ(root->right->right->key, 8);

	// Left left imbalance
	AVL::insertNode(root, -1);
	AVL::insertNode(root, -2);
	ASSERT_EQ(root->left->key, -1);
	ASSERT_EQ(root->left->left->key, -2);
	ASSERT_EQ(root->left->right->key, 0);

	// Left right imbalance
	AVL::insertNode(root, -5);
	AVL::insertNode(root, -4);
	ASSERT_EQ(root->left->left->key, -4);
	ASSERT_EQ(root->left->left->left->key, -5);
	ASSERT_EQ(root->left->left->right->key, -2);
}

TEST(AVL, removeNode)
{
	// No children
	auto root = createNode(0);
	AVL::removeNode(root, 0);
	EXPECT_EQ(root, nullptr);

	root = generateTree(); // Full BST of height 2 with min key 0
	root->left->left->left = createNode(-1);

	// No imbalance
	AVL::removeNode(root, 5);
	EXPECT_EQ(root->right->key, 6);

	// Left left imbalance
	AVL::removeNode(root, 6);
	EXPECT_EQ(root->key, 1);
	EXPECT_EQ(root->left->key, 0);
	EXPECT_EQ(root->right->key, 3);
	EXPECT_EQ(root->left->left->key, -1);
	EXPECT_EQ(root->left->right, nullptr);
	EXPECT_EQ(root->right->left->key, 2);
	EXPECT_EQ(root->right->right->key, 4);

	// Two imbalances that needs fixing
	root = createNode(5);
	root->left = createNode(2);
	root->right = createNode(8);
	root->left->left = createNode(1);
	root->left->right = createNode(3);
	root->right->left = createNode(7);
	root->right->right = createNode(10);
	root->left->right->right = createNode(4);
	root->right->left->left = createNode(6);
	root->right->right->left = createNode(9);
	root->right->right->right = createNode(11);
	root->right->right->right->right = createNode(12);
	AVL::removeNode(root, 1);
	EXPECT_EQ(root->key, 8);
	EXPECT_EQ(root->left->key, 5);
	EXPECT_EQ(root->right->key, 10);
	EXPECT_EQ(root->left->left->key, 3);
	EXPECT_EQ(root->left->right->key, 7);
	EXPECT_EQ(root->right->left->key, 9);
	EXPECT_EQ(root->right->right->key, 11);
	EXPECT_EQ(root->left->left->left->key, 2);
	EXPECT_EQ(root->left->left->right->key, 4);
	EXPECT_EQ(root->left->right->left->key, 6);
	EXPECT_EQ(root->left->right->right, nullptr);
	EXPECT_EQ(root->right->left->left, nullptr);
	EXPECT_EQ(root->right->left->right, nullptr);
	EXPECT_EQ(root->right->right->left, nullptr);
	EXPECT_EQ(root->right->right->right->key, 12);

	// One right child
	root = createNode(5);
	root->right = createNode(6);
	root->right->right = createNode(7);
	root->right->right->right = createNode(8);
	AVL::removeNode(root, 6);
	ASSERT_EQ(root->key, 7);
	ASSERT_EQ(root->left->key, 5);
	ASSERT_EQ(root->right->key, 8);

	// One left child
	root = createNode(5);
	root->left = createNode(4);
	root->left->left = createNode(3);
	root->left->left->left = createNode(2);
	AVL::removeNode(root, 4);
	ASSERT_EQ(root->key, 3);
	ASSERT_EQ(root->left->key, 2);
	ASSERT_EQ(root->right->key, 5);
}

TEST(AVL, random_insertions_and_deletions)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 19999);

	auto root = createNode(1000);
	bool arr[20000] = { };
	arr[1000] = true;

	for (int i = 0; i < 1000; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			int rand = (int) dist(rng);
			arr[rand] = true;
			AVL::insertNode(root, rand);
		}

		for (int j = 0; j < 10; ++j)
		{
			int rand = (int) dist(rng);
			arr[rand] = false;
			AVL::removeNode(root, rand);
		}
	}

	ASSERT_TRUE(AVL::isTreeBalanced(root));

	int treeSize = AVL::getSize(root);
	int treeArr[treeSize];
	int i = 0;
	AVL::getTreeArray(root, treeArr, i);
	bool treeBoolArr[20000] = { };

	for (int i = 0; i < AVL::getSize(root); ++i)
	{
		treeBoolArr[treeArr[i]] = true;
	}

	bool equal = true;

	for (int i = 0; i < 19999; ++i)
	{
		if (treeBoolArr[i] != arr[i])
		{
			equal = false;
			break;
		}
	}

	ASSERT_TRUE(equal);

}