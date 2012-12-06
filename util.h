#include <deque>

#ifndef _UTIL_H_
#define _UTIL_H_

// Imprime lista []
void printDeque(std::deque<int> &v);

// CrossOver de GA, com k e m, dois filhos
void crossOver(std::deque<int> &v1, std::deque<int> &v2,
			   std::deque<int> &c1, std::deque<int> &c2);

void removeDuplicates(std::deque<int> &c);

inline void mutation(std::deque<int> &v);

template<class Iter, class T>
Iter binary_find(Iter begin, Iter end, T val);
#endif // _UTIL_H_