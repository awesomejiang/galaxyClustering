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



def plot_cmr(data,i,outputfile):
	
	r = np.array(data['r'])
	if i>0 and i<5:
		color = np.array(data['color'+str(i)])
	c = np.array(data['cluster'])
		

	plt.scatter(r, color, c=c, edgecolor='')
	plt.xlabel("r")
	plt.ylabel('color'+str(i))
	#plt.show()
	plt.savefig(outputfile+"_cmr"+str(i))



data1 = readfile("kmeans_output.txt")
"""
for i in range(4):
	plot_cmr(data1,i+1,"kmeans")


data2 = readfile("density_output.txt")

for i in range(4):
	plot_cmr(data2,i+1,"density")

"""
data3 = readfile("mine_output.txt")

for i in range(4):
	plot_cmr(data3,i+1,"mine")





























