#ifndef cs225_SCOPED_ARRAY_H_
#define cs225_SCOPED_ARRAY_H_
#include <cstdint>
#include <exception>

namespace cs225
{
template <class T>
class scoped_array
{ 
 public:
  scoped_array();

  scoped_array(uint64_t sze);

  scoped_array(const scoped_array&other);

  scoped_array(scoped_array&&other);

  scoped_array&operator=(scoped_array rhs);

  ~scoped_array();

  void clear();

  void swap(scoped_array&other);

  void resize(uint64_t size);

  const T& operator[](uint64_t idx) const;

  T& operator[](uint64_t idx);

  const T& at(uint64_t idx) const;

  T& at(uint64_t idx);

    uint64_t size() const;

  bool empty() const;
  
 private:
  T* arr_;
  uint64_t size_;

 


 };


}
#include "scoped_array.tcc"
#endif
