/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if(curDim < Dim && curDim >= 0){
       if(first[curDim] != second[curDim]){
         return first[curDim] < second[curDim];
       } else{
         return first < second;
       }
     }
     return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double d1 = getDistance(target, currentBest);
     double d2 = getDistance(target, potential);
     if(d2 < d1){
       return true;
     } else if(d2 > d1){
       return false;
     } else {
       return potential < currentBest;
     }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     size = newPoints.size();
     if(size > 0){
       for(size_t i = 0; i < size; i++){
         points.push_back(newPoints[i]);
       }
       root = buildTree(0, size - 1, 0);
     } else{
       root = NULL;
     }
}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(int start, int end, int d){
  int mid = (start + end) / 2;
  quickSelect(start, end, d, mid);
  KDTreeNode* subroot = new KDTreeNode(points[mid]);
  if(start <= mid - 1){
    subroot->left = buildTree(start, mid - 1, (d + 1) % Dim);
  }
  if(end >= mid + 1){
    subroot->right = buildTree(mid + 1, end, (d + 1) % Dim);
  }
  return subroot;
}

template<int Dim>
void KDTree<Dim>::quickSelect(int start, int end, int d, int mid){
  if(start >= end){
    return;
  }
  int initP = (start + end) / 2;
  int pIndex = partition(start, end, initP, d);
  if(mid == pIndex){
    return;
  }
  else if(mid < pIndex){
    quickSelect(start, pIndex - 1, d, mid);
  }
  else{
    quickSelect(pIndex + 1, end, d, mid);
  }
}

template<int Dim>
int KDTree<Dim>::partition(int start, int end, int pIndex, int d){
    Point<Dim> pVal = points[pIndex];
    swap(points[pIndex], points[end]);
    int part = start;
    for(int i = start; i < end; i++)
    {
        if(smallerDimVal(points[i], pVal, d))
        {
            std::swap(points[part], points[i]);
            part++;
        }
    }
    std::swap(points[end], points[part]);
    return part;
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
   size = other.size;
	 root = other.root;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
   KDTree<Dim> copy = new KDTree(rhs);
   return copy;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
	 size = 0;
}

template <int Dim>
void KDTree<Dim>::clear(KDTree<Dim>::KDTreeNode* subroot) {
	if (subroot == NULL){
    return;
  } else{
    if(subroot->left != NULL && subroot->right != NULL){
      clear(subroot->left);
      clear(subroot->right);
      delete subroot;
    } else if(subroot->left == NULL && subroot->right != NULL){
      clear(subroot->right);
      delete subroot;
    } else if(subroot->left != NULL && subroot->right == NULL){
      clear(subroot->left);
      delete subroot;
    } else{
      delete subroot;
    }
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     if(points.size() == 0){
        return Point<Dim>();
     }
     return findNearest(query, root, 0);
}

template<int Dim>
double KDTree<Dim>::getDistance(const Point<Dim> & p1, const Point<Dim> & p2) const{
  double distance = 0;
	for(int i = 0; i < Dim; i++){
		distance += (p1[i] - p2[i]) * (p1[i] - p2[i]);
  }
	return sqrt(distance);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearest(const Point<Dim>& query, KDTreeNode* subroot, int d) const{
  Point<Dim> nearest = subroot->point;
  Point<Dim> pnearest;
  double radius = 0;
  double distance = 0;
  if(subroot->left == NULL && subroot->right == NULL){
    return nearest;
  }

  if(smallerDimVal(query, nearest, d) && subroot->left != NULL){
    nearest = findNearest(query, subroot->left, (d + 1) % Dim);
    radius = getDistance(nearest, query);
    distance = abs(subroot->point[d] - query[d]);

    if(shouldReplace(query, nearest, subroot->point)){
      nearest = subroot->point;
      radius = getDistance(nearest, query);
    }
    if(distance <= radius && subroot->right != NULL){
      pnearest = findNearest(query, subroot->right, (d + 1) % Dim);
      if(shouldReplace(query, nearest, pnearest)){
        nearest = pnearest;
      }
    }
    if(shouldReplace(query, nearest, subroot->point)){
      nearest = subroot->point;
      radius = getDistance(nearest, query);
    }

  } else if(smallerDimVal(nearest, query, d) && subroot->right != NULL){
    nearest = findNearest(query, subroot->right, (d + 1) % Dim);
    radius = getDistance(nearest, query);
    distance = abs(subroot->point[d] - query[d]);

    if(shouldReplace(query, nearest, subroot->point)){
      nearest = subroot->point;
      radius = getDistance(nearest, query);
    }
    if(distance <= radius && subroot->left != NULL){
      pnearest = findNearest(query, subroot->left, (d + 1) % Dim);
      if(shouldReplace(query, nearest, pnearest)){
        nearest = pnearest;
      }
    }
    if(shouldReplace(query, nearest, subroot->point)){
      nearest = subroot->point;
      radius = getDistance(nearest, query);
    }
  }
  return nearest;
}
