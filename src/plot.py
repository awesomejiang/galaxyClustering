from mpl_toolkits.mplot3d import Axes3D
from scipy.stats import gaussian_kde
import matplotlib.pyplot as plt
import numpy as np
import readfile

list = []
for i in range(45):
	if i>=2 and i<=44:
		list .append(i)
x = np.array(list)
print(x)
y = np.array([0.035621532	,0.048775069	,0.090489966	,0.205005383	,0.241863617	,0.029410826	,0.029410826	,0.028993772	,0.028993772	,0.028993772	,0.29890921	,0.29890921	,0.29890921	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.192498866	,0.079258273	,0.09679686	,0.182460005	,0.170460202	,0.149293178	,0.035621532	,0.048775069	,0.090489966	,0.205005383	,0.241863617
])
print(y)


plt.scatter(x,y, )
plt.xlabel("k")
plt.ylabel("R^2")
#plt.show()
plt.savefig("figure5")

















