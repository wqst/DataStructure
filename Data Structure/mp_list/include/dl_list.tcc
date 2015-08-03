/**
 * @file dl_list.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include <utility>
#include "dl_list.h"
#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <memory>
#include "rgba_pixel.h"


namespace cs225
{

template <class T>
dl_list<T>::dl_list()
:head_(nullptr),tail_(nullptr),size_(0)
{
    /// @todo mp_list.1
}

template <class T>
dl_list<T>::dl_list(const dl_list& other)
:tail_(other.tail_),size_(other.size())
{	head_.swap=other.head_.get();
   if (other.head_!=nullptr&&other.tail_!=nullptr&&other.size()!=0)
     {node* curr=other.head_.get();
     
      while (curr!=nullptr)
        {push_back(curr->data);
         curr=curr->next.get();}
      }
     
   /// @todo mp_list.1
    /// hint: re-use your push_X function(s)!
}

template <class T>
dl_list<T>::dl_list(dl_list&& other)
{
  swap(other);
  other.head_=nullptr;
  other.tail_=nullptr;
  other.size_=0;
   
    /// @todo mp_list.1
}

template <class T>
dl_list<T>& dl_list<T>::operator=(dl_list rhs)
{

   
   swap(rhs);
   
   //std::swap(head_,rhs.head_);
   //std::swap(tail_,rhs.tail_);
   //std::swap(size_,rhs.size_);
   return *this;
  /// @todo mp_list.1
}

template <class T>
void dl_list<T>::clear()
{
 node* next;
  while (head_!=nullptr)
   {(*next).swap(*(head_->next));
    
    head_.swap(*next);
   }
  
  
  size_=0;
}

template <class T>
void dl_list<T>::swap(dl_list& other)
{ tail_=other.tail_;
  size_=other.size_;
  head_.swap(other.head_);
 /**dl_list c(std::move(this));
 this=std::move(other);
 other=std::move(c);**/
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::push_front(T data)
{node* n=new node{data};
std::unique_ptr<node> a{n};
 //a->next=std::move(head_);
 a->prev=nullptr;
if (head_!=nullptr)
   { a->next.swap(head_);
     a->next->prev=a.get();
     head_.swap(a);
}
else 
   {
    a->next=nullptr;
    tail_=a.get();
    head_=std::move(a);
   }
   
   //head_=std::move(a);
 //a=nullptr;
 size_++;
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::push_back(T data)
{node* n=new node{data};
 std::unique_ptr<node> a{n};
 a->next=nullptr;
 //a->prev=tail_;
 
if (tail_!=nullptr)
{ a->prev=tail_;
  a->prev->next=std::move(a);
tail_=tail_->next.get();
  }
else   
{a->prev=nullptr;
  head_=std::move(a);
tail_=head_.get();
  //a->prev=nullptr;
 }
 //a=nullptr;
 size_++;
//tail_=tail_->next.get();

    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::reverse()
{
    reverse(head_, tail_);
}

template <class T>
void dl_list<T>::reverse(std::unique_ptr<node>& first, node*& last)
{
 if (size_==0)
    return;
  
 if (first==nullptr||last==nullptr)
    return;
 node* t1=first.get();
 node* t2=last;
 node* temp1;
 node* temp2;
/**if (first.get()==head_.get()&&last==tail_)
{
 tail_=head_.get();
 //std::unique<ptr> temp==nullptr;
 tail_->prev->next.swap(head_);
  	
}**/
 
 while (t1!=t2&&t2!=t1->next.get()&&t1->prev!=nullptr&&t2->next!=nullptr&&(head_.get()!=first.get()&&tail_!=last))
 {
 temp1=t1->prev;
 temp2=t2->prev;
 t1->prev=t2->prev;
 t2->prev=temp1;
 t1->next->prev=t2;
 t2->next->prev=t1;  
 temp1->next.swap(temp2->next);
 t1->next.swap(t2->next);
 t1=temp1->next->next.get();
 t2=temp2;
 }

if ((t1->prev==nullptr&&t2->next==nullptr)||(head_.get()==first.get()&&tail_==last))
{ 
node* var;
var=t1;
temp1=t1->next.get();
  temp2=t2->prev;
  temp1->prev=t2;
  temp2->next.swap(head_);
  t1->prev=t2->prev;
  if (var->prev==nullptr)
  t2->prev=nullptr;
   else t2->prev=var->prev;
 //Is prev right?
  //if (t1->prev!=nullptr)
  
  t1->next.swap(t2->next);
  tail_=temp2->next.get();
  t1=temp1;
  t2=temp2;
    while (t1!=t2&&t2!=t1->next.get())
 {
 temp1=t1->prev;
 temp2=t2->prev;
 t1->prev=t2->prev;
 t2->prev=temp1;
 t1->next->prev=t2;
 t2->next->prev=t1;  
 temp1->next.swap(temp2->next);
 t1->next.swap(t2->next);
 t1=temp1->next->next.get();
 t2=temp2;
 }
}

else if (t1->prev==nullptr&&t2->next!=nullptr)//&&(head_.get()!=first.get()||tail_!=last))
{ 
  temp1=t1->next.get();
  temp2=t2->prev;
 t1->prev=t2->prev;
 t2->prev=nullptr;
 temp1->prev=t2;
 t2->next->prev=t1;
 t1->next.swap(t2->next);
 temp2->next.swap(head_->next);
 t1=temp1;
 t2=temp2;
    while (t1!=t2&&t2!=t1->next.get())
 {
 temp1=t1->prev;
 temp2=t2->prev;
 t1->prev=t2->prev;
 t2->prev=temp1;
 t1->next->prev=t2;
 t2->next->prev=t1;  
 temp1->next.swap(temp2->next);
 t1->next.swap(t2->next);
 t1=temp1->next->next.get();
 t2=temp2;
 }
}


 else if (t1->prev!=nullptr&&t2->next==nullptr)//&&(head_.get()!=first.get()||tail_!=last))
{temp1=t1->prev;
 temp2=t2->prev;
 t1->next->prev=t2;
 temp1->next.swap(temp2->next);
 t1->next.swap(t2->next);
  t1->prev=t2->prev;
  t2->prev=temp1;
 t1=t2->next.get();
t2=temp2; 




    while (t1!=t2&&t2!=t1->next.get())
 {
 temp1=t1->prev;
 temp2=t2->prev;
 t1->prev=t2->prev;
 t2->prev=temp1;
 t1->next->prev=t2;
 t2->next->prev=t1;  
 temp1->next.swap(temp2->next);
 t1->next.swap(t2->next);
 t1=temp1->next->next.get();
 t2=temp2;
 }
}

if(t2==t1->next.get())
{
 temp1=t1->prev;
 temp2=t2->next.get();
 t1->prev=t2;
 t2->prev=temp1;
 t2->next->prev=t1;
 t1->next.swap(temp1->next);
 t1->next.swap(t2->next);

}

/**if (first.get()==tail_&&last==head_.get())
{
 node* temp3=tail_->prev;
 tail_=head_.get();
 //std::unique<ptr> temp==nullptr;
 temp3->next.swap(head_);
  	
}**/

 /**     node* end1=last->next;
  node* start1=first->prev;
  node* temp=first;
  node* temp1;

 first=last;
 last=temp;
 temp1=first;

 while (temp1!=first&&temp1==nullptr)
{
  temp= temp1->next;
  temp1->next=temp1->prev;
  temp1->prev=temp;
  temp1=temp1->next;

}
  
  if(start1!=nullptr)
{
  start1->next=first;
  first->prev=start1;
}

 else
{  start->prev=nullptr;}

 if (end1!=nullptr)

{
  end1->prev=last;
  last->next=end1;
}
 else 
{
 last->=null;
}
 temp1=nullptr;
 temp=nullptr;
 end1=nullptr;
 start1=nullptr;**/
   /** 
   if(first==nullptr||last==nullptr||first==last)
     return;
   int c1=0;
   int c2=0;
   
    node* temp=first.get();
    
    
   while (temp->next!=nullptr)
    {
     c1++;
     //temp =temp->next.get();
    temp=temp->next.get();
   }
    temp=last;
    
    while (temp->next!=nullptr)
    {
     c2++;
     temp=temp->next.get();
    }
    
    if (c1<c2)
      return;
 
    node* work=temp;
    
    while(work!=last)
    {
      temp=work->prev;
      work->prev=work->next.get();
      work->next.swap(temp->prev->next);
      work=work->prev;
     
    }
    temp=work->prev;
    work->prev=work->next.get();
    work->next.swap(temp->prev->next);

    temp =first->next.get();
    node* temp2=first->prev;
    first->next.swap(last->prev->prev->next);//
    last->prev=temp;
  
    if (last->prev!=nullptr)
       last->prev->next.swap(last->prev->next);
    else 
       head_.swap(last->prev->next);

    if (first->next!=nullptr)
       first->next->prev=first.get();
    else
       tail_=first.get();

    temp= first.get();
    first.swap(last->prev->next);
    last=temp;
 
    **/

    /// @todo mp_list.1
}

/**template <class T>
void dl_list<T>::reverseNth( int n )
{
    /// @todo Graded in MP3.1

    //nothing is idiotproof to a sufficiently trained idiot
    if(n <= 0)
        return;

    ListNode* start = head_.get();
    ListNode* stop = head_.get();

    //see how many sections we have to flip, rounding up
    int sections = ceil((double)size_ / (double)n);

    //cout << sections << endl;

    for(int i = 0; i < sections; i++)
    {
        //setting the end for our flip
        for(int j = 1; j < n; j++)
        {
            //don't want to read after the tail
            if(stop->next == nullptr)
                break;
            stop = stop->next.get();
        }

        //actually reverse it
        reverse(start, stop);

        //get set up for the next one
        start = stop->next;
        stop = start;
    }
}**/

template <class T>
void dl_list<T>::reverse_nth(unsigned n)
{
   if (n==1||n==0) return;

 if (size_==0) return;
    
    //std::unique_ptr<node> head2=nullptr;
    //node* temp;
    node* temp2;
    node* var;
   // node* temp3;
    //node* temp3=head_.get();
    tail_=head_.get();
    if (tail_==nullptr) return;
       int sections=ceil((double)size_/(double)n);
    //for (int j=1;j)
    //!!!! get head
      for (unsigned j=1;j<n;j++)
    {
    tail_=tail_->next.get();
    }
      reverse();
      var=tail_;
      tail_->next->prev=tail_;
      //tail_=head_.get();
    //temp2=tail_;
     if (sections==1) 
       //tail_=head_.get();
     return;
    //head_.swap(tail_->next);    
    for (int i=1; i<sections-1;i++)

       {{//tail->next->prev=
std::cout << "[test_inserts]: " << std::endl;
         temp2=tail_->prev;
         var=tail_;
         tail_->next->prev=tail_;
        tail_=tail_->next.get();
        head_.swap(temp2->next->next);}
      { for (unsigned j=1;j<n;j++)
        tail_=tail_->next.get();
       }
        reverse();
        head_->prev=var;
        
        //tail_=head_.get();
        head_.swap(temp2->next->next);
        
        //head_.swap(tail_->next);
        
   }
     //temp=tail_->next.get();
     int a=size_%n;
     int k=a;
     if (a==0)
       k=n;
     var=tail_;
     temp2=tail_->prev;
     tail_->next->prev=tail_;
     tail_=tail_->next.get();
      head_.swap(temp2->next->next);
    for (int j=1;j<k;j++)
      {  //temp2=tail_->prev;
         tail_=tail_->next.get();
         //head_.swap(temp2->next->next);
      }
         reverse();
      head_->prev=var;
      tail_->next=nullptr;
      //tail_=head_.get();
      head_.swap(temp2->next->next);
 //head_.swap(start);
 //tail_=temp;
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::waterfall()
{
node* temp;
  if (head_==nullptr||head_->next==nullptr||size_==0||tail_==nullptr)
   return;
node* curr=head_->next.get();
if (curr->next!=nullptr)
temp=curr->next.get();
else 
temp=curr;
while (curr!=nullptr&&curr->next!=nullptr)
  {tail_->next.swap(curr->prev->next);
   curr->next->prev=curr->prev;
   curr->prev->next.swap(curr->next);
   curr->next=nullptr;
   curr->prev=tail_;
   tail_=curr;
   if (temp->next!=nullptr)//&&temp->next->next!=nullptr)
   curr=temp->next.get();
   
   else 
    curr=temp;
  if (temp->next!=nullptr)
     { if (temp->next->next!=nullptr)
         temp=curr->next.get();
       else temp=curr;
     }
  
 }
  /**node* curr=head_->next.get();
  node* temp=nullptr;
  while (curr!=nullptr&&curr->next!=nullptr)
    {curr->next->prev=curr->prev;
    tail_->next.swap(curr->prev->next);
    curr->prev->next.swap
    curr->prev->next.swap(curr->next);
    curr->prev=tail_;
    temp=curr->next->next.get();
    curr->next=nullptr;
    tail_=curr;
    curr=temp;}**/
 
  

    /// @todo mp_list.1
}

template <class T>
auto dl_list<T>::split(unsigned split_point) -> dl_list
{
    if (split_point >= size_)
        return {};

    if (split_point == 0)
    {
        dl_list lst;
        swap(*this);
        return lst;
    }

    auto old_size = size_;
    auto new_head = split(head_.get(), split_point);

    // set up current list
    size_ = split_point;
    for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
        ;

    // set up returned list
    dl_list ret;
    ret.head_ = std::move(new_head);
    for (ret.tail_ = ret.head_.get(); ret.tail_->next;
         ret.tail_ = ret.tail_->next.get())
        ;
    ret.size_ = old_size - split_point;
    return ret;
}

template <class T>
auto dl_list<T>::split(node* start, unsigned split_point)
    -> std::unique_ptr<node>
{ assert(split_point > 0);
 if (start==nullptr)
    return nullptr;
  node* temp=start;
  std::unique_ptr<node> head2=nullptr;
  //int count=split_point;
  //while (count--) 
    for (unsigned i=0;i<split_point;i++)
  {
    temp=temp->next.get();
  }
  //if (temp->prev!=nullptr)
     temp->prev->next.swap(head2);
  temp->prev=nullptr;
  return head2;
  

    //assert(split_point > 0);
    /// @todo mp_list.2
}

template <class T>
void dl_list<T>::merge(dl_list& to_merge)
{
    head_ = merge(std::move(head_), std::move(to_merge.head_));

    for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
        ;
    size_ += to_merge.size_;

    to_merge.tail_ = nullptr;
    to_merge.size_ = 0;
}

template <class T>
auto dl_list<T>::merge(std::unique_ptr<node> first,
                       std::unique_ptr<node> second) -> std::unique_ptr<node>
{

  node* newlist;
  node* newnext;
  std::unique_ptr<node> firstlist=nullptr;
  firstlist.swap(first);
  std::unique_ptr<node> secondlist=nullptr;
   secondlist.swap(second);
  //node* secondList=second.get();  
head_=nullptr;
if (firstlist->data<secondlist->data)
   {newlist=firstlist.get();
    head_.swap(firstlist);
    firstlist.swap(newlist->next);
   }
else 
 {
    newlist=secondlist.get();
    head_.swap(secondlist);
    secondlist.swap(newlist->next);
 }  
   
  while (firstlist!=nullptr||secondlist!=nullptr)

   {
     if (secondlist==nullptr||(firstlist!=nullptr&&firstlist->data<secondlist->data))
     {
       newlist->next.swap(firstlist);
       newnext=newlist->next.get();
       newnext->prev=newlist;
       newlist=newlist->next.get();
       firstlist.swap(newlist->next);
     } 

     else 
     {//if (secondlist->prev=nullptr)
       newlist->next.swap(secondlist);
       newnext=newlist->next.get();
       newnext->prev=newlist;
       newlist=newlist->next.get();
       secondlist.swap(newlist->next);
     //}
      }
    }

     /**if (firstlist!=nullptr)
     {   //while (firstlist!=nullptr)
      //{
          
          newlist->next.swap(firstlist);
          newnext=newlist->next.get();
          newnext->prev=newlist;
          while (newlist->next.get()!=nullptr)
         {
          newlist=newlist->next.get();
         }**/
       /**newnext=newlist->next.get();
       newnext->prev=newlist;
       newlist=newlist->next.get();
       firstlist.swap(newlist->next);**/
      //}
    // } 
      
        /**else if(secondlist!=nullptr)
    { //while (secondlist!=nullptr)
     //{
       newlist->next.swap(secondlist);
       newnext=newlist->next.get();
       newnext->prev=newlist;
        while (newlist->next.get()!=nullptr)
        {
         newlist=newlist->next.get();  
        }**/
       //newlist=newlist->next.get();
       //secondlist.swap(newlist->next);
     //}
 //  }
    firstlist=nullptr;
    secondlist=nullptr;
    tail_=newlist;
    tail_->next=nullptr;
    head_.swap(firstlist);
firstlist->prev=nullptr;
return firstlist;
   //return firstlist;
 //return secondlist;
  /// @todo mp_list.2
}

template <class T>
void dl_list<T>::sort()
{
    if (!head_)
        return;

    head_ = mergesort(std::move(head_), size_);
    for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
        ;
}

template <class T>
auto dl_list<T>::mergesort(std::unique_ptr<node> start, uint64_t length)
    -> std::unique_ptr<node>
{
   if (length==1)
      return start;
  int mid=length/2;
  //std::unique_ptr<node> temp=nullptr;
  std::unique_ptr<node> right=nullptr;
  right=split(start.get(),mid);
  std::unique_ptr<node> left=nullptr;
  //std::unique_ptr<node> tail
  left.swap(start);
  
  right=mergesort(std::move(right),length-mid);
  start=mergesort(std::move(left),mid);
  return merge(std::move(start),std::move(right));
    

   /// @todo mp_list.2

}
}
