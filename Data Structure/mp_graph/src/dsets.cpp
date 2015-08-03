#include "dsets.h"

using namespace std;

void dsets::add_elements(uint64_t num) {
	for(uint64_t i = 0; i < num; i++)
		sets.push_back(-1);
}

uint64_t dsets::find(uint64_t elem) {
	if(sets[elem] <= -1)
		return elem;
	int end = find(sets[elem]);
	sets[elem] = end;
	return end;
}

void dsets::merge(uint64_t a, uint64_t b) {
	int aroot = find(a);
	int broot = find(b);
        auto temp=sets[aroot]+sets[broot];
	if(aroot == broot)	//already in the same set
		return;
	if(sets[aroot] <= sets[broot]) {	//if node is root, it will contain the size of its tree * -1
		sets[aroot] = temp;
		sets[broot] = aroot;
	}
	else {
		sets[broot] = temp;
		sets[aroot] = broot;
	}
}
