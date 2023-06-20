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

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    int getNodeHeight(Node<T> *node) const;
    int getNodeSize(Node<T> *node) const;
    bool contains(Node<T> *node, const T &element) const;
    void removeAllNodesHelp(Node<T> *&node);
    void insertNodeAsChild(Node<T> *node, const T &element);
    void removeNode(Node<T> *node, const T &element);
    Node<T> *getNodeMax(Node<T> *node) const;
    Node<T> *getParentNode(Node<T> *help, Node<T> *node) const;
    void copy(Node<T> *&root1, Node<T> *root2);
    void initializeArray(Node<T> *node, T *arr, int &i);
    void initializeTree(T *arr, int i, int j);
    void initializeRetardTree(T *arr, int i, int j);
    void balanceInsert(Node<T> *node);
    void insertionBalance(const T &element);
    Node<T> *getNode(Node<T> *node, const T &element) const;
    Node<T> *getParentNodeElem(Node<T> *help, const T &element) const;
    bool insertAlt(const T &element);
    const T getCeilingHelp(Node<T> *node, const T &element);

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;
    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    root = NULL;
    upperBound = 0;
}//DONE

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    if(obj.root == NULL){
        root = NULL;
        upperBound = 0;
    }
    else{
        upperBound = 0;
        root = NULL;
        copy(root, obj.root);
        this->upperBound = obj.upperBound;
    }
}//DONE

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    removeAllNodes();
}//DONE

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    return (root == NULL);
}//DONE

template<class T>
int ScapegoatTree<T>::getHeight() const {
    return getNodeHeight(root);
}//DONE

template<class T>
int ScapegoatTree<T>::getNodeHeight(Node<T> *node) const {
    if(node == NULL){
        return -1;
    }
    if (node->right == NULL && node->left == NULL){
        return 0;
    }
    else if(getNodeHeight(node->left) >= getNodeHeight(node->right)){
        return getNodeHeight(node->left) + 1;
    }
    else if(getNodeHeight(node->right) >= getNodeHeight(node->left)){
        return getNodeHeight(node->right) + 1;
    }
}//DONE

template<class T>
int ScapegoatTree<T>::getSize() const {
    return getNodeSize(root);
}//DONE

template<class T>
int ScapegoatTree<T>::getNodeSize(Node<T> *node) const {
    if(node == NULL){
        return 0;
    }
    if (node->right == NULL && node->left == NULL){
        return 1;
    }
    else if(node->right == NULL && node->left != NULL){
        return getNodeSize(node->left) + 1;
    }
    else if(node->left == NULL && node->right != NULL){
        return getNodeSize(node->right) + 1;
    }
    else if(node->left != NULL && node->right != NULL){
        return getNodeSize(node->right) + getNodeSize(node->left) + 1;
    }
}//DONE

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    if(isEmpty()){ //DEFAULT CASE
        Node<T> *crt = new Node<T>(element, NULL, NULL);
        root = crt;
        upperBound = 1;
        return true;
    }
    else{
        if(contains(root, element)){
            return false;
        }
        else{
            insertNodeAsChild(root, element);
            upperBound++;
            
            float res = log(upperBound) / log(1.5);
            
            if(getHeight() > res){
                insertionBalance(element);
            }
            
            return true;
        }
    }
}//DONE

template<class T>
bool ScapegoatTree<T>::insertAlt(const T &element) {
    if(isEmpty()){ //DEFAULT CASE
        Node<T> *crt = new Node<T>(element, NULL, NULL);
        root = crt;
    }
    else{
        if(contains(root, element)){
            return false;
        }
        else{
            insertNodeAsChild(root, element);
            return true;
        }
    }
}//DONE

template<class T>
void ScapegoatTree<T>::insertionBalance(const T &element) {
    Node<T> *node = getParentNodeElem(root, element);
    while(!(3*getNodeSize(node) > 2*getNodeSize(getParentNode(root, node)))){
        node = getParentNode(root, node);
    }
    balanceInsert(getrentNode(root, node));
}Pa

template<class T>
void ScapegoatTree<T>::balanceInsert(Node<T> *node) {
    if(node != root){
        int i = getSize();
        T *arr = new T[i];
        i = 0;
        initializeArray(node, arr, i);
        int j = getNodeSize(node);
        i = 1;
        Node<T> *scapegoat = node;
        Node<T> *parent = getParentNode(root, node);
        removeAllNodesHelp(scapegoat);
        if(parent->left == node){
            parent->left = NULL;
        }
        else if(parent->right == node){
            parent->right = NULL;
        }
        initializeTree(arr, i, j);
        delete [] arr;
    }
    else{
        balance();
    }
}

template<class T>
void ScapegoatTree<T>::initializeTree(T *arr, int i, int j) {
    if(i <= j){
        int mid = (i+j)/2;
        insertAlt(arr[mid-1]);
        initializeTree(arr, i, mid - 1);
        initializeTree(arr, mid + 1, j);
    }
}

template<class T>
void ScapegoatTree<T>::initializeRetardTree(T *arr, int i, int j) {
    if(i <= j){
        int mid = (i+j)/2;
        insert(arr[mid-1]);
        initializeRetardTree(arr, i, mid - 1);
        initializeRetardTree(arr, mid + 1, j);
    }
}

template<class T>
void ScapegoatTree<T>::insertNodeAsChild(Node<T> *node, const T &element){
    if(node->element > element){
        if(node->left == NULL){
            Node<T> *crt = new Node<T>();
            crt->element = element;
            node->left = crt;
            crt->left = NULL;
            crt->right = NULL;
        }
        else{
            insertNodeAsChild(node->left, element);
        }
    }
    else if(node->element < element){
        if(node->right == NULL){
            Node<T> *crt = new Node<T>();
            crt->element = element;
            node->right = crt;
            crt->left = NULL;
            crt->right = NULL;
        }
        else{
            insertNodeAsChild(node->right, element);
        }
    }
}//DONE

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    if(contains(root, element)){
        removeNode(root, element);
        if(upperBound > 2*getSize() || 2*getSize() > 2*upperBound){
            balance();
        }
        return true;
    }
    else{
        return false;
    }
}//DONE (BALANCE ADDED)

template<class T>
void ScapegoatTree<T>::removeNode(Node<T> *node, const T &element) {
    if (node == NULL){
        return;
    }
    else if (node->element > element){
        removeNode(node->left, element);
    }
    else if (node->element < element){
        removeNode(node->right , element);
    }
    else{
        if (node->left != NULL && node->right != NULL) {
            T elem = (getNodeMax(node->left))->element;
            removeNode(node->left, (getNodeMax(node->left))->element);
            node->element = elem;
        }
        else if (node->left != NULL || node->right != NULL){
            if(node == root){
                Node<T> *del = node;
                if(node->left != NULL){
                    root = root->left;
                    node->left = NULL;
                }
                else if(node->right != NULL){
                    root = root->right;
                    node->right = NULL;
                }
                delete del;
                node = NULL;
            }
            else{
                Node<T> *parent = getParentNode(root, node);
                if(node->left != NULL){
                    if(parent->right != NULL && node->element == parent->right->element){
                        parent->right = node->left;
                    }
                    else if(parent->left != NULL && node->element == parent->left->element){
                        parent->left = node->left;
                    }
                }
                else if(node->right != NULL){
                    if(parent->right != NULL && node->element == parent->right->element){
                        parent->right = node->right;
                    }
                    else if(parent->left != NULL && node->element == parent->left->element){
                        parent->left = node->right;
                    }
                }
                Node<T> *del = node;
                delete del;
                node = NULL;
            }
        }
        else{
            if(node == root){
                Node<T> *del = node;
                delete del;
                node = NULL;
                root = NULL;
            }
            else{
                Node<T> *parent = getParentNode(root, node);
                if(parent->right != NULL)
                {if(node->element == parent->right->element)
                    {getParentNode(root, node)->right = NULL;}}
                if(parent->left != NULL)
                {if(node->element == parent->left->element)
                    {getParentNode(root, node)->left = NULL;}}
                Node<T> *del = node;
                delete del;
                node = NULL;
            }
        }
    }
}//DONE

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    removeAllNodesHelp(root);
    root = NULL;
    upperBound = 0;
}//DONE

template<class T>
void ScapegoatTree<T>::removeAllNodesHelp(Node<T> *&node) {
    if(node == NULL){
        return;
    }
    if(node->left != NULL){
        removeAllNodesHelp(node->left);
    }
    if(node->right != NULL){
        removeAllNodesHelp(node->right);
    }
    Node<T> *del = node;
    delete del;
    node = NULL;
}//DONE

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    Node<T> *crp = root;
    while(crp){
        if(crp->element == element){
            return crp->element;
        }
        else if(crp->element > element){
            crp = crp->left;
        }
        else if(crp->element < element){
            crp = crp->right;
        }
    }
    throw NoSuchItemException();
}//DONE

template<class T>
bool ScapegoatTree<T>::contains(Node<T> *node, const T &element) const {
    if(node == NULL){
        return false;
    }
    else{
        if(node->element == element){
            return true;
        }
        else{
            if(contains(node->right, element) == true || contains(node->left, element) == true){
                return true;
            }
            else{
                return false;
            }
        }
    }
}//DONE

template<class T>
Node<T> *ScapegoatTree<T>::getNode(Node<T> *node, const T &element) const{
    if(node->element == element){
        return node;
    }
    else{
        if(contains(node->right, element)){
            getNode(node->right, element);
        }
        else if(contains(node->left, element)){
            getNode(node->left, element);
        }
    }
}//DONE

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
    } else if (tp == inorder) {
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
    } else if (tp == postorder) {
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
}//DONE

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        if (node == NULL)
          return;
          
        std::cout << "\t" << node->element;
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);

        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    } else if (tp == inorder) {
        if (node == NULL)
          return;

        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        std::cout << "\t" << node->element;

        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == postorder) {
        if (node == NULL)
          return;

        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }

        std::cout << "\t" << node->element;
    }
}//DONE

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

}//DONE

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
}//DEFAULT

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    if(this !=&rhs){
        removeAllNodes();
        copy(root, rhs.root);
        this->upperBound = rhs.upperBound;
    }
    return *this;
}//DONE

template<class T>
void ScapegoatTree<T>::copy(Node<T> *&root1, Node<T> *root2){
    if (root2 != NULL){
        root1 = new Node<T>(root2->element, NULL, NULL);
        copy(root1->left, root2->left);
        copy(root1->right, root2->right);
    }
    else{
        root1 = NULL;
    }
}//DONE

template<class T>
void ScapegoatTree<T>::balance() {
    if(root != NULL){
        int i = getSize();
        T *arr = new T[i];
        i = 0;
        initializeArray(root, arr, i);
        int j = getSize();
        i = 1;
        int upp = upperBound;
        removeAllNodes();
        initializeRetardTree(arr, i, j);
        delete [] arr;
    }
}

template<class T>
void ScapegoatTree<T>::initializeArray(Node<T> *node, T *arr, int &i){
    
    if(node!= NULL){
        if(node->left != NULL){
            initializeArray(node->left, arr, i);
        }
        
        arr[i] = node->element;
        i++;
        
        if(node->right != NULL){
            initializeArray(node->right, arr, i);
        }
    }
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    if(isEmpty()){
        throw NoSuchItemException();
    }
    else{
        Node<T> *crp = root;
        Node<T> *ceils = NULL;
        while(crp){
            if(crp->element >= element){
                if(ceils == NULL || ceils->element > crp->element){
                    ceils = crp;
                }
                crp = crp->left;
            }
            else{
                crp = crp->right;
            }
        }
        if(ceils == NULL) throw NoSuchItemException();
        else return ceils->element;
    }
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    if(isEmpty()){
        throw NoSuchItemException();
    }
    else{
        Node<T> *crp = root;
        Node<T> *ceils = NULL;
        while(crp){
            if(crp->element <= element){
                if(ceils == NULL || ceils->element < crp->element){
                    ceils = crp;
                }
                crp = crp->right;
            }
            else{
                crp = crp->left;
            }
        
        }
        if(ceils == NULL) throw NoSuchItemException();
        else return ceils->element;
    }
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
    if(!isEmpty()){
        Node<T> *crp = root;
        while(crp->left){
            crp=crp->left;
        }
        return crp->element;
    }
    else{
        throw NoSuchItemException();
    }
}//DONE

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    if(!isEmpty()){
        Node<T> *crp = root;
        while(crp->right){
            crp=crp->right;
        }
        return crp->element;
    }
    else{
        throw NoSuchItemException();
    }
}//DONE

template<class T>
Node<T> *ScapegoatTree<T>::getNodeMax(Node<T> *node) const{
    Node<T> *crp = node;
    while(crp->right){
        crp=crp->right;
    }
    return crp;
}//DONE

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    if(isEmpty()){
        throw NoSuchItemException();
    }
    else{
        Node<T> *crp = root;
        Node<T> *ceils = NULL;
        while(crp){
            if(crp->element > element){
                if(ceils == NULL || ceils->element > crp->element){
                    ceils = crp;
                }
                crp = crp->left;
            }
            else{
                crp = crp->right;
            }
        
        }
        if(ceils == NULL) throw NoSuchItemException();
        else return ceils->element;
    }
}

template<class T>
Node<T>* ScapegoatTree<T>::getParentNode(Node<T> *help, Node<T> *node) const{
    if(((help->right != NULL) && (help->right->element == node->element)) || ((help->left != NULL) && (help->left->element == node->element))){
        return help;
    }
    else{
        if(contains(help->right, node->element)){
            return getParentNode(help->right, node);
        }
        else{
            return getParentNode(help->left, node);
        }
    }
}//DONE

template<class T>
Node<T>* ScapegoatTree<T>::getParentNodeElem(Node<T> *help, const T &element) const{
    if(((help->right != NULL) && (help->right->element == element)) || ((help->left != NULL) && (help->left->element == element))){
        return help;
    }
    else{
        if(contains(help->right, element)){
            return getParentNodeElem(help->right, element);
        }
        else{
            return getParentNodeElem(help->left, element);
        }
    }
}//DONE
