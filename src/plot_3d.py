from mpl_toolkits.mplot3d import Axes3D
from scipy.stats import gaussian_kde
import matplotlib.pyplot as plt
import numpy as np

def readfile(filename):
	file = open(filename)
	res = [[] for i in range(8)];
	res = {'id':[],'ra':[],'dec':[],'redshift':[],
			'color1':[],'color2':[],'color3':[],'color4':[],
			'errc1':[],'errc2':[],'errc3':[],'errc4':[],'r':[],'cluster':[]}

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

	fig = plt.figure()
	ax = fig.add_subplot(111, projection='3d')
	
	ra = np.array(data['ra'])
	dec = np.array(data['dec'])
	z = np.array(data['redshift'])

	ax.scatter(ra, dec, z, c='b')

	ax.set_xlabel('X Label')
	ax.set_ylabel('Y Label')
	ax.set_zlabel('Z Label')

	plt.show()
	#plt.savefig(outputfile+"_data")



def plot_color(data,i,outputfile):
	
	fig = plt.figure()
	ax = fig.add_subplot(111, projection='3d')
	
	ra = np.array(data['ra'])
	dec = np.array(data['dec'])
	z = np.array(data['redshift'])
	if i>0 and i<5:
		c = np.array(data['color'+str(i)])

	ax.scatter(ra, dec, z, c=c)

	ax.set_xlabel('X Label')
	ax.set_ylabel('Y Label')
	ax.set_zlabel('Z Label')

	plt.show()
	#plt.savefig(outputfile+"_color"+str(i))



def plot_clusters(data,outputfile):

	fig = plt.figure()
	ax = fig.add_subplot(111, projection='3d')
	
	ra = np.array(data['ra'])
	dec = np.array(data['dec'])
	z = np.array(data['redshift'])
	c = np.array(data['cluster'])

	ax.scatter(ra, dec, z, c=c)

	ax.set_xlabel('X Label')
	ax.set_ylabel('Y Label')
	ax.set_zlabel('Z Label')

	plt.show()
	#plt.savefig(outputfile+"_clusters")


def plot_density(data,outputfile):

	fig = plt.figure()
	ax = fig.add_subplot(111, projection='3d')
	
	ra = np.array(data['ra'])
	dec = np.array(data['dec'])
	z = np.array(data['redshift'])
	xyz = np.vstack([ra,dec,z])
	c = gaussian_kde(xyz)(xyz)

	ax.scatter(ra, dec, z, c=c)

	ax.set_xlabel('X Label')
	ax.set_ylabel('Y Label')
	ax.set_zlabel('Z Label')

	plt.show()
	#plt.savefig(outputfile+"_density")

data1 = readfile("kmeans_output.txt")

plot_data(data1,"kmeans")
plot_clusters(data1,"kmeans")
#plot_density(data1,"kmeans")


data2 = readfile("density_output.txt")

plot_clusters(data2,"density")



data3 = readfile("mine_output.txt")

plot_clusters(data3,"mine")

























