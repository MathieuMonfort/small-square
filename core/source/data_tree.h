//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_DATA_TREE_H
#define SMALLSQUARE_DATA_TREE_H
#include <vector>
#include <list>

using namespace std;


template <class T>
struct Node {
    Node * parent;
    list<Node * > children;
    T data;

    Node(T data, Node * parent ){
        this->data = data;
        this->parent = parent;
    }
};

template <class T>
class Tree{
private:
    Node<T> * _root;

    Node<T> * GetFirst(T data) {
        return TraverseOrReturn(_root, data);
    }
    Node<T> * TraverseOrReturn(Node<T> *n, T data){
        if(n->data == data) {return n;}

        for(auto it = n->children.begin(); it != n->children.end(); it++){
            Node<T> * traversedChild = TraverseOrReturn((*it), data);
            if(traversedChild == nullptr){continue;}
            if(traversedChild->data == data ) {return traversedChild; } 
        }

        return nullptr;
    }
    vector<T> TraverseOrPushback(Node<T> * n) {
        vector<T> result;
        result.push_back(n->data);
        for(auto it = n->children.begin(); it != n->children.end(); it++){
            vector<T> traversedChild = TraverseOrPushback(*it);
            result.insert(result.end(),traversedChild.begin() , traversedChild.end());
        }
        return result;
    }
    void Insert(T data, Node<T> * parent){
        parent->children.push_back(new Node<T>(data, parent));
    }

public:
    explicit Tree(T data)  {
        _root = new Node<T>(data, nullptr);
    }
    Tree<T> Subtree(T newRoot){
        if(!GetFirst(newRoot)) {return nullptr;}
        return Tree(GetFirst(newRoot));
    }
    void Exclude(T branch){

        Node<T> branchRoot = GetFirst(branch);
        if(branchRoot == nullptr) {return; }


        for(Node<T> * n : branchRoot.parent.children ){
            if (n->data == branch) {

            }
        }
    }

    T GetRoot(){
        return _root->data;
    }
    vector<T> Flatten(){
        return TraverseOrPushback(_root);
    }
    vector<T> Flatten(T data){
        if(!GetFirst(data)) { return vector<T>(); }
        return TraverseOrPushback(GetFirst(data));
    }

    T ChildOf(T data, int i = 0){
        Node<T> *  n = GetFirst(data);
        if(!n) {return nullptr;}
        if(n->children.size() == 0){return nullptr;}
        if(n->children.size() <= i ){return nullptr;}
        auto it = n->children.begin();
        advance( it, i);
        return (*it)->data;
    }
    vector<T> ChildrenOf(T data){
        vector<T> result;
        Node<T> *  n = GetFirst(data);

        for(auto it = n->children.begin(); it != n->children.end(); it++){
            result.push_back((*it)->data );
        }
        return result;
    }
    T ParentOf(T data){
        Node<T> *  n = GetFirst(data);
        if(!n) {return nullptr;}
        if(!n->parent) {return nullptr;}
        return n->parent->data;
    }
    vector<T> PathTo(T data){
        Node<T> *  n = GetFirst(data);
        vector<T> result;
        result.push_back(data);
        if(!n) {return result;}

        do{
            n = n->parent; 
            result.push_back(n->data);
        }while(n != _root);

        return result;
    }

    int Insert(T data, T parent){
        if(GetFirst(data)) {return -1;}
        Node<T> * pNode  = GetFirst(parent);
        if(pNode == nullptr) { return -1; }
        Insert(data, pNode);
        return 0;
    }
    int Insert(T data){
        return Insert(data, _root->data);
    }
};

#endif