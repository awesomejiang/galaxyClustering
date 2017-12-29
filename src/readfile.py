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
		res['errc1'].append(float(list[8]));
		res['errc2'].append(float(list[9]));
		res['errc3'].append(float(list[10]));
		res['errc4'].append(float(list[11]));
		res['r'].append(float(list[12]));
		res['cluster'].append(int(list[13]));

	return res


























