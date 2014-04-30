#ifndef NARYTREEPEOPLE_H_
#define NARYTREEPEOPLE_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <typeinfo>

using namespace std;

typedef struct sNaryNode {
	void *data;
	int n;
	struct sNaryNode **child;
} NaryNode;

typedef struct sPeople {
	int id;
	string *name;
	int age;
} People;

typedef NaryNode NaryTree;
typedef void (*DataFreeFunc)(const void *);
DataFreeFunc dFree;

NaryTree *createNode(int children, void *data);
void insertNodebyID(NaryTree *tree, int id, void *data);
int appendChild(NaryNode *root, void *data);
void *createPeople(int id, string name, int age);
void printTree(NaryTree *tree);
void freeTree(NaryTree *tree, DataFreeFunc dFree);
unsigned  sizeOfNaryTree(NaryNode *root);

#endif /* NARYTREEPEOPLE_H_ */
