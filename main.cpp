#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
#include <string>
#include "BTree.h"
#include <cmath>
using namespace std;

int main(int argc, char * argv[]){
    ArgumentManager am(argc,argv);
    const string inputFileName = am.get("input");
    const string commandFileName = am.get("command");
    const string outputFileName = am.get("output");
    ifstream inputReader;
    ifstream commandReader;
    ofstream outputWriter;
    inputReader.open(inputFileName);
    commandReader.open(commandFileName);
    outputWriter.open(outputFileName);
    BTree* bTreePtr = nullptr;
    int height = 0;
    if(commandReader){
        string command = "";
        while(getline(commandReader, command)){
            if(command.find("Degree") != string::npos){
                //cout << "Command:" << command << endl;
                int equalSignIndex = command.find('=');
                string stringOrder = command.substr(equalSignIndex + 1);
                //cout << "Order in string:" << stringOrder << "." << endl;
                int order = stoi(stringOrder);
                //cout << "Order in int:" << order << endl;
                bTreePtr = new BTree(order);
                if(inputReader){
                    string stringInput = "";
                    int input = 0;
                    while(inputReader >> stringInput){
                        input = stoi(stringInput);
                        bTreePtr->insert(input);
                    }
                    height = bTreePtr->Height();
                }
            }
            else if(command.find("Inorder") != string::npos){
                //cout << "Command:" << command << endl;
                bTreePtr->printInorder(outputWriter);
                outputWriter << endl;
            }
            else if(command.find("Level") != string::npos){
                //cout << "Command:" << command << endl;
                int spaceSignIndex = command.find(' ');
                string stringLevel = command.substr(spaceSignIndex + 1);
                //cout << "Level in string:" << stringLevel <<  "." << endl;
                int level = stoi(stringLevel);
                //cout << "Level in int:" << level << endl;
                if(level >= 1 && level <= height){
                    bTreePtr->printDegree(level,outputWriter);
                    outputWriter << endl;
                }
                else outputWriter << "empty\n";

            }
            command = "";
        }
    }
    return 0;
}
