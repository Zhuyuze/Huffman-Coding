#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <hash_map>
using namespace std;
using namespace __gnu_cxx;
hash_map<int, string> store;

struct node {
	int data;
	int weight;
	node* left;
	node* right;
};
class quadHeap {

	int size;
	int length;
	node* allLeaf;
	public:
		quadHeap(string fileName) {
			size = 0;
			length = 1;
			allLeaf = new node;
			readFreqTable(fileName);
			buildMinHeap(allLeaf, size);
		}
		~quadHeap() {
			delete[] allLeaf;
		}
		void readFreqTable(string fileName) {
			ifstream input;
			int indx, freq;
			input.open(fileName.c_str(), ios::in);
			if (!input.is_open()) {
				cout << "file load failed!" << endl;
				return;
			}
			while (!input.eof()) {

				input >> indx >> freq;
				if (input.fail()) break;
				size++;
				if (size > length) {
					length *= 2;
					node* t = allLeaf;
					allLeaf = new node[length];
					for (int i = 0; i < size-1; i++) {
						allLeaf[i].data = t[i].data;
						allLeaf[i].weight = t[i].weight;
						allLeaf[i].left = NULL;
						allLeaf[i].right = NULL;
					}
					delete[] t;
				}
				allLeaf[size-1].data = indx;
				allLeaf[size-1].weight = freq;
				allLeaf[size-1].left = NULL;
				allLeaf[size-1].right = NULL;
			}
			input.close();
		}

		void minHeapify(node* a, int pos, int len) {
			int i = 0;
			if (pos*4 + 1 < len && a[pos].weight > a[pos*4+1].weight) i = pos*4 + 1;
			else i = pos;
			if (pos*4 + 2 < len && a[i].weight > a[pos*4+2].weight) i = pos*4 + 2;
			if (pos*4 + 3 < len && a[i].weight > a[pos*4+3].weight) i = pos*4 + 3;
			if (pos*4 + 4 < len && a[i].weight > a[pos*4+4].weight) i = pos*4 + 4;
			if (i == pos) return;
			node k = a[i];
			a[i] = a[pos];
			a[pos] = k;
			minHeapify(a, i, len);
		}
		void minHeapifyDown(node* a, int len) {
			
			if (len == 0) return;
			int p = (len + 3) / 4 - 1;
			if (a[len].weight >= a[p].weight) return;
			node k = a[len];
			a[len] = a[p];
			a[p] = k;
			
			minHeapifyDown(a, p);
		}
		void buildMinHeap(node* a, int len) {
			for (int i = (len-2)/4; i >=0; i--){
			minHeapify(a, i, len);
			}
		}		
		node popMinNode() {
			node n = *allLeaf;
			size--;
			allLeaf[0] = allLeaf[size];
			minHeapify(allLeaf, 0, size);
			return n;
		}		
		void pushNode(node n) {
			size++;
			if (size > length) {
				length *= 2;
				node* t = allLeaf;
				allLeaf = new node[length];
				for (int i = 0; i < size-1; i++) {
					allLeaf[i].data = t[i].data;
					allLeaf[i].weight = t[i].weight;
					allLeaf[i].left = NULL;
					allLeaf[i].right = NULL;
				}
				delete[] t;
			}
			allLeaf[size-1] = n;
			minHeapifyDown(allLeaf, size-1);	
				
		}		
		node* buildHuffmanTree() {
			while(size > 1) {
				node* l = new node(popMinNode());
				node* r = new node(popMinNode());
				node n;
				n.data = -1;
				n.weight = l->weight + r->weight;
				n.left = l;
				n.right = r;
				pushNode(n);
			}
			return allLeaf;
		}
};
void read(string fileName) {
	hash_map<int, int> freq;
	int temp;
	ifstream input;
	input.open(fileName.c_str(), ios::in);
	if (!input.is_open()) {
		cout << "file load failed!" << endl;
		return;
	}
	while (!input.eof()) {

		input >> temp;
		if (input.fail()) break;
			
		if (freq.find(temp) == freq.end()) {
			freq[temp] = 1;
		}
		else freq[temp]++; 
	}
	input.close();
	ofstream output;
	output.open("frequency_table.txt", ios::out);
	if (!output) cout << "failed to write!" << endl;
	hash_map<int, int>::iterator it = freq.begin();
	while (it != freq.end()) {
		output << it->first << " " << it->second << endl;
		it++;
	}
	output.close();
}
void printCode(node* n, string s) {
	if (n == NULL) return;
	if (n->data != -1) {
		store[n->data] = s;
		return;
	}
	printCode(n->left, s+"0");
	printCode(n->right, s+"1");	
}
void deleteTree(node* t) {
	if (t == nullptr || t == NULL) return;
	deleteTree(t->left);
	deleteTree(t->right);
	delete t;
}
void encode(string fileName) {
	int temp;
	string all = "";
	ifstream input;
	input.open(fileName.c_str(), ios::in);
	if (!input.is_open()) {
		cout << "file load failed!" << endl;
		return;
	}
	while (!input.eof()) {

		input >> temp;
		if (input.fail()) break;
		string t = store[temp];
		all += t;
	}
	input.close();
	
	ofstream output;
	output.open("encoded.bin", ios::out | ios::binary);
	if (!output) cout << "failed to write!" << endl;
	unsigned char buffer = 0;
	int counter = 0;
	int pos = 0;
	while (all[pos] != '\0') {
		buffer = buffer | ((all[pos] - '0') << (7 - counter));
		counter++;
		pos++;
		if (counter == 8) {
			output << buffer;
			counter = 0;
			buffer = 0;
		}
	}
	if (counter > 0) output<< buffer;
	

	output.close();
}




int main() {
	string fileName;
	cin >> fileName;
	read(fileName);
	quadHeap q("frequency_table.txt");
	node* huffmanTree = q.buildHuffmanTree();
	printCode(huffmanTree, "");
	hash_map<int, string>::iterator it = store.begin();
	ofstream output;
	output.open("code_table.txt", ios::out);
	if (!output) cout << "failed to write!" << endl;
	while (it != store.end()) {
		output << it->first << " " << it->second << endl;
		it++;
	}
	output.close();
	//deleteTree(huffmanTree);
	encode(fileName);
	
	return 0;
}
