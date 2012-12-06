#include "util.h"
#include <algorithm>
#include <functional>
#include <iostream>

template<class Iter, class T>
Iter binary_find(Iter begin, Iter end, T val)
{
    // Finds the lower bound in at most log(last - first) + 1 comparisons
    Iter i = std::lower_bound(begin, end, val);

    if (i != end && *i == val)
        return i; // found
    else
        return end; // not found
}

void printDeque(std::deque<int> &v) {
	std::cout << "[";
	for (int i = 0; i < v.size()-1; i++) {
		std::cout << v[i] << " ";
	}
	std::cout << v[v.size()-1] << "]" << std::endl;
}

void crossOver(std::deque<int> &v1, std::deque<int> &v2,
	std::deque<int> &c1, std::deque<int> &c2) {

	unsigned int k, m, first, second, size;

	size = v1.size();

	// GA loci
	k = rand()%size;
	m = rand()%size;

	// Getting first and second loci
	if (k > m) {

		first = m;
		second = k;
	} else {
		first = k;
		second = m;
	}

	for (int i = 0; i < first; i++) {
		c1[i] = v1[i];
		c2[i] = v2[i];
	}
	for (int i = first; i < second; i++) {
		c1[i] = v2[i];
	 	c2[i] = v1[i];
	}
	for (int i = second; i < size; i++) {
		c1[i] = v1[i];
		c2[i] = v2[i];
	}	

	removeDuplicates(c1);
	removeDuplicates(c2);

}

void removeDuplicates(std::deque<int> &c) {

	std::deque<int> duplicates;
	std::deque<int> missing;	
	std::deque<int> aux = std::deque<int>(c);

	for (int i = 0; i < c.size(); i++) {

		if (i != c.size()-1)
			if (aux[i] == aux[i+1])
				duplicates.push_back(i);
		if(!(std::binary_search(aux.begin(), aux.end(), i))) { 		   
    		/* aux does not contain i */
    	    missing.push_back(i);
		}			
	}
	std::deque<int>::iterator it;
	for (int i = 0; i < duplicates.size(); i++) {
		it = std::find(c.begin(), c.end(), aux[duplicates[i]]);	
		*it = missing[i];
	}		
	
	
	duplicates.clear();
	missing.clear();
	aux.clear();
}

inline void mutation(std::deque<int> &v) {
	unsigned int k, m, n, size;

	size = v.size();

	// GA loci
	k = rand()%size;
	m = rand()%size;

	n = v[k];
	v[k] = v[m];
	v[m] = n;
}