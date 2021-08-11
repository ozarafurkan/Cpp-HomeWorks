#pragma once
#include <iostream>
using namespace std;
class HuffmanNode {
public:
	// One of the input characters
	char getData() { return data; } // getting data 
	int getFreq() { return freq; } // gettin freq
	void setData(char data) { this->data = data; } //setting data 
	void setFreq(int freq) { this->freq = freq; }//setting freq 
	HuffmanNode* left, * right;	// Left and right child
	HuffmanNode() { 
		left = right = NULL;
		data = NULL;
		freq = NULL;
	};
	HuffmanNode(char data, int freq)	{

		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
private:
	// Frequency of the character
	char data;
	int freq;


	


};

struct myComparator { // special comparator for priority queue for ordering huffman tree

	bool operator()(HuffmanNode* l, HuffmanNode* r) 

	{
		return (l->getFreq() > r->getFreq());// returns true if left freq > right freq
	}
};