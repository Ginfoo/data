// 10:36 PM/10/10/2017

#pragma once
#ifndef VALUE_TYPE
#define VALUE_TYPE char
#endif // !VALUE_TYPE
#include <iostream>
typedef VALUE_TYPE value_type;

typedef struct TreeNode
{
	value_type e;
	typedef TreeNode* tree_node_pointer;
	tree_node_pointer leftChild;
	tree_node_pointer rightChild;
} TreeNode;

//Ç°Ðò±éÀú
void PreOrder(TreeNode*& t)
{
	if (t != nullptr)
	{
		std::cout << t->e << std::endl;
		PreOrder(t->leftChild);
		PreOrder(t->rightChild);
	}
}

void InOrder(TreeNode*& t)
{
	if (t != nullptr)
	{
		InOrder(t);
		std::cout << t->e << std::endl;
		InOrder(t);
	}
}

void PostOrder(TreeNode*& t)
{
	if (t != nullptr)
	{
		PostOrder(t);
		PostOrder(t);
		std::cout << t->e << std::endl;
	}
}
