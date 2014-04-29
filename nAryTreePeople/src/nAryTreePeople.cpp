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
NaryTree *findNode(NaryTree *tree, int id);
int appendChild(NaryNode *root, void *data);
void *createPeople(int id, string name, int age);
void printTree(NaryTree *tree);
void freeTree(NaryTree *tree, DataFreeFunc dFree);

int main() {

	//root
	NaryTree *tree = createNode(0, createPeople(0, "Grandhmother", 80));

//	appendChild(tree, createPeople(1, "Son1", 34));
//	appendChild(tree, createPeople(2, "Son2", 33));
//
//	appendChild(tree->child[0], createPeople(11, "Son1 of Son1", 2));

	printTree(tree);
	//findNode(tree, 3);

	freeTree(tree, dFree);

	return 0;
}

NaryTree *findNode(NaryTree *tree, int id) {

	NaryNode *node = (NaryNode*) calloc(1, sizeof(NaryNode));
	sPeople people;

	if (typeid((*(sPeople*) tree->data)) == typeid(sPeople)) {
		people = (*(sPeople*) tree->data);
		cout << "Id:" << people.id << endl;
		cout << "Age:" << people.age << endl;
		cout << "Name:" << people.name->c_str() << endl;
	}

	if (people.id == id) {
		cout << "Achou" << endl;
	}

	for (int i = 0; i < tree->n; i++) {

		findNode(tree->child[i], id);
	}

	return tree;
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

void *createPeople(int id, string name, int age) {

	sPeople *ptr = (sPeople*) calloc(1, sizeof(sPeople));
	ptr->id = id;
	ptr->age = age;
	ptr->name = new string(name);

	return ptr;
}

void printTree(NaryTree *tree) {

	if (tree == NULL)
		return;

	if (typeid((*(sPeople*) tree->data)) == typeid(sPeople)) {
		sPeople people = (*(sPeople*) tree->data);
		cout << "Id:" << people.id << endl;
		cout << "Age:" << people.age << endl;
		cout << "Name:" << people.name->c_str() << endl;
	}

	for (int i = 0; i < tree->n; i++)
		printTree(tree->child[i]);
}

void freeTree(NaryTree *tree, DataFreeFunc dFree) {
	if (tree == NULL)
		return;

	 for (int i = 0; i < tree->n; ++i)
		freeTree(tree->child[i], dFree);

	free(tree->child);
	if (dFree)
		dFree(tree->data);
	free(tree);
}
