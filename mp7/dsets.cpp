/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
  for(int i = 0; i < num; i++){
    set.push_back(-1);
  }
}

int DisjointSets::find(int elem){
  if(set[elem] < 0){
    return elem;
  } else{
    set[elem] = find(set[elem]);
    return set[elem];
  }
}

void DisjointSets::setunion(int a, int b){
  int root1 = find(a);
  int root2 = find(b);
  if(root1 == root2){
    return;
  }
  int newRoot = set[root1] + set[root2];
  if(set[root1] > set[root2]){
    set[root1] = root2;
    set[root2] = newRoot;
  } else{
    set[root2] = root1;
    set[root1] = newRoot;
  }
}

int DisjointSets::size(int elem){
  int count = 1;
  if(set[elem] < 0){
    return count;
  } else{
    count += size(set[elem]);
    return count;
  }
}

void DisjointSets::clearSet(){
  while(!set.empty()){
    set.pop_back();
  }
}
