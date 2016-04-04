
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
    

//HuffmanNode class
    
    //constructor
    HuffmanNode::HuffmanNode(char l, int f, std::shared_ptr<HuffmanNode> lChild, std::shared_ptr<HuffmanNode> rChild) : letter(l), frequency(f), leftChild(lChild), rightChild(rChild){
        
    }
    
    //copy constructor
    HuffmanNode::HuffmanNode(const HuffmanNode& rhs): letter(rhs.letter), frequency(rhs.frequency), leftChild(rhs.leftChild), rightChild(rhs.rightChild){
        
    }
    
    //move constructor
    HuffmanNode::HuffmanNode(HuffmanNode&& rhs): letter(rhs.letter), frequency(rhs.frequency), leftChild(std::move(rhs.leftChild)), rightChild(std::move(rhs.rightChild)){
        rhs.letter = 0;
        rhs.frequency = 0;
    }
    
    //copy assignment operator
    HuffmanNode & HuffmanNode::operator=(HuffmanNode& rhs){
        if (this != &rhs){
            letter = rhs.letter;
            frequency = rhs.frequency;
            leftChild = rhs.leftChild;
            rightChild = rhs.rightChild;
        }
    }
    
    //move assignment operator
    HuffmanNode & HuffmanNode::operator=(HuffmanNode&& rhs){
        if (this != &rhs){
            letter = rhs.letter;
            rhs.letter = 0;
            frequency = rhs.frequency;
            rhs.frequency = 0;
            leftChild = std::move(rhs.leftChild);
            rightChild = std::move(rhs.rightChild);
        }
        return *this;
    }
    
    //Returns frequency of given node
    int HuffmanNode::getFrequency() const{
        return frequency;
    }
    
    //Returns character associated with node
    char HuffmanNode::getChar() const{
        return letter;
    }
    
    //Returns left child of node
    std::shared_ptr<HuffmanNode> HuffmanNode::getLeft(){
        return HuffmanNode::leftChild;
    }
    
    //Returns right child of node
    std::shared_ptr<HuffmanNode> HuffmanNode::getRight(){
        return HuffmanNode::rightChild;
    }
    
    //Destructor
    HuffmanNode::~HuffmanNode(){
        rightChild = nullptr;
        leftChild = nullptr;
    }
    
    
//CompareQueue class
    
    //Construtor
    CompareQueue::CompareQueue(){
        
    }
    
    //Compares given nodes, smaller frequency first and if frequency is equal then it
    //checks for the character with the lower ascii value (except null char)
    bool CompareQueue::operator()(const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) const{
            if (a.get()->getFrequency() > b.get()->getFrequency()){
                return true;
            }
            else if (a.get()->getFrequency() == b.get()->getFrequency()){
                if (a.get()->getChar() > b.get()->getChar() && a.get()->getChar() != 0 && b.get()->getChar() != 0){
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
    
    
//HuffmanTree class
    
    //Constructor
    HuffmanTree::HuffmanTree(){
        
    }
    
    //copy constructor
    HuffmanTree::HuffmanTree(const HuffmanTree& rhs) : characterMap(rhs.characterMap), codeTable(rhs.codeTable), root(rhs.root), treeQueue(rhs.treeQueue){
        
    }
    
    //move constructor
    HuffmanTree::HuffmanTree(HuffmanTree&& rhs) : characterMap(std::move(rhs.characterMap)), codeTable(std::move(rhs.codeTable)), root(std::move(rhs.root)), treeQueue(std::move(rhs.treeQueue)){
        rhs.characterMap.clear();
    }
    
    //copy assignment operator
    HuffmanTree & HuffmanTree::operator =(HuffmanTree& rhs){
        if (this != &rhs){
            characterMap = rhs.characterMap;
            codeTable = rhs.codeTable;
            root = rhs.root;
            treeQueue = rhs.treeQueue;
        }
    }
    
    //move assignment operator
    HuffmanTree & HuffmanTree::operator =(HuffmanTree&& rhs){
        if (this != &rhs){
            characterMap = std::move(rhs.characterMap);
            rhs.characterMap.clear();
            codeTable = std::move(rhs.codeTable);
            root = std::move(rhs.root);
            treeQueue = std::move(rhs.treeQueue);
        }
        return *this;
    }
    
    //Takes in the name of the file and reads out of it character by character and stores
    //each charcater along with its frequency in an unordered map
    void HuffmanTree::fileReader(std::string fileName){
        std::ifstream fileStream(fileName.c_str(), std::ios::in);
        char nextCharacter;
        if (!fileStream){
            std::cerr << "File open failed!" << std::endl;
        }
        while (!fileStream.eof()){
            fileStream.get(nextCharacter);
            //unordered map is empty
            if (characterMap.empty()){
                characterMap[nextCharacter] = 1;
            }
            //character doesn't exist as key in unordered map
            else if (characterMap.count(nextCharacter) == 0){
                characterMap[nextCharacter] = 1;
            }
            //character exists as key (increment frequency)
            else if (characterMap.count(nextCharacter) == 1){
                characterMap[nextCharacter] = characterMap[nextCharacter] + 1;
            }
        }
        //Removes extra new line characters
        if (characterMap.count('\n') == 1){
            characterMap['\n'] = characterMap['\n'] - 2;
            if (characterMap['\n'] == 0){
                characterMap.erase(characterMap.find('\n'));
            }
        }
        fileStream.close();
    }
    
    //Iterates through unordered map of character frequencies and creates a priority queue
    //from it, lower frequencies are removed from queue first
    void HuffmanTree::createQueue(){
        for (std::unordered_map<char, int>::iterator i = characterMap.begin(); i != characterMap.end(); i++){
            std::shared_ptr<HuffmanNode> node(new HuffmanNode(i -> first, i -> second, nullptr, nullptr));
            treeQueue.push(node);
        }
        
    }
    
    //Loops while the size of the priority queue is greater than 1, adds queued 
    //nodes into tree and creates parent nodes by combining frequencies
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
            }
            if (treeQueue.size() == 1){
                root = treeQueue.top();
            }
        }
    }
    
    //Recursively traverses the tree in order, and creates the specific code for 
    //each character (made up of 0s and 1s)
    void HuffmanTree::traverseTree(std::shared_ptr<HuffmanNode> node, int left, std::string code){
        if (node == nullptr){
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
    
    //Calls the traverse tree method to create the code table
    void HuffmanTree::createCodeTable(){
        std::string code = "";
        int left = 2;
        traverseTree(root, 2, code);
    }
    
    //Computes the compression ratio for the textfile created with the compress method
    int HuffmanTree::computeBytes(std::string codeString){
        int nBits = codeString.length();
        return (nBits/8) + (nBits%8 ? 1 : 0);
    }
    
    //Creates the code string for the input file and writes this to the output file,
    //also writes a header file with the code table
    void HuffmanTree::compressFile(std::string fileName, std::string outputFile){
        std::ifstream fileStream(fileName.c_str(), std::ios::in);
        std::string textFile;
        stringCode = "";
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
        
        std::cout << "Packed file size: " << HuffmanTree::computeBytes(stringCode) << " bytes" << std::endl;
        
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
    
    //Returns the string code for the tree
    std::string HuffmanTree::getStringCode(){
        return stringCode;
    }
    
    //Returns the charater map for the tree
    std::unordered_map<char, int> HuffmanTree::getCharacterMap(){
        return characterMap;
    }
    
    //Returns the code table for the tree
    std::unordered_map<char, std::string> HuffmanTree::getCodeTable(){
        return codeTable;
    }
    
    //Returns the root of the tree
    std::shared_ptr<HuffmanNode> HuffmanTree::getRoot(){
        return root;
    }
    
    //Returns the priority queue of the tree
    std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, CompareQueue> HuffmanTree::getQueue(){
        return treeQueue;
    }
    
    //Destructor
    HuffmanTree::~HuffmanTree(){
        root = nullptr;
    }
}
