#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <hash_map>
#include <sstream>
using namespace std;
using namespace __gnu_cxx;
hash_map<int, string> store;

struct node {
	int data;
	int weight;
	node* left;
	node* right;
	node() {
		data = -1;
		left = NULL;
		right = NULL;
	}
};

void readCodeTable(string tableName) {
	ifstream input;
	input.open(tableName.c_str(), ios::in);
	if (!input.is_open()) {
		cout << "file load failed!" << endl;
		return;
	}
	int temp;
	string tmpstr;
	while (!input.eof()) {		
		input >> temp >> tmpstr;
		if (input.fail()) break;
		store[temp] = tmpstr;
	}
	input.close();
}


void rebuildHuffmanTree(node* root) {
	hash_map<int, string>::iterator it = store.begin();
	node* tmp = root;
	while (it != store.end()) {
		string r = it->second;
		int d = it->first;
		int i = 0;
		while (i < r.length()) {
			if (r[i] == '0') {
				if (tmp->left == NULL) tmp->left = new node;	
				tmp = tmp->left;
			} else {
				if (tmp->right == NULL) tmp->right = new node;
				tmp = tmp->right;
			}
			i++;
		}
		tmp->data = d;
		tmp = root;
		it++;
	}
}
void deleteTree(node* t) {
	if (t == NULL) return;
	deleteTree(t->left);
	deleteTree(t->right);
	delete t;
}
void decode(node* t, string binName) {
	string all = "";
	ifstream input;
	input.open(binName.c_str(), ios::in | ios::binary);
	char c = 0;
	while (input.get(c)) {
		stringstream tmp;
		for (int i = 7; i > 0; i--) tmp<<((c>>i) & 1);//q
		tmp << (c&1);
		all += tmp.str();
	}
	input.close();
	ofstream output;
	output.open("decoded.txt", ios::out);
	int pos = 0;
	node* root = t, *tmp = t;
	while (pos < all.length()) {	
		if (all[pos] == '0' && tmp->left != NULL){
			tmp = tmp->left;
			pos++;
		} else if (all[pos] == '1' && tmp->right != NULL) {
			tmp = tmp->right;
			pos++;
		} else if (tmp->data != -1) {
			output << tmp->data << endl;
			tmp = root;
		}
	}
	output.close();
	
}
int main() {
	string binName, tableName;
	cin >> binName >> tableName;
	
	readCodeTable(tableName);
	node* huffmanTree = new node;
	rebuildHuffmanTree(huffmanTree);
	decode(huffmanTree, binName);
	
	
	deleteTree(huffmanTree);
	return 0;
}
