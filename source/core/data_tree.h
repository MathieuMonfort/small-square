#ifndef DATA_TREE_H
#define DATA_TREE_H

//#include <list>
#include <vector>

using namespace std;


template <class T>
struct node{
    node * parent; 
    vector<node * > children;
    T data;

    node(T data, node * parent ){
        this->data = data;
        this->parent = parent;
    }
};


template <class T>
class tree{
private:
    node<T> * root;

    node<T> * TraverseOrReturn(node<T> *n, T data){
        if(n->data == data) {return n;}

        for(int i =0; i< n->children.size() ; i++) {
            node<T> * traversedChild = TraverseOrReturn(n->children[i], data);
            if(traversedChild == nullptr){continue;}
            if(traversedChild->data == data ) {return traversedChild; } 
        }

        return nullptr;
    }

    vector<T> TraverseOrPushback(node<T> * n){
        vector<T> result;
        result.push_back(n->data);
        for(int i =0; i< n->children.size() ; i++){
            vector<T> traversedChild = TraverseOrPushback(n->children[i]);
            result.insert(result.end(),traversedChild.begin() , traversedChild.end());
        }
        return result;
    } 

    void insert(T data, node<T> * parent){
        parent->children.push_back(new node<T>(data,parent));
    }

    node<T> * GetFirst(T data){
        return TraverseOrReturn(root, data);
    }
public:
    explicit tree(T data)  {
        root = new node<T>(data, nullptr);
    }

    T GetRoot(){
        return root->data;
    }
    
    T ChildOf(T data, int i = 0){
        node<T> *  n = GetFirst(data); 
        if(!n) {return nullptr;}
        if(n->children.size() == 0){return nullptr;}
        if(n->children.size() <= i ){return nullptr;}
        return n->children[i]->data;
    }

    vector<T> ChildrenOf(T data){
        vector<T> result;
        node<T> *  n = GetFirst(data); 

        for(int i =0; i< n->children.size(); i++){
            result.push_back(n->children[i]->data );
        }
        return result;
    }

    T ParentOf(T data){
        node<T> *  n = GetFirst(data); 
        if(!n) {return nullptr;}
        return n->parent->data;
    }

    vector<T> PathTo(T data){
        node<T> *  n = GetFirst(data); 
        vector<T> result;
        result.push_back(data);
        if(!n) {return result;}

        do{
            n = n->parent; 
            result.push_back(n->data);
        }while(n != root);

        return result;
    }

    int insert(T data, T parent){
        node<T> * p_node  = GetFirst(parent);
        if( p_node == nullptr) { return -1; }
        insert(data, p_node);
        return 0;
    }

    int insert(T data){
        insert(data, root);
        return 0;
    }
    vector<T> flatten(){
        return TraverseOrPushback(root);
    }


};

#endif