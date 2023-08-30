#pragma once

#include "frequency_table.h"
#include <unordered_map> 
#include<string>
#include<vector>
#include<queue>
#include <stdio.h>

// struct for the nodes of the tree?
using namespace std;
struct Node
{
    char c;
    int frequency;
    Node* left, * right;
    Node() {}
    Node(char k, int t) :c(k), frequency(t), left(nullptr), right(nullptr)
    {}
};
struct CompFreq {
    bool operator()(Node* p1, Node* p2)
    {
        // return "true" if "p1" is ordered  
        // before "p2", for example: 
        return p1->frequency > p2->frequency;
    }
};

class huffman_encoder {
private:
    string fileName;
    priority_queue<Node*, vector<Node*>, CompFreq> pqTree;
    //tree node
    Node* rootOfTree; 
    //this map stores the code of each character
    unordered_map<char, string> mp;
    //new frequency table with no 0.
    unordered_map<char, int> newFreq;

    
    public:
        huffman_encoder(const frequency_table &table);
        ~huffman_encoder();
        std::string get_character_code(char c) const;
        std::string encode(const std::string &file_name) const;
        std::string decode(const std::string &string_to_decode) const;

        void encodeI();
        void encodeII(Node* root, string codeStr, unordered_map<char, string>& mp)const;
        void decode(Node* root, string decodeStr, string& result)const;
        

};
