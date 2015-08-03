/**
 * @file avl_tree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include "avl_tree.h"

template <class K, class V>
const V& avl_tree<K, V>::find(const K& key) const
{
    return find(root_.get(), key);
}

template <class K, class V>
const V& avl_tree<K, V>::find(const node* subtree, const K& key) const
{
    if (!subtree)
    {
        throw std::out_of_range{"invalid key"};
    }
    else if (key == subtree->key)
    {
        return subtree->value;
    }
    else if (key < subtree->key)
    {
        return find(subtree->left.get(), key);
    }
    else
    {
        return find(subtree->right.get(), key);
    }
}

template <class K, class V>
void avl_tree<K, V>::rotate_left(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
        
        //if (t->right!=nullptr)
        std::unique_ptr<node> temp;
        
        temp.swap(t->right);
        t->right.swap(temp->left);
        t->height=max(getHeight(t->left.get()),getHeight(t->right.get()))+1;
        temp->left.swap(t);
        temp->height=max(getHeight(temp->left.get()),getHeight(temp->right.get()))+1;
        t.swap(temp);
        /*else 
        {
          std::unique_ptr<node> temp;
          temp.swap(t);
          t.swap(temp->left);
          t->height=max(getHeight(t->left.get()),getHeight(t->right.get()))+1;
          t->right.swap(temp);
          t->right->height--;
        }
        //Node* tr = t->right;*/
        /*t->right = tr->left;
        tr->left = t;
        t->height = calculateSubtreeHeight(t.get());
        tr->height = calculateSubtreeHeight(tr.get());
        t = tr;*/
 

 
    /// @todo Your code here
}

template <class K, class V>
void avl_tree<K, V>::rotate_left_right(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotate_left(t->left);
    rotate_right(t);
}

template <class K, class V>
void avl_tree<K, V>::rotate_right(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

     //if (t->left!=nullptr)
     std::unique_ptr<node> temp;
      
        temp.swap(t->left);
      //std::cout << "2" <<std::endl;
      
        t->left.swap(temp->right);
      //std::cout << "3" <<std::endl;
        t->height=max(getHeight(t->left.get()),getHeight(t->right.get()))+1;
      //std::cout << "4" <<std::endl;
        temp->right.swap(t);
      //std::cout << "5" <<std::endl;
        temp->height=max(getHeight(temp->left.get()),getHeight(temp->right.get()))+1;
        t.swap(temp);
     
   /** else 
        {
          std::unique_ptr<node> temp;
          temp.swap(t);
          t.swap(temp->right);
          t->height=max(getHeight(t->left.get()),getHeight(t->right.get()))+1;
          t->left.swap(temp);
          t->left->height--;
        }
**/
    /*Node* tl = t->left;
        t->left = tl->right;
        tl->right = t;
        t->height = calculateSubtreeHeight(t.get());
        tl->height = calculateSubtreeHeight(tl.get());
        t = tl;*/


   /*std::unique_ptr<node> temp;
 temp=std::move(t->left);
   //node* temp=t->right.get();
   
    t->left.swap(temp->right);
     temp->left=nullptr;
      temp->right.swap(t);
   
   
   //    //t->left.swap(t->right);
        t->height=max(getHeight(t->left.get()),getHeight(t->right.get()))+1;
         temp->height=max(getHeight(temp->left.get()),getHeight(temp->right.get()))+1;
        t.swap(temp);*/
  

  /// @todo Your code here
}
template <class K, class V>
void avl_tree<K, V>::rotate_right_left(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
   rotate_right(t->right);
   rotate_left(t) ;

   /// @todo Your code here
}

template <class K, class V>
void avl_tree<K, V>::insert(K key, V value)
{
    insert(root_, std::move(key), std::move(value));
}

template <class K, class V>
void avl_tree<K, V>::insert(std::unique_ptr<node>& subtree, K key, V value)
{
  if (!subtree)
     subtree=std::make_unique<node>(std::move(key),std::move(value));
  else if (key<subtree->key)
    {
     insert(subtree->left,key,value);
    }
  else 
    {
     insert(subtree->right,key,value);
    }
  rebalance(subtree);


   /** if (subtree->key>key)
    {
     if (subtree->left==nullptr)
        {std::unique_ptr<node> temp{new node(key,value)};
         subtree->left.swap(temp);
        }
     else 
        insert (subtree->left,key,value);
    }
    else if (subtree->key<key)
   {
    if (subtree->right==nullptr)
        {std::unqiue_ptr<node> temp{new node(key,value)};
         subtree->right.swap(temp);     
        }
     else insert(subtree->right, key, value);
   }
    else return;
  subtree->height=max(getHeight(subtree->left.get()),getHeight(subtree->right.get()))+1;
  */


   /// @todo Your code here
}

template <class K, class V>
void avl_tree<K, V>::rebalance(std::unique_ptr<node>& subroot)
{
   auto balance=getHeight(subroot->left.get())-getHeight(subroot->right.get());
   if (balance==2)
   {
    rebalance_left(subroot);
   }
  else if (balance==-2)
   {
    rebalance_right(subroot);
   }
  subroot->height=1+std::max(getHeight(subroot->left.get()),getHeight(subroot->right.get()));
      /// @todo Your code here
}

template <class K, class V>
void avl_tree<K, V>::rebalance_left(std::unique_ptr<node>& subroot)
{
  auto balance_left=getHeight(subroot->left->left.get())-getHeight(subroot->left->right.get());  
 if (balance_left==1)
   rotate_right(subroot);
 else 
   rotate_left_right(subroot);

  /// @todo Your code here
}

template <class K, class V>
void avl_tree<K, V>::rebalance_right(std::unique_ptr<node>& subroot)
{
  auto balance_right=getHeight(subroot->right->left.get())-getHeight(subroot->right->right.get()); 
  if (balance_right==-1)
   rotate_left(subroot);
  else
   rotate_right_left(subroot);

   /// @todo Your code here
}

template <class K, class V>
int64_t avl_tree<K, V>::getHeight(node* t)
{
    if (t == nullptr)
        return -1;
    return t->height;
}

template <class K, class V>
int64_t avl_tree<K, V>::calculateSubtreeHeight(node* & node) {
        return 1 + max(heightOrNeg1(node->left), heightOrNeg1(node->right));
}
