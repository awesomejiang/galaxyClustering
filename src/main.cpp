#include <iostream>
#include <string>
#include <vector>
#include "galaxy.h"
#include "io.h"
#include "kmeans.h"
#include "density.h"
#include "mine.h"

#define KMEANS_K 17
#define DENSITY_K 15
#define DENSITY_SIGMA 3
#define MINE_K 3
#define MINE_SIGMA 1.5
#define MINE_M 19
#define PY "python R2.py"

using namespace std;


void run_kmeans(vector<Galaxy> galaxy_kmeans,int k){

	//run kmeans
	//cout<<"running kmeans algorithm..."<<endl;
	kmeans(galaxy_kmeans,k);
	//cout<<"kmeans algorithm end."<<endl;

	//cout<<"output cluster info into txt."<<endl;
	string output_file1 = "kmeans_output.txt";
	output(galaxy_kmeans, output_file1);
}

void run_density(vector<Galaxy> galaxy_density, int k, double sigma){

	//run density algo
	//cout<<"running density algorithm..."<<endl;
	density(galaxy_density, k, sigma);
	//cout<<"density algorithm end."<<endl;

	//cout<<"output cluster info into txt."<<endl;
	string output_file2 = "density_output.txt";
	output(galaxy_density, output_file2);

}

void run_mine(vector<Galaxy> galaxy_mine, int k, double sigma, int m){

	//run mine algo
	//cout<<"running mine algorithm..."<<endl;
	vector<Galaxy> galaxy_mine_output = mine(galaxy_mine, k, sigma, m);
	//cout<<"density algorithm end."<<endl;

	//cout<<"output cluster info into txt."<<endl;
	string output_file3 = "mine_output.txt";
	output(galaxy_mine_output, output_file3);
}

int main(){
	srand((unsigned)time(NULL));
	
	//input datum file
	string input_file = "data.txt";
	vector<Galaxy> data = read_file(input_file);
	cout<<"load "<<data.size()<<" lines of datum successfully!"<<endl;

	run_kmeans(data,KMEANS_K);//int k
	run_density(data,DENSITY_K,DENSITY_SIGMA);//int k, double sigma
	run_mine(data,MINE_K,MINE_SIGMA,MINE_M);//int k, double sigma, int m
/*for(int n =0;n<10;n++){
	for(int i = 3;i<8;i++){
		for(double j=1;j<5;j=j+0.5){
			for(int k=15;k<20;k++){
				run_mine(data,i,j,k);
				//printf("%d\t%f\t%d\n",i,j,k);
				system(PY);
			}
		}
	}
}*/
	system(PY);
	//cout<<"call plot command"<<endl;
	cout<<"prom end."<<endl;
}







