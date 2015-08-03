/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace quackfun
{

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the standard library stack in this problem. Its pop
 * function works a bit differently from the stack we built. Try searching
 * for "stl stack" to learn how to use it.
 *
 * @hint Think recursively!
 */
template <typename T>
T sum(std::stack<T>& s)
{
    if (s.size()==0)
      return 0;
 T temp=s.top();
 s.pop();
 int total=temp+sum(s);
s.push(temp);
return total;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the standard library queue in this problem. Its pop
 * function works a bit differently from the stack we built. Try searching
 * for "stl stack" to learn how to use it.
 *
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(std::queue<T>& q)
{
    std::stack<T> s;
    std::queue<T> q1;
     
    uint64_t num=1;
      while(!q.empty())
   {
   if (num%2 ==1)
     {for (uint64_t i=0;i<num;i++)
       {  if (!q.empty())
         {
         q1.push(q.front());
         q.pop();
         }
        }
      }
    else  
    {for (uint64_t i=0;i<num;i++)
      { 
       if (!q.empty())
     {
       s.push(q.front());
       q.pop();
     }
      }
      while (!s.empty())
     {
       q1.push(s.top());
       s.pop();
     }

    } 
      num++;
    }
    q=q1;
}




/**
 * @return true if the parameter stack and queue contain only elements of
 * exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to
 *   use in your return statement, and you may only declare TWO local
 *   variables of parametrized type T to use however you wish.
 *   No other local variables can be used.
 * - After execution of verify_same, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verify_same(std::stack<T>& s, std::queue<T>& q)
{
bool retval = true; // optional
	T stemp; // rename me
    T temp; // rename :) 
	if(s.size()==0)
		return true;
	stemp = s.top();
	s.pop();
	retval=verify_same(s,q);
	temp = q.front();
	q.pop();
	retval = (retval&&(stemp==temp));
	q.push(temp);
	s.push(stemp);
    return retval;
}
}
