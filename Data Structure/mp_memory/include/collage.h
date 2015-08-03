#ifndef CS225_COLLAGE_H_
#define CS225_COLLAGE_H_
#include <cstdint>
#include <exception>
#include "scoped_array.h"
#include "scoped_ptr.h"
#include "epng.h"

namespace cs225
{
class collage
{
public: 
  
 
 collage(uint64_t size);
 collage(const collage &other);
 collage (collage &&other);
 collage& operator=(collage rhs);
 ~collage();
 void swap(collage &other);
 void layers(uint64_t max);
 uint64_t layers() const;
 uint64_t filled() const;
 void emplace_picture(const std::string &filename,uint64_t index,uint64_t x,uint64_t y);
 void change_layer(uint64_t src,uint64_t dest);
 void position(uint64_t index,uint64_t x,uint64_t y);
 void erase(uint64_t index);
 void clear();
 const epng::png* at(uint64_t index) const;
 epng::png* at(uint64_t index);
 epng::png draw() const;

private:
scoped_array<scoped_ptr<epng::png>>* iarr;
uint64_t* xarr;
uint64_t* yarr;

};

}

#endif
