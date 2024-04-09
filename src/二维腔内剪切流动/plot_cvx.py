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
lth = len(x)
x0 = np.zeros(lth)
y0 = np.zeros(lth)
k = 0

ary_v = np.genfromtxt("coor1000_v.txt", dtype=None)
# 定义数据

xv = 1000*ary_v[:, 0]   # 取出10个随机数
yv = 1000*ary_v[:, 1]   # 取出10个随机数

for i in range(lth):
    if(x[i] < 0.5+1.0/80 and x[i] > 0.5-1.0/80):
        x0[k] = y[i]
        y0[k] = xv[i]
        k += 1

print(k)
xx = np.zeros(k)
yy = np.zeros(k)

for i in range(k):
    xx[i] = x0[i]
    yy[i] = y0[i]

# 绘图
# 1. 确定画布
# plt.figure(figsize=(8, 4))  # figsize:确定画布大小

# 2. 绘图
plt.scatter(xx,  # 横坐标
            yy,  # 纵坐标
            c='red',  # 点的颜色
            label='t=0')  # 标签 即为点代表的意思
# 3.展示图形
plt.legend()  # 显示图例

plt.show()  # 显示所绘图形
