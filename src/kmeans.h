
#ifndef KMEANS_H
#define KMEANS_H

#include <algorithm>
#include <iostream>
#include <limits.h>
#include "galaxy.h"

vector<Galaxy> kmeans(vector<Galaxy> &data, int k){
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
				double tmp_dist = galaxy.dist(centers[i]);
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
					new_center.ra += galaxy.ra;
					new_center.dec += galaxy.dec;
					new_center.redshift += galaxy.redshift;
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
			if( centers[i].dist(new_centers[i]) ){
				flag = 1;
			}
			centers[i] = new_centers[i];
		}
		//cout<<endl;
	}

	return centers;
}


#endif