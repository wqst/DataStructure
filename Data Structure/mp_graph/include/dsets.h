#ifndef DSETS_H
#define DSETS_H

#include <vector>
#include <queue>

class dsets{

public:

  void add_elements(uint64_t num);
  uint64_t find(uint64_t elem);
  void merge(uint64_t a,uint64_t b);


private:

  std::vector<int> sets;

};

#endif
