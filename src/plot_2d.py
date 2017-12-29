from mpl_toolkits.mplot3d import Axes3D
from scipy.stats import gaussian_kde
import matplotlib.pyplot as plt
import numpy as np
import readfile

def readfile(filename):
	file = open(filename)
	res = [[] for i in range(8)];
	res = {'id':[],'ra':[],'dec':[],'redshift':[],
			'color1':[],'color2':[],'color3':[],'color4':[],
			'r':[],'cluster':[]}

	for line in file:
		list = line.split()

		res['id'].append(list[0]);
		res['ra'].append(float(list[1]));
		res['dec'].append(float(list[2]));
		res['redshift'].append(float(list[3]));
		res['color1'].append(float(list[4]));
		res['color2'].append(float(list[5]));
		res['color3'].append(float(list[6]));
		res['color4'].append(float(list[7]));
		res['r'].append(float(list[8]));
		res['cluster'].append(int(list[9]));

	return res


def plot_data(data,outputfile):

	ra = np.array(data['ra'])
	dec = np.array(data['dec'])
	s = np.array([70-100*i for i in data['redshift']])
	
	plt.scatter(ra, dec, c='b', s=s, edgecolor='')
	plt.xlabel("ra")
	plt.ylabel("dec")
	#plt.show()
	plt.savefig(outputfile+"_data")


def plot_color(data,i,outputfile):
	
	ra = np.array(data['ra'])
	dec = np.array(data['dec'])
	s = np.array([70-100*i for i in data['redshift']])
	if i>0 and i<5:
		c = np.array(data['color'+str(i)])

	plt.scatter(ra, dec, c=c, s=s, edgecolor='')
	plt.xlabel("ra")
	plt.ylabel("dec")
	#plt.show()
	plt.savefig(outputfile+"_color"+str(i))


def plot_clusters(data,outputfile):

	ra = np.array(data['ra'])
	dec = np.array(data['dec'])
	s = np.array([70-100*i for i in data['redshift']])
	c = np.array(data['cluster'])

	plt.scatter(ra, dec, c=c, s=s, edgecolor='')
	plt.xlabel("ra")
	plt.ylabel("dec")
	#plt.show()
	plt.savefig(outputfile+"_clusters")


def plot_density(data,outputfile):
	
	ra = np.array(data['ra'])
	dec = np.array(data['dec'])
	s = np.array([70-100*i for i in data['redshift']])
	xy = np.vstack([ra,dec])
	c = gaussian_kde(xy)(xy)

	plt.scatter(ra, dec, c=c, s=s, edgecolor='')
	plt.xlabel("ra")
	plt.ylabel("dec")
	#plt.show()
	plt.savefig(outputfile+"_density")


data1 = readfile("kmeans_output.txt")

plot_data(data1,"kmeans")
plot_clusters(data1,"kmeans")
#plot_density(data1,"kmeans")


data2 = readfile("density_output.txt")

plot_clusters(data2,"density")



data3 = readfile("mine_output.txt")

plot_clusters(data3,"mine")


























