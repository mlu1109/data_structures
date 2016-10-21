#include <gtest/gtest.h>
#include "avl.hpp"
#include "helper.hpp"

TEST(AVL_TEST_HELPER, getCalculatedHeight)
{
	auto root = createNode(0);
	EXPECT_EQ(getCalculatedHeight(root), 0);

	root->left = createNode(1);
	EXPECT_EQ(getCalculatedHeight(root), 1);

	root = generateTree();
	EXPECT_EQ(getCalculatedHeight(root), 2);

	root->left->left->right = createNode(3);
	EXPECT_EQ(getCalculatedHeight(root), 3);
}

TEST(AVL, getBalance)
{
	auto root = createNode(0);
	EXPECT_EQ(AVL::getBalance(root), 0);

	root->left = createNode(1);
	root->height = 1;
	EXPECT_EQ(AVL::getBalance(root), 1);

	root->right = createNode(1);
	EXPECT_EQ(AVL::getBalance(root), 0);

	root->left = nullptr;
	EXPECT_EQ(AVL::getBalance(root), -1);

	root->right->right = createNode(2);
	root->height = 2;
	root->right->height = 1;
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

TEST(AVL, insertKey_and_balanceNode)
{
	auto root = createNode(0);

	// Right right imbalance
	AVL::insertKey(root, 5);
	AVL::insertKey(root, 6);
	ASSERT_EQ(root->key, 5);
	ASSERT_EQ(root->left->key, 0);
	ASSERT_EQ(root->right->key, 6);

	// Right left imbalance
	AVL::insertKey(root, 8);
	AVL::insertKey(root, 7);
	ASSERT_EQ(root->key, 5);
	ASSERT_EQ(root->left->key, 0);
	ASSERT_EQ(root->right->key, 7);
	ASSERT_EQ(root->right->left->key, 6);
	ASSERT_EQ(root->right->right->key, 8);

	// Left left imbalance
	AVL::insertKey(root, -1);
	AVL::insertKey(root, -2);
	ASSERT_EQ(root->left->key, -1);
	ASSERT_EQ(root->left->left->key, -2);
	ASSERT_EQ(root->left->right->key, 0);

	// Left right imbalance
	AVL::insertKey(root, -5);
	AVL::insertKey(root, -4);
	ASSERT_EQ(root->left->left->key, -4);
	ASSERT_EQ(root->left->left->left->key, -5);
	ASSERT_EQ(root->left->left->right->key, -2);
}

TEST(AVL, removeKey)
{
	// No children
	auto root = createNode(0);
	AVL::removeKey(root, 0);
	EXPECT_EQ(root, nullptr);

	root = generateTree(); // Full BST of height 2 with min key 0
	AVL::insertKey(root, -1);
	EXPECT_EQ(root->left->left->left->key, -1);

	// No imbalance
	AVL::removeKey(root, 5);
	EXPECT_EQ(root->right->key, 6);

	// Left left imbalance
	AVL::removeKey(root, 6);
	EXPECT_EQ(root->key, 1);
	EXPECT_EQ(root->left->key, 0);
	EXPECT_EQ(root->right->key, 3);
	EXPECT_EQ(root->left->left->key, -1);
	EXPECT_EQ(root->left->right, nullptr);
	EXPECT_EQ(root->right->left->key, 2);
	EXPECT_EQ(root->right->right->key, 4);

	// Two imbalances that needs fixing
	root = createNode(5);
	AVL::insertKey(root, 2);
	AVL::insertKey(root, 8);
	AVL::insertKey(root, 1);
	AVL::insertKey(root, 3);
	AVL::insertKey(root, 7);
	AVL::insertKey(root, 10);
	AVL::insertKey(root, 4);
	AVL::insertKey(root, 6);
	AVL::insertKey(root, 9);
	AVL::insertKey(root, 11);
	AVL::insertKey(root, 12);
	AVL::removeKey(root, 1);
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
	AVL::removeKey(root, 6);
	ASSERT_EQ(root->key, 7);
	ASSERT_EQ(root->left->key, 5);
	ASSERT_EQ(root->right->key, 8);

	// One left child
	root = createNode(5);
	root->left = createNode(4);
	root->left->left = createNode(3);
	root->left->left->left = createNode(2);
	AVL::removeKey(root, 4);
	ASSERT_EQ(root->key, 3);
	ASSERT_EQ(root->left->key, 2);
	ASSERT_EQ(root->right->key, 5);
}

TEST(AVL, random_insertions_and_deletions)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 50000);

	auto root = createNode(1000);
	bool arr[50000] = { };
	arr[1000] = true;

	for (int i = 0; i < 5000; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			int rand = (int) dist(rng);
			arr[rand] = true;
			AVL::insertKey(root, rand);
		}

		for (int j = 0; j < 10; ++j)
		{
			int rand = (int) dist(rng);
			arr[rand] = false;
			AVL::removeKey(root, rand);
		}
	}

	ASSERT_TRUE(isTreeBalanced(root));

	int treeSize = AVL::getSize(root);
	int treeArr[treeSize];
	int i = 0;
	AVL::getTreeArray(root, treeArr, i);
	bool treeBoolArr[50000] = { };

	for (int i = 0; i < AVL::getSize(root); ++i)
		treeBoolArr[treeArr[i]] = true;

	bool equal = true;

	for (int i = 0; i < 50000; ++i)
	{
		if (treeBoolArr[i] != arr[i])
		{
			equal = false;
			break;
		}
	}

	ASSERT_TRUE(equal);
}
