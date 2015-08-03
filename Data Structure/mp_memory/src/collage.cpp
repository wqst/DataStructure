#include "collage.h"
#include <iostream>
#include <cstdint>
#include <exception>
#include "epng.h"
#include "scoped_array.h"
#include "scoped_ptr.h"

namespace cs225
{
   
    collage::collage(uint64_t size)

{

     xarr=new uint64_t[size];
     yarr=new uint64_t[size];
     iarr=new scoped_array<scoped_ptr<epng::png>>(size);
  
   for (uint64_t i=0;i<size;i++)
    {xarr[i]=0;
    yarr[i]=0;}

}
     
    collage::collage(const collage& other)
    {   uint64_t size_=other.iarr->size();
       xarr=new uint64_t[size_];
       yarr=new uint64_t[size_];
   for (uint64_t j=0;j<size_;j++)
       {xarr[j]=other.xarr[j];
       yarr[j]=other.yarr[j];}


    
     iarr=new scoped_array<scoped_ptr<epng::png>>(size_);
     for (uint64_t i=0;i<size_;i++)
    (*iarr)[i]= new epng::png(*(*other.iarr)[i].get());

    }
    
    collage::collage(collage&& other)  /*construct an array?*/
    {for (uint64_t i=0; i<iarr->size();i++)
      iarr[i].clear();
     std::swap(xarr,other.xarr);
     std::swap(yarr,other.yarr);
     std::swap(iarr,other.iarr);
     
    }
   /*void collage::clear()
    {for (uint64_t i=0;i<iarr->size();i++)
      iarr[i].clear();
      iarr->clear();
     iarr=nullptr;
     delete[] xarr;
     delete[] yarr;
     xarr=nullptr;
     yarr=nullptr;
}*/
    collage::~collage()
    {/*for (uint64_t i=0;i<iarr->size();i++)
      iarr[i].clear();
    iarr->clear();*/
    /*{dclear();*/
    delete[] xarr;
    delete[] yarr;
    xarr=nullptr;
    yarr=nullptr;
}



   epng::png collage::draw() const
   {size_t maxW=0;
    size_t maxH=0;
    uint64_t a=iarr->size();
    for (uint64_t i=0;i<a;i++)
         {if (!(*iarr)[i].empty())
      { maxW=(std::max)(maxW,(*iarr)[i].get()->width()+xarr[i]);
        maxH=(std::max)(maxH,(*iarr)[i].get()->height()+yarr[i]);
      } 
        else i+=0;}
    epng::png* layers=new epng::png(maxW,maxH);
    epng::rgba_pixel* pixel;
    for (uint64_t k=0;k<a; k++)
     { for (size_t i=0;i<(*iarr)[k]->width();i++)
          {for (size_t j=0;j<(*iarr)[k]->height();j++)
            {  pixel=(*layers)(xarr[k]+i,yarr[k]+j);
               *pixel=*(*((*iarr)[k].get()))(i,j);

            }
          }
     }
     return *layers;
}


    collage & collage::operator=(collage rhs)/*use swap directly?*/
    { 
         
     std::swap(xarr,rhs.xarr);
     std::swap(yarr,rhs.yarr);
     std::swap(iarr,rhs.iarr);
 return *this;
}
 
    void collage::swap(collage& other)
    {

     std::swap(xarr,other.xarr);
     std::swap(yarr,other.yarr);
     std::swap(iarr,other.iarr);
}

    void collage::layers(uint64_t max) /*max=0*/
    {scoped_array<scoped_ptr<epng::png>>* used=new scoped_array<scoped_ptr<epng::png>>(max);
      for (uint64_t i=0;i<max;i++)
         (*used)[i]=new epng::png(*((*iarr)[i].get()));

uint64_t* f=new uint64_t[max];
     uint64_t* s=new uint64_t[max];
    /*iarr->resize(max);*/
    uint64_t size_=iarr->size();
  for (uint64_t pic=0;pic<size_;pic++)
    {if (max> size_)
      {for (uint64_t i=0;i<size_;i++)
       {f[i]=xarr[i];
       s[i]=yarr[i];}
      }
    else 
      {for (uint64_t j=0;j<max;j++)
       {f[j]=xarr[j];
       s[j]=yarr[j];}
     }}
   delete[] xarr;
   delete[] yarr;
   xarr =nullptr;
   yarr =nullptr;
   std::swap(xarr, f);
   std::swap(yarr, s);
}
    
    uint64_t collage::layers() const
    {return iarr->size();}

    uint64_t collage::filled() const
    {uint64_t size_=iarr->size();
     uint64_t c=size_;
for (uint64_t i=0;i<size_;i++)
  {if ((*iarr)[i].get()==nullptr)
    c--;
}
return c;
}

    void collage::emplace_picture(const std::string& filename, uint64_t index, uint64_t x, uint64_t y)
    {  if (index>=iarr->size()) throw std::out_of_range("out of range!");
    (*iarr)[index].clear();/*iarr[index]->clear()*/
    epng::png* temp=new epng::png(filename);
    scoped_ptr<epng::png> ptr(temp);
     (*iarr)[index].swap(ptr);
     
   /* ((*iarr)[index].get())->load(filename);*/
    delete temp;
    
    xarr[index]=x;
    yarr[index]=y;
}

    void collage::change_layer(uint64_t src, uint64_t dest)
    { if (dest>=iarr->size()||src>=iarr->size())
          throw std::out_of_range("out of range!");
     iarr[dest].clear();
     iarr[dest].swap(iarr[src]);

}

    void collage::position(uint64_t index, uint64_t x, uint64_t y)
    { if (index>=iarr->size())
         throw std::out_of_range("out of range!");
      if ((*iarr)[index].get()==nullptr)
         throw std::invalid_argument("invalide argumet!");
xarr[index]=x;
yarr[index]=y;

}

    void collage::erase(uint64_t index)
    {if (index>=iarr->size())
         throw std::out_of_range("out of range!");
     iarr[index].clear();
}

    const epng::png* collage::at(uint64_t index) const
    {if (index>=iarr->size())
         throw std::out_of_range("out of range!");
return (*iarr)[index].get();

}

    epng::png* collage::at(uint64_t index)
    {if (index>=iarr->size())
         throw std::out_of_range("out of range!");
return (*iarr)[index].get();
}



    



}
