// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.
// 11/17/2023 modification by Prof Sipantzi
// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"

#pragma once

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <class Key, class E>
class BST : public Dictionary<Key, E> {
private:
    BSTNode<Key, E>* root;   // Root of the BST

    int nodecount;         // Number of nodes in the BST

    // Private "helper" functions
    void clearhelp(BSTNode<Key, E>*);
    BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*,
        const Key&, const E&);
    BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
    BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
    BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
    E* findhelp(BSTNode<Key, E>*, const Key&) const;
    void printhelp(BSTNode<Key, E>*, int) const;
    void vist(BSTNode<Key, E>*) const;


public:
    BST() { root = NULL; nodecount = 0; }  // Constructor

    //Note from Prof Sipantzi -- I've commented out the destructor
    //since you would have to change clearhelp() to make it work with
    //doubly-threaded trees and that is not part of the assignment.
    //~BST() { clearhelp(root); }            // Destructor

    void clear()   // Reinitialize tree
    {
        clearhelp(root); root = NULL; nodecount = 0;
    }

    // Insert a record into the tree.
    // k Key value of the record.
    // e The record to insert.
    void insert(const Key& k, const E& e) {
        root = inserthelp(root, k, e);
        nodecount++;
    }

    // Remove a record from the tree.
    // k Key value of record to remove.
    // Return: The record removed, or NULL if there is none.
    E* remove(const Key& k) {
        E* temp = findhelp(root, k);   // First find it
        if (temp != NULL) {
            root = removehelp(root, k);
            nodecount--;
        }
        return temp;
    }
    // Remove and return the root node from the dictionary.
    // Return: The record removed, null if tree is empty.
    E* removeAny() {  // Delete min value
        if (root != NULL) {
            E* temp = new E;
            *temp = root->element();
            root = removehelp(root, root->key());
            nodecount--;
            return temp;
        }
        else return NULL;
    }

    // Return Record with key value k, NULL if none exist.
    // k: The key value to find. */
    // Return some record matching "k".
    // Return true if such exists, false otherwise. If
    // multiple records match "k", return an arbitrary one.
    E* find(const Key& k) const { return findhelp(root, k); }

    // Return the number of records in the dictionary.
    int size() { return nodecount; }

    void print() const { // Print the contents of the BST
        if (root == NULL) cout << "The BST is empty.\n";
        else printhelp(root, 0);
    }


    void printInorder() const;
    void printReverse() const;
};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key, E>* r) const {
    cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
    if (root == NULL) return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(
    BSTNode<Key, E>* root, const Key& k, const E& it) {
    if (root == NULL)  // Empty tree: create node
        return new BSTNode<Key, E>(k, it, NULL, NULL);
    BSTNode<Key, E>* curr = root;
    BSTNode<Key, E>* prev = NULL;

    // Finds where to insert
    while (curr != NULL) {
        prev = curr;
        if (k < curr->key()) {
            if (!curr->leftIsThreaded()) {
                curr = curr->left();
            }
            else {
                break; // Left is threaded, stops the loop
            }
        }
        else {
            if (!curr->rightIsThreaded()) {
                curr = curr->right();
            }
            else {
                break; // Right is threaded, stops the loop
            }
        }
    }

    BSTNode<Key, E>* newNode = new BSTNode<Key, E>(k, it);

    if (k < prev->key()) {
        newNode->setLeft(prev->left(), true); // Set thread for left
        newNode->setRight(prev, true); // Set thread for right
        prev->setLeft(newNode);
    }
    else {
        newNode->setRight(prev->right(), true); // Set thread for right
        newNode->setLeft(prev, true); // Set thread for left
        prev->setRight(newNode);
    }

    return root; // Returns the root

}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
    if (rt->left() == NULL)
        return rt;
    else return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
    if (rt->left() == NULL) // Found min
        return rt->right();
    else {                      // Continue left
        rt->setLeft(deletemin(rt->left()));
        return rt;
    }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
    if (rt == NULL) return NULL;    // k is not in tree
    else if (k < rt->key())
        rt->setLeft(removehelp(rt->left(), k));
    else if (k > rt->key())
        rt->setRight(removehelp(rt->right(), k));
    else {                            // Found: remove it
        BSTNode<Key, E>* temp = rt;
        if (rt->left() == NULL) {     // Only a right child
            rt = rt->right();         //  so point to right
            delete temp;
        }
        else if (rt->right() == NULL) { // Only a left child
            rt = rt->left();          //  so point to left
            delete temp;
        }
        else {                    // Both children are non-empty
            BSTNode<Key, E>* temp = getmin(rt->right());
            rt->setElement(temp->element());
            rt->setKey(temp->key());
            rt->setRight(deletemin(rt->right()));
            delete temp;
        }
    }
    return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
    const Key& k) const {
    if (root == NULL) return NULL;          // Empty tree
    if (k < root->key())
        return findhelp(root->left(), k);   // Check left
    else if (k > root->key())
        return findhelp(root->right(), k);  // Check right
    else {
        E* temp = new E;
        *temp = root->element();
        return temp;  // Found it
    }
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const {
    if (root == NULL) return;           // Empty tree

    // Go through left side of tree
    if (root->left() != NULL && !root->leftIsThreaded())
        printhelp(root->left(), level + 1);

    // Print the node
    for (int i = 0; i < level; i++)
    {
        cout << "  ";
    }
    cout << root->key() << "\n";

    // Go through right side of tree
    if (root->right() != NULL && !root->rightIsThreaded())
        printhelp(root->right(), level + 1);
}

template<typename Key, typename E>
void BST<Key, E>::printInorder() const
{
    BSTNode<Key, E>* curr = root;

    // Go to left most node
    while (curr != NULL && curr->left() != NULL && !curr->leftIsThreaded()) {
        curr = curr->left();
    }

    // Go through the tree in order
    while (curr != NULL) {
        // Print node
        cout << curr->key() << "-" << curr->element() << "\n";

        // Move to left most node
        if (curr->right() != NULL && !curr->rightIsThreaded()) {
            curr = curr->right();
            while (curr->left() != NULL && !curr->leftIsThreaded()) {
                curr = curr->left();
            }
        }
        else {
            curr = curr->right();
        }
    }
}

template <typename Key, typename E>
void BST<Key, E>::printReverse() const {
    BSTNode<Key, E>* curr = root;

    // Go to right most node
    while (curr != NULL && curr->right() != NULL && !curr->rightIsThreaded()) {
        curr = curr->right();
    }

    // Go through tree in reverse order
    while (curr != NULL) {
        // Print node
        cout << curr->key()<< "-" << curr->element() << "\n";

        // Go right most node
        if (curr->left() != NULL && !curr->leftIsThreaded()) {
            curr = curr->left();
            while (curr->right() != NULL && !curr->rightIsThreaded()) {
                curr = curr->right();
            }
        }
        else {
            curr = curr->left();
        }
    }
}