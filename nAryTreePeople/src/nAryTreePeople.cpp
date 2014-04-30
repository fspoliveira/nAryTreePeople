#include "nAryTreePeople.h"

int main() {

	//root
	NaryTree *tree = createNode(0, createPeople(0, "Grandhmother", 80));

	appendChild(tree, createPeople(1, "Son1", 34));
	appendChild(tree, createPeople(2, "Son2", 33));

	//appendChild(tree->child[0], createPeople(11, "Son1 of Son1", 2));

	insertNodebyID(tree, 1, createPeople(11, "Son1 of Son1", 2));
	insertNodebyID(tree, 2, createPeople(21, "Son1 of Son2", 2));
	insertNodebyID(tree, 21, createPeople(211, "Son 1 of 21", 1));
	insertNodebyID(tree, 21, createPeople(212, "Son 2 of 21", 2));

	insertNodebyID(tree, 212, createPeople(2121, "Son 1 of 212", 3));

	printTree(tree);

	freeTree(tree, dFree);

	return 0;
}

void insertNodebyID(NaryTree *tree, int id, void *data) {
	if (typeid((*(sPeople*) tree->data)) == typeid(sPeople)) {
		sPeople people = (*(sPeople*) tree->data);

		if (people.id == id) {
			appendChild(tree, data);
		}
	}

	for (int i = 0; i < tree->n; ++i)
		insertNodebyID(tree->child[i], id, data);
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
		cout <<"**************************************:" <<  endl;
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
