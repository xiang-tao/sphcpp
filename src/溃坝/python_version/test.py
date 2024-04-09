import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import cKDTree
import time
import numba
from numba.typed import List
dx = 0.03
dy = 0.03
rho0 = 1000
H = 0.92*np.sqrt(dx**2+dy**2)
dt = 0.001
c0 = 10
g = np.array([0.0, -9.8])
gamma = 7
alpha = 0.1
maxstep = 2000
dtype = [("position", "float64", (2, )),
         ("velocity", "float64", (2, )),
         ("rho", "float64"),
         ("mass", "float64"),
         ("pressure", "float64"),
         ("sound", "float64"),
         ("isBd", "bool")]


def initial_position(dx, dy):
    pp = np.mgrid[2*dx:1+dx:dx, 2*dy:2+dy:dy].reshape(2, -1).T

    x0 = np.arange(0, 4+dx, dx)
    x1 = np.arange(-dx/2, 4+dx+dx/2, dx)
    y = np.arange(dy, 4+dy, dx)

    bp0 = np.column_stack((x0, np.zeros_like(x0)))
    bp1 = np.column_stack((x1, np.full_like(x1, dx)))
    bp = np.vstack((bp0, bp1))

    lp0 = np.column_stack((np.zeros_like(y), y))
    lp1 = np.column_stack((np.full_like(y, dy), y+dy/2))
    lp = np.vstack((lp0, lp1))

    rp0 = np.column_stack((np.full_like(y, 4), y))
    rp1 = np.column_stack((np.full_like(y, 4-dy), y+dy/2))
    rp = np.vstack((rp0, rp1))
    bpp = np.vstack((bp, lp, rp))
    return pp, bpp


# 初始化
pp, bpp = initial_position(dx, dy)
num_particles = pp.shape[0] + bpp.shape[0]
particles = np.zeros(num_particles, dtype=dtype)
particles["rho"] = rho0
particles['position'] = np.vstack((pp, bpp))
particles['isBd'][pp.shape[0]:] = True
particles['isBd'][:pp.shape[0]] = False
# Visualization
color = np.where(particles['isBd'], 'red', 'blue')
plt.scatter(particles['position'][:, 0],
            particles['position'][:, 1], c=color, s=5)
plt.grid(True)
plt.show()
