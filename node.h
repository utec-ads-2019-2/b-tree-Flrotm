#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cmath>
using namespace std;
template<typename T>
class BTree;

template <typename T>
class Node {
public:
    int deg;
    unsigned int size;
    vector<unsigned int> keys;
    vector<Node<T>*> childs;
    bool isLeaf;
    friend class Btree;

public:
        Node(unsigned int size, bool isLeaf = true) : deg(size), isLeaf(isLeaf) {
            keys.resize(size - 1);
            childs.resize(size);
        }

        /**
         * An alternative is to create two different nodes (Internal and Leaf) that inherite from Node 
         * an implement this function
         */


    Node *search(int k) {
            int i = 0;
            while (i<this->size and k > this->keys.at(i)) {
                ++i;
            }
            if(i==this->deg-1)
                return nullptr;
            if (this->keys[i]==k)
                return this;
            if (this->isLeaf)
                return nullptr;

            return this->childs[i]->search(k);
    }

    void split(int k, Node<T> *nuevo){
        auto newNode = new Node<T>(nuevo->deg, nuevo->isLeaf);
        int mitad = ceil((this->deg - 1) / 2);
        newNode->size=childs.size()-1;

        for (int j = 0; j < size-1; j++)
            newNode->keys[j] = nuevo->keys[j+size];
        if (!newNode->isLeaf){
            for(int i=0 ; i <= size ; ++i) {
                newNode->childs[i] = newNode->childs[mitad+1+i];
            }
        }
        newNode->size = mitad;

        for(int i=this->size+1;i>k+1;--i)
            this->childs[i] = this->childs[i-1];

        this->childs[k+1] = newNode;

        for(int i=this->size;i>k;--i)
            this->keys.at(i) = this->keys.at(i-1);

        this->keys[k]=newNode->keys[mitad];
        this->size++;

    }

    void insertNonFull(T data) {

        int i = this->keys.size();

        if(this->isLeaf) {
            while(i>0 and data<this->keys[i-1]) {
                this->keys[i]=this->keys[i-1];
                i--;
            }
            this->keys[0]= data;
            size++;
        }
        else {
            while(i>0 and data<this->keys[i])
                i--;

            if(this->childs[i]->size==this->deg - 1){
                split(i, this->childs[i]);

                if(this->keys[i]<data)
                    i++;
            }
            this->childs[i]->insertNonFull(data);
        }
    }

    void print() {
        int index;
        for (index = 0; index < this->keys.size(); ++index) {
            if (!this->isLeaf)
                this->childs[index]->print();
            cout << " " << this->keys[index];
        }
        if (!this->isLeaf)
            this->childs[index]->print();
    }

    void removeFromLeaf (int idx){

        for (int i=idx+1; i<size; ++i){
            keys[i-1] = keys[i];}

        size--;
   }

    void removeFromNonLeaf(int i)
    {
        // Falta el merge y dar delete

        int k = keys[i];

        if (childs[i]->n >= deg){
            int p = search(i);
            keys[i]=p;
            childs[i]->remove(p);
        }
        else if  (childs[i+1]->n >= deg){
            int s = search(i);
            keys[i]=s;
            childs[i+1]->remove(s);
        }
        else{
            childs[i]->remove(k);
        }

    }

};

#endif
