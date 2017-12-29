#ifndef DENSITY_H
#define DENSITY_H


#include "galaxy.h"
#include <math.h>
#include <vector>


//calculate density in every galaxy positon by adding all neighbor attributes
vector<Galaxy> density(vector<Galaxy> &data, int k, double sigma){
	vector<double> res;
	for(auto galaxy:data){
		double tmp = 0;
		for(auto neighbor:data){
			if(galaxy.id != neighbor.id)
				tmp += galaxy.gaussian(neighbor,sigma);
		}
		res.push_back(tmp);
	}

	vector<Galaxy> centers;
	int len = res.size();
	for(int i=0;i<k;i++){
		double max = -1;
		double pos = -1;
		for(int j=0;j<len;j++){
			double tmp = res[j];
			if(tmp>max && data[j].cluster==-1 ){
				max = tmp;
				pos = j;
			}
		}
		data[pos].cluster = i;
		centers.push_back(data[pos]);

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

	return centers;
}

#endif