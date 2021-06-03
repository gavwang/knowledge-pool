
#include <iostream>
#include <string>
#include <cstring>  // or include string.h
#include <cassert>
#include <vector>
#include "myAlgorithm.h"
#include "myMap.h"
#include "avltree.h"

using namespace std;

class base {
public:
    base(){
        cout << "base constructure" <<endl;
    };

    ~base()
    {
        cout << "base destructor" <<endl;
    };

};

class derivedClass: public base {
public:
    derivedClass(){
        cout << "derivedClass constructure" <<endl;
    };

    ~derivedClass(){
        cout << "derivedClass destructor" <<endl;
    };

};


int main(int argc, char* argv[])
{
    cout << "*************************************************************" << endl;
    cout << "*" << endl;
    cout << "*   This is my demostration for C++ basic knowledge" << endl ;
    cout << "*" << endl;
    cout << "*************************************************************" << endl;
    cout << endl;
    cout << endl;

    derivedClass d;


#if 0
    char number[] = "1234567890" ;
    cout << "string2Int" << string2int(number)<< endl;
    //cout << "int32 max = " << INT32_MAX << " size = " <<  max_int_char_size() <<endl;
    vector<string> msg = {"hello", "world", "from", "VS code"};
    //msg.assign
    testMyMap();

    Avltree<int, string> avl;

    BTree<int, string> bTree;
    BTreeNode<int,string>* root;
    bTree.create(root);


    bTree.inorderTraversal(root);
#endif
    cout << "input q to exit program" << endl;
    int ret;
    cin >> ret;


    
    return 0;
}
