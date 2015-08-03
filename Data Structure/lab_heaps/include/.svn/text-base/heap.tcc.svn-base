/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::left_child(size_t idx) const
{
    /// @todo Update to return the index of the left child.
    return idx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::right_child(size_t idx) const
{
    /// @todo Update to return the index of the left child.
    return idx*2+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t idx) const
{
    /// @todo Update to return the parent index.
    return idx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::has_child(size_t idx) const
{
    /// @todo Update to return whether the node at index has a child.
    return idx*2<elems_.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::max_priority_child(size_t idx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t leftchild=left_child(idx);
    size_t rightchild=right_child(idx);
    if (idx*2+1<elems_.size())
        return (higher_priority_(elems_[leftchild],elems_[rightchild]))?leftchild:rightchild;
    else return idx*2;

    //return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapify_down(size_t idx)
{
   if (has_child(idx))
{
  size_t childIdx=max_priority_child(idx);
    if (higher_priority_(elems_[childIdx],elems_[idx]))
    {
     std::swap(elems_[idx],elems_[childIdx]);
     heapify_down(childIdx);
    }

} 

   /// @todo Implement the heapifyDown algorithm.
}

template <class T, class Compare>
void heap<T, Compare>::heapify_up(size_t idx)
{
    if (idx == root())
        return;
    size_t parentIdx = parent(idx);
    if (higher_priority_(elems_[idx], elems_[parentIdx]))
    {
        std::swap(elems_[idx], elems_[parentIdx]);
        heapify_up(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
elems_.push_back(0);

  
   /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
   elems_.push_back(0);
    for (int i = 0; i < elems.size(); i++)
    {
        elems_.push_back(elems[i]);
    }
    for (int i = parent(elems_.size()); i > 0; i--)
    {
        heapify_down(i);
    }
   /// @todo Construct a heap using the buildHeap algorithm
}

template <class T, class Compare>
void heap<T, Compare>::pop()
{
  //	T retval=elems_[1];
  elems_[1]=elems_[elems_.size()-1];
  elems_.pop_back(); 
 heapify_down(1);
   //return retval;
   /// @todo Remove the element with the highest priority.
}

template <class T, class Compare>
const T& heap<T, Compare>::peek() const
{
    /// @todo Return the element with the highest priority (do *not* remove!)
    return elems_[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(T elem)
{
    elems_.push_back(elem);
    heapify_up(elems_.size()-1);
   /// @todo Add an element to the heap
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return elems_.size()==1;
}
