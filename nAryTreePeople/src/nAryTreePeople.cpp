#include "nAryTreePeople.h"

int main() {

	//root
	NaryTree *tree = createNode(0, createPeople(0, "Grandhmother", 80));

	appendChild(tree, createPeople(1, "Son1", 34));
	appendChild(tree, createPeople(2, "Son2", 33));
	appendChild(tree, createPeople(3, "Son3", 60));

	//static mode
	//appendChild(tree->child[0], createPeople(11, "Son1 of Son1", 1));

	/**************************************************************************
	 dynamic mode
	 ***************************************************************************/
	//dont include duplicade items
	insertNodeById(tree, 1, createPeople(11, "Son1 of Son1", 1), true);
	insertNodeById(tree, 1, createPeople(11, "Son1 of Son1", 1), true);

	//Son from id 2 with id 21
	insertNodeById(tree, 2, createPeople(21, "Son1 of Son2", 2), true);
	//Son from id 21 with id 211
	insertNodeById(tree, 21, createPeople(211, "Son1 of Son21", 21), true);

	insertNodeById(tree, 3, createPeople(31, "Son1 of Son3", 33), true);

	cout << "Size of Tree: " << sizeOfNaryTree(tree) << endl;

	printTree(tree);

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

bool insertNodeById(NaryTree *tree, int id, void *data, bool searchNode) {

	if (tree == NULL)
		return false;

	if (typeid((*(sPeople*) tree->data)) == typeid(sPeople)) {

		if (searchNode) {
			sPeople people = (*(sPeople*) tree->data);

			if (people.id == id) {

				if(!verifyKeySonOfNode(tree, data)){
					appendChild(tree, data);
					searchNode = false;
					return searchNode;
				}
			}

			for (int i = 0; i < tree->n; ++i)
				searchNode = insertNodeById(tree->child[i], id, data,
						searchNode);
		}
	}
	return searchNode;
}

bool verifyKeySonOfNode(NaryTree *tree, void *data) {

	if (typeid((*(sPeople*) tree->data)) == typeid(sPeople)) {

		for (int i = 0; i < tree->n; ++i) {

			sPeople peopleTree = (*(sPeople*) tree->data);
			sPeople peopleData = (*(sPeople*) tree->data);

			if (peopleTree.id == peopleData.id) {
				return true;
			}
		}
	}
	return false;
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
		cout << "**************************************:" << endl;

		for (int i = 0; i < tree->n; i++)
			printTree(tree->child[i]);
	}
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

unsigned sizeOfNaryTree(NaryNode *root) {
	unsigned size = 0;

	if (root) {
		size++;
		for (int i = 0; i < root->n; ++i)
			size += sizeOfNaryTree(root->child[i]);
	}
	return size;
}
