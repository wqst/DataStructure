/**
 * @file kdtree.tcc
 * Implementation of kd_tree class.
 */

#include "math.h"
#include "kdtree.h"
#include <iostream>

template <int Dim>
bool kd_tree<Dim>::smaller_in_dimension(const point<Dim>& first,
                                       const point<Dim>& second,
                                       int curDim) const
{
    /**
     * @todo Implement this function!
     */
        if (first[curDim] == second[curDim])
        return first < second;
    return first[curDim] < second[curDim];
}

template <int Dim>
bool kd_tree<Dim>::should_replace(const point<Dim>& target,
                                 const point<Dim>& current_best,
                                 const point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     int d_curr = distance(current_best, target); 
    int d_pot  = distance(potential, target);
    if (d_pot == d_curr)
        return potential < current_best;
    return d_pot < d_curr;
}

template<int Dim>
int kd_tree<Dim>::distance(const point<Dim> &a, const point<Dim>&b) const
{
    int ret = 0;
    for (int i = 0; i < Dim; i++)
    {
        ret+= pow(a[i]-b[i],2);
    }
    return ret;
}

template <int Dim>
kd_tree<Dim>::kd_tree(const std::vector<point<Dim>>& newpoints)
{
    
      points = newpoints;
    if (points.size()!=0)
        buildKD(0, 0, newpoints.size()-1); 

   /**
     * @todo Implement this function!
     */
}

template<int Dim>
void kd_tree<Dim>::buildKD(int dim, int left, int right)
{
    if(left==right)
        return;
    int median = (left+right)/2;
    quickSelect(median, left, right, dim);
    if (left < median)
        buildKD((dim+1)%Dim, left, median-1);
    if (right > median)
        buildKD((dim+1)%Dim, median+1, right);
}

template <int Dim>
point<Dim> kd_tree<Dim>::find_nearest_neighbor(const point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    point<Dim> val = NNShelper(0, query, 0, points.size()-1, points[(points.size()-1)/2]);
     
    return val;
}

template<int Dim>
point<Dim> kd_tree<Dim>::NNShelper(int curDim, const point<Dim> &query, int left, int right, const point<Dim> &currentBest) const
{
    //cout<<"[dim]: "<<curDim<<" [left]: "<<left<<" [right]: "<<right<<" [query]: "<<query<<" [curr]: "<<currentBest<<endl;
    point<Dim> ret_val = currentBest;
    bool target_left = true;
    if (left == right)
    {
        // at leaf node
        // 1. check if closer than currentBest node
        if (should_replace(query, currentBest, points[left]))
        {
            // 2. return current best and radius
             ret_val = points[left];
            return ret_val;
        }
        ret_val = currentBest;
        return ret_val;
    }
    //Get closest point in the subtree containing target
    int median = (left + right)/2;
    int otherSubMedian;
    if (smaller_in_dimension(points[median], query, curDim) && right > median)
    {
        ret_val = NNShelper((curDim+1)%Dim, query, median+1, right, currentBest);
        target_left = false;
        otherSubMedian = (left+median-1)/2;
    }
    if (smaller_in_dimension(query, points[median], curDim) && left < median)
    {   
        ret_val = NNShelper((curDim+1)%Dim, query, left, median-1, currentBest);
        target_left = true;
        otherSubMedian = (median+1+right-1)/2;
    }

    //Check if current node is closer than obtained above
    if (should_replace(query, ret_val, points[median]))
        ret_val = points[median];
    
    //Check the other subtree
    point<Dim> a = points[median];
    //cout<<"[split dist]: "<<a[curDim]-query[curDim]<<" [radius]: "<<distance(query, ret_val)<<" [median]: "<<points[median]<<" [ret_val]: "<<ret_val<<endl;
    if (pow(a[curDim] - query[curDim],2) <= distance(query, ret_val))
    {
        if (target_left && right > median)
            ret_val = NNShelper((curDim+1)%Dim, query, median+1, right, ret_val);
        if (!target_left && left < median)
            ret_val = NNShelper((curDim+1)%Dim, query, left, median-1, ret_val);
    }
    return ret_val;

}

template<int Dim>
void kd_tree<Dim>::quickSelect(int k, int left, int right, int curDim)
{
    //partition
    while(left != right)
    {
        int pivotNewIndex = partition(left, right, k, curDim);
        if (pivotNewIndex == k)
            return ;
        else if (k < pivotNewIndex) 
            right = pivotNewIndex-1;
        else
        {
            left = pivotNewIndex+1;
        }
    }
}

template<int Dim>
int kd_tree<Dim>::partition(int left, int right, int k, int curDim)
{
    point<Dim> pivot = points[k];
    point<Dim> temp = points[right];
    points[right] = points[k];
    points[k] = temp;
    int storeIndex = left;
    for (int i = left; i < right; i++)
    {
        if (smaller_in_dimension(points[i], pivot, curDim) || points[i] == pivot)
        {
            temp = points[storeIndex];
            points[storeIndex] = points[i];
            points[i] = temp;
            storeIndex++;
        }
    }
    temp = points[right];
    points[right] = points[storeIndex];
    points[storeIndex] = temp;
    return storeIndex;
}
