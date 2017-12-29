#ifndef MINE_H
#define MINE_H


#include "galaxy.h"
#include <math.h>
#include <vector>


struct Test {  
   	double d;
   	double p;
   	int n;  
};

bool SortByM1( const Test &v1, const Test &v2){
   	return v1.d < v2.d;
}  
  
vector< vector<Galaxy> > colorkmeans(vector<Galaxy> data, int k){
	vector< vector<Galaxy> > res(k,vector<Galaxy>(0));

	//find initial k seeds randomly
	random_shuffle(data.begin(), data.end());
	vector<Galaxy> centers;
	for(int i=0;i<k;i++){

		Galaxy tmp = data[i];
		strcpy(tmp.id,"cluster center");
		tmp.cluster = i;
		centers.push_back(tmp);
	}

	//iterating
	int flag = 1;
	while(flag){
		//cout<<"kmeans iterating..."<<endl;
		//find nearest center for every galaxy.
		for(auto &galaxy:data){
			double min_dist = (double)INT_MAX;
			int min_center = -1;
			for(int i=0;i<k;i++){
				double tmp_dist = galaxy.colordist(centers[i]);
				if(tmp_dist<min_dist){
					min_dist = tmp_dist;
					min_center = i;
				}
			}
			galaxy.cluster = min_center;
		}


		//modify centers
		vector<Galaxy> new_centers;
		for(int i=0;i<k;i++){
			int counter = 0;
			Galaxy new_center;
			strcpy(new_center.id,"cluster center");
			new_center.cluster = i;

			for(auto &galaxy:data){
				if(galaxy.cluster==i){
					new_center.color1 += galaxy.color1;
					new_center.color2 += galaxy.color2;
					new_center.color3 += galaxy.color3;
					new_center.color4 += galaxy.color4;
					counter++;
				}
			}

			new_center.ra = new_center.ra/counter;
			new_center.dec = new_center.dec/counter;
			new_center.redshift = new_center.redshift/counter;
			new_center.color1 = new_center.color1/counter;
			new_center.color2 = new_center.color2/counter;
			new_center.color3 = new_center.color3/counter;
			new_center.color4 = new_center.color4/counter;

			new_centers.push_back(new_center);
		}

		flag = 0;
		for (int i=0;i<k;i++){
			//printf("\t%1f",centers[i].dist(new_centers[i]));
			if( centers[i].colordist(new_centers[i]) ){
				flag = 1;
			}
			centers[i] = new_centers[i];
		}
		//cout<<endl;
	}

	for(auto &galaxy:data){
		int c = galaxy.cluster;
		galaxy.cluster = -1;
		res[c].push_back(galaxy);
	}
	
	return res;
}



//calculate density in every galaxy positon by adding all neighbor attributes
int positiondensity(vector<Galaxy> &data, double sigma, int m){
	vector<double> res;
	for(auto &galaxy:data){
		double tmp = 0;
		for(auto neighbor:data){
			if(galaxy.id != neighbor.id)
				tmp += galaxy.positiongaussian(neighbor,sigma);
		}
		if(tmp<1){
			galaxy.cluster = -2;
		}
		res.push_back(tmp);
	}
 
  
	vector<Galaxy> centers;
	int counter = 0;
	int len = res.size();
	if(m<len){
		for(int i=0;i<len;i++){
			vector<Test> vecTest;
			for(int j=0;j<len;j++){
				if(i!=j){
					Test test;
					test.d = data[i].positiongaussian(data[j],sigma);
					test.p = res[j];
					test.n = j;
					vecTest.push_back(test);
				}
			}
			sort(vecTest.begin(),vecTest.end(),SortByM1);

			int flag = 0;
			for(int j=0;j<m;j++){
				if(vecTest[j].p>=res[i])
					flag++;
			}
			if(flag == 0){
				data[i].cluster = counter++;
				centers.push_back(data[i]);
			}
		}
	}
//cout<<len<<"\t"<<centers.size()<<endl;
	if(centers.empty()){
		double max = -1;
		int max_n = -1;
		for(int i=0;i<len;i++){
			if(res[i]>max){
				max = res[i];
				max_n = i;
			}
		}
		centers.push_back(data[max_n]);
	}


	for(auto &galaxy:data){
		if(galaxy.cluster==-1){
			double min_dist = (double)INT_MAX;
			int cluster = -1;
			for(auto center:centers){
				double tmp_dist = galaxy.dist(center);
				if(tmp_dist<min_dist){
					min_dist = tmp_dist;
					cluster = center.cluster;
				}
			}
			galaxy.cluster = cluster;
		}
	}

	return counter;
}

vector<Galaxy> mine(vector<Galaxy> &data, int k, double sigma, int m){
	vector<Galaxy> res;
	vector< vector<Galaxy> > subsets = colorkmeans(data, k);

	int cluster_counter = 0;
	for(auto &subset:subsets){
		int count = positiondensity(subset,sigma,m);
		for(auto &galaxy:subset){
			if(galaxy.cluster != -2){
				galaxy.cluster = galaxy.cluster;
			}

			res.push_back(galaxy);
		}
		cluster_counter += count;
	}

	return res;
}

#endif
