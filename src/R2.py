import numpy as np

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


def get_r2_numpy(r, c):
	x = np.array(r)
	y = np.array(c)
	slope, intercept = np.polyfit(x, y, 1)
	r_squared = 1 - (sum((y - (slope * x + intercept))**2) / ((len(y) - 1) * np.var(y, ddof=1)))
	return r_squared


def R2(data):
	max_cluster = -1
	for i in data['cluster']:
		if i >max_cluster:
			max_cluster = i
			
	counter = 0
	r2 = 0
	for cluster in range(max_cluster+1):
		r = []
		c1 = []
		c2 = []
		c3 = []
		c4 = []
		n = len(data['cluster'])
		for i in range(n):
			if data['cluster'][i] == cluster:
				r.append(data['r'][i])
				c1.append(data['color1'][i])
				c2.append(data['color2'][i])
				c3.append(data['color3'][i])
				c4.append(data['color4'][i])
		
		if len(r)>=4:
			counter = counter+1
			r2 = r2+ (get_r2_numpy(r,c1)+get_r2_numpy(r,c1)+get_r2_numpy(r,c1)+get_r2_numpy(r,c1))/4
	
	if counter == 0:
		return "too few"
	else:
		return str(max_cluster+1)+'\t'+str(r2/counter)
		



data1 = readfile("kmeans_output.txt")

data2 = readfile("density_output.txt")

data3 = readfile("mine_output.txt")

file = open("text.txt",'a')
file.write(str(R2(data3))+"\n")

#print(R2(data3))







