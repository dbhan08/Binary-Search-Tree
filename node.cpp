#include "node.h"
#include <iostream>

using namespace std;

node::node(int newValue) {
value = newValue;
left = NULL;
right = NULL;

}

void node::setLeft(node* newLeft) {
left = newLeft;

}

void node::setRight(node* newRight) {
right = newRight;

}

node* node::getLeft() {
return left;
}

node* node::getRight() {
return right;
}
