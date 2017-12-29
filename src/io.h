#ifndef IO_H
#define IO_H
#include "galaxy.h"
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>

#define _USE_MATH_DEFINES

using namespace std;


vector<Galaxy> read_file(string filename){
	ifstream input_file;
	input_file.open(filename.c_str());
	if(!input_file){
		cout<<"file does not exist!"<<endl;
		exit(0);
	}

	vector<Galaxy> res;
	//read lines
	//sequence:	objid	ra	dec	redshift	petroMag_u	petroMag_g	petroMag_r	petroMag_i	petroMag_z	petroMagErr_u	petroMagErr_g	petroMagErr_r	petroMagErr_i	petroMagErr_z
	while( !input_file.eof() ){
		Galaxy tmp;

		double u, g, r, i, z;
		input_file>>tmp.id;
		input_file>>tmp.ra;
		input_file>>tmp.dec;
		input_file>>tmp.redshift;
		input_file>>u;
		input_file>>g;
		input_file>>r;
		input_file>>i;
		input_file>>z;

		tmp.color1 = u-g;
		tmp.color2 = g-r;
		tmp.color3 = r-i;
		tmp.color4 = i-z;

		tmp.r = r;

		if(tmp.redshift>0.02 && tmp.redshift<0.2)
			res.push_back(tmp);
	}

	input_file.close();
	cout<<"input number:"<<res.size()<<endl;
	return res;
}

void output(vector<Galaxy> &data, string filename){
	ofstream output_file;
	output_file.open(filename);
	
	for(auto galaxy:data){
		output_file<<galaxy.id<<"\t";
		output_file<<galaxy.ra<<"\t";
		output_file<<galaxy.dec<<"\t";
		output_file<<galaxy.redshift<<"\t";
		output_file<<galaxy.color1<<"\t";
		output_file<<galaxy.color2<<"\t";
		output_file<<galaxy.color3<<"\t";
		output_file<<galaxy.color4<<"\t";
		output_file<<galaxy.r<<"\t";
		output_file<<galaxy.cluster<<endl;

	}
	output_file.close();
}
#endif
