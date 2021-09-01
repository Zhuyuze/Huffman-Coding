#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include "weights.cpp"
#include "freqSort.cpp"
#include "element.hpp"
#include "binaryHeap.cpp"
#include "quadHeap.cpp"
#include "pairingHeap.cpp"
#include "node.hpp"
#include <ctime>
using namespace std;


void build_tree_using_binary_heap(string fileName) {
	
}


void deepFirstScan(node* t) {
	if (t->left != NULL) deepFirstScan(t->left);
	if (t->right != NULL) deepFirstScan(t->right);
	if (t->data != -1) cout << t->data << endl;
	return;
}






int main(int argc, char** argv) {
/* 
	// count weights
	string s = "sample_input_large.txt";
	weights w(s);
	w.print();
*/
	

	clock_t start;
	string table = "frequency_table.txt";

	// binary heap
	binaryHeap b(table);
	start = clock();
	node* t = b.buildHuffmanTree();
	cout << clock() - start << endl;

	
	// quad heap
	quadHeap q(table);
	start = clock();
	node* tq = q.buildHuffmanTree();
	cout << clock() - start << endl;

/*
	//pairing heap
	start = clock();
	pairingHeap p(table);
	node* tp = p.buildHuffmanTree();
	cout << clock() - start << endl;
*/
	
	
	// choose quard heap to complete
/*
	string table = "frequency_table.txt"
	quadHeap q(table);
	node* huffman = q.buildHuffmanTree();
*/
	
	
	
	return 0;	
}
