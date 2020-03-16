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




void insert(node* &root,node* head ,int value) {
   
    if(root == NULL) {
        root = new node(value);
    } else if(value == *head->getValue()) {
        return;
        
    } else if(value < *head->getValue()) {
        
        if(head->getLeft() == NULL) {
            head->setLeft(new node(value));
            
        } else {
        insert(root, head->getLeft(),value);
        }
    } else {
        
        if(head->getRight() == NULL) {
            head->setRight(new node(value));
            
        } else {
        insert(root,head->getRight(),value);
        }
        
        
    }
    
    
    
    
}
// Concept for visualize function from Ali Fakhry
void visualize(node* head, int depth=0)
{
    if(head->getRight())
        visualize(head->getRight(), depth+1);
    int temp = depth;
    while(depth > 0) {
        cout << "  ";
        depth --;
    }
  
    cout << *head->getValue() << endl;
    
    if(head->getLeft()) {
        visualize(head->getLeft(), temp+1);
    }
}




node* search(node* root, int value) {
   
    if(value == *root->getValue()) {
       // cout << root->getValue() << "a" << endl;
        return root;
    
        
        
       
    } else if(value < *root->getValue()) {
       
        if(root->getLeft() != NULL) {
    
        return search(root->getLeft(), value);
        } else {
            
        
            return NULL;
                    }
    } else if(value > *root->getValue() ) {
        
        
        if(root->getRight() != NULL) {
           
       //      cout << root->getRight()->getValue() << "c" << endl;
        return search(root->getRight(), value);
            
        } else {
         
          //  cout << "k" << endl;
            return NULL;
        }
    } else {
       
        return NULL;
    }
 

 
}

node* findAbove(node* root, node* find) {
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
    
    
    
}






void remvove(node* &root, int value) {
 
    if(value == *root->getValue()) {
        if(root->getLeft() == NULL && root->getRight() == NULL) {
            root->setValue(0);
        } else if(root->getLeft() != NULL && root->getRight() == NULL) {
            node* temp = root->getLeft();
            root->setValue(*(temp->getValue()));
            root->setRight(temp->getRight());
            root->setLeft(temp->getLeft());
            delete temp;
        } else if(root->getLeft() == NULL && root->getRight() != NULL) {
            node* temp = root->getRight();
            root->setValue(*(temp->getValue()));
            root->setRight(temp->getRight());
            root->setLeft(temp->getLeft());
            delete temp;
            
        } else {
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
            
            
        }
  
        return;
        
    }
    node* parent = findAbove(root,search(root,value));
    int side = 0;
    if(parent != NULL) {
        node* temp = NULL;
        if(parent->getLeft() == search(root,value)) {
            side = 1;
            temp = parent->getLeft();
            
        } else {
            temp = parent->getRight();
        
        }
        
        
        if(temp->getLeft() == NULL && temp->getRight() == NULL) {
            if(side == 1) {
                parent->setLeft(NULL);
            } else {
                parent->setRight(NULL);
                delete temp;
            }
              delete temp;
            
        } else if(temp->getLeft() != NULL && temp->getRight == NULL) {
            
            if(side == 1) {
                parent->setLeft(temp->getLeft());
            } else {
                parent->setRight(NULL);
                delete temp;
            }
            delete temp;
            
        } else if(temp->getLeft() == NULL && temp->getRight != NULL) {
            
            if(side == 1) {
                parent->setLeft(temp->getRight());
            } else {
                parent->setRight(temp->getRight());
                delete temp;
            }
            delete temp;
        } else {
            
        }
        
        
        
        
    } else {
        cout << "Value is not in tree!" << endl;
    }
    
    
    
}





// Majority of my main function taken from heap project. Also includes code from Omar and the calling of a function provided by Stefan Ene's heap
int main() {
    
    
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
        
        
    } else if(strcmp(inp, "quit") == 0) {
        running = false;
        
        
    } else {
        cout << "Enter a valid option" << endl;;
        
    }
    
    
        
        
    }
    
   
    
    
    
    
    
    
    return 0;
}
