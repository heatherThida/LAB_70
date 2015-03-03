/*
 * Jimmy Patel & Robert Bayer
 * COEN 70 Lab #9 // Tuesday 9:15 - 12:00
 * TA Patrick
 *
 * Filename: RBTree.h
 * Requires: RBNode.h (node header file) and main.cpp (test program)
 *
 * Red-Black Trees
 * */

#include <iostream>
#include "RBNode.h"
#include <iomanip> //setw function for pretty print of trees

using namespace std;

class RBTree {
public:
    RBTree();
    ~RBTree();
    
    RBTree(const RBTree&);
    RBTree& operator=(const RBTree&);
    
    void addNode(int);
    RBNode<int>* getSibling(RBNode<int>*);
    RBNode<int>* getAunt(RBNode<int>*);
    RBNode<int>* getGrandparent(RBNode<int>*);
    void printTree(RBNode<int>*, int);
    
    void rotateLeft(RBNode<int>*);
    void rotateRight(RBNode<int>*);
    void fixTree(RBNode<int>*);
    
    void remove_all(RBNode<int>*);
    RBNode<int>* makeCopy(RBNode<int>*);
    
    RBNode<int>* root;
};


RBTree::RBTree(){
    root = NULL;
}

//destruct recursively using remove_all
RBTree::~RBTree(){
    remove_all(root);
}

//delete the entire tree using recursion
void RBTree::remove_all(RBNode<int>* r){
    if(r == NULL)
        return;
    remove_all(r->left());
    remove_all(r->right());
    delete r;
}

//equal operator
RBTree& RBTree::operator=(const RBTree& r){
    //self-check
    if(this == &r)
        return *this;
    
    //delete
    if(root != NULL){
        remove_all(root);
    }
    
    //copy
    root = makeCopy(r.root);
    return *this;
}

//copy one tree to another
RBNode<int>* RBTree::makeCopy(RBNode<int>* r){
    if(r != NULL)
        return new RBNode<int>(r->data(), makeCopy(r->left()), makeCopy(r->right()), r->color(), r->parent());
    return NULL;
}

//copy constructor
RBTree::RBTree(const RBTree& r){
    root = NULL;
    *this = r;
}

//rotate tree to the left
void RBTree::rotateLeft(RBNode<int>* r){
    
    RBNode<int>* y;
    
    y = r->right();
    r->set_right(y->left());
    
    if(y->left() != NULL){
        y->left()->set_parent(r);
    }
    y->set_parent(r->parent());
    if(r->parent() == NULL){
        root = y;
    }
    else if(r == r->parent()->left()){
        r->parent()->set_left(y);
    }
    else
        r->parent()->set_right(y);
    
    y->set_left(r);
    r->set_parent(y);
}

//rotate tree to the right
void RBTree::rotateRight(RBNode<int>* r){
    
    RBNode<int>* y;
    
    y = r->left();
    r->set_left(y->right());
    
    if(y->right() != NULL){
        y->right()->set_parent(r);
    }
    y->set_parent(r->parent());
    if(r->parent() == NULL){
        root = y;
    }
    else if(r == r->parent()->right()){
        r->parent()->set_right(y);
    }
    else
        r->parent()->set_left(y);
    
    y->set_right(r);
    r->set_parent(y);
}

//return the node that is the sibling
RBNode<int>* RBTree::getSibling(RBNode<int>* r){
    if(r->parent() == NULL)
        return NULL;
    if(r == r->parent()->left())
        return r->parent()->right();
    else
        return r->parent()->left();
}

//returns the other child of the grandparent (parent's sibling)
RBNode<int>* RBTree::getAunt(RBNode<int>* r){
        if(r->parent() == NULL)
            return NULL;
        return getSibling(r->parent());
}

//returns grandparent of given node
RBNode<int>* RBTree::getGrandparent(RBNode<int>* r){
    if(r->parent() == NULL || r->parent()->parent() == NULL)
        return NULL;
    return r->parent()->parent();
}

//depth starts @ 0, r starts at NULL
void RBTree::printTree(RBNode<int>* r, int depth){
    if(r != NULL){
        printTree(r->right(), depth + 1);
        cout << setw(4 * depth) << " " << r->data() << endl;
        printTree(r->left(), depth + 1);
    }
}

//add a node (breaks red & black, use fix Tree to rebuild)
void RBTree::addNode(int value){
    //first insertion
    if(root == NULL){
        root = new RBNode<int>(value, NULL, NULL, RBNode<int>::BLACK, NULL);
        fixTree(root);
    }
    
    RBNode<int>* nNode = new RBNode<int>(value, NULL, NULL, RBNode<int>::RED, NULL);
    
    RBNode<int>* trail = root;
    RBNode<int>* temp = root;
    while(temp != NULL){
        if(value > temp->data()){
            if(temp->right() == NULL){
                nNode->set_parent(temp);
                temp->set_right(nNode);
                fixTree(nNode);
                return;
            }
            else{
                trail = temp;
                temp = temp->right();
            }
        }
        else if(value < temp->data()){
            if(temp->left() == NULL){
                nNode->set_parent(temp);
                temp->set_left(nNode);
                fixTree(nNode);
                return;
            }
            else{
                trail = temp;
                temp = temp->left();
            }
        }
        else if(value == temp->data()){
            cout << "Value already exists in tree." << endl;
            return;
        }
    }
    
}

//fix the tree by changing colors and rebalancing (taken from lab pseudocode)
void RBTree::fixTree(RBNode<int>* r){
    RBNode<int>* y;
    
    if(r == root){
        r->set_color(RBNode<int>::BLACK);
        return;
    }
    
    //if parent is black, quit, the tree is a red black tree
    if(r->parent()->color() == RBNode<int>::BLACK)
        return;
    
    if(r->color() == RBNode<int>::RED && r->parent()->color() == RBNode<int>::RED){
        if(getAunt(r) == NULL || getAunt(r)->color() == RBNode<int>::BLACK){
            if(getGrandparent(r)->left() == r->parent() && r->parent()->right() == r){
                y = r->parent();
                rotateLeft(y);
                fixTree(y);
            }
            else if(getGrandparent(r)->right() == r->parent() && r->parent()->left() == r){
                y = r->parent();
                rotateRight(y);
                fixTree(y);
            }
            else if(getGrandparent(r)->left() == r->parent() && r->parent()->left() == r){
                r->parent()->set_color(RBNode<int>::BLACK);
                getGrandparent(r)->set_color(RBNode<int>::RED);
                rotateRight(getGrandparent(r));
                return;
            }
            else if(getGrandparent(r)->right() == r->parent() && r->parent()->right() == r){
                r->parent()->set_color(RBNode<int>::BLACK);
                getGrandparent(r)->set_color(RBNode<int>::RED);
                rotateLeft(getGrandparent(r));
                return;
            }
        }
        else if(getAunt(r)->color() == RBNode<int>::RED){
            r->parent()->set_color(RBNode<int>::BLACK);
            getAunt(r)->set_color(RBNode<int>::BLACK);
            getGrandparent(r)->set_color(RBNode<int>::RED);
            fixTree(getGrandparent(r));
        }
    }
}


