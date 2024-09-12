#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_set>
using namespace std;

class BinarySearchTree
{
private:
	

public:
	class node
	{
	public:
		node* left;
		node* right;
		node* parent;
		double key;
		string name;
		string team;
		int dataType;

		node(string n, int k, string t, int dt) : left(NULL), right(NULL), parent(NULL), name(n), team(t), key(k), dataType(dt) {}
	};

	node* root;
	BinarySearchTree()
	{
		root = NULL;
	}
	void TREE_INSERT(string n, int k, string t, int dt);
	node* FIND_NODE(node*, string pn);
	bool isEmpty() const { return root == NULL; }
	node* FIND_MAX(node*);
	node* FIND_MIN(node*);
	void INORDER_TREE_WALK(node*);
	void REVERSE_INORDER_TREE_WALK(node*);
	void FIND_TRIPLE_DOUBLES(node* pointsRoot, node* assistsRoot, node* reboundsRoot, unordered_set<string>& tripleDoublePlayers);
	

	/*
	void POSTORDER_TREE_WALK(node*);
	void PREORDER_TREE_WALK(node*);
	void REMOVE_MAX(node*);
	int SUCCESSOR(node*, int d);
	*/
	void DELETE(string name);
	void TRANSPLANT(node*, node*);
};

BinarySearchTree::node* BinarySearchTree::FIND_NODE(node* x, string pn) {
	if(x == NULL || x->name == pn)
		return x;
	if (pn < x->name)
		return FIND_NODE(x->left, pn);
	else
		return FIND_NODE(x->right, pn);
}  
/*
double getDouble() {
	double n;
	cout << "Enter a double : ";
	cin >> num;
	if (cin.fail()) {
		cin.clear();       
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		cout << "Invalid input. Please enter a double." << std::endl;
	}
	else {
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		return num;
	}
}
*/
void BinarySearchTree::DELETE(string name) {

	node* z = FIND_NODE(root,name);

	if (z == NULL) {
		cout << "Node not found." << endl;
	}
	if (z->left == NULL) {
		TRANSPLANT(z, z->right);
	}
	else if (z->right == NULL) {
		TRANSPLANT(z, z->left);
	}
	else {
		node* y = z->right;
		while (y->left != NULL) y = y->left; // y is the successor node of x
		if (y->parent != NULL) {
			TRANSPLANT(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		TRANSPLANT(z, y);
		y->left = z->left;
		y->left->parent = y;
	}
	delete z;
};
void BinarySearchTree::TRANSPLANT(node* p, node* q) {
	if (p->parent == NULL) root = q;
	else if (p == p->parent->left) p->parent->left = q;
	else if (p == p->parent->right) p->parent->right = q;
	if (q != NULL) q->parent = p->parent;
}


/*
int BinarySearchTree::SUCCESSOR(node* x, int d) {
	while (x != NULL && d != x->key) {
		if (d < x->key)
			x = x->left;
		else
			x = x->right;
	}
	if (x->right != NULL) return MIN(x->right);
	else {
		node* y = x->parent;
		while (y != NULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y->key;
	}
}


void BinarySearchTree::REMOVE_MAX(node* x) {
	while (x->right != NULL) {
		x = x->right;
	}
	if (x->left != NULL) {
		x->left->parent = x->parent;
	}
	if (x->parent != NULL) {
		x->parent->right = x->left;
	}
	else {
		root = x->left;
	}
	delete(x);
}
*/
BinarySearchTree::node* BinarySearchTree::FIND_MAX(node* x) {
	if(x == NULL)
		return x;
	while (x->right != NULL) {
		x = x->right;
	}
	return x;	
}
BinarySearchTree::node* BinarySearchTree::FIND_MIN(node* x) {
	if (x == NULL)
		return x;
	while (x->left != NULL) {
		x = x->left;
	}
	return x;
}

void BinarySearchTree::INORDER_TREE_WALK(node* x)
{
	if (x != NULL)
	{
		INORDER_TREE_WALK(x->left);
		cout << x->name << " (" << x->team << " ) " << x->key << " " << x->dataType << endl;
		INORDER_TREE_WALK(x->right);
	}
}

void BinarySearchTree::REVERSE_INORDER_TREE_WALK(node* x) {
	if (x != NULL)
	{
		REVERSE_INORDER_TREE_WALK(x->right);
		cout << x->name << " (" << x->team << " ) " << x->key << " " << x->dataType << endl;
		REVERSE_INORDER_TREE_WALK(x->left);
	}	
}


/*
void BinarySearchTree::POSTORDER_TREE_WALK(node* x) {
	if (x != NULL)
	{
		if (x->left) POSTORDER_TREE_WALK(x->left);
		if (x->right) POSTORDER_TREE_WALK(x->right);
		cout << " " << x->key << " ";
	}
}

void BinarySearchTree::PREORDER_TREE_WALK(node* x) {
	if (x != NULL) {
		cout << " " << x->key << " ";
		if (x->left) PREORDER_TREE_WALK(x->left);
		if (x->right) PREORDER_TREE_WALK(x->right);
	}
}
*/
void BinarySearchTree::TREE_INSERT(string n, int k, string t, int dt)
{
	// This implements the algorithm in page 261 of the textbook
	node* z = new node(n,k,t,dt);
	node* y = NULL;
	node* x = root;
	node* parent = NULL;

	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;

	if (y == NULL)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;

}

void BinarySearchTree::FIND_TRIPLE_DOUBLES(node* pointsRoot, node* assistsRoot, node* reboundsRoot, unordered_set<string>& tripleDoublePlayers) {
	if (pointsRoot == NULL) return;
	FIND_TRIPLE_DOUBLES(pointsRoot->left, assistsRoot, reboundsRoot, tripleDoublePlayers);

	node* assistsNode = FIND_NODE(assistsRoot, pointsRoot->name);
	node* reboundsNode = FIND_NODE(reboundsRoot, pointsRoot->name);

	if (assistsNode != NULL && reboundsNode != NULL) {
		if (pointsRoot->key >= 10 && assistsNode->key >= 10 && reboundsNode->key >= 10) {
			tripleDoublePlayers.insert(pointsRoot->name);
		}
	}

	FIND_TRIPLE_DOUBLES(pointsRoot->right, assistsRoot, reboundsRoot, tripleDoublePlayers);
}

int main()
{
	BinarySearchTree Points;
	BinarySearchTree Assists;
	BinarySearchTree Rebounds;
	int choice;
	double key;
	string name;
	string team;
	int datatype;
	while (true)
	{
		cout << endl << endl;
		cout << " Binary Search Tree Example " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Insertion " << endl;
		cout << " 2. Delete " << endl;
		cout << " 3. Max Records " << endl;
		cout << " 4. Min Records " << endl;
		cout << " 5. Display Player Information in descending order " << endl;
		cout << " 6. Display players with triple doubles " << endl;
		cout << " 7. Exit " << endl;
		cout << " Enter your choice : ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1: 
			cout << " Enter name, data, team name, data type (data type (1) for points, (2) for assists, (3) for rebounds)\n" << endl;
			cout << " Type name (string) : ";
			cin >> name;
			cout << " Type data (double): ";
			cin >> key;
			cout << " Type team name (string) :";
			cin >> team;
			cout << " Type data type (double) : ";
			cin >> datatype;
			if (datatype == 1) Points.TREE_INSERT(name, key, team, datatype);
			else if(datatype == 2) Assists.TREE_INSERT(name, key, team, datatype);
			else Rebounds.TREE_INSERT(name, key, team, datatype);
			cout << " -------------------" << endl;
			break;
		case 2: cout << endl;
			cout << "Enter the name of the player to be deleted (string value)!" << endl;
			cin >> name;
			Points.DELETE(name);
			Assists.DELETE(name);
			Rebounds.DELETE(name);
			cout << name << " deleted! " << endl;
			cout << " -------------------" << endl;
			break;
		case 3: 
		{
			cout << endl;
			cout << "Max Records: " << endl;
			BinarySearchTree::node* maxPoints = Points.FIND_MAX(Points.root);
			if(maxPoints != NULL)
				cout << "Name: " << maxPoints->name << " Team: " << maxPoints->team << " Points: " << maxPoints->key << endl;
			else
				cout << " No player exixts! " << endl;
			BinarySearchTree::node* maxAssists = Points.FIND_MAX(Assists.root);
			if (maxAssists != NULL)
				cout << "Name: " << maxAssists->name << " Team: " << maxAssists->team << " Assists: " << maxAssists->key << endl;
			else
				cout << " No player exixts! " << endl;
			BinarySearchTree::node* maxRebounds = Points.FIND_MAX(Rebounds.root);
			if(maxRebounds != NULL)
				cout << "Name: " << maxRebounds->name << " Team: " << maxRebounds->team << " Rebounds: " << maxRebounds->key << endl;
			else
				cout << " No player exixts! " << endl;
			cout << " -------------------" << endl;
			break;
		}
		case 4: 
		{
			cout << endl;
			cout << "Min Records: " << endl;
			BinarySearchTree::node* minPoints = Points.FIND_MIN(Points.root);
			if (minPoints != NULL)
				cout << "Name: " << minPoints->name << " Team: " << minPoints->team << " Points: " << minPoints->key << endl;
			else
				cout << " No player exixts! " << endl;
			BinarySearchTree::node* minAssists = Points.FIND_MIN(Assists.root);
			if(minAssists != NULL)
				cout << "Name: " << minAssists->name << " Team: " << minAssists->team << " Assists: " << minAssists->key << endl;
			else
				cout << " No player exixts! " << endl;
			BinarySearchTree::node* minRebounds = Points.FIND_MIN(Rebounds.root);
			if(minRebounds != NULL)	
				cout << "Name: " << minRebounds->name << " Team: " << minRebounds->team << " Rebounds: " << minRebounds->key << endl;
			else
				cout << " No player exixts! " << endl;
			cout << " -------------------" << endl;
			break;
		}
		case 5: cout << endl;
			cout << " Reverse In-Order Traversal " << endl;
			Points.REVERSE_INORDER_TREE_WALK(Points.root);
			Assists.REVERSE_INORDER_TREE_WALK(Assists.root);
			Rebounds.REVERSE_INORDER_TREE_WALK(Rebounds.root);
			cout << " -------------------" << endl;
			break;
		case 6:
		{
			cout << "Listing players with triple doubles: " << endl;
			unordered_set<string> tripleDoublePlayers;
			Points.FIND_TRIPLE_DOUBLES(Points.root, Assists.root, Rebounds.root, tripleDoublePlayers);
			if (tripleDoublePlayers.empty()) {
				cout << "No players with triple doubles." << endl;
			}
			else {
				for (const auto& player : tripleDoublePlayers) {
					cout << player << endl;
				}
			}
			cout << " -------------------" << endl;
			break;
		}
		case 7: system("pause");
			return 0;
			break;

		default:
			cout << "Invalid choice";
		}
	}
}
