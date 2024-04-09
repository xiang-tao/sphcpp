# 导入我们所需的库 as：即给库取别名，方便书写
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import matplotlib

rc('mathtext', default='regular')

ary_x = np.genfromtxt("coor_x.txt", dtype=None)
ary_p = np.genfromtxt("coor_p.txt", dtype=None)
# 定义数据
lth = len(ary_x)
x0 = np.zeros(lth)
y0 = np.zeros(lth)
k = 0
# 定义数据
for i in range(lth):
    if(ary_x[i] >= -0.4 and ary_x[i] <= 0.4):
        x0[k] = ary_x[i]
        y0[k] = ary_p[i]
        k += 1
x = np.zeros(k)
y = np.zeros(k)
for i in range(k):
    x[i] = x0[i]
    y[i] = y0[i]
x = np.sort(x)
x_sy = np.argsort(x)
for i in range(k):
    y[i] = y[x_sy[i]]

plt.plot(x, y, linestyle='--', color='g')
plt.xlabel('x')
plt.ylabel(r'p')

plt.show()  # 显示所绘图形
