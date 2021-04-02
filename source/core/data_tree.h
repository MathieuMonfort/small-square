#ifndef DATA_TREE_H
#define DATA_TREE_H

#include <list> 

using namespace std;


template <class T>
struct node{
    node * parent; 
    list<node * > children;
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

        for(typename list<node<T> *>::iterator it = n->children.begin(); it != n->children.end(); it++){
            node<T> * traversedChild = TraverseOrReturn((*it), data);
            if(traversedChild == NULL){continue;}
            if(traversedChild->data == data ) {return traversedChild; } 
        }

        return NULL;
    }

    list<T> TraverseOrPushback(node<T> * n){
        list<T> result;
        result.push_back(n->data);
        for(typename list<node<T> *>::iterator it = n->children.begin(); it != n->children.end(); it++ ){
            list<T> traversedChild = TraverseOrPushback(*it);
            result.splice(result.end(),traversedChild );
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
        root = new node<T>(data, NULL);
    }

    T GetRoot(){
        return root->data;
    }
    
    T ChildOf(T data, int i = 0){
        node<T> *  n = GetFirst(data); 
        if(n == NULL) {return NULL;}
        if(n->children.size() == 0){return NULL;}
        if(n->children.size() <= i ){return NULL;}

        typename list<node<T> *>::iterator it = n->children.begin();
        advance(it, i);
        return (*it)->data; 
    }

    list<T> ChildrenOf(T data){
        list<T> result;
        node<T> *  n = GetFirst(data); 

        for(typename list<node<T> *>::iterator it = n->children.begin() ; it != n->children.end(); it++ ){
            result.push_back((*it)->data );
        }
        return result;
    }

    T ParentOf(T data){
        node<T> *  n = GetFirst(data); 
        if(n == NULL) {return NULL;}
        return n->parent->data;
    }

    list<T> PathTo(T data){
        node<T> *  n = GetFirst(data); 
        list<T> result;
        if(n == NULL) {return result;}

        result.push_front(data);
        do{
            n = n->parent; 
            result.push_front(n->data);
        }while(n != root);

        return result;
    }

    int insert(T data, T parent){
        node<T> * p_node  = GetFirst(parent);
        if( p_node == NULL) { return -1; }
        insert(data, p_node);
        return 0;
    }

    int insert(T data){
        insert(data, root);
        return 0;
    }
    list<T> flatten(){
        return TraverseOrPushback(root);
    }


};

#endif