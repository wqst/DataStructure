/**
 * @file binary_tree.tcc
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class T>
int binary_tree<T>::height() const
{
    // Call recursive helper function on root
    return height(root_.get());
}

template <class T>
int binary_tree<T>::height(const node* subRoot) const
{
    // Base case
    if (!subRoot)
        return -1;

    // Recursive definition
    auto left = height(subRoot->left.get());
    auto right = height(subRoot->right.get());
    return std::max(left, right) + 1;
}

template <class T>
void binary_tree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root_.get());

    // Finish the line
    std::cout << std::endl;
}

template <class T>
void binary_tree<T>::printLeftToRight(const node* subRoot) const
{
    // Base case - null node
    if (!subRoot)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left.get());

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right.get());
}

template <typename T>
void binary_tree<T>::mirror()
{
// your code here
    mirror(root_.get());
}

/*
* mirror helper
*/
template <typename T>
void binary_tree<T>::mirror(node* subRoot)
{
    if (subRoot == nullptr)
        return;
     //std::unique_ptr<node> temp;
     //temp.swap(subRoot->left); 
     //subRoot->left.swap(subRoot->right);
     subRoot->left.swap(subRoot->right);

    mirror(subRoot->left.get());
    mirror(subRoot->right.get());
}

/**
* @return True if an in-order traversal of the tree would produce a nondecreasing list
* output values, and false otherwise. This is also the criterion for a binary tree to be
* a binary search tree.
*/
template <typename T>
bool binary_tree<T>::isOrdered() const
{
return isOrdered(root_.get());
}

/**
* Helper function for isOrdered()
*/
template <typename T>
bool binary_tree<T>::isOrdered(const node* subRoot) const
{
    bool lOrdered = false, rOrdered = false;
    int rMost = 0, lMost = 0;
    if (subRoot == nullptr)
        return true;
    if (subRoot->left != nullptr)
    {
        lOrdered = isOrdered(subRoot->left.get());
        rMost = rightMost(subRoot->left.get());
    }
    else
    {
        lOrdered = true;
        rMost = subRoot->elem;
    }

    if (subRoot->right != nullptr)
    {
        rOrdered = isOrdered(subRoot->right.get());
        lMost = leftMost(subRoot->right.get());
    }
    else
    {
        rOrdered = true;
        lMost = subRoot->elem;
    }
    if (lOrdered && rOrdered && (lMost>=subRoot->elem) && (rMost<=subRoot->elem))
        return true;
    return false;
}

/**
* return left-most node on the tree
*/
template <typename T>
T binary_tree<T>::leftMost(const node* subRoot) const
{
    if (subRoot->left == nullptr)
        return subRoot->elem;
    return leftMost(subRoot->left.get());
}

/**
* return the right-most node on the tree
*/
template <typename T>
T binary_tree<T>::rightMost(const node* subRoot) const
{
    if (subRoot->right == nullptr)
        return subRoot->elem;
    return rightMost(subRoot->right.get());

}

/**
* Prints out all the possible paths from the root of the tree to any leaf node.
* That is, all sequences starting at the root node and continuing downwards, ending at a
* leaf node. Paths ending in a left node should be printed before paths ending in a node
* further to the right.
*/
template <typename T>
void binary_tree<T>::printPaths() const
{
    // your code here
    int path[1000];
    printPathsHelper(root_.get(), path, 0);
}

template <typename T>
void binary_tree<T>::printPathsHelper(const node* subRoot, int path[], int size) const
{
    if (subRoot == nullptr)
        return;

    path[size] = subRoot->elem;
    size++;

    if (subRoot->left ==nullptr && subRoot->right == nullptr)
    {
        std::cout<<"Path:";
        for(int i = 0; i < size; i++)
        {
            std::cout<<" "<<path[i];
        }
        std::cout<<std::endl;
    }
    else
    {
        printPathsHelper(subRoot->left.get(),path,size);
        printPathsHelper(subRoot->right.get(),path,size);
    }
}


/**
* Each node in a tree has a distance from the root node - the depth of that node,
* or the number of edges along the path from that node to the root. This function returns
* the sum of the distances of all nodes to the root node (the sum of the depths of all
* the nodes). Your solution should take O(n) time, where n is the number of nodes in the tree.
* @return The sum of the distances of all nodes to the root
*/
template <typename T>
uint64_t binary_tree<T>::sumDistances() const
{
    int count = 0;
    return sumDistHelper(root_.get(),count);
}

template <typename T>
int binary_tree<T>::sumDistHelper(const node* subRoot, int count) const
{
    if (subRoot == nullptr)
        return 0;
    //cout<<"[data]: "<<subRoot->elem<<" | [count]: "<<count<<endl;
    int retVal = sumDistHelper(subRoot->left.get(), ++count) + sumDistHelper(subRoot->right.get(), count)+count;
    //cout<<"[retVal]: "<<retVal<<endl;
    return retVal-1;
}
