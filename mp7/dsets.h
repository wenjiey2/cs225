/* Your code here! */
#ifndef DSETS_H
#define DSETS_H

#include <vector>

class DisjointSets{
public:
  /**
   * This function creates n unconnected root nodes at the end of the vector.
   *
   * @param The number of nodes to create
   **/
  void addelements(int num);

  /**
   * This function should compress paths and find the root of the uptree
   *
   * @param The element to do path compression on
   * @return the index of the root of the up-tree of parameter elem
   **/
  int find(int elem);

  /**
   * This function should be implemented as union-by-size
   *
   * @param a	Index of the first element to union
   * @param b	Index of the second element to union
   **/
  void setunion(int a, int b);

  /**
   * This function should compute the size of the uptree containing the element
   *
   * @param The element of the uptree
   * @return size of the uptree
   **/
  int size(int elem);
  
  void clearSet();

private:
  // A vector containing all the disjoint sets
  std::vector<int> set;
};

#endif
