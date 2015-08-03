#include "scoped_array.h"
#include <iostream>
#include <cstdint>
#include <exception>

namespace cs225 
{

template <class T>
scoped_array<T>::scoped_array()
{arr_=nullptr;
size_=0;
}

template <class T>
scoped_array<T>::scoped_array(uint64_t sze)
{arr_= new T[sze];
size_=sze;
}

template <class T>
scoped_array<T>::scoped_array(const scoped_array<T>& other)
{size_=other.size_;
T* temp=new T[size_];
for (uint64_t i=0;i<size_;i++)
   temp[i]=other.arr_[i];
arr_=temp;
temp=nullptr;

}

template <class T>
scoped_array<T>::scoped_array(scoped_array<T>&& other)
{
size_=other.size_;
arr_=other.arr_;
other.size_=0;
other.arr_=nullptr;
}

template <class T>
scoped_array<T>& scoped_array<T>::operator=(scoped_array<T> rhs)
{
swap(rhs);
return *this;

}

template <class T>
scoped_array<T>::~scoped_array()
{
clear();
}

template <class T>
void scoped_array<T>::clear()
{
size_ = 0;
delete[] arr_;
arr_=nullptr;

}

template <class T>
void scoped_array<T>::swap(scoped_array<T>& other)
{std::swap(arr_,other.arr_);
std::swap(size_,other.size_);
}

template <class T>
void scoped_array<T>::resize(uint64_t size)
{
    T* temp = new T[size];
 if (size==0)
{size_=0;
delete[] arr_;
arr_=nullptr;
}
 
   else  if(size_ < size){
        for(uint64_t i = 0; i <size_; i++ ){
            temp[i] = arr_[i];
        }
        size_ = size;
        delete[] arr_;
        arr_ = nullptr;
        std::swap(arr_, temp);
    }
    else{
    for(uint64_t i = 0; i<size; i++){
        temp[i] = arr_[i];
    }
    delete[] arr_;
    arr_ = nullptr;
    std::swap(arr_, temp);
    size_ = size;
    }
}



template <class T>
const T& scoped_array<T>::operator[](uint64_t idx) const
{return arr_[idx];}

template <class T>
T& scoped_array<T>::operator[](uint64_t idx)
{return arr_[idx];}

template <class T>
const T& scoped_array<T>::at(uint64_t idx) const
{if (idx>=size_)
throw std::out_of_range("out of range!");
return arr_[idx];
}

template <class T>
T& scoped_array<T>::at(uint64_t idx)
{if (idx>=size_)
throw std::out_of_range("out of range!");
return arr_[idx];
}

template <class T>
uint64_t scoped_array<T>::size() const
{return size_;}

template <class T>
bool scoped_array<T>::empty() const
{
return (arr_==nullptr);

}
}
