#include "HuffmanTree.hpp"

// Compress the input string
std::string HuffmanTree::compress(const std::string inputStr) {
    std::map<char, size_t> charMap;
    std::map<char, size_t>::iterator i;

    size_t count[256] = {0};

    // Read characters, count frequency, and store in array
    for (int i = 0; inputStr[i] != '\0'; i++) {
        count[inputStr[i]]++;    
    }
    for(int i = 0; i < 256; i++) {
        if(count[i] != 0){
            charMap.insert(std::pair<char,size_t>((char)i, count[i]));                   
        }
    }

    // Create Heap Queue and populate it
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> queue;
    for (i = charMap.begin(); i != charMap.end(); ++i) {
        HuffmanNode* node = new HuffmanNode(i->first, i->second);
        n++;
        queue.insert(node);
    }

    // Build the Huffman Tree using the Heap Queue
    while (queue.size() != 1){
        HuffmanNode* left = queue.min();
        queue.removeMin();
        HuffmanNode* right = queue.min();
        queue.removeMin();
        size_t totalFrequency = (left->getFrequency() + right->getFrequency());
        HuffmanNode* parent = new HuffmanNode('\0', totalFrequency, nullptr, left, right);
        left->parent = parent;
        right->parent = parent;
        queue.insert(parent);
    }

    root = queue.min();

    // Encoding each character in the string using a map
    std::map<char, std::string> codeMap;
    std::string code = "";
    std::string output = "";

    for (i = charMap.begin(); i != charMap.end(); ++i) {
        findCode(queue.min(), codeMap, code);
    }
    
    for (auto i : inputStr) {
        output += codeMap[i];
    }
   return output;
}

// Serialize the tree using recursive helper function
std::string HuffmanTree::serializeTree() const {
    if (root == nullptr) return "";
    std::string output = "";
    serialize(root, output);
    return output;
}

// Decompress the compressed string into the original input string
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    std::string output = "";
    std::stack<HuffmanNode*> treeStack;
   
    // Reconstruct the tree using the serializedTree
    for(std::string::const_iterator i = serializedTree.begin(); i != serializedTree.end(); i++){
        if(*i == 'L'){
            i++;
            HuffmanNode *n = new HuffmanNode(*i, 0);
            treeStack.push(n);
        } else {
            HuffmanNode* right = treeStack.top();
            treeStack.pop();
            HuffmanNode* left = treeStack.top();
            treeStack.pop();
            HuffmanNode* branch = new HuffmanNode('\0', 0, nullptr, left, right);
            treeStack.push(branch);
        }
    }

    // Copy whatever remains in the stack to the root of the newly constructed Huffman Tree and clean up
    HuffmanNode* root = treeStack.top();
    treeStack.pop();

    // Reconstruct the text from the code using the Huffman Tree
    HuffmanNode* curr = root;
    for (auto character : inputCode) {
        if (character == '0') curr = curr->left;
        else curr = curr->right;

        // Once a leaf is reached, add character to output and start again from root
        if (curr->isLeaf()) {
            output += curr->getCharacter();
            curr = root;
        }
    }   
    return output;
}