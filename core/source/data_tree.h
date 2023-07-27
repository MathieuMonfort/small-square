//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_DATA_TREE_H
#define SMALLSQUARE_DATA_TREE_H
#include <vector>
#include <list>

using namespace std;

namespace smallsquare {

    /**
     * A Node is a part of a Tree containing 1 Object of Type T.
     * @tparam T The class of the object contained in the Node.
     */
    template<class T>
    struct Node {

        /**
         * A pointer to the Node's parent.
         */
        Node *parent;

        /**
         * A list of pointer to the Node's children.
         */
        list<Node *> children;

        /**
         * An object of type T.
         */
        T data;

        /**
         * The constructor to the Node class. While a Node can be without children, it has to have a parent, unless it's the root node (handled by the Tree class).
         * @param data An object of type T contained within the node.
         * @param parent A pointer to the Node's parent.
         */
        Node(T data, Node *parent) {
            this->data = data;
            this->parent = parent;
        }
    };

    /**
     * A Tree is a data structure where any node can have any number of children and only 1 parent.
     * @tparam T The class of the objects contained in every Tree's Node.
     */
    template<class T>
    class Tree {
    private:

        /**
         * The root node is a node acting only as a termination to any tree.
         * It's the only node that is permitted to not have a parent.
         */
        Node<T> *_root;

        /**
         * Get the first node the tree containing the object data.
         * See TraverseOrReturn for more information.
         * @param data The object the function looks for.
         * @return
         */
        Node<T> *GetFirst(T data) {
            return TraverseOrReturn(_root, data);
        }


        //TODO: Could be optimised further.

        /**
         * Traverses the tree and returns once it finds a Node containing Object data.
         * Since an Object can only be included once inside a Tree,
         * the order in which it's looked up in the tree is not supposed to have any real significance apart from fine optimisation.
         * @param n The starting node
         * @param data The object the function looks for
         * @return A pointer to a Node containing the object data or nullptr if data is not in branch.
         */
        Node<T> *TraverseOrReturn(Node<T> *n, T data) {
            if (n->data == data) { return n; }

            for (auto it = n->children.begin(); it != n->children.end(); it++) {
                Node<T> *traversedChild = TraverseOrReturn((*it), data);
                if (traversedChild == nullptr) { continue; }
                if (traversedChild->data == data) { return traversedChild; }
            }

            return nullptr;
        }

        /**
         * Traverses the tree or subtree adding every object to the return vector.
         * @param n The starting node.
         * @return A vector containing pointers to every Node in the tree or subtree.
         */
        vector<T> TraverseOrPushback(Node<T> *n) {
            vector<T> result;
            result.push_back(n->data);
            for (auto it = n->children.begin(); it != n->children.end(); it++) {
                vector<T> traversedChild = TraverseOrPushback(*it);
                result.insert(result.end(), traversedChild.begin(), traversedChild.end());
            }
            return result;
        }
        /**
         * Insert a new Node containing object data as children of Node parent
         * @param data The object encapsulated into the new Node
         * @param parent The new Node's parent.
         */
        void Insert(T data, Node<T> *parent) {
            parent->children.push_back(new Node<T>(data, parent));
        }

    public:
        /**
         * The constructor to the Tree Class.
         * @param data The object contained in the root node.
         */
        explicit Tree(T data) {
            _root = new Node<T>(data, nullptr);
        }

        /**
         * Extract a Subtree from a tree starting
         * @param newRoot
         * @return
         */
        Tree<T> Subtree(T newRoot) {
            if (!GetFirst(newRoot)) { return nullptr; }
            return Tree(GetFirst(newRoot));
        }


        /**
         * Remove a subtree by dereferencing it;
         * @param branch The object found at the root of the subtree to be deleted.
         */
        void Exclude(T branch) {

            Node<T> branchRoot = GetFirst(branch);
            if (branchRoot == nullptr) { return; }


            for (Node<T> *n: branchRoot.parent.children) {
                if (n->data == branch) {
                    n = nullptr;
                }
            }
        }

        /**
         * Get the current Tree's root's object.
         * @return An object of Type T contained in the Tree's root Node
         */
        T GetRoot() {
            return _root->data;
        }

        /**
         * Get every objects in the tree organised in a vector destroying any hierarchy.
         * @return A vector of objects of type T.
         */
        vector<T> Flatten() {
            return TraverseOrPushback(_root);
        }

        /**
         * Get every objects in a subtree starting at data organised in a vector destroying any hierarchy.
         * @param data The root of the subtree to be flattened.
         * @return A vector of objects of type T.
         */
        vector<T> Flatten(T data) {
            if (!GetFirst(data)) { return vector<T>(); }
            return TraverseOrPushback(GetFirst(data));
        }

        /**
         * Get a child of data. Either the first child of data or a child with index i.
         * @param data The parent.
         * @param i The child's index.
         * @return An object of type T, child of data.
         */
        T ChildOf(T data, int i = 0) {
            Node<T> *n = GetFirst(data);
            if (!n) { return nullptr; }
            if (n->children.size() == 0) { return nullptr; }
            if (n->children.size() <= i) { return nullptr; }
            auto it = n->children.begin();
            advance(it, i);
            return (*it)->data;
        }

        /**
         * Get all the children of data organised in a vector.
         * @param data The parent.
         * @return A vector of objects of type T, children of data.
         */
        vector<T> ChildrenOf(T data) {
            vector<T> result;
            Node<T> *n = GetFirst(data);

            for (auto it = n->children.begin(); it != n->children.end(); it++) {
                result.push_back((*it)->data);
            }
            return result;
        }

        /**
         * Get the parent of data.
         * @param data The child.
         * @return An object of type T, parent of data.
         */
        T ParentOf(T data) {
            Node<T> *n = GetFirst(data);
            if (!n) { return nullptr; }
            if (!n->parent) { return nullptr; }
            return n->parent->data;
        }

        /**
         * Get every Node between the root Node and data organised in a vector and in a hierarchical order.
         * @param data The path's endpoint
         * @return A vector of objects of type T
         */
        vector<T> PathTo(T data) {
            Node<T> *n = GetFirst(data);
            vector<T> result;
            result.push_back(data);
            if (!n) { return result; }

            do {
                n = n->parent;
                result.push_back(n->data);
            } while (n != _root);

            return result;
        }

        /**
         * Insert an object in a new Node inside the Tree as a child of parent.
         * @param data The object to be inserted.
         * @param parent The parent of the new Node.
         * @return 0 if the object is effectively inserted in the tree, -1 if something went wrong.
         */
        int Insert(T data, T parent) {
            if (GetFirst(data)) { return -1; }
            Node<T> *pNode = GetFirst(parent);
            if (pNode == nullptr) { return -1; }
            Insert(data, pNode);
            return 0;
        }

        /**
         * Insert an abject in a new Node inside the tree as a child of the root Node.
         * @param data The object to be inserted.
         */
        void Insert(T data) {
            Insert(data, _root);
        }
    };

}

#endif