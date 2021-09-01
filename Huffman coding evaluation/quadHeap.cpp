
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include "node.hpp"
using namespace std;

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
		
		void print() {
			//heapSort(allLeaf, size);
			for (int i = 0; i < size; i++) {
				cout << allLeaf[i].data << "\t" << allLeaf[i].weight << endl;
			}
			cout << length << endl;
			cout << size << endl;
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
