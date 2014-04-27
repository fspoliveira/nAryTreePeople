//============================================================================
// Name        : Tree.cpp
// Author      : Fernando Santiago
// Version     : 1.3
// Copyright   : Open
// More Info   : http://www.gnu.org/licenses/gpl-howto.pt-br.html
// Based       : http://kylelemons.net/download/Complex_Data_Structures_N-ary_Tree_PDF.pdf
// Description : N-Ary Tree in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <stdlib.h>

using namespace std;

typedef struct sNaryNode {
	void *data;
	int n;
	struct sNaryNode **child;
} NaryNode;

typedef struct sPeople {
	int id;
	int age;
} People;

typedef NaryNode NaryTree;
typedef void (*DataFreeFunc)(const void *);

NaryTree *createNode(int children, void *data);
int appendChild(NaryNode *root, void *data);
void *createIntData(int data);
void *createPeople(int id, string nome, int idade);
void printTree(NaryTree *tree);
void freeTree(NaryTree *tree, DataFreeFunc dFree);

int main() {

	//root
	NaryTree *tree = createNode(0, createIntData(0));

	appendChild(tree, createPeople(1, "Fernando", 34));
	appendChild(tree, createPeople(2, "Claudia", 34));

	printTree(tree);

	DataFreeFunc dFree;
	freeTree(tree, dFree);

	return 0;
}

NaryTree *createNode(int children, void *data) {
	NaryNode *node = (NaryNode*) calloc(1, sizeof(NaryNode));
	node->data = data;
	node->n = children;
	node->child = (NaryNode**) calloc(children, sizeof(NaryNode*));

	return node;
}

int appendChild(NaryNode *root, void *data) {
	root->n++;
	root->child = (NaryNode**) realloc(root->child,
			(root->n) * sizeof(NaryNode*));
	root->child[root->n - 1] = createNode(0, data);
	return root->n - 1;
}

void *createIntData(int data) {
	int *ptr = (int*) calloc(1, sizeof(int));
	*ptr = data;
	return ptr;
}

void *createPeople(int id, string nome, int idade) {
	sPeople *ptr = (sPeople*) calloc(1, sizeof(sPeople));
	ptr->id = id;
	ptr->age = idade;
	return ptr;
}

void printTree(NaryTree *tree) {

	if (tree == NULL)
		return;

	sPeople people = (*(sPeople*) tree->data);
	cout << people.id << endl;
	cout << people.age << endl;

	for (int i = 0; i < tree->n; i++)
		printTree(tree->child[i]);
}

void freeTree(NaryTree *tree, DataFreeFunc dFree) {

	if (tree == NULL)
		return;

	for (int i = 0; i < tree->n; i++)
		freeTree(tree, dFree);

	free(tree->child);
	if (dFree)
		dFree(tree->data);
	free(tree);
}

