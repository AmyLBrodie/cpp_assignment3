#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Huffman.h"
#include <string>
#include <memory>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

TEST_CASE("Creation of HuffmanNodes"){
    BRDAMY004::HuffmanNode node = BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr);
    REQUIRE(node.getChar() == 'a');
    REQUIRE(node.getFrequency() == 4);
    REQUIRE(node.getLeft() == nullptr);
    REQUIRE(node.getRight() == nullptr);
    
    std::shared_ptr<BRDAMY004::HuffmanNode> left(new BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr));
    std::shared_ptr<BRDAMY004::HuffmanNode> right(new BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr));
    BRDAMY004::HuffmanNode node1 = BRDAMY004::HuffmanNode('1', 10, left, right);
    REQUIRE(node1.getChar() == '1');
    REQUIRE(node1.getFrequency() == 10);
    REQUIRE(node1.getLeft().get() -> getChar() == node.getChar());
    REQUIRE(node1.getLeft().get() -> getFrequency() == node.getFrequency());
    REQUIRE(node1.getRight().get() -> getChar() == node.getChar());
    REQUIRE(node1.getRight().get() -> getFrequency() == node.getFrequency());
    
    BRDAMY004::HuffmanNode node2 = BRDAMY004::HuffmanNode(0, 5, nullptr, nullptr);
    REQUIRE(node2.getChar() == 0);
    REQUIRE(node2.getFrequency() == 5);
    REQUIRE(node2.getLeft() == nullptr);
    REQUIRE(node2.getRight() == nullptr);
}


TEST_CASE("Copy Construction of HuffmanNode"){
    BRDAMY004::HuffmanNode node = BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr);
    BRDAMY004::HuffmanNode newNode(node);
    REQUIRE(newNode.getChar() == node.getChar());
    REQUIRE(newNode.getFrequency() == node.getFrequency());
    REQUIRE(newNode.getLeft() == nullptr);
    REQUIRE(newNode.getRight() == nullptr);
    
    std::shared_ptr<BRDAMY004::HuffmanNode> left(new BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr));
    std::shared_ptr<BRDAMY004::HuffmanNode> right(new BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr));
    BRDAMY004::HuffmanNode node1 = BRDAMY004::HuffmanNode('1', 10, left, right);
    BRDAMY004::HuffmanNode newNode1(node1);
    REQUIRE(newNode1.getChar() == node1.getChar());
    REQUIRE(newNode1.getFrequency() == node1.getFrequency());
    REQUIRE(newNode1.getLeft() -> getChar() == node1.getLeft() -> getChar());
    REQUIRE(newNode1.getLeft() -> getFrequency() == node1.getLeft() -> getFrequency());
    REQUIRE(newNode1.getRight() -> getChar() == node1.getRight() -> getChar());
    REQUIRE(newNode1.getRight() -> getFrequency() == node1.getRight() -> getFrequency());
}


TEST_CASE("Move Construction of HuffmanNode"){
    BRDAMY004::HuffmanNode node = BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr);
    BRDAMY004::HuffmanNode newNode = std::move(node);
    REQUIRE(newNode.getChar() == 'a');
    REQUIRE(newNode.getChar() != node.getChar());
    REQUIRE(newNode.getFrequency() == 4);
    REQUIRE(newNode.getFrequency() != node.getFrequency());
    REQUIRE(newNode.getLeft() == nullptr);
    REQUIRE(newNode.getRight() == nullptr);
    
    std::shared_ptr<BRDAMY004::HuffmanNode> left(new BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr));
    std::shared_ptr<BRDAMY004::HuffmanNode> right(new BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr));
    BRDAMY004::HuffmanNode node1 = BRDAMY004::HuffmanNode('1', 10, left, right);
    BRDAMY004::HuffmanNode newNode1 = std::move(node1);
    REQUIRE(newNode1.getChar() == '1');
    REQUIRE(newNode1.getChar() != node1.getChar());
    REQUIRE(newNode1.getFrequency() == 10);
    REQUIRE(newNode1.getFrequency() != node.getFrequency());
    REQUIRE(newNode1.getLeft().get() -> getChar() == 'a');
    REQUIRE(node1.getLeft() == nullptr);
    REQUIRE(newNode1.getLeft().get() -> getFrequency() == 4);
    REQUIRE(newNode1.getRight().get() -> getChar() == 'a');
    REQUIRE(node1.getRight() == nullptr);
    REQUIRE(newNode1.getRight().get() -> getFrequency() == 4);
}


TEST_CASE("Move Assignment Operator of HuffmanNode"){
    BRDAMY004::HuffmanNode node = BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr);
    std::shared_ptr<BRDAMY004::HuffmanNode> left(new BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr));
    std::shared_ptr<BRDAMY004::HuffmanNode> right(new BRDAMY004::HuffmanNode('b', 5, nullptr, nullptr));
    BRDAMY004::HuffmanNode node1 = BRDAMY004::HuffmanNode('1', 10, left, right);
    node = std::move(node1);
    REQUIRE(node.getChar() == '1');
    REQUIRE(node.getFrequency() == 10);
    REQUIRE(node.getLeft().get() -> getChar() == 'a');
    REQUIRE(node.getLeft().get() -> getFrequency() == 4);
    REQUIRE(node.getLeft().get() -> getLeft() == nullptr);
    REQUIRE(node.getLeft().get() -> getRight() == nullptr);
    REQUIRE(node.getRight().get() -> getChar() == 'b');
    REQUIRE(node.getRight().get() -> getFrequency() == 5);
    REQUIRE(node.getRight().get() -> getLeft() == nullptr);
    REQUIRE(node.getRight().get() -> getRight() == nullptr);
    
    REQUIRE(node1.getChar() == 0);
    REQUIRE(node1.getFrequency() == 0);
    REQUIRE(node1.getLeft() == nullptr);
    REQUIRE(node1.getRight() == nullptr);
}


TEST_CASE("Copy Assignment Operator of HuffmanNode"){
    BRDAMY004::HuffmanNode node = BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr);
    std::shared_ptr<BRDAMY004::HuffmanNode> left(new BRDAMY004::HuffmanNode('a', 4, nullptr, nullptr));
    std::shared_ptr<BRDAMY004::HuffmanNode> right(new BRDAMY004::HuffmanNode('b', 5, nullptr, nullptr));
    BRDAMY004::HuffmanNode node1 = BRDAMY004::HuffmanNode('1', 10, left, right);
    node = node1;
    REQUIRE(node.getChar() == '1');
    REQUIRE(node.getFrequency() == 10);
    REQUIRE(node.getLeft().get() -> getChar() == 'a');
    REQUIRE(node.getLeft().get() -> getFrequency() == 4);
    REQUIRE(node.getLeft().get() -> getLeft() == nullptr);
    REQUIRE(node.getLeft().get() -> getRight() == nullptr);
    REQUIRE(node.getRight().get() -> getChar() == 'b');
    REQUIRE(node.getRight().get() -> getFrequency() == 5);
    REQUIRE(node.getRight().get() -> getLeft() == nullptr);
    REQUIRE(node.getRight().get() -> getRight() == nullptr);
    
    REQUIRE(node.getChar() == node1.getChar());
    REQUIRE(node.getFrequency() == node1.getFrequency());
    REQUIRE(node.getLeft().get() -> getChar() == node1.getLeft().get() -> getChar());
    REQUIRE(node.getLeft().get() -> getFrequency() == node1.getLeft().get() -> getFrequency());
    REQUIRE(node.getLeft().get() -> getLeft() == node1.getLeft().get() -> getLeft());
    REQUIRE(node.getLeft().get() -> getRight() == node1.getLeft().get() -> getRight());
    REQUIRE(node.getRight().get() -> getChar() == node1.getRight().get() -> getChar());
    REQUIRE(node.getRight().get() -> getFrequency() == node1.getRight().get() -> getFrequency());
    REQUIRE(node.getRight().get() -> getLeft() == node1.getRight().get() -> getLeft());
    REQUIRE(node.getRight().get() -> getRight() == node1.getRight().get() -> getRight());
}


TEST_CASE("Construction of HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    REQUIRE(tree.getCharacterMap().size() == 0);
    REQUIRE(tree.getCodeTable().size() == 0);
    REQUIRE(tree.getRoot() == nullptr);
    REQUIRE(tree.getQueue().size() == 0);
}


TEST_CASE("Copy Construction of HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    tree.fileReader("test.txt");
    tree.createQueue();
    tree.insertNodes();
    tree.createCodeTable();
    tree.compressFile("test.txt", "testOutput");
    BRDAMY004::HuffmanTree tree2(tree);
    
    REQUIRE(tree2.getCharacterMap()['a'] == tree.getCharacterMap()['a']);
    REQUIRE(tree2.getCharacterMap()['/'] == tree.getCharacterMap()['/']);
    REQUIRE(tree2.getRoot().get() -> getChar() == tree.getRoot().get() -> getChar());
    REQUIRE(tree2.getRoot().get() -> getFrequency() == tree.getRoot().get() -> getFrequency());
    REQUIRE(tree2.getCodeTable()['a'] == tree.getCodeTable()['a']);
    REQUIRE(tree2.getQueue().top().get() -> getChar() == tree.getQueue().top().get() -> getChar());
    tree2.getQueue().pop();
    tree.getQueue().pop();
    REQUIRE(tree2.getQueue().top().get() -> getChar() == tree.getQueue().top().get() -> getChar());
    tree2.getQueue().pop();
    tree.getQueue().pop();
    REQUIRE(tree2.getQueue().top().get() -> getChar() == tree.getQueue().top().get() -> getChar());
    tree2.getQueue().pop();
    tree.getQueue().pop();
    REQUIRE(tree2.getQueue().top().get() -> getChar() == tree.getQueue().top().get() -> getChar());
}


TEST_CASE("Move Construction of HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    tree.fileReader("test.txt");
    tree.createQueue();
    tree.insertNodes();
    tree.createCodeTable();
    tree.compressFile("test.txt", "testOutput");
    std::unordered_map<char, int> characterMap = tree.getCharacterMap();
    std::unordered_map<char, std::string> codeTable = tree.getCodeTable();
    std::shared_ptr<BRDAMY004::HuffmanNode> root = tree.getRoot();
    std::priority_queue<std::shared_ptr<BRDAMY004::HuffmanNode>, std::vector<std::shared_ptr<BRDAMY004::HuffmanNode>>, BRDAMY004::CompareQueue> treeQueue = tree.getQueue();
    
    BRDAMY004::HuffmanTree tree2;
    tree2= std::move(tree);
    REQUIRE(tree2.getCharacterMap()['a'] == characterMap['a']);
    REQUIRE(tree2.getCharacterMap()['/'] == characterMap['/']);
    REQUIRE(tree2.getRoot().get() -> getChar() == root.get() -> getChar());
    REQUIRE(tree2.getRoot().get() -> getFrequency() == root.get() -> getFrequency());
    REQUIRE(tree2.getCodeTable()[' '] == codeTable[' ']);
    REQUIRE(tree2.getQueue().top().get() -> getChar() == treeQueue.top().get() -> getChar());
    tree2.getQueue().pop();
    treeQueue.pop();
    REQUIRE(tree2.getQueue().top().get() -> getChar() == treeQueue.top().get() -> getChar());
    REQUIRE(tree.getCharacterMap().size() == 0);
    REQUIRE(tree.getCodeTable().size() == 0);
    REQUIRE(tree.getQueue().size() == 0);
    REQUIRE(tree.getRoot() == nullptr);
}


TEST_CASE("Copy Assignment Operator of HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    tree.fileReader("test.txt");
    tree.createQueue();
    tree.insertNodes();
    tree.createCodeTable();
    tree.compressFile("test.txt", "testOutput");
    BRDAMY004::HuffmanTree tree2;
    tree2.fileReader("test1.txt");
    tree2.createQueue();
    tree2.insertNodes();
    tree2.createCodeTable();
    tree2.compressFile("test1.txt", "test1Output");
    
    tree = tree2;
    
    REQUIRE(tree2.getCharacterMap()['a'] == tree.getCharacterMap()['a']);
    REQUIRE(tree2.getCharacterMap()['/'] == tree.getCharacterMap()['/']);
    REQUIRE(tree2.getRoot().get() -> getChar() == tree.getRoot().get() -> getChar());
    REQUIRE(tree2.getRoot().get() -> getFrequency() == tree.getRoot().get() -> getFrequency());
    REQUIRE(tree2.getCodeTable()['a'] == tree.getCodeTable()['a']);
    REQUIRE(tree2.getQueue().top().get() -> getChar() == tree.getQueue().top().get() -> getChar());
    tree2.getQueue().pop();
    tree.getQueue().pop();
    REQUIRE(tree2.getQueue().top().get() -> getChar() == tree.getQueue().top().get() -> getChar());
    tree2.getQueue().pop();
    tree.getQueue().pop();
    REQUIRE(tree2.getQueue().top().get() -> getChar() == tree.getQueue().top().get() -> getChar());
    tree2.getQueue().pop();
    tree.getQueue().pop();
    REQUIRE(tree2.getQueue().top().get() -> getChar() == tree.getQueue().top().get() -> getChar());
}


TEST_CASE("Move Assignment Operator of HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    tree.fileReader("test.txt");
    tree.createQueue();
    tree.insertNodes();
    tree.createCodeTable();
    tree.compressFile("test.txt", "testOutput");
    BRDAMY004::HuffmanTree tree2;
    tree2.fileReader("test1.txt");
    tree2.createQueue();
    tree2.insertNodes();
    tree2.createCodeTable();
    tree2.compressFile("test1.txt", "test1Output");
    
    std::unordered_map<char, int> characterMap = tree2.getCharacterMap();
    std::unordered_map<char, std::string> codeTable = tree2.getCodeTable();
    std::shared_ptr<BRDAMY004::HuffmanNode> root = tree2.getRoot();
    std::priority_queue<std::shared_ptr<BRDAMY004::HuffmanNode>, std::vector<std::shared_ptr<BRDAMY004::HuffmanNode>>, BRDAMY004::CompareQueue> treeQueue = tree2.getQueue();
    
    tree = std::move(tree2);
    
    REQUIRE(tree.getCharacterMap()['a'] == characterMap['a']);
    REQUIRE(tree.getCharacterMap()['/'] == characterMap['/']);
    REQUIRE(tree.getRoot().get() -> getChar() == root.get() -> getChar());
    REQUIRE(tree.getRoot().get() -> getFrequency() == root.get() -> getFrequency());
    REQUIRE(tree.getCodeTable()[' '] == codeTable[' ']);
    REQUIRE(tree.getQueue().top().get() -> getChar() == treeQueue.top().get() -> getChar());
    tree.getQueue().pop();
    treeQueue.pop();
    REQUIRE(tree.getQueue().top().get() -> getChar() == treeQueue.top().get() -> getChar());
    REQUIRE(tree2.getCharacterMap().size() == 0);
    REQUIRE(tree2.getCodeTable().size() == 0);
    REQUIRE(tree2.getQueue().size() == 0);
    REQUIRE(tree2.getRoot() == nullptr);
}


TEST_CASE("Creating characterMap for HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    tree.fileReader("test.txt");
    std::unordered_map<char, int> characterMap = tree.getCharacterMap();
    REQUIRE(characterMap['a'] == 5);
    REQUIRE(characterMap[' '] == 5);
    REQUIRE(characterMap['v'] == 3);
    REQUIRE(characterMap['/'] == 2);
    REQUIRE(characterMap['\n'] == 2);
    REQUIRE(characterMap['\t'] == 3);
}


TEST_CASE("Creating priority queue for HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    tree.fileReader("test.txt");
    tree.createQueue();
    
    std::priority_queue<std::shared_ptr<BRDAMY004::HuffmanNode>, std::vector<std::shared_ptr<BRDAMY004::HuffmanNode>>, BRDAMY004::CompareQueue> treeQueue;
    treeQueue = tree.getQueue();
    
    REQUIRE(treeQueue.top().get() -> getChar() == '\n');
    treeQueue.pop();
    REQUIRE(treeQueue.top().get() -> getChar() == '/');
    treeQueue.pop();
    REQUIRE(treeQueue.top().get() -> getChar() == '\t');
    treeQueue.pop();
    REQUIRE(treeQueue.top().get() -> getChar() == 'v');
    treeQueue.pop();
    REQUIRE(treeQueue.top().get() -> getChar() == ' ');
    treeQueue.pop();
    REQUIRE(treeQueue.top().get() -> getChar() == 'a');
    treeQueue.pop();
    REQUIRE(treeQueue.size() == 0);
}


TEST_CASE("Inserting nodes into HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    tree.fileReader("test.txt");
    tree.createQueue();
    tree.insertNodes();
    std::shared_ptr<BRDAMY004::HuffmanNode> root = tree.getRoot();
    std::shared_ptr<BRDAMY004::HuffmanNode> next;
    next = root.get() -> getLeft();
    next = next.get() -> getLeft();
    next = next.get() -> getLeft();
    
    REQUIRE(root.get() -> getChar() == 0);
    REQUIRE(next.get() -> getChar() == '\n');
    
    next = root.get() -> getRight();
    next = next.get() -> getRight();
    next = next.get() -> getRight();
    REQUIRE(next.get() -> getChar() == 'v');
    
    next = root.get() -> getLeft();
    next = next.get() -> getLeft();
    next = next.get() -> getRight();
    REQUIRE(next.get()-> getChar() == '/');
    
    next = root.get() -> getRight();
    next = next.get() -> getRight();
    next = next.get() -> getLeft();
    REQUIRE(next.get() -> getChar() == '\t');
    
    next = root.get() -> getLeft();
    next = next.get() -> getRight();
    REQUIRE(next.get() -> getChar() == ' ');
    
    next = root.get() -> getRight();
    next = next.get() -> getLeft();
    REQUIRE(next.get() -> getChar() == 'a');
}


TEST_CASE("Creating code table for HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    tree.fileReader("test.txt");
    tree.createQueue();
    tree.insertNodes();
    tree.createCodeTable();
    std::unordered_map<char, std::string> codeTable = tree.getCodeTable();
    
    REQUIRE(codeTable['a'] == "10");
    REQUIRE(codeTable[' '] == "01");
    REQUIRE(codeTable['\t'] == "110");
    REQUIRE(codeTable['\n'] == "000");
    REQUIRE(codeTable['v'] == "111");
    REQUIRE(codeTable['/'] == "001");
}


TEST_CASE("Compressing characters from HuffmanTree"){
    BRDAMY004::HuffmanTree tree;
    tree.fileReader("test.txt");
    tree.createQueue();
    tree.insertNodes();
    tree.createCodeTable();
    tree.compressFile("test.txt", "testOutput");
    std::string stringCode = tree.getStringCode();
    
    REQUIRE(stringCode == "10101001010111101101001001001000111111000110110110");
}
