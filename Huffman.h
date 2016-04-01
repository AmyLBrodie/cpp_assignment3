
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
    
    
    class HuffmanNode{
    private:
        char letter;
        int frequency;
        std::shared_ptr<HuffmanNode> leftChild;
        std::shared_ptr<HuffmanNode> rightChild;
    public:
        HuffmanNode(char l, int f, std::shared_ptr<HuffmanNode> lChild, std::shared_ptr<HuffmanNode> rChild);
        ~HuffmanNode();
        
        int getFrequency() const;
        char getChar() const;
        std::shared_ptr<HuffmanNode> getLeft();
        std::shared_ptr<HuffmanNode> getRight();
    };
    
    class CompareQueue{
    public:
        CompareQueue();
        bool operator() (const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) const;
    };
    
    class HuffmanTree{
    private:
        //std::string textFile = "";
        std::unordered_map<char, int> characterMap;
        std::unordered_map<char, std::string> codeTable;
        std::shared_ptr<HuffmanNode> root;
        std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, CompareQueue> treeQueue;
    public:
        HuffmanTree();
        ~HuffmanTree();
        
        void fileReader(std::string fileName);
        void createQueue();
        void insertNodes();
        void traverseTree(std::shared_ptr<HuffmanNode> node, int left, std::string code);
        void createCodeTable();
        void compressFile(std::string fileName, std::string outputFile);
    };
}

#endif /* HUFFMAN_H */

