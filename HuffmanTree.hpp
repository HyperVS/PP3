#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <iostream>
#include <map>
#include <stack>

class HuffmanTree : HuffmanTreeBase {
    private:
        size_t n;
        HuffmanNode* root;
    public:
        std::string compress(const std::string inputStr) override;
        std::string serializeTree() const override;
        std::string decompress(const std::string inputCode, const std::string serializedTree) override;
        void findCode(const HuffmanNode* node, std::map<char, std::string>& codeMap, std::string code) {
            if (node == nullptr) 
                return;

            if(node->isLeaf())
                codeMap[node->getCharacter()] = code; 

            findCode(node->left, codeMap, code + "0");
            findCode(node->right, codeMap, code + "1");

        }

        // Helper function to recursively serialize the Huffman Tree in postorder traversal
        void serialize(const HuffmanNode* node, std::string& outString) const {
            if (node == nullptr) return;
            
            serialize(node->left, outString);
            serialize(node->right, outString);

            // If node is a leaf
            if (node->isLeaf()) outString = outString + "L" + node->getCharacter();

            // If node is a branch
            if (node->isBranch()) outString += "B";
        }

};

#endif /*HUFFMANTREE_H*/