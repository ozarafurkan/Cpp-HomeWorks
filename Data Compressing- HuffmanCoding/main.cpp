#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <queue>
#include "minHeap.h"
#include <bitset>


using namespace std;

map<char, int> readThefile() //Reads and fills the frequencies into a map
{
	ifstream in;
	char myWord;
	map<char, int> freq;
	in.open("text.txt"); // taking letters from txt file
	if (!in)
		cout << "File couldn't be found!\n";
	else {
		while (in >> noskipws >> myWord) { // noskips for taking white spaces
			freq[myWord]++;	// creating myWord key and incrementing its value if it already exist it just increment the value 
		}
	}
	return freq;
}

void calculateTheCodes(class HuffmanNode* rootNode, string str, map<char, string>& codes) // this func traverse over the list and calculates
// the exact huffman codes
{

	if (!rootNode)
		return;
	if (rootNode->getData() != 0) {
		codes[rootNode->getData()] = str;
		//if(rootNode->getData() == ' ')
		//	cout << "Space " << ": " << str << "\n"; // optimazing outputs for special chars
		//else if(rootNode->getData()=='\n')
		//	cout << "Newline " << ": " << str << "\n";
		//else
		//	cout << rootNode->getData() << ": " << str << "\n"; // printing the huffman codes for each char

	}
	//storing codes in string variable so we can put as much as we want 0 front of the code
	calculateTheCodes(rootNode->left, str + "0", codes); // one move left means 0
	calculateTheCodes(rootNode->right, str + "1", codes);// one move right means 1


}

void printTheCodes(map<char, string>& codes) {
	cout << "************ THE HUFFMAN CODE TABLE ************" << endl;
	for (auto i = codes.begin();i != codes.end();i++) { //traverse over the map with iterator i 

		if (i->first == ' ')
			cout << "Space " << ": " << i->second << "\n"; // optimazing outputs for special chars
		else if (i->first == '\n')
			cout << "Newline " << ": " << i->second << "\n";
		else
			cout << i->first << " : " << i->second << endl;// printing the huffman codes for each char

	}
	cout << endl << endl;
}

void create_HuffMan_tree(priority_queue<HuffmanNode*, vector<HuffmanNode*>, myComparator>& HuffmanTree) {
	class HuffmanNode* leftChild, * rightChild, * topNode;


	while (HuffmanTree.size() != 1)  // in here  this func traversal on priority queue the purpose of while loops state 
	//  stick together all nodes in one root node the while loop will turns till there is just one node inside so that means the root node
	{
		leftChild = HuffmanTree.top(); // storing the huffmanTree's top as left child temporarly
		HuffmanTree.pop(); // poping the top for traverse over the priority queue
		rightChild = HuffmanTree.top();  // same logic with upper lines
		HuffmanTree.pop();


		topNode = new HuffmanNode(); // giving space on memory
		topNode->setData(0); // settin data as a special char so we can determine it is it last node or not 
		topNode->setFreq(leftChild->getFreq() + rightChild->getFreq()); // adding 2 nodes frequency 

		topNode->right = rightChild; // for creating the huffman tree placing their right and left nodes for every node 
		topNode->left = leftChild;

		HuffmanTree.push(topNode); // pushing the exact huffman node we have created
	}



}

void printTextAs_HuffManTree(map<char, string>codes)//this func print the command screen and write it in a file at the same time
{
	ifstream in;
	ofstream out;
	char myWord;
	map<char, int> freq;
	cout << "huffman.txt: " << endl;
	in.open("text.txt"); // reading letters from txt file
	out.open("huffman.txt");//for writing the ascii codes in txt file
	if (!in)
		cout << "File couldn't be found!\n";
	else {
		while (in >> noskipws >> myWord) { // noskipws for taking white spaces

			cout << codes[myWord] << "  "; //printing into screen
			out << codes[myWord] << " "; //writing into text file

		}
	}
	in.close();
	out.close();
	cout << endl << endl;

}

void printTextAs_Ascii()//this func print the command screen and write it in a file at the same time
{
	ifstream in;
	ofstream out;
	char myWord;
	map<char, int> freq;
	string myAscii;
	cout << endl << "ascii.txt: " << endl;
	in.open("text.txt"); // reading letters from txt file
	out.open("ascii.txt");//for writing the ascii codes in txt file
	if (!in)
		cout << "File couldn't be found!\n";
	else {
		while (in >> noskipws >> myWord) {
			myAscii = bitset<8>(myWord).to_string(); // converting them to binary via the func from library
			cout << myAscii << "  ";
			out << myAscii << " ";
		}
	}
	in.close();
	out.close();
}

int main()//driver code
{

	map<char, int> freq;
	map<char, string>codes;//To store every code for each char in text

	priority_queue<HuffmanNode*, vector<HuffmanNode*>, myComparator> HuffmanTree;

	freq = readThefile();


	map<char, int>::iterator it;
	for (it = freq.begin(); it != freq.end(); it++) {//filling the huffmannýde typed priority queue 
		HuffmanTree.push(new HuffmanNode(it->first, it->second));
	}
	create_HuffMan_tree(HuffmanTree); // sending the huffman tree var to making it exact huffman tree


	calculateTheCodes(HuffmanTree.top(), "", codes); // we send here HufmannTree's top as root.

	printTheCodes(codes);
	printTextAs_HuffManTree(codes);
	printTextAs_Ascii();


	return 0;
}

