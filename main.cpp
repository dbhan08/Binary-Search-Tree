/*
 Following program is a binary search tree in which a user can input numbers into the tree, delete them, and search for  them
 By :Deyvik Bhan
 3/09/20
 */


#include "node.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include<cstdlib>
#include <iomanip>

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



// Following function inserts into the tree
void insert(node* &root,node* head ,int value) {
   // If tree is empty
    if(root == NULL) {
        // Make it a new node
        root = new node(value);
    } else if(value == *head->getValue()) {
        // If value is already in tree no need for another node
        return;
        
    } else if(value < *head->getValue()) {
        // If new value is less then the current nodes value
        
        if(head->getLeft() == NULL) {
            // If the left is not null, make a new node with the given value
            head->setLeft(new node(value));
            
        } else {
            // Transverse to the less
        insert(root, head->getLeft(),value);
        }
    } else {
        //If given value is greater then current nodes value
        if(head->getRight() == NULL) {
            // If the right node is null make new node of the given value
            head->setRight(new node(value));
            
        } else {
            // Transverse to the right
        insert(root,head->getRight(),value);
        }
        
        
    }
    
    
    
    
}
// Ali helped me with this particular block of code
void visualize(node* head, int depth=0)
{
    if(head != NULL ) {
    if(head->getRight() != NULL) {
        //   cout << "a" << endl;
      //  cout << head->getRight() << endl;
         visualize(head->getRight(), depth+1);
     
    }
   // cout << "d" << endl;
    int temp = depth;

    while(depth > 0) {
        cout << "  ";
        depth --;
    }
    if(head != NULL) {
      
    cout << *head->getValue() << endl;
   //    cout << "b" << endl;
   
    }
   
    if(head->getLeft() != NULL) {
// cout << "c" << endl;
       visualize(head->getLeft(), temp+1);
       

    }
    }
    
   // cout << "kms" << endl;
}



// Following function searches the tree and wfinds the value
node* search(node* root, int value) {
   
    if(root != NULL) {
        // If the tree is not empty
    if(value == *root->getValue()) {
        // If the current node has the same value as the value being searched for return the current node(node found)
       // cout << root->getValue() << "a" << endl;
        return root;
    
        
        
       
    } else if(value < *root->getValue()) {
        // If value being searched for is less then the current nodes value
       
        if(root->getLeft() != NULL) {
            // If there is a left node transverse to that node and check if it is equal
    
        return search(root->getLeft(), value);
        } else {
            // There is no node that matches the value
        
            return NULL;
                    }
    } else if(value > *root->getValue() ) {
        // If the value being searched for is greater then the current nodes value
        
        
        if(root->getRight() != NULL) {
           // If there is a right node transverse to that node and call the function
       //      cout << root->getRight()->getValue() << "c" << endl;
        return search(root->getRight(), value);
            
        } else {
         // There is no node that matches the values
          //  cout << "k" << endl;
            return NULL;
        }
    } else {
       
        return NULL;
    }
    } else {
        return NULL;
    }

 
}
// Following function is used to find the parent, which is used in the delte function. Functions basically the exact same as the search functin
node* findAbove(node* root, node* find) {
    
    if(find != NULL && root != NULL) {
    if(root->getLeft() == find || root->getRight() == find) {
        return root;
    } else if(*root->getValue() > *find->getValue()) {
        if(root->getLeft()) {
            return findAbove(root->getLeft(),find);
        } else {
            return NULL;
        }
        
        
    } else if(*root->getValue() < *find->getValue()) {
        if(root->getRight()) {
            return findAbove(root->getRight(),find);
        } else {
            return NULL;
        }
        
    } else {
        return NULL;
    }
    
    } else {
        return NULL;
    }
    
}







        
        
void remove(node* &root, int value) {
    // If the value to be deleted is the root
    if(value == *root->getValue()) {
        // If the only node is the root set the root to null
        if(root->getLeft() == NULL && root->getRight() == NULL) {
            root->setValue(0);
        } else if(root->getLeft() != NULL && root->getRight() == NULL) {
            // If the left is the only child, make the left child the root
            node* temp = root->getLeft();
            root->setValue(*(temp->getValue()));
            root->setRight(temp->getRight());
            root->setLeft(temp->getLeft());
        free(temp);
        } else if(root->getLeft() == NULL && root->getRight() != NULL) {
            // If the only child is the right make it the root
            node* temp = root->getRight();
            root->setValue(*(temp->getValue()));
            root->setRight(temp->getRight());
            root->setLeft(temp->getLeft());
           free(temp);
            
        } else {
            // If there are two childs find the next closest value, can be done in two ways. Either the value is the closest number greater then the root or the closest number les then the root. In this code it will be the closest number less then the root.
            // Below code replaces the root with the cclosest value
            node* replace = root->getLeft();
            node* parRep = root;
            while(replace->getRight() != NULL) {
                parRep = replace;
                replace = replace->getRight();
            }
            if(parRep == root) {
                root->setLeft(replace->getLeft());
            } else {
                parRep->setRight(replace->getLeft());
            }
            root->setValue(*replace->getValue());
            free(replace);
            
            
        }
        
        return;
        
    }
// For values that are not the root
    node* parent = findAbove(root,search(root,value)); // The parent node for the value being found
    
    
    // Finds if the node to be deleted is from the left or right side of the parent node
    int side = 0;
    if(parent != NULL) {
        node* temp = NULL;
        if(parent->getLeft() == search(root,value)) {
            side = 1;
            temp = parent->getLeft();
            
        } else {
            temp = parent->getRight();
            
        }
        
        // If the node to be deleted has no children
        if(temp->getLeft() == NULL && temp->getRight() == NULL) {
            if(side == 1) {
                parent->setLeft(NULL);
            } else {
                parent->setRight(NULL);
              
            }
            free(temp);
            // If the node to be deleted has only a left node
        } else if(temp->getLeft() != NULL && temp->getRight() == NULL) {
            
            if(side == 1) {
                parent->setLeft(temp->getLeft());
            } else {
              

                parent->setRight(temp->getLeft());
               
            }
            
  
            
            free(temp);
           // cout << *parent->getRight()->getValue() << endl;
            // If thee is only a right child
        } else if(temp->getLeft() == NULL && temp->getRight() != NULL) {
            
            if(side == 1) {
                parent->setLeft(temp->getRight());
            } else {
                parent->setRight(temp->getRight());
                
            }
          free(temp);
            // Below is if there is two children of the node to be deleted
        } else {
            // This is excecuted similary to the code above form replacing the root if it has two children
            node* replace = temp->getLeft();
            node* parRep = temp;
            while(replace->getRight() != NULL) {
                parRep = replace;
                replace = replace->getRight();
            }
            
            if(parRep == temp) {
                parRep->setLeft(replace->getLeft());
            } else {
                parRep->setRight(replace->getLeft());
            }
            
            temp->setValue(*replace->getValue());
            free(replace);
            
        }
        
        
        
        
    } else {
        cout << "Value is not in tree!" << endl;
    }
    
    
    
}





// Majority of my main function taken from heap project. Also includes code from Omar and the calling of a function provided by Stefan Ene's heap
int main() {
    
    // The main function jsut takes care of basic input stuff
    // Just the input stuff
    node* root = new node(0);
    node* curr = new node(0);
    curr = NULL;
    root = NULL;
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
        
        for(int i = 0; modif[i] != 0; i++) {
            insert(root,root,modif[i]);
        }
        //cout << root->getValue() << endl;
        visualize(root,0);
       // int size = sizeof(modif)/sizeof(modif[0]);
        
       
        
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
            for(int i = 0; modif[i] != 0; i++) {
                insert(root,root,modif[i]);
            }
              visualize(root,0);
            //cout << root->ge
            
            
            
            // int size = sizeof(modif)/sizeof(modif[0]);
            
            
        }
        
        
    } else {
        cout << "Enter a valid option!" << endl;
    }
    
    
    bool running = true;
    while(running) {
        cout << "Would you like to 'insert', 'delete', 'search', or quit?" << endl;
        char inp[50];
    cin.get(inp,50);
    cin.clear();
    cin.ignore(50,'\n');
    if(strcmp(inp, "insert") == 0)  {
        cout << "What would you like to Insert" << endl;
        char inp[100];
        cin.get(inp,100);
        cin.clear();
        cin.ignore(100,'\n');
        int a = atoi(inp);
        insert(root,root,a);
        visualize(root,0);

        
        
        
    } else if(strcmp(inp, "search") == 0) {
        cout << "What would you like to search for" << endl;
        char inp[100];
        cin.get(inp,100);
        cin.clear();
        cin.ignore(100,'\n');
        int a = atoi(inp);
        
      //  cout << *root->getValue() << endl;
        
      //  cout << *search(root,a) ->getValue() << "l" << endl;
     //   cout << search(root,a) << "n" << endl;
      
        if( search(root,a) != NULL) {
          
            cout << "The number was found!" << endl;
        } else {
          //  cout << search(root,a) << endl;
            cout << "Number not in tree!" << endl;
        }
        
        //  cout << root->getValue()  << "z" << endl;
        
    } else if(strcmp(inp, "delete") == 0) {
        char inp[100];
        cin.get(inp,100);
        cin.clear();
        cin.ignore(100,'\n');
        int a = atoi(inp);
        remove(root,a);
       
        visualize(root,0);
        
        
    } else if(strcmp(inp, "quit") == 0) {
        running = false;
        
        
    } else {
        cout << "Enter a valid option" << endl;;
        
    }
    
    
        
        
    }
    
   
    
    
    
    
    
    
    return 0;
}
