#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <functional>

#include "util.h"

using namespace std;

int main(int argc, char **argv) {
  	//srand ( unsigned ( time (NULL) ) );
	srand ( 2 );

	int size = 10;

	vector<deque<int> > population;
	population.resize(500);

	deque<int> test,c1,c2;
	
	c1.resize(size);
	c2.resize(size);

	for (int i = 0; i < size; i++) {
		test.push_back(i);		
	}

	// População Inicial
	for (int i = 0; i < 500; i++) {
		random_shuffle(test.begin(), test.end());
		population[i] = deque<int>(test);
	}


	// Iteração GA
	for (int i = 0; i < 5000; i++) {

		// Gerar Nova População
		for (int j = 0; i < 1000; i++) {
			int k,m;
			k = rand()%500;
			m = rand()%500;

			crossOver(population[k],population[m],c1,c2);		
			printDeque(c1);
			printDeque(c2);
		}

	}

	return 0;


}