#include "node.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;



// Following parse function from Stefan Ene https://github.com/Stefanene/Heap/blob/master/main.cpp
void parse(char* in, int* modif, int &count) {
    int l = 0;  //keeps track of # of chars before space
    for (int i = 0; i < strlen(in); i++) {
        if (in[i] == ' ') {
            if (l == 1) {
                int temp = 0;
                temp = in[i-1] - '0';
                modif[count] = temp;
                count++;
                l = 0;
            } else {
                int temp = 0;
                for (int a = 0; a < l; a++) {
                    temp = 10 * temp + (in[i-l+a] - '0');
                }
                modif[count] = temp;
                count++;
                l = 0;
            }
        } else {
            int temp = 0;
            l++;
            if (i == strlen(in) - 1) {  //last possible pair of chars
                for (int a = 0; a < l; a++) {
                    temp = 10 * temp + (in[i+a+1-l] - '0');
                }
                modif[count] = temp;
                count++;
            }
        }
    }
}




void insert(node* &root, int value) {
    
    if(root == NULL) {
        root = new node(value);
    } else if(value == root->getValue()) {
        return;
        
    } else if(value < root->getValue()) {
        insert(root->getLeft(),value)
        
    } else {
        insert(root->getRight(),value);
        
        
        
    }
    
    
    
    
}

bool search(node* root, int value) {
    
    if(value == root->getValue()) {
        return true;
    } else if(value < root->getValue()) {
        search(root->getLeft(), value);
    } else if(value > root->getValue()) {
        search(root->getRight(), value);
    }
    return false;
    
}


void delete() {
    
}





// Majority of my main function taken from heap project. Also includes code from Omar and the calling of a function provided by Stefan Ene's heap
int main() {
    
    
    // Just the input stuff
    
    int count = 0;
    int modif[100];
    char fileName[30];
    
    for (int i = 0; i < 100; i++) {
        modif[i] = 0;
    }
    
    cout << "If you would like to input manually type '1' if you would like to do it from a file type '2':" << endl;
    char inp[10];
    char input[100000];
    cin.get(inp,10);
    cin.clear();
    cin.ignore(1000000,'\n');
    if(strcmp(inp,"1")== 0) {
        cout << "Enter a set of numbers sperated by spaces:" << endl;
        char in[100000];
        cin.get(in, 100000);
        cin.clear();
        cin.ignore(1000000, '\n');
        parse(in,modif,count);
        int size = sizeof(modif)/sizeof(modif[0]);
        
       
        
    } else if(strcmp(inp,"2")== 0) {
        
        // Following chunk from Omar Nassar
        cout << endl << "What is the name of the file?" << endl << ">> ";
        cin.get(fileName, 30);
        cin.clear();
        cin.ignore(100000, '\n');
        streampos size;
        ifstream file(fileName, ios::in | ios::binary | ios::ate);
        if (file.is_open()) {
            size = file.tellg();
            file.seekg(0, ios::beg);
            file.read(input, size);
            file.close();
            parse(input,modif,count);
            
            
            int size = sizeof(modif)/sizeof(modif[0]);
            
            
        }
        
        
    } else {
        cout << "Enter a valid option!" << endl;
    }
    
    
    
    
    
    
    
    
    return 0;
}
