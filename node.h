#ifndef node_h
#define node_h
#include <iostream>
#include <cstring>

using namespace std;

class node {
public:
node(int value);
~node();
node* getLeft();
node* getRight();
void setValue(int value);
int  getValue();
void setLeft(node*);
void setRight(node*);

private:
node* left;
node* right;
int value;

};






#endif
