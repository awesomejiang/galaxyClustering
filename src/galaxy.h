#ifndef GALAXY_H
#define GALAXY_H
#include <math.h>
#include <string.h>

class Galaxy{
	public:
	char id[30] = "\0";
	double ra = 0;
	double dec = 0;
	double redshift = 0;
	//u,g,r,i,z from oringin data.txt
	//spec1,2,3,4 = u-g,g-r,r-i,i-z

	double color1 = 0;
	double color2 = 0;
	double color3 = 0;
	double color4 = 0;

	double r = 0;
	//default cluster 0.
	int cluster = -1;

	double dist(Galaxy&);
	double colordist(Galaxy&);
	double gaussian(Galaxy&, double);
	double positiongaussian(Galaxy&, double);
	Galaxy& operator= (const Galaxy&);
	void print();
};




double Galaxy::dist(Galaxy &A){
	double res = 0;
	res = sqrt(
			pow(2*M_PI/360*(ra*redshift-A.ra*A.redshift),2)
		+	pow(2*M_PI/360*(dec*redshift-A.dec*A.redshift),2)
		+	pow(redshift-A.redshift,2)
		+	pow(color1-A.color1,2)
		+	pow(color2-A.color2,2)
		+	pow(color3-A.color3,2)
		+	pow(color4-A.color4,2)
		);
	return res;
}


double Galaxy::colordist(Galaxy &A){
	double res = 0;
	res = sqrt(
			pow(color1-A.color1,2)
		+	pow(color2-A.color2,2)
		+	pow(color3-A.color3,2)
		+	pow(color4-A.color4,2)
		);
	return res;
}

double Galaxy::gaussian(Galaxy& neighbor, double sigma){
	/*double mu = sqrt(
			pow(2*M_PI/360*(ra-neighbor.ra),2)
		+	pow(2*M_PI/360*(dec-neighbor.dec),2)
		+	pow(redshift-neighbor.redshift,2)
		);
	*/
	double mu = dist(neighbor);

	return 1/(sqrt(2*M_PI)*sigma)*pow(M_E, -0.5*pow((mu/sigma),2));
}

double Galaxy::positiongaussian(Galaxy& neighbor, double sigma){
	double mu = sqrt(
			pow(2*M_PI/360*(ra*redshift-neighbor.ra*neighbor.redshift),2)
		+	pow(2*M_PI/360*(dec*redshift-neighbor.dec*neighbor.redshift),2)
		+	pow(redshift-neighbor.redshift,2)
		);
	
	//double mu = dist(neighbor);

	return 1/(sqrt(2*M_PI)*sigma)*pow(M_E, -0.5*pow((mu/sigma),2));
}

Galaxy& Galaxy::operator= (const Galaxy& A){
	strcpy(id, A.id);
	ra = A.ra;
	dec = A.dec;
	redshift = A.redshift;

	color1 = A.color1;
	color2 = A.color2;
	color3 = A.color3;
	color4 = A.color4;

	r = A.r;
	
	cluster = A.cluster;

	return *this;
}

void Galaxy::print(){
		printf("ra:%3f,dec:%3f,redshift:%3f,1:%3f,2:%3f,3:%3f,4:%3f,cluster:%d\n", ra,dec,redshift,color1,color2,color3,color4,cluster);
}

#endif