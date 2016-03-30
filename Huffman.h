
/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3022H Tutorial 3 
 * Created on 29 March 2016, 11:06 PM
 */

#include <string>
#include <memory>
#include <queue>
#include <unordered_map>

#ifndef HUFFMAN_H
#define HUFFMAN_H

namespace BRDAMY004{
    
    
    
    class FileReader{
    public:
        std::unordered_map<char, int> characterMap;
        FileReader(std::string fileName);
    };
    
    class HuffmanNode{
    private:
        char letter;
        int frequency;
        std::shared_ptr<HuffmanNode> leftChild;
        std::shared_ptr<HuffmanNode> rightChild;
    public:
        HuffmanNode(char l, int f);
        ~HuffmanNode();
        
        int getFrequency() const;
    };
    
    class CompareQueue{
    public:
        CompareQueue();
        bool operator() (const HuffmanNode& a, const HuffmanNode& b) const;
    };
    
    class HuffmanTree{
    private:
        std::shared_ptr<HuffmanNode> root;
        std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, CompareQueue> treeQueue;
    public:
        HuffmanTree();
        ~HuffmanTree();
        
        void insertNode(char letter, int frequency);
    };
}

#endif /* HUFFMAN_H */

