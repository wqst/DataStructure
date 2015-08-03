/**
 * @file quadtree.h
 * quadtree class definition.
 * @date Spring 2008
 * @date Modified Summer 2014
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <iostream>
#include "epng.h"
#include "rgba_pixel.h"

namespace cs225
{

/**
 * A tree structure that is used to compress epng::png images.
 */
class quadtree
{
  public:

  quadtree();
  quadtree (const epng::png &source, uint64_t resolution);
  quadtree (const quadtree &other);
  quadtree (quadtree &&other);
  ~quadtree ()=default;
  quadtree& operator= (quadtree other);
  void 	swap (quadtree &other);
  void 	build_tree (const epng::png &source, uint64_t resolution);
  const epng::rgba_pixel& operator() (uint64_t x, uint64_t y) const;
  epng::png decompress () const;
  void 	rotate_clockwise ();
  void 	prune (uint32_t tolerance);
  uint64_t pruned_size (uint32_t tolerance) const;
  uint32_t ideal_prune (uint64_t num_leaves) const;
  //void clearTree(node* & subRoot);
  //void print (std::ostream &out=std::cout) const;
  //bool operator== (const quadtree &other) const;
 	
  



  private:
   //void print (std::ostream &out, const node* current, int level) const;
   //bool equal (const node* firstPtr, const node* secondPtr) const;

    /**
     * A simple class representing a single node of a quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class node
    {
      public:
        std::unique_ptr<node> northwest;
        std::unique_ptr<node> northeast;
        std::unique_ptr<node> southwest;
        std::unique_ptr<node> southeast;
        epng::rgba_pixel element; // the pixel stored as this node's "data"
    
   uint64_t x;
   uint64_t y;
   uint64_t res;

   node(uint64_t xcoord, uint64_t ycoord, uint64_t resolution)
   {
    x=xcoord;
    y=ycoord;
    res=resolution;
    northwest=nullptr;
    northeast=nullptr;
    northwest=nullptr;
    southeast=nullptr;
   }

   node(uint64_t xcoord, uint64_t ycoord, uint64_t resolution, epng::png& source)
   {
     x=xcoord;
     y=ycoord;
     res=resolution;
     northwest=nullptr;
    northeast=nullptr;
    northwest=nullptr;
    southeast=nullptr;
     element=*(source(x,y));

   }


   node(node* const other)
   {
    x=other->x;
    y=other->y;
    res=other->res;
    northwest=nullptr;
    northeast=nullptr;
    northwest=nullptr;
    southeast=nullptr;
    element=other->element;

   }

   };

     //void clearTree( QuadtreeNode * & subroot);

    //QuadtreeNode* copy(QuadtreeNode *otherRoot);

    void buildTreeHelper (epng::png const & source, uint64_t resolution, node* subroot);

    const epng::rgba_pixel& getPixelHelper(uint64_t x, uint64_t y, uint64_t res, node* subroot) const;

    bool isInRange(uint64_t x, uint64_t y, node* subroot) const;

    void clockwiseRotate(node* subroot);

    void prune(uint32_t tolerance, node* subroot);

    uint64_t difference(node* a, node* b) const;
    
    //uint64_t pruneSize(uint32_t tolerance, node* subroot) const;
    uint64_t pruneSize(uint32_t tolerance, node* subRoot,uint64_t &n) const;

    std::unique_ptr<node> root_; // the root of the tree

    uint32_t idealPrune(uint64_t numLeaves, uint64_t n, uint64_t interval) const;

    void traverse(node* subroot, epng::png& retVal) const;

    //bool checkTol(node* subroot, node* avgRoot, uint64_t avg)const;

    bool checkTol(node* n, node* Tn, uint64_t tol) const;

    void clearTree(std::unique_ptr<node> subRoot);

    //void decompress(epng::png& img,uint64_t x, uint64_t y, uint64_t res, node* const subRoot) const;

/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};
}
#endif
