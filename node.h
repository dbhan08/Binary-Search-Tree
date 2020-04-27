/*
 Following is the header file for the node class
 By :Deyvik Bhan
 3/09/20
 */


#ifndef node_h
#define node_h
#include <iostream>
#include <cstring>

using namespace std;

class node {
    // Below are the functions which will be defined in the cpp file
public:
node(int value);
~node();
node* getLeft();
node* getRight();
void setValue(int value);
int*  getValue();
void setLeft(node*);
void setRight(node*);


private:
    // All the essential variables
node* left;
node* right;
int value;


};






#endif
