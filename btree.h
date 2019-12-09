#ifndef BTREE_H
#define BTREE_H

#include "node.h"

template <typename T>
class BTree {
private:
        Node<T>* root;
        unsigned int degree;

    public:
        BTree(unsigned int degree) : degree(degree), root(nullptr) {};

        T find(int k) {
            if (this->root== nullptr)
                return false;
            else
                return this->root->search(k) != nullptr;

        }

        void insert(T data) {
            if(find(data)){
                return;
                //no acepta repetidos
            }
            if(this->root== nullptr){
                auto newNode = new Node<T>(this->degree, true);
                this->root=newNode;
                this->root->keys.push_back(data);
            }
            else {
                if(this->root->keys.size()==this->degree-1) {

                    auto newRoot = new Node<T>(this->degree, false);

                    newRoot->childs.push_back(this->root);
                    newRoot->split(0, this->root);

                    int i = 0;
                    if(newRoot->keys[0]<data)
                        i++;

                    newRoot->childs[i]->insertNonFull(data);
                    this->root = newRoot;
                } else {
                    this->root->insertNonFull(data);
                }
            }
        }

    bool remove(int k){

        bool idx = find(k);
        if(!idx){
          return false;
         }

        if (idx < this->root->size and this->root->keys[idx] == k){

            if (this->root->isLeaf)
                this->root->removeFromLeaf(idx);
            else
                this->root->removeFromNonLeaf(idx);
        }
        else{

            bool flag = idx == this->root->size;
            if (this->root->childs[idx]->n < this->root->deg)
                insert(idx);
            if (flag and idx > this->root->size)
                this->root->childs[idx-1]->remove(k);
            else
                this->root->childs[idx]->remove(k);
        }
        return true;
    }

    void print() {
            if(this->root)
                this->root->print();
            cout<<endl;

        }

        ~BTree(); // Faltó destructor
};





#endif
