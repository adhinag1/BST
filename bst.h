#ifndef BST_H
#define BST_H

#include<stdio.h>

typedef struct Data
{
	int value;
} Data;

typedef struct Node
{
	Data data;
  struct Node * left;
  struct Node * right;
  struct Node * parent;
} Node;

typedef struct Tree
{
  Node * root;
  Data * (*insert)();
  Data * (*search)();
  void (*sort)();
  int (*compare)();
  struct Tree * (*clone)(); 
  void (*delete)();
  void (*removeData)();
} Tree;

Node * newNode(Data d, Node * parent);
Tree * newTree();

Data * insertTree(Tree * bst, Data value);
Data * searchTree(Tree * bst, Data value);
void sortTree(Tree * bst, Data * value);
int compareTree(Tree * bst, Tree * copy_bst);
Tree * cloneTree(Tree * bst);
void deleteTree(Tree * bst);
void removeData(Tree * bst, Data value);

#include "bst.c"
#endif