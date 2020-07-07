#include "list.h"
#include "iostream"

using namespace std;
int main() {
  List<int> *temp = new List<int>();
  List<int> list;
  temp->insertFront(8);
  temp->insertFront(5);
  temp->insertFront(4);
  temp->insertFront(2);
  temp->insertFront(9);
  temp->insertFront(7);
  temp->insertFront(6);
  temp->insertFront(1);
  temp->insertFront(3);

  temp->print(cout);
  temp->sort();
  temp->print(cout);
  delete temp;
  return 0;
}
