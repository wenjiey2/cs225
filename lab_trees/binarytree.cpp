/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node*& root){
  if(root->left == NULL && root->right == NULL){
    return;
  }
  if(root->left != NULL && root->right == NULL){
    root->right = root->left;
    root->left = NULL;
    mirror(root->right);
  } else if(root->right != NULL && root->left == NULL){
    root->left = root->right;
    root->right = NULL;
    mirror(root->left);
  } else if(root->right != NULL && root->left != NULL){
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
  }
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    return isOrderedI(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedI(typename BinaryTree<T>::Node* root) const{
  InorderTraversal<T> iot(root);
  int prev = 0;
  int next = 0;
	for(typename TreeTraversal<T>::Iterator it = iot.begin(); it != iot.end(); ++it) {
    prev = next;
    next = (*it)->elem;
    if(next < prev){
      return false;
    }
  }
  return true;
}


/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{

    // your code here
    return isOrderedR(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedR(const Node* root) const{
  if(root == NULL){
    return true;
  } else if(root->left == NULL && root->right == NULL){
      return true;
    } else if(root->left != NULL && root->right == NULL){
      return root->left->elem < root->elem;
    } else if(root->right != NULL && root->left == NULL){
      return root->elem < root->right->elem;
    } else {
      return isOrderedR(root->left) && isOrderedR(root->right) &&
      root->left->elem < root->elem && root->elem < root->right->elem;
    }
}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here
    vector<T> curr;
    printP(paths, root, curr);
}

template <typename T>
void BinaryTree<T>::printP(vector<vector<T> > &paths, const Node* subRoot, vector<T> curr) const{
  if(subRoot == NULL){
    return;
  }
  curr.push_back(subRoot->elem);
  if((subRoot->left == NULL) && (subRoot->right == NULL)){
   paths.push_back(curr);
   return;
  }
  if(subRoot->left != NULL){
   printP(paths, subRoot->left, curr);
  }
  if(subRoot->right != NULL){
   printP(paths, subRoot->right, curr);
  }
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int sum = 0;
    return sumDist(0, root, sum);
}

template <typename T>
int & BinaryTree<T>::sumDist(int dist, const Node* subRoot, int &sum) const{
	sum += dist;
	if(subRoot->left != NULL){
		sum = sumDist(dist + 1, subRoot->left, sum);
  }
	if(subRoot->right != NULL){
		sum = sumDist(dist + 1, subRoot->right, sum);
  }
	return sum;
}
