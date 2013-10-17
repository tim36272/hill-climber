#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <vector>

#define LOWER_BOUND -1
#define MAX_ITERATIONS 1000
#define MAX_FITNESS 150

using namespace std;

double eval(int *pj);

void print_vector(std::ostream& out,int *vec) {
	for(int i=0;i<150;i++) {
		out<<vec[i];
	}
}

int getSuccessor(int *vec,double best_ever) {
	int position = 0;
	double max=best_ever;
	int max_at;
	double result;
	std::vector<int> positions_at_max;
	bool set_max = false;

	while(position<150) {
		std::cout<<"bit "<<position<<std::endl;
		//flip this bit and evaluate
		vec[position] = 1-vec[position];
		result = eval(vec);
		if(result > max) {
			max = result;
			max_at = position;
			set_max = true;
		}
		else if (result==max) {
			positions_at_max.push_back(position);
		}
		//flip it back  to continue evaluating
		vec[position] = 1-vec[position];
		position++;
	}
	//if this successor was superior modify the vec
	if(max > best_ever) {
//		std::cout<<"max > best_ever"<<std::endl;
		vec[max_at] = 1-vec[max_at];
	}
	//if it was the same, try to get off the plateu by flipping a random bit
//	if(positions_at_max.size()==0) std::cout<<"None at max"<<std::endl;
	else if(max == best_ever && positions_at_max.size()>0) {
//		std::cout<<"o"<<std::endl;
		int random_bit_to_flip = rand()%positions_at_max.size();
		random_bit_to_flip = positions_at_max[random_bit_to_flip];
//		std::cout<<"Flp: "<<random_bit_to_flip;
		vec[random_bit_to_flip] = 1-vec[random_bit_to_flip];
	}
	else if(!set_max){
		//a local optimum is reached
		std::cout<<"At local optimum"<<std::endl;
		return -1;
	}
	else {
		std::cout<<"WTF?????????????????????????????????????????????????"<<std::endl;
	}
	return max;
}

double HillClimb(std::ostream& out) {
	//setup logger
	std::ofstream fout;
	fout.open("log_out.csv",std::ios::app);
	int* vec;
	vec = new int[150];
	for(int i=0;i<150;i++) {
		vec[i] = rand()%2;
	}
	out<<"Initial string: ";
	print_vector(out,vec);

	int iterations = 0;
	int current_value = 0;
	double best_ever = 0;
	bool optimum_found = false;
	while(iterations < MAX_ITERATIONS) {
		std::cout<<"Iteration "<<iterations<<" ";
		print_vector(std::cout,vec);
		cout.flush();

		if(!optimum_found) current_value = getSuccessor(vec,best_ever);

		std::cout<<" = "<<current_value<<std::endl;

		if(current_value>best_ever) {
			best_ever = current_value;
		}
		else if(current_value==MAX_FITNESS && !optimum_found) {
			std::cout<<"Optimum found"<<std::endl;
			optimum_found = true;
		}
		iterations++;
		//print to logger
		fout<<iterations<<","<<current_value<<std::endl;
	}
	out<<std::endl<<"Final string:   ";
	print_vector(out,vec);
	out<<std::endl<<"After "<<iterations<<" iterations maximum found: "<<best_ever<<std::endl;
	if(best_ever==64) {
		print_vector(cout,vec);
		std::cout<<std::endl;
	}
	return best_ever;
}

int main() {
	std::ofstream fout;
	fout.open("data");
	double best_ever=LOWER_BOUND;
	double result;
	int number_of_times_best_found=0;
	int number_of_times_over_50=0;

	int number_of_runs = 30;
	for(int i=0;i<number_of_runs;i++) {
		fout<<"Test #"<<i<<":"<<std::endl;
		srand(i);
		result = HillClimb(fout);
		fout<<std::endl;
		if(result > best_ever) {
			best_ever = result;
			number_of_times_best_found=0;
		}
		if(result==best_ever) number_of_times_best_found++;
		if(result>=50) number_of_times_over_50++;
	}

	std::cout<<"Found "<<best_ever<<" "<<number_of_times_best_found/double(number_of_runs)*100.<<"% of the time"<<std::endl;
	std::cout<<"Found over 50 "<<number_of_times_over_50/double(number_of_runs)*100.<<"% of the time"<<std::endl;

}

