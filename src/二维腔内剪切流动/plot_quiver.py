# 导入我们所需的库 as：即给库取别名，方便书写
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import math

rc('mathtext', default='regular')

ary = np.genfromtxt("coor1000.txt", dtype=None)
# 定义数据

x = 1000*ary[:, 0]   # 取出10个随机数
y = 1000*ary[:, 1]   # 取出10个随机数

ary_v = np.genfromtxt("coor1000_v.txt", dtype=None)
# 定义数据

xv = 1000*ary_v[:, 0]   # 取出10个随机数
yv = 1000*ary_v[:, 1]   # 取出10个随机数
C = np.zeros(len(x))

for i in range(len(x)):
    C[i] = math.sqrt(xv[i]**2+yv[i]**2)

plt.quiver(x, y, xv, yv, C)
plt.show()
