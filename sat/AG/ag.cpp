#include "ag.h"

void GeneticAlgorithm( Info info, int sizePopulation ){
	Population population;
	population.sizePop = sizePopulation;
	
	InitialPopulation ( &population, info );
	EvaluatePopulation ( &population, info );
	Individual best =  BestIndividual (population);
	Population bestPopulation = BestPopulation( population );

	// while ( !Satisfy ( best, info ) ) {
	// 	BestPopulation


	// }

}

void PrintGeneticAlgorithm( Info info, int sizePopulation ){
	Population population;
	population.sizePop = sizePopulation;
	
	InitialPopulation ( &population, info );
	EvaluatePopulation ( &population, info );
	Individual best =  BestIndividual (population);

	for (int i = 0; i < sizePopulation; ++i){
		for (int j = 0; j < info.nVariables; ++j){
			cout << population.individual[i].solution[j] << " ";
		}
		cout << endl << population.individual[i].fitness << endl;
	}
	cout << endl << "best" << best.fitness << endl;
	for (int j = 0; j < info.nVariables; ++j){
		cout << best.solution[j] << " ";
	}
	cout << endl;

	Population tmp, copy;
	copy = Copy (population);
	tmp = BestPopulation( copy );

	free(copy.individual);

	cout << endl << "best population" << endl;
	for (int i = 0; i < sizePopulation/2; ++i){
		for (int j = 0; j < info.nVariables; ++j){
			cout << tmp.individual[i].solution[j] << " ";
		}
		cout << endl << tmp.individual[i].fitness << endl;
	}

	cout <<  endl << "aaa" << endl;
		for (int i = 0; i < sizePopulation; ++i){
		for (int j = 0; j < info.nVariables; ++j){
			cout << population.individual[i].solution[j] << " ";
		}
		cout << endl << population.individual[i].fitness << endl;
	}

	NewPopulation(tmp);
	// while ( !Satisfy ( best, info ) ) {
	// 	BestPopulation


	// }

}

void InitialPopulation ( Population *p, Info info ){
	p->individual = (Individual*) malloc (sizeof(Individual) * (p->sizePop));    

	for (int i = 0; i < p->sizePop; ++i){
		(p->individual[i]).solution = InitialSolution( info.nVariables );
		(p->individual[i]).id = i;
	}
}

int *InitialSolution ( int n ){
	int *variables = ( int * ) malloc ( sizeof( int ) * n );

	for ( int i = 0; i < n; ++i )
		variables[i] = Random(2);

	return variables;
}

int Random (int n){
	int random = rand() % n;
	return random;
}

int CalculateFitness ( int *individual, Info info ){
	int fitness = 0;

	for (int i = 0; i < info.nClauses * 3; i+=3){
		int clauseSatisfied = 0;

		for (int j = 0; j < 3; ++j){

			if (info.clauses[i+j] > 0)
				clauseSatisfied += individual[info.clauses[i+j] - 1];
			else
				clauseSatisfied += Not ( individual[abs( info.clauses[i+j] ) - 1] );
		}

		if (clauseSatisfied != 0)
			fitness++;
	}

	return fitness;
}

int Not ( int p ){
	return p == 0 ? 1 : 0;
}

void EvaluatePopulation ( Population *p, Info info ){

	for (int i = 0; i < p->sizePop; ++i)
		(p->individual[i]).fitness = CalculateFitness ( (p->individual[i]).solution, info );

}

Individual BestIndividual ( Population p ){
	Individual best;
	best.solution = p.individual[0].solution;
	best.fitness = p.individual[0].fitness;
	best.id = p.individual[0].id;

	for (int i = 1; i < p.sizePop; ++i){
		
		if ( p.individual[i].fitness > best.fitness ){
			best.solution =  p.individual[i].solution;
			best.fitness = p.individual[i].fitness;
			best.id = p.individual[i].id;
		}
	}

	return best;
}

int WorstFitness ( Population p ){
	int worst = p.individual[0].fitness ;

	for (int i = 1; i < p.sizePop; ++i){
		
		if ( p.individual[i].fitness < worst )
			worst = p.individual[i].fitness;
	}
	return worst;
}

bool Satisfy ( Individual best , Info info ){
	int fitness = CalculateFitness( best.solution , info);
	return fitness == info.nClauses ? true : false;
}

Population BestPopulation ( Population p ){
	Population b;
	int sizeb = (p.sizePop)/2;
	b.sizePop = sizeb;
	
	b.individual = (Individual*) malloc (sizeof(Individual) * sizeb);    

	int worstFitness = WorstFitness (p);

	for (int i = 0; i < sizeb; ++i){
		b.individual[i] = BestIndividual (p);
		p.individual[b.individual[i].id].fitness = worstFitness;  	
	}	

	return b;
}

Population Copy ( Population p ){
	int *vet, f, id;
	Population copy; 

	copy.individual = (Individual*) malloc (sizeof(Individual) * p.sizePop);    

	copy.sizePop = p.sizePop;

	for (int i = 0; i < p.sizePop; ++i){
		copy.individual[i].solution = p.individual[i].solution; 
		copy.individual[i].fitness = p.individual[i].fitness; 
		copy.individual[i].id = p.individual[i].id;
	}

	return copy;
}
void  NewPopulation ( Population best ){
	Population children;

	if ( (best.sizePop) % 2 == 0 ) 
		children.sizePop = best.sizePop ;
	else 
		children.sizePop =  (best.sizePop) - 1 ; 
	
	children.individual = (Individual*) malloc (sizeof(Individual) * children.sizePop);    	

	queue<int> q; 
	vector<double> percentFitness;
	vector<int> vetFitness;

	for (int i = 0; i < best.sizePop; ++i)
		vetFitness.push_back(best.individual[i].fitness);

	int sum = 0, k;
	for (int i = 0; i < best.sizePop; ++i)
		sum += best.individual[i].fitness;

	for (int j = 0; j < children.sizePop; ++j){
		int sumFitness = 0; 
		double percent = 0;

		for (int i = 0; i < vetFitness.size(); ++i)
			sumFitness += vetFitness.at(i);

		for (int i = 0; i < vetFitness.size(); --i){
			percent += vetFitness.at(i) / (double) sumFitness;
			percentFitness.push_back (percent);
		}

		k = Roulette ( percentFitness, sumFitness );


		for (int i = 0; i < vetFitness.size(); ++i)
		{
			cout << vetFitness.at(i) << " " << endl;
		}

		for (int i = 0; i < percentFitness.size(); ++i)
		{
			cout << percentFitness.at(i) << " " << endl;
		}

		percentFitness.clear();
		cout << endl << endl;	
		if (k == 0)
			vetFitness.erase (vetFitness.begin());
		else 
			vetFitness.erase (vetFitness.begin() + k-1); 
			
		q.push(k);
	}

	 cout << "fila de Crossover" << q.size()<<endl;
	 for (int i = 0; i < q.size(); ++i)
	 {
	 	cout << " " << q.front();
	 	q.pop();
	 }
	 cout << endl;

//roulette a e b

	//double chance = (a.fitness + b.fitness) / (double) sumFitness;
	//double change = Random (101)/100;
	
	//if( change > chance ){
		// children = Crossover(a, b);
// Mutation();
// EvaluatePopulatoin();
	//return new;
}

int Roulette ( vector<double> percent , int sum ){
	double r = Random (101)/100.0; 
	int i;
	for (i = 0; i < percent.size(); ++i){
		if ( r > percent.at(i) )
			continue;
		break;
	}

	cout <<"d " << i << endl; 
	return i;
}
	




// Population Crossover ( Individual a, Individual b){}