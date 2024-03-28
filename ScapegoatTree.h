#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;
    int getSize() const;

    bool insert(const T &element);
    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;
    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;
    const T &getFloor(const T &element) const;

    const T &getMin() const;
    const T &getMax() const;

    const T &getNext(const T &element) const;

private:
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;

    void removeAllNodes(Node<T>*& node){
        
        if(node == NULL){
            return;
        }

        removeAllNodes(node->left);
        removeAllNodes(node->right);
        
        Node<T>* temp = node;
        delete temp;
        node = NULL;
    }

    Node<T>* copy_const(const Node<T>* node){

        if(node == NULL){
            return NULL;
        }
           
        Node<T>* result = new Node<T>();
        
        result->element = node->element;
        result->left = copy_const(node->left);
        result->right = copy_const(node->right);

        return result;
    }

    int getHeight(const Node<T>* node)const{
        
        if(node == NULL){
            return -1;
        }

        if(getHeight(node->right) >= getHeight(node->left)){
            return 1 + getHeight(node->right);

        }

        else{
            return 1 + getHeight(node->left);
        }
    }

    int getSize(const Node<T>* node)const{

        if(node == NULL){
            return 0;
        }

        return 1 + getSize(node->left) + getSize(node->right);
        
    }


    T& getMin(Node<T>* node) const{
        
        if(node == NULL){
            throw NoSuchItemException();
        }

        if(node->left){
            return getMin(node->left);
        }

        else{
            return node->element;
        }

    }

    T& getMax(Node<T>* node) const{

        if(node == NULL){
            throw NoSuchItemException();
        }

        if(node->right){
            return getMax(node->right);
        }

        else{
            return node->element;
        }

    }

    const T& Ceil(Node<T>* root, const T& input) const {
        // Base case
        if (root == NULL)
            throw NoSuchItemException();

        // We found equal key
        if (root->element == input)
            return root->element;

        // If root's key is smaller, ceil must be in right
        // subtree
        if (root->element < input)
            return Ceil(root->right, input);

        // Else, either left subtree or root has the ceil value
        // T& ceil = Ceil(root->left, input);

        else{

            try{Ceil(root->left, input);}

            catch(NoSuchItemException a)
            {return root->element;}
            return Ceil(root->left, input);

        }
    }


    const T& Floor(Node<T>* root, const T& input) const {
        // Base case
        if (root == NULL)
            throw NoSuchItemException();

        // We found equal key
        if (root->element == input)
            return root->element;

        // If root's key is smaller, ceil must be in right
        // subtree
        if (root->element > input)
            return Floor(root->left, input);

        // Else, either left subtree or root has the ceil value
        // T& ceil = Ceil(root->left, input);

        else{

            try{Floor(root->right, input);}

            catch(NoSuchItemException a)
            {return root->element;}
            return Floor(root->right, input);

        }
    }


    const T& getNext(Node<T>* root, const T& input) const {
        // Base case
        if (root == NULL)
            throw NoSuchItemException();

        // We found equal key

        // If root's key is smaller, ceil must be in right
        // subtree
        if (root->element <= input)
            return getNext(root->right, input);

        // Else, either left subtree or root has the ceil value
        // T& ceil = Ceil(root->left, input);

        else{

            try{getNext(root->left, input);}

            catch(NoSuchItemException a)
            {return root->element;}
            return getNext(root->left, input);

        }
    }
    
    int storeInArray(Node<T>*ptr, T arr[], int i)
    {
        if (ptr == NULL)
            return i;
        
        i = storeInArray(ptr->left, arr, i);
        arr[i++] = ptr->element;
        return storeInArray(ptr->right, arr, i);
    }


    void balance(Node<T>*& node){
        
        int size = getSize(node);
        T* arr = new T[size];
        
        storeInArray(node, arr, 0);
        removeAllNodes(node);
        
        node = NULL;
        binary_search_builder(node, arr, 0, size-1);
        
        delete[] arr;
        
    }
        
    
    void binary_search_builder(Node<T>*& node, T arr[], int low, int high){

        if(high >= low){
            int mid = (low + high)/2;
        
            node = new Node<T>();
            node->element = arr[mid];
            
            binary_search_builder(node->left, arr, low, mid-1);
            binary_search_builder(node->right, arr, mid+1, high);

        }
    }
    
    const T& get(Node<T>* node, const T&element) const{
        
        if(node == NULL){
            throw NoSuchItemException();
        }
        
        if(node->element == element){
            return node->element;
        }
        
        else{
            
            if(node->element > element){
                return get(node->left, element);
            }
            
            else{
                return get(node->right, element);
            }
        }
    }


    Node<T>*& getNode(Node<T>*& node, const T&element) const{
        
        if(node == NULL){
            throw NoSuchItemException();
        }
        
        if(node->element == element){
            return node;
        }
        
        else{
            
            if(node->element > element){
                return get(node->left, element);
            }
            
            else{
                return get(node->right, element);
            }
        }
    }

    
    void Insert_to_right_place(Node<T>*& node, const T &element){
        
        if(node == NULL){
            node = new Node<T>();

            node -> element = element;
            upperBound++;
        }
        
        else if(node->element > element){
            Insert_to_right_place(node->left, element);
        
            int height = getHeight();
            if( height > (log(upperBound)/log(1.5) )){
                
                int size_of_node = getSize(node);
                int size_of_child = getSize(node->left);
                
                if( ((float)size_of_child/size_of_node) > (float)2/3 ){
             
                   balance(node);       
                  
                }
            }
        }
        
        else{
            Insert_to_right_place(node->right, element);
            
            int height = getHeight();
            if( height > (log(upperBound)/log(1.5) )){
                
                int size_of_node = getSize(node);
                int size_of_child = getSize(node->right);
             
                if( ((float)size_of_child/size_of_node) > (float)2/3 ){
             
                    balance(node);       
                  
                }   
            }
        }
    }

    void remove(Node<T>*& node, const T &element){

        // this will have a side effect and return the boolean value
        // we assume that it is inside the tree

        if(node == NULL){
            return;
        }

        if(node->element > element){
            remove(node->left, element);
        }

        else if(node->element < element){
            remove(node->right, element);
        }

        else{

            if(node->left == NULL and node->right == NULL){

                //no child Maybe there can be some problems occur here 

                Node<T>* temp = node;
                delete temp;
                node = NULL;

            }

            else if(node->left != NULL and node->right == NULL){
                
                // one child
                
                Node<T>* temp = node;
                node = node->left; 
                delete temp;
                

            }

            else if(node->left == NULL and node->right != NULL){

                // one child
                Node<T>* temp = node;
                node = node->right; 
                delete temp;
                
                
            }

            else if(node->left != NULL and node->right != NULL){
                
                // two childs
                
                node->element = getMax(node->left);
                remove(node->left, node->element);
                
            }
        }
    }
        

private: 
    Node<T> *root;
    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    
    root = NULL;
    upperBound = 0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    
    root = copy_const(obj.root);
    upperBound = obj.upperBound;

}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    removeAllNodes();

}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    return root == NULL;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    return getHeight(root);

}

template<class T>
int ScapegoatTree<T>::getSize() const {
    return getSize(root);
    
    // log(upperbound)/log(3/2)

}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    
    try{get(root, element);}
    catch(NoSuchItemException a)
    {

        // Node<T>* new_node = new Node<T>();
        // new_node->element = element;
        
        Insert_to_right_place(root, element);

        return true;
        
    }
    
    // BURASI ELSE Gibi iste burayı yapmak lazım return getNext(root->left, input);
    // Side effect + return true
    return false;   
}


template<class T>
bool ScapegoatTree<T>::remove(const T &element) {

    try{get(root, element);}
    catch(NoSuchItemException a)
    {
        return false;        
    }

    remove(root, element);

    if(upperBound/2.0 <= getSize(root) and getSize(root) <= upperBound){

    }

    else{
        
        balance();
        upperBound = getSize(root);
    }
    
    return true; 
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {

    removeAllNodes(root);
    upperBound=0;
    root = NULL;
    
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    return get(root, element);
    
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;



    } 
    
    else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
    
    else if (tp == postorder) {
        
        // check if the tree is empty?
        
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).

        //output the node.
        std::cout << "\t" << node->element;

        if (node->left) {
            std::cout << "," << std::endl;
        }

        print(node->left, preorder);

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);

    } 
    
    
    else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    
    
    else if (tp == postorder) {

        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
         
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // finally, output comma (if needed) and the right subtree.
        print(node->right, postorder);
        
        if (node->right) {
            std::cout << "," << std::endl;
        }

        //output node
        std::cout << "\t" << node->element;

    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    
    if(this == &rhs){
    	return *this;
    
    }
    
    else{
	    removeAllNodes();

	    root = copy_const(rhs.root);
	    upperBound = rhs.upperBound;
	    
	    return *this;}


}

template<class T>
void ScapegoatTree<T>::balance() {
    balance(root);
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    return Ceil(root, element);

}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    return Floor(root, element);

}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
    return(getMin(root));


}

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    return(getMax(root));

}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    return getNext(root, element);
}
