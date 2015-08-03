/**
 * @file quadtree.cpp
 * quadtree class implementation.
 * @date Spring 2008
 * @date Modified Summer 2014
 */

#include "quadtree.h"
#include "rgba_pixel.h"
#include <cmath>
#include <iostream>

namespace cs225
{

quadtree::quadtree()
{
    root_ = nullptr;
}

quadtree::quadtree(const epng::png& source, uint64_t resolution)
{
   // cout<<"[In constructor]..."<<endl;
    build_tree(source, resolution);
    //cout<<"[Done building a tree!]"<<endl;
}

quadtree::quadtree(const quadtree& other)
{
    //cout<<"[In copy constructor]..."<<endl;
    if (other.root_ == nullptr)
    {
        root_ = nullptr;
        return;
    }
     

   
    build_tree(other.decompress(),other.root_->res);
   /** root_->northwest = std::move(other.root_->northwest);
    northeast = std::move(other.root_->northeast);
    southwest = std::move(other.southwest);
    southeast = std::move(other.southeast);
    x=other.x;
    y=other.y;
    res=other.res;
    element=other.element;
   **/
    //cout<<"[Done copying a tree!]"<<endl;
}

quadtree::quadtree(quadtree&& other)
{
 if (other.root_==nullptr) return;
 swap(other);
 other.root_=nullptr;
 /**other.northwest=nullptr;
 other.northeast=nullptr;
 other.southwest=nullptr;
 other.southeast=nullptr; 
 other.element=nullptr;
 other.x=nullptr;
 other.y=0;
 other.res=0;**/
}


/**quadtree::quadtreeNode* quadtree::copy( node*otherroot_)
{
    if (otherroot_ == nullptr)
    {
        return nullptr;
    }
    node*retVal = new quadtreeNode::quadtreeNode(otherroot_);
    retVal->northwest = copy(otherroot_->northwest);
    retVal->northeast = copy(otherroot_->northeast);
    retVal->southwest = copy(otherroot_->southwest);
    retVal->southeast = copy(otherroot_->southeast);
    return retVal;
}**/



/**void quadtree::clearTree( node* & subroot)
{
    // base case
    if ( subroot == nullptr )
        return;
    
    // recursively clear all other nodes
    clearTree(subroot->northwest);
    clearTree(subroot->northeast);
    clearTree(subroot->southwest);
    clearTree(subroot->southeast);
    // delete the root_ and set it to nullptr
    delete subroot;
    subroot = nullptr;
}**/


/**
 *  Member Fucntion
 */
quadtree& quadtree::operator= (quadtree other)
{
    //check self-assignment
   // if (root_->get() == other.root_->get())
        //return *this;

    //clear self
    //copy other
    swap(other);
    return *this;
}

void quadtree::swap(quadtree& other)
{
  root_.swap(other.root_);
  /**root_->southeast.swap(other.root_->southeast);
  root_->southwest.swap(other.root_->southwest);
  root_->northeast.swap(other.root_->northeast);
  root_->northwest.swap(other.root_->northwest);
  std::swap(root_->x,other.root_->x);
  std::swap(root_->y,other.root_->y);
  std::swap(root_->res,other.root_->res);
  std::swap(root_->element,other.root_->element);**/

}


void quadtree::build_tree (const epng::png & source, uint64_t resolution)
{
    //first construct a tree that has enough leaves
    //  with: x, y, res

    //Then load the leaves with the correct pixels
    
    //compute and store the average color of the children of non-leave nodes on the way back up
    //cout<<"[In buildTree]..."<<endl;
    
    std::unique_ptr<node> temp{new node(0,0,resolution)};
    root_.swap(temp);
    //root_{new node(0,0,resolution)};

    buildTreeHelper (source, resolution, root_.get());
    //cout<<"[Tree built!]"<<endl;
}

void quadtree::	buildTreeHelper (epng::png const & source, uint64_t resolution, node* subroot)
{
    //base case when res == 1
    //load correct pixels
    if (resolution ==1)
    {
        subroot->element = *(source(subroot->x,subroot->y));
        return;
    }
    //initialize new nodes
   std::unique_ptr<node> nw{new node(subroot->x, subroot->y, resolution/2)};
   std::unique_ptr<node> ne{new node(subroot->x + resolution/2, subroot->y, resolution/2)};
   std::unique_ptr<node> sw{new node(subroot->x, subroot->y + resolution/2, resolution/2)};
   std::unique_ptr<node> se{new node(subroot->x + resolution/2, subroot->y + resolution/2, resolution/2)};
     subroot->northwest.swap(nw);
     subroot->northeast.swap(ne);
     subroot->southwest.swap(sw);
     subroot->southeast.swap(se);
 
    //recursively build tree on children
    buildTreeHelper(source, resolution/2, subroot->northwest.get());
    buildTreeHelper(source, resolution/2, subroot->northeast.get());
    buildTreeHelper(source, resolution/2, subroot->southwest.get());
    buildTreeHelper(source, resolution/2, subroot->southeast.get());

    //store average color
    subroot->element.red = (subroot->northwest->element.red + subroot->northeast->element.red + subroot->southwest->element.red + subroot->southeast->element.red)/4; 
    subroot->element.green = (subroot->northwest->element.green + subroot->northeast->element.green + subroot->southwest->element.green + subroot->southeast->element.green)/4; 
    subroot->element.blue = (subroot->northwest->element.blue + subroot->northeast->element.blue + subroot->southwest->element.blue + subroot->southeast->element.blue)/4; 
}

const epng::rgba_pixel& quadtree::operator() (uint64_t x, uint64_t y) const
{
     if (root_.get()==nullptr||(!isInRange(x, y, root_.get())))
     throw std::out_of_range("out of range!");
     return getPixelHelper(x,y, root_->res, root_.get()); 
    
	
}

const epng::rgba_pixel& quadtree::getPixelHelper(uint64_t x, uint64_t y, uint64_t res, node* subroot) const
{
   
    if(x>res||y>res||subroot == nullptr)
    {
			return epng::rgba_pixel();}
    else{
	if(res==1||subroot -> northeast == nullptr)
		return subroot->element;
	
	if(x<res/2&&y<res/2)
		return getPixelHelper(x,y,res/2,subroot->northwest.get());
	if(x>=res/2&&y<res/2)
		return getPixelHelper(x-res/2,y,res/2,subroot->northeast.get());
	if(x<res/2&&y>=res/2)
		return getPixelHelper(x,y-res/2,res/2,subroot->southwest.get());
	if(x>=res/2&&y>=res/2)
		return getPixelHelper(x-res/2,y-res/2,res/2,subroot->southeast.get());
	return epng::rgba_pixel();}

    /** if ((subroot->x == x && subroot->y == y&&subroot->res == 1) || (subroot->northwest == nullptr))
        return subroot->element;
    if (isInRange(x,y,subroot->northwest.get()))
    {
        //in nw
        return getPixelHelper(x,y,subroot->northwest.get());

    } else if (isInRange(x,y,subroot->northeast.get()))
    {
        //in ne
        return getPixelHelper(x,y,subroot->northeast.get());

    } else if (isInRange(x,y,subroot->southwest.get()))
    {
        //in sw
        return getPixelHelper(x,y,subroot->southwest.get());

    } else
    {
        //in se
        return getPixelHelper(x,y,subroot->southeast.get());
    }*/
}

/**
 *  Computes whether a given (x,y) is in range of a quadtreeNode with its left-top most index as startX and startY
 */
bool quadtree::isInRange(uint64_t x, uint64_t y, node* subroot) const
{
    uint64_t x_range = subroot->x+subroot->res;
    uint64_t y_range = subroot->y+subroot->res;

    return (x >= subroot->x && x< x_range)&& (y >= subroot->y && y < y_range);
}


epng::png quadtree::decompress() const
{
    if (root_.get() == nullptr)
        throw std::runtime_error("runtime error!");
    uint64_t resolution = root_->res;
    epng::png retVal(resolution, resolution);
    
   *(retVal(root_->x,root_->y))=(*this)(root_->x,root_->y);
    traverse(root_->northwest.get(),retVal);
 traverse(root_->northeast.get(),retVal);
 traverse(root_->southwest.get(),retVal);
 traverse(root_->southeast.get(),retVal);

    for (uint64_t i = 0; i < resolution; i++)
    
        for (uint64_t j = 0; j < resolution; j++)
        {
		// (*this)(i, j)
            //(retVal(i,j)) = getPixelHelper(i, j, root_.get());
            *(retVal(i,j)) = (*this)(i,j);


        }
    
    return retVal;

}

void  quadtree::traverse(node* subroot, epng::png& retVal) const
{
 if (subroot==nullptr)
    return;
 *(retVal(subroot->x,subroot->y))=(*this)(subroot->x,subroot->y);
 traverse(subroot->northwest.get(),retVal);
 traverse(subroot->northeast.get(),retVal);
 traverse(subroot->southwest.get(),retVal);
 traverse(subroot->southeast.get(),retVal);
}


void quadtree::rotate_clockwise()
{
   clockwiseRotate(root_.get()); 
   
}

void quadtree::clockwiseRotate(node* subRoot)
{
    //base case: do nothing and return
    if (subRoot->northwest == nullptr)
        return;

    //swap the pouint64_ters to pouint64_t to the correct node after rotation
    std::unique_ptr<node> temp;
    temp.swap(subRoot->northwest);
    subRoot->northwest.swap(subRoot->southwest);
    subRoot->southwest.swap(subRoot->southeast);
    subRoot->southeast.swap(subRoot->northeast);
    subRoot->northeast.swap(temp);
    
    //start assigning new x,y coordinates after the rotation
    subRoot->northwest->x = subRoot->x;
    subRoot->northwest->y = subRoot->y;

    subRoot->northeast->x = subRoot->x + subRoot->res/2;
    subRoot->northeast->y = subRoot->y;
    
    subRoot->southwest->x = subRoot->x;
    subRoot->southwest->y = subRoot->y + subRoot->res/2;
    
    subRoot->southeast->x = subRoot->x + subRoot->res/2;
    subRoot->southeast->y = subRoot->y + subRoot->res/2;

    //recursively call rotate on children
    clockwiseRotate(subRoot->northwest.get());
    clockwiseRotate(subRoot->northeast.get());
    clockwiseRotate(subRoot->southwest.get());
    clockwiseRotate(subRoot->southeast.get());
    
}

void quadtree::prune(uint32_t tolerance)
{
   prune(tolerance, root_.get()); 
}

void quadtree::prune(uint32_t tolerance, node* subRoot)
{
    if (subRoot==nullptr||subRoot->northwest == nullptr)
        return;
    
    if (checkTol(subRoot, subRoot, tolerance))
    {
       
        clearTree(std::move(subRoot->northwest));
        clearTree(std::move(subRoot->northeast));
        clearTree(std::move(subRoot->southwest));
        clearTree(std::move(subRoot->southeast));
        return;
    }
    //recursively call prune on children
   
    prune(tolerance,subRoot->northwest.get());
    prune(tolerance,subRoot->northeast.get());
    prune(tolerance,subRoot->southwest.get());
    prune(tolerance,subRoot->southeast.get());
    

  }

void quadtree::clearTree(std::unique_ptr<node> subRoot)
{
    // base case
    // subRoot == nullptr;
    if (subRoot==nullptr)
        return;
    
    // recursively clear all other nodes
    clearTree(std::move(subRoot->northwest));
    clearTree(std::move(subRoot->northeast));
    clearTree(std::move(subRoot->southwest));
    clearTree(std::move(subRoot->southeast));
    
    subRoot = nullptr;
   // delete subRoot;
}

bool quadtree::checkTol(node* n, node* Tn, uint64_t tol) const
{
    if (n->northwest == nullptr)
    
   {
		uint64_t t=(n->element.red-Tn->element.red)*(n->element.red-Tn->element.red)+(n->element.green-Tn->element.green)*(n->element.green-Tn->element.green)+(n->element.blue-Tn->element.blue)*(n->element.blue-Tn->element.blue);
		if(t<=tol)
			return true;
		else return false;
	}
	bool nw=checkTol(n->northwest.get(),Tn,tol);
	bool ne=checkTol(n->northeast.get(),Tn,tol);
	bool se=checkTol(n->southeast.get(),Tn,tol);
	bool sw=checkTol(n->southwest.get(),Tn,tol);
	return nw&&ne&&sw&&se;



   /*{
        return; // (difference(subRoot, avgRoot)<=tol);
    }*/
    /**return (difference(subRoot, avgRoot)<=tol&&difference(subRoot, subRoot->northwest.get())<=tol&&difference(subRoot, subRoot->northeast.get())<=tol&&difference(subRoot, subRoot->southwest.get())<=tol&&difference(subRoot, subRoot->southeast.get())<=tol);**/

   /*return  (checkTol(subRoot->northwest.get(), avgRoot, tol) &&
                checkTol(subRoot->northeast.get(), avgRoot, tol) &&
                checkTol(subRoot->southwest.get(), avgRoot, tol) &&
                checkTol(subRoot->southeast.get(), avgRoot, tol));*/
}


/**uint64_t quadtree::difference(node* a, node* b) const
{
   //std::cout <<(a->element.red-b->element.red)*(a->element.red-b->element.red) <<std::endl;
    return (a->element.red-b->element.red)*(a->element.red-b->element.red)+(a->element.green-b->element.green)*(a->element.green-b->element.green)+(a->element.blue-b->element.blue)*(a->element.blue-b->element.blue);
}**/

uint64_t quadtree::pruned_size(uint32_t tolerance) const
{
    uint64_t n=0;
    return pruneSize(tolerance, root_.get(),n);
}

uint64_t quadtree::pruneSize(uint32_t tolerance, node* subRoot,uint64_t &n) const
{
  if (subRoot==nullptr) 
       return n;
  if (checkTol(subRoot,subRoot,tolerance))
       n++;
  else{
  pruneSize(tolerance,subRoot->northwest.get(),n);
  pruneSize(tolerance,subRoot->northeast.get(),n);
  pruneSize(tolerance,subRoot->southwest.get(),n);
  pruneSize(tolerance,subRoot->southeast.get(),n);}
   return n;

  /** if (subRoot->northwest == nullptr)
        return 1;
    if (checkTol(subRoot, subRoot, tolerance))
    {
        return 1;
    }
    return pruneSize(tolerance, subRoot->northwest.get()) + pruneSize(tolerance, subRoot->northeast.get()) + pruneSize(tolerance, subRoot->southwest.get()) + pruneSize(tolerance, subRoot->southeast.get());
**/
}

uint32_t quadtree::ideal_prune(uint64_t numLeaves)const
{
    //max difference is 195075
    
    return idealPrune(numLeaves, 255*255*3, 0);
    /*
    for (uint64_t i = 0; i < 255*255*3; i++)
        cout<<pruneSize(i)<<" "<<i<<endl; 
    return 0;
    */
}


uint32_t quadtree::idealPrune(uint64_t numLeaves, uint64_t max, uint64_t min) const
{
   if (max>min+1){
   if (pruned_size((max+min)/2)>numLeaves)
        return idealPrune(numLeaves,max,(max+min)/2);
   if (pruned_size((max+min)/2)<=numLeaves)
        return idealPrune(numLeaves,(max+min)/2,min);}
        if (pruned_size(min)<=numLeaves)
               return min;
        else return max;




    /** if (pruned_size(n) == numLeaves)
    {
        while (pruned_size(n) == numLeaves)
            n--;
        return n+1;
    }
    if (pruned_size(n) < numLeaves)
    {
        return idealPrune(numLeaves, n-interval/2, interval/2);
    }
    else
    {
        return idealPrune(numLeaves, n+interval/2, interval/2);
    }**/
}

}
