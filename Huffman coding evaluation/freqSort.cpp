#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include "element.hpp"
using namespace std;

class freqSort {

	int size;
	int length;
	element* allweights;

	public:
		freqSort(string fileName) {
			size = 0;
			length = 1;
			allweights = new element;
			readFreqTable(fileName);
			sortFreqByWeight();
		}
		~freqSort() {
			delete[] allweights;
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
					element* t = allweights;
					allweights = new element[length];
					for (int i = 0; i < size-1; i++) {
						allweights[i].index = t[i].index;
						allweights[i].weight = t[i].weight;
					}
					delete[] t;
				}
				allweights[size-1].index = indx;
				allweights[size-1].weight = freq;
			}
		}

		void sortFreqByWeight() {
			sort(allweights, allweights+size, [](element e1, element e2){return e1.weight < e2.weight;});
		}
		void print() {
			ofstream output;
			output.open("sorted_frequency_table.txt", ios::out);
			if (!output) cout << "failed to write!" << endl;
			for (int i = 0; i < size; i++) {
				output << allweights[i].index << " " << allweights[i].weight << endl;
			}
			output.close();
			cout << length << endl;
			cout << size << endl;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
};
