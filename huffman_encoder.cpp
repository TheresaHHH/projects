#include "huffman_encoder.h"
#include "frequency_table.h"
#include <string>
#include <queue>
#include <vector>
#include <unordered_map> 


/*Constructs a huffman_encoder object. This should
build a Huffman tree using all the non-zero entries
of the table */
huffman_encoder::huffman_encoder(const frequency_table &table){
	for (int i = 0; i < 128; i++) 
	{
		int f = table.get_frequency(static_cast<char>(i));
		if (f!=0) //build new frequecy table with non-zero entries
		{
			//cout << static_cast<char>(i) << endl;
			newFreq[static_cast<char>(i)] = f;
			//cout << f<<"   20";
		}
	}
	//cout << "22  " << newFreq.size() << endl;
	rootOfTree = nullptr;
	encodeI();
}

huffman_encoder::~huffman_encoder(){}

std::string huffman_encoder::get_character_code(char character) const {
	std::unordered_map<char, string>::const_iterator it;
	//cout << character << "   33 ";
	it = mp.find(character);
	return it->second;
}

std::string huffman_encoder::encode(const std::string &file_name) const {
	ifstream file1(file_name);
	//unordered_map<char, int> temp;
	std::unordered_map<char, string>::const_iterator it;
	string s = ""; 
	vector<char>cc;
	char c;
	//read file and store it in a char vector
	while (!file1.eof())
	{
		c = file1.get();
		cc.push_back(c);
	}
	//cout << "56  "<<cc.size()<<endl;
	cc.pop_back();
	//concat encode string
	for (unsigned int i = 0; i < cc.size();i++) 
	{
		if (mp.count(cc.at(i))) 
		{
			s = s + get_character_code(cc.at(i));
		}
		else {
			// the file contains a letter not present in the tree
			s = "";
			break;
		}
	}
	return s;
}

std::string huffman_encoder::decode(const std::string &string_to_decode) const {
	string s="";
	//cout << "68  "<<string_to_decode << endl;
	//int b = string_to_decode.length();
	//while (i < b-2) {
		decode(rootOfTree, string_to_decode, s);
	//}
	//single letter
	if (string_to_decode.size() == 1) 
	{
		auto it = newFreq.begin();
		s = it->first; 
	}
	return s;
}
void huffman_encoder::encodeI()
{   //Create a leaf node for each unique character and insert into the priority queue.
	std::unordered_map<char, int>::const_iterator it;
	for (it = newFreq.begin(); it != newFreq.end(); it++)
	{
		//cout << "73 " << it->first<<" "<< it->second << endl;
		Node* n = new Node(it->first, it->second);
		pqTree.push(n);
	}

	//while the priority queue has more than one item
	int x = 0;
	while (pqTree.size() != 1)
	{
		Node* left = pqTree.top();
		pqTree.pop();
		Node* right = pqTree.top();
		pqTree.pop();
		int sum = left->frequency + right->frequency;
		Node* n = new Node('\0', sum);
		n->left = left;
		n->right = right;
		pqTree.push(n); x++;
	}
	rootOfTree = pqTree.top();
	encodeII(rootOfTree, "", mp);
	/*
	cout << "115  "<< endl;
	for (auto it : mp)
	{
		cout << it.first << " code" << it.second << '\n';
	}*/
}


void huffman_encoder::encodeII(Node* n, string codeStr, unordered_map<char, string>& mp)const
{
	if (n == nullptr)
	{
		return;//base case
	}

	if (newFreq.size()==1) //single letter
	{
		//cout << "130" << endl;
		mp[n->c] = "1";
		return;
	}

	// assigns code to the leaf node
	if (n->left==nullptr && n->right==nullptr) {
		mp[n->c] = codeStr;
	}

	// recursive case
	encodeII(n->left, codeStr + "0", mp);
	encodeII(n->right, codeStr + "1", mp);
}

void huffman_encoder::decode(Node* root, string decodeStr, string& result)const
{
	Node* n = root;
	//if (n == nullptr) { return; }
	for (unsigned int i = 0; i < decodeStr.size(); i++)
	{   
		if (decodeStr[i] != '0'&& decodeStr[i] != '1') 
		{// characters other than ‘0’ or‘1’
			result = ""; break; 
		}
		if (decodeStr[i] == '0')
		{
			n = n->left;
		}
		else
		{
			n = n->right;
		}
		if (n == nullptr) { return; }
		// reached leaf node 
		if ( n->left == nullptr && n->right == nullptr)
		{
			result += n->c;
			n = root;
		}
	}
}