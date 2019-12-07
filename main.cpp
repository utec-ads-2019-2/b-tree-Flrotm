#include <iostream>
#include "btree.h"
using namespace std;

int main() {
BTree<int> arbol(3);

arbol.insert(2);
arbol.insert(0);
arbol.insert(5);


arbol.print();


    if(arbol.find(5)){
        cout<<"encontrado"<<endl;

    } else{
        cout<<"no"<<endl;
    }
}
