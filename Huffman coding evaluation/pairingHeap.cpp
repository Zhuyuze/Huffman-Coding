#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include "node.hpp"
using namespace std;

class pairingHeap {

	int size;
	struct pairingNode {
		node* pnode;
		pairingNode *sibling, *child, *prev;
		pairingNode(pairingNode* p) {
			this->pnode = p->pnode;
			child = NULL;
			sibling = NULL;
			prev = NULL;
		}
		pairingNode(node* n) {
			this->pnode = n;
			child = NULL;
			sibling = NULL;
			prev = NULL;
		}
	};
	pairingNode* min;
	public:
		pairingHeap(string fileName) {
			size = 0;
			min = NULL;
			readFreqTable(fileName);
			//sortFreqByWeight();
		}
		void scanDelete(pairingNode* t) {
			if (t != NULL) {
				scanDelete(t->child);
				scanDelete(t->sibling);
				delete t;
			}
		}
		~pairingHeap() {
			scanDelete(min);
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
				node* n = new node;
				n->weight = freq;
				n->data = indx;
				n->left = NULL;
				n->right = NULL;
				pushNode(new pairingNode(n));	
			}
		}
		
		pairingNode* combine(pairingNode* a) {
			if (a->sibling == NULL) return a;
			while (a->sibling != NULL) {
				pairingNode* t = a;
				pairingNode* u = a->sibling;
				a = a->sibling->sibling;
				pairingNode* temp = compareAndInsert(t, u);
				temp->sibling = a;
				a = temp;
			}
			return a;
		}
		node* popMinNode() {
			
			pairingNode* out = min;
			if (min->child == NULL) min = NULL;
			else min = combine(min->child);
			node* outnode = out->pnode;
			delete out;
			size--;
			return outnode;
			
			
			/*
			if (size > 1) {
				pairingNode* s = t;
				pairingNode* head = t;
				while (t != NULL) {
					t = t->sibling;
					if (s->pnode.weight < t->pnode.weight) s = t;
				}
				pairingNode* temp = head->sibling;
				head->sibling = s->sibling;
				if (head->sibling != NULL) head->sibling->sibling = temp;
			
				min = s;
				pairingNode* schild = min->child;
				if (min != head) min->child = head;
				else min->child = min->sibling;
				min->sibling = NULL;
			
				while (head != NULL) {
					if (head->sibling == s) head->sibling = schild;
					head = head->sibling;
				}
			}
			*/
		}
		
		
		pairingNode* compareAndInsert(pairingNode* &a, pairingNode* b) {
			if (b == NULL) return a;
			if (b->pnode->weight < a->pnode->weight) {
				b->prev = a->prev;
				a->prev = b;
				a->sibling = b->child;
				if (a->sibling != NULL) a->sibling->prev = a;
				b->child = a;
				a = b;
			} else {
				b->prev = a;
				a->sibling = b->sibling;
				if (a->sibling != NULL) a->sibling->prev = a;
				b->sibling = a->child;
				if (b->sibling != NULL) b->sibling->prev = b;;
				a->child = b;
			}
			return a;
		}
		void pushNode(pairingNode* n) {
			pairingNode* temp = n;
			if (min == NULL) {
				min = temp;
			} else {
				compareAndInsert(min, temp);
			}
			size++;	
		}
		
		
		node* buildHuffmanTree() {
			while(size > 1) {
				node* l = popMinNode();
				node* r = popMinNode();
				node* temp = new node;
				temp->data = -1;
				temp->weight = l->weight + r->weight;
				temp->left = l;
				temp->right = r;
				pushNode(new pairingNode(temp));
			}
			return min->pnode;
		}
		
		
		void deepFirstScan(pairingNode* t) {
			if (t->child != NULL) deepFirstScan(t->child);
			if (t->sibling != NULL) deepFirstScan(t->sibling);
			if (t->pnode->data != -1) cout << t->pnode->data << endl;
			return;
		}
		void print() {
			deepFirstScan(min);
			cout << size << endl;
		}
		
		
};
