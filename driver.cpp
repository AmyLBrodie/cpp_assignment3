
/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3022H Tutorial 3
 * Created on 29 March 2016, 8:13 PM
 */

#include <cstdlib>
#include <string>
#include "Huffman.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    string inputFile;
    string outputFile;
    
    for (int i=0; i<argc; i++){
        if (i == 1){
            inputFile = string(argv[i]);
        }
        else if (i==2){
            outputFile = string(argv[i]);
        }
    }
    
    BRDAMY004::HuffmanTree tree;
    tree.fileReader(inputFile);
    tree.createQueue();
    tree.insertNodes();
    tree.createCodeTable();
    tree.compressFile(inputFile, outputFile);
    
    return 0;
}

