#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <hash_map>
#include "element.hpp"
using namespace std;
using namespace __gnu_cxx;

class weights {
	
	int size;
	int length;
	element* allweights;
	hash_map<int, int> freq;
	
	public:
	weights(string fileName) {
		size = 0;
		length = 1;
		allweights = new element;
		getWeightsFromFile(fileName);
	}
	~weights() {
		delete[] allweights;
	}
	int findElement(int a) {
		for (int i = 0; i < size; i++) {
			if (allweights[i].index == a) return i;
		}
		return -1;
	}
	void getWeightsFromFile(string fileName) {
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
				size++;
			}
			else freq[temp]++; 
			/*
			int pos = findElement(temp);
			if (pos != -1) {
				allweights[pos].weight++;
			} else {
				size++;
				if (size > length) {
					length *= 2;
					element* t = allweights;
					allweights = new element[length];
					for (int i = 0; i < size-1; i++) {
						allweights[i].index = t[i].index;
						allweights[i].weight = t[i].weight;
					}
					delete[] t;
				}
				
				allweights[size-1].index = temp;
				allweights[size-1].weight = 1;
			}
			*/
		}
	}
	void print() {
		ofstream output;
		output.open("frequency_table.txt", ios::out);
		if (!output) cout << "failed to write!" << endl;
		
		hash_map<int, int>::iterator it = freq.begin();
		while (it != freq.end()) {
			output << it->first << " " << it->second << endl;
			it++;
		}
		/*
		for (int i = 0; i < size; i++) {
			
			output << allweights[i].index << " " << allweights[i].weight << endl;
			cout << allweights[i].index << "\t" << allweights[i].weight << endl;
		}
		*/
		output.close();
		//cout << length << endl;
		//cout << size << endl;
	}

};
