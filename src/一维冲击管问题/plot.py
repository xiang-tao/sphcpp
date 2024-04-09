# 导入我们所需的库 as：即给库取别名，方便书写
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import matplotlib

rc('mathtext', default='regular')

ary = np.genfromtxt("coor.txt", dtype=None)
# 定义数据

x = 10*ary   # 取出10个随机数
y = np.zeros(len(x))


# 绘图
# 1. 确定画布
# plt.figure(figsize=(8, 4))  # figsize:确定画布大小

# 2. 绘图
plt.scatter(x,  # 横坐标
            y,  # 纵坐标
            c='red',  # 点的颜色
            label='t=o')  # 标签 即为点代表的意思
# 3.展示图形
plt.legend()  # 显示图例

plt.show()  # 显示所绘图形
