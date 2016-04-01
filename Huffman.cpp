
/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3022H Tutorial 3 
 * Created on 29 March 2016, 11:06 PM
 */

#include "Huffman.h"
#include <string>
#include <memory>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

namespace BRDAMY004{
    

    
    // HuffmanNode class
    HuffmanNode::HuffmanNode(char l, int f, std::shared_ptr<HuffmanNode> lChild, std::shared_ptr<HuffmanNode> rChild) : letter(l), frequency(f), leftChild(lChild), rightChild(rChild){
        
    }
    
    int HuffmanNode::getFrequency() const{
        return frequency;
    }
    
    char HuffmanNode::getChar() const{
        return letter;
    }
    
    std::shared_ptr<HuffmanNode> HuffmanNode::getLeft(){
        return HuffmanNode::leftChild;
    }
    
    std::shared_ptr<HuffmanNode> HuffmanNode::getRight(){
        return HuffmanNode::rightChild;
    }
    
    HuffmanNode::~HuffmanNode(){
        
    }
    
    
    //CompareQueue class
    CompareQueue::CompareQueue(){
        
    }
    
    bool CompareQueue::operator()(const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) const{
            if (a.get()->getFrequency() > b.get()->getFrequency()){
                return true;
            }
            else if (a.get()->getFrequency() == b.get()->getFrequency()){
                if (a.get()->getChar() > b.get()->getChar()){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
    }
    
    
  // HuffmanTree class
    
    HuffmanTree::HuffmanTree(){
        
    }
    
    
    void HuffmanTree::fileReader(std::string fileName){
        std::ifstream fileStream(fileName.c_str(), std::ios::in);
        char nextCharacter;
        if (!fileStream){
            std::cerr << "File open failed!" << std::endl;
        }
        while (!fileStream.eof()){
            fileStream.get(nextCharacter);
            if (characterMap.empty()){
                characterMap[nextCharacter] = 1;
            }
            else if (characterMap.count(nextCharacter) == 0){
                characterMap[nextCharacter] = 1;
            }
            else if (characterMap.count(nextCharacter) == 1){
                characterMap[nextCharacter] = characterMap[nextCharacter] + 1;
            }
        }
        if (characterMap.count('\n') == 1){
            characterMap['\n'] = characterMap['\n'] - 2;
        }
        
        fileStream.close();
    }
    
    
    void HuffmanTree::createQueue(){
        for (std::unordered_map<char, int>::iterator i = characterMap.begin(); i != characterMap.end(); i++){
            std::shared_ptr<HuffmanNode> node(new HuffmanNode(i -> first, i -> second, nullptr, nullptr));
            treeQueue.push(node);
        }
        
    }
    
    
    void HuffmanTree::insertNodes(){
        if (!treeQueue.empty()){
            while (treeQueue.size() > 1){
                std::shared_ptr<HuffmanNode> left(treeQueue.top());
                treeQueue.pop();
                std::shared_ptr<HuffmanNode> right(treeQueue.top());
                treeQueue.pop();
                
                int frequency = left.get() -> getFrequency() + right.get() -> getFrequency();
                std::shared_ptr<HuffmanNode> node(new HuffmanNode(0, frequency, left, right));
                treeQueue.push(node);
                //std::cout << node.get() -> getChar() << ":" << node.get() ->getFrequency() << std::endl; 
            }
            if (treeQueue.size() == 1){
                root = treeQueue.top();
                //std::cout << root.get() -> getChar() << ":" << root.get() ->getFrequency() << std::endl;
            }
        }
    }
    
    
    void HuffmanTree::traverseTree(std::shared_ptr<HuffmanNode> node, int left, std::string code){
        if (node == nullptr){
            //code = "";
            return;
        }
        if (left == 0){
            code = code +"0";
        }
        else if (left == 1){
            code = code + "1";
        }
        traverseTree(node.get() -> getLeft(), 0, code);
        if (node.get() -> getChar() != 0){
            codeTable[node.get() -> getChar()] = code;
        }
        
        traverseTree(node -> getRight(), 1, code);
    }
    
    
    void HuffmanTree::createCodeTable(){
        std::string code = "";
        int left = 2;
        traverseTree(root, 2, code);
        
        for (std::unordered_map<char, std::string>::iterator i = codeTable.begin(); i != codeTable.end(); i++){
            std::cout << i->first << ":" <<i->second << std::endl;
        }
    }
    
    
    void HuffmanTree::compressFile(std::string fileName, std::string outputFile){
        std::ifstream fileStream(fileName.c_str(), std::ios::in);
        std::string textFile;
        std::string stringCode = "";
        if (!fileStream){
            std::cerr << "File open failed!" << std::endl;
        }
        std::ostringstream oss;
        oss << fileStream.rdbuf();
        textFile = oss.str();
        
        fileStream.close();
        
        textFile.erase(textFile.length() -1);
        
        for (int i=0; i<textFile.length(); i++){
            stringCode += codeTable[textFile[i]];
        }
        
        std::string headerFile = outputFile + ".hdr";
        std::ofstream writeHeader(headerFile.c_str(), std::ios::out);
        writeHeader << codeTable.size() << std::endl;
        for (std::unordered_map<char, std::string>::iterator i = codeTable.begin(); i != codeTable.end(); i++){
            writeHeader << i->first << ":" << i->second << std::endl;
        }
        writeHeader.close();
        
        std::ofstream writeBlock(outputFile.c_str());
        writeBlock << stringCode.c_str();
        writeBlock.close();
    }
    
    
    HuffmanTree::~HuffmanTree(){
        root = nullptr;
    }
}
