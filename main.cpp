#include <iostream>
//#include <std::vector>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <fstream>
#include <ctime>
#include "util.h"

using namespace std;

// Compare two Jobs by processingTime/earlinessPenalty
bool sortPA(Job *first, Job *second) {
  return first->processingTime/first->earlinessPenalty > second->processingTime/second->earlinessPenalty;
}

// Compare two Jobs by processingTime/tardinessPenalty
bool sortPB(Job *first, Job *second) {
  return first->processingTime/first->tardinessPenalty < second->processingTime/second->tardinessPenalty;
}


int inline earlinessPenalty(Job *job, int startTime, int dueDate) {
  return maxi( 0 , (dueDate - (startTime+job->processingTime))*job->earlinessPenalty);
}

int inline tardinessPenalty(Job *job, int startTime, int dueDate) {
  return maxi( 0 , ((startTime+job->processingTime) - dueDate)*job->tardinessPenalty);
}

// Calculate Penalty from a Job
int inline calculatePenalty(Job *job, int startTime, int dueDate) {
  return earlinessPenalty(job,startTime,dueDate) + tardinessPenalty(job,startTime,dueDate);
}

int simulate(int initialTime, std::vector<int> &allocation, std::vector<Job*> &jobs ,int dueDate) {
  int t = initialTime;
  int penalty = 0;

  for (unsigned int j = 0; j < allocation.size(); j++) {
    int p = calculatePenalty(jobs[allocation[j]],t,dueDate);
    penalty += p;
    t += jobs[allocation[j]]->processingTime;

  }

  return penalty;
}

int searchTime(std::vector<int> &allocation, std::vector<Job*> &jobs, int dueDate, int *result) {
	int t = 0;
    int penalty = simulate(t, allocation, jobs, dueDate);
    for (t = 1; t <= dueDate; t += 4) {
    	int npenalty = simulate(t, allocation, jobs, dueDate);
        if (npenalty < penalty)
        	penalty = npenalty;
		else
			break;
	}
	*result = penalty;
	return t-1;
}

int main(int argc, char **argv) {
	srand ( 2 );

/*************************************************************/

cout.precision(20);

  	unsigned int n_problem;
  	unsigned int n_jobs;

	int pTime;
	int ePenalty;
	int tPenalty;
	int sumP = 0;
	int countRep = 0;
	double h = 0;
	std::vector<std::vector<Job*> > instances;
	std::vector<int> dueDates;
	
	if (argc != 3) {
	    cout << "Syntax: " << argv[0] << " inputFile.txt h" << endl;
		return -1;
	}
	  
	h = atof(argv[2]);
	time_t sumT = 0;
	  
	// for (int ou = 0; ou < 100; ou++) {
	    
	
	/* Begin: Inicialização */
	ifstream input(argv[1], ifstream::in);

	input >> n_problem;
	input >> n_jobs;
	while (input.good()) {

	    std::vector<Job*> instance;

	    sumP = 0;
	    for (unsigned int i = 0; i < n_jobs; i++) {

	      input >> pTime; input >> ePenalty; input >> tPenalty;

	      sumP += pTime;

	      Job *job = new Job(i,pTime,ePenalty,tPenalty);

	      instance.push_back(job);

	    }
	    dueDates.push_back( ceil(sumP*h) );
	    instances.push_back(instance);
	    input >> n_jobs;

	  }
	  /* End: Inicialização */

	/*************************************************************/

	int size = n_jobs;



	for (int inst = 0; inst < instances.size(); inst++) {
		time_t start = clock();
		cout << "***********************************************"<< endl;

		vector<std::pair<std::vector<int>, int> > population;
		
		//population.resize(200);
		
		int popSize = 100;

		std::vector<int> test,c1,c2;
		
		c1.resize(size);
		c2.resize(size);

		for (int i = 0; i < size; i++) {
			test.push_back(i);		
		}

		// População Inicial
		for (int i = 0; i < popSize; i++) {
			int result, t;
			t = searchTime(c1,instances[inst],dueDates[inst], &result);
			random_shuffle(test.begin(), test.end());
			population.push_back(std::pair<std::vector<int>,int> (std::vector<int>(test), 
							     result));
		}
		
		sort(population.begin(), population.end(), sort_pred());

		// Iteração GA
		for (int i = 0; i < 20000; i++) {

			// Gerar Nova População
			for (int j = 0; j < popSize/4; j++) {
				int k,m,t,result;
				k = rand()%(popSize/4);
				m = rand()%(popSize/4);

				crossOver(population[k].first,population[m].first,c1);		
				if (h/4+.1 > ((double) rand() / (((float)RAND_MAX)+1))) {
					mutation(c1);
					t = searchTime(c1,instances[inst],dueDates[inst], &result);
					population.push_back(std::pair<std::vector<int>,int> (std::vector<int>(c1),
								  	  result));					
				} else {
					t = searchTime(c1,instances[inst],dueDates[inst], &result);
					population.push_back(std::pair<std::vector<int>,int> (std::vector<int>(c1),						
								  	  result));
				}

			}
			sort(population.begin(), population.end(), sort_pred());			

			population.erase(population.end()-(popSize/4), population.end());
			cout << population[0].second << endl;
		}

		cout << "* " <<  population[0].second << endl;
		cout << "Time: " << (1.0*(clock()-start)/CLOCKS_PER_SEC) << " s" << endl;
	}
	return 0;


}