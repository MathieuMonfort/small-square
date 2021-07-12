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
struct Node{

};

template <class T>
struct DynamicNode : public Node<T> {
    DynamicNode * parent;
    list<DynamicNode * > children;
    T data;

    DynamicNode(T data, DynamicNode * parent ){
        this->data = data;
        this->parent = parent;
    }
};

template <class T>
class Tree{
protected:
    Node<T> * _root;

    virtual Node<T> * GetFirst(T data){}
    virtual Node<T> * TraverseOrReturn(Node<T> * n, T data){}
    virtual vector<T>  TraverseOrPushback(Node<T> * n){}
    virtual void Insert(T data, Node<T> * parent){}

public:
    virtual Tree<T> Subtree(T newRoot){}
    virtual void Exclude(T branch){}
    virtual T GetRoot(){}

    virtual vector<T> Flatten(){}
    virtual vector<T> Flatten(T data){}

    virtual T ChildOf(T Data, int i =0 ){}
    virtual vector<T> ChildrenOf(T data){}
    virtual T ParentOf(T data){}
    virtual vector<T> PathTo(T data){}

    virtual int Insert(T data, T parent){}
    virtual int Insert(T data){}
};


template <class T>
class DynamicTree : public Tree<T> {
private:
    DynamicNode<T> * _root;

    DynamicNode<T> * GetFirst(T data) override {
        return TraverseOrReturn(_root, data);
    }
    DynamicNode<T> * TraverseOrReturn(DynamicNode<T> *n, T data) override{
        if(n->data == data) {return n;}

        for(int i =0; i< n->children.size() ; i++) {
            DynamicNode<T> * traversedChild = TraverseOrReturn(n->children[i], data);
            if(traversedChild == nullptr){continue;}
            if(traversedChild->data == data ) {return traversedChild; } 
        }

        return nullptr;
    }
    vector<T> TraverseOrPushback(DynamicNode<T> * n) override {
        vector<T> result;
        result.push_back(n->data);
        for(int i =0; i< n->children.size() ; i++){
            vector<T> traversedChild = TraverseOrPushback(n->children[i]);
            result.insert(result.end(),traversedChild.begin() , traversedChild.end());
        }
        return result;
    }
    void Insert(T data, DynamicNode<T> * parent) override{
        parent->children.push_back(new DynamicNode<T>(data, parent));
    }

public:
    explicit DynamicTree(T data)  {
        _root = new DynamicNode<T>(data, nullptr);
    }
    DynamicTree<T> Subtree(T newRoot){
        if(!GetFirst(newRoot)) {return nullptr;}
        return DynamicTree(GetFirst(newRoot));
    }
    void Exclude(T branch){

        DynamicNode<T> branchRoot = GetFirst(branch);
        if(branchRoot == nullptr) {return; }


        for(DynamicNode<T> * n : branchRoot.parent.children ){
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
        DynamicNode<T> *  n = GetFirst(data);
        if(!n) {return nullptr;}
        if(n->children.size() == 0){return nullptr;}
        if(n->children.size() <= i ){return nullptr;}
        return n->children[i]->data;
    }
    vector<T> ChildrenOf(T data){
        vector<T> result;
        DynamicNode<T> *  n = GetFirst(data);

        for(int i =0; i< n->children.size(); i++){
            result.push_back(n->children[i]->data );
        }
        return result;
    }
    T ParentOf(T data){
        DynamicNode<T> *  n = GetFirst(data);
        if(!n) {return nullptr;}
        if(!n->parent) {return nullptr;}
        return n->parent->data;
    }
    vector<T> PathTo(T data) override{
        DynamicNode<T> *  n = GetFirst(data);
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
        DynamicNode<T> * pNode  = GetFirst(parent);
        if(pNode == nullptr) { return -1; }
        Insert(data, pNode);
        return 0;
    }
    int Insert(T data){
        return Insert(data, _root);
    }
};

#endif