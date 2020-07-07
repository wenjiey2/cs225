/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode* temp;
  while(head_ != NULL){
  	temp = head_->next;
  	delete head_;
  	head_ = temp;
  }
  head_ = NULL;
  tail_ = NULL;
  temp = NULL;
  length_ = 0;

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if(length_ == 0){
    head_ = new ListNode(ndata);
    head_->next = NULL;
    head_->prev = NULL;
    tail_ = head_;
  }
  else{
    ListNode* front = new ListNode(ndata);
    head_->prev = front;
    front->next = head_;
    front->prev = NULL;
    head_ = front;
  }
  length_ ++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if(length_ == 0){
    head_ = new ListNode(ndata);
    head_->next = NULL;
    head_->prev = NULL;
    tail_ = head_;
  }
  else{
    ListNode* back = new ListNode(ndata);
    tail_->next = back;
    back->prev = tail_;
    tail_ = back;
    tail_->next = NULL;
  }
  length_ ++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {

  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if(startPoint == endPoint || startPoint == NULL || endPoint == NULL){
    return;
  }

  ListNode* start = startPoint;
  ListNode* startTemp = startPoint;
  ListNode* startPrev = startPoint->prev;
  ListNode* endNext = endPoint->next;
  ListNode* end = endPoint;

  while(start != endPoint){
    ListNode* temp = start->next;
    start->next = start->prev;
    start->prev = temp;
    start = start->prev;
  }

  start->next = start->prev;

  if(startPrev != NULL){
    start->prev = startPrev;
  }

  if(startPoint != head_){
    startPrev->next = start;
    startTemp->next = endNext;
  } else{
    head_ = start;
    head_->prev = NULL;
  }
  if(endNext == NULL){
    tail_ = startTemp;
    tail_->next = NULL;
  } else{
    endNext->prev = startTemp;
  }
  endPoint = startTemp;
  startPoint = end;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if(head_ == NULL || n == 0){
    return;
  }
  ListNode * start = head_;
  ListNode * end = head_;
  ListNode * temp1;
  ListNode * temp2;

  if(n >= length_){
    temp1 = head_;
    temp2 = tail_;
    reverse(temp1, temp2);
  } else if(n < length_){

    while(start != NULL && start->next != NULL){
      end = start;

      for(int i = 0; i < n-1; i++){
        if(end->next != NULL){
          end = end->next;
        }
      }
      ListNode* endNext = end->next;

      temp1 = start;
      temp2 = end;
      reverse(temp1, temp2);
      start = endNext;
    }
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if(head_ == NULL || head_->next == NULL){
    return;
  }

  ListNode* curr = head_;

  ListNode* temp;
  while(curr->next != tail_ && curr->next != NULL){
    temp = curr->next;
    tail_->next = temp;
    temp->prev = tail_;
    curr->next = temp->next;
    temp->next->prev = curr;
    curr = temp->next;
    tail_ = temp;
    tail_->next = NULL;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if(start == NULL || splitPoint == 0){
    return start;
  }

  ListNode* split = start;
	for(int i = 0; i < splitPoint - 1; i++){
		split = split->next;
  }
  ListNode* newHead = split->next;
	split->next = NULL;
  if(newHead != NULL){
    newHead->prev = NULL;
  }

	return newHead;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* thru1 = first;
  ListNode* thru2 = second;
  ListNode* curr;
  ListNode* start;

  if(thru1->data < thru2->data){
    curr = thru1;
    thru1 = thru1->next;
  } else{
    curr = thru2;
    thru2 = thru2->next;
  }

  start = curr;

  while(thru1 != NULL && thru2 != NULL){
    if(thru1->data < thru2->data){
      curr->next = thru1;
      thru1->prev = curr;
      thru1 = thru1->next;
    } else{
      curr->next = thru2;
      thru2->prev = curr;
      thru2 = thru2->next;
    }
    curr = curr->next;
  }

  if(thru1 != NULL){
    curr->next = thru1;
    thru1->prev = curr;
  } else if(thru2 != NULL){
    curr->next = thru2;
    thru2->prev = curr;
  }

  return start;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode* temp = start;
  if(chainLength == 1){
    start->next = NULL;
    start->prev = NULL;
    return start;
  }
  if(chainLength > 1){
    int subLength = chainLength / 2;
    for(int i = 0; i < subLength; i++){
      temp = temp->next;
    }
    ListNode* left = mergesort(start, subLength);
    ListNode* right = mergesort(temp, chainLength - subLength);
    return merge(left, right);
  }

  return NULL;
}
