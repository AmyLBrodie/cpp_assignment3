
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

namespace BRDAMY004{
    
    
    // FileReader class
    FileReader::FileReader(std::string fileName){
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
        std::cout << characterMap['a'] << std::endl;
        std::cout << characterMap['v'] << std::endl;
        std::cout << characterMap[' '] << std::endl;
        std::cout << characterMap['\n'] << std::endl;  
        std::cout << characterMap['\t'] << std::endl;
    }
    
    
    // HuffmanNode class
    HuffmanNode::HuffmanNode(char l, int f) : letter(l), frequency(l){
        
    }
    
    int HuffmanNode::getFrequency() const{
        return frequency;
    }
    
    HuffmanNode::~HuffmanNode(){
        
    }
    
    
    //CompareQueue class
    CompareQueue::CompareQueue(){
        
    }
    
    bool CompareQueue::operator()(const HuffmanNode& a, const HuffmanNode& b) const{
            if (a.getFrequency() < b.getFrequency()){
                return true;
            }
            else{
                return false;
            }
    }
    
    
    // HuffmanTree class
    HuffmanTree::HuffmanTree(){
        
    }
    
    void HuffmanTree::insertNode(char letter, int frequency){
       
    }
    
    HuffmanTree::~HuffmanTree(){
        
    }
}
