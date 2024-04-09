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

    x0 = np.arange(0, 4+dx, dx)  # arange包含起始不包含末尾，即此为0-4，步长为dx
    x1 = np.arange(-dx/2, 4+dx+dx/2, dx)
    y = np.arange(dy, 4+dy, dx)

    # np.zeros_like(a):返回与数组a相同维度，但是值是0的数组
    # np.full_like(a,dx):返回与数组a相同的维度，但是值是dx的数组
    # np.column_stack(a,b):将数组a,b按照列合并
    # np.vstack(a,b):按照垂直方向堆叠数组成一个新数组，a,b的维度要一致
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


def find_neighbors_within_distance(points, h):
    tree = cKDTree(points)
    neighbors = tree.query_ball_tree(tree, h)
    return neighbors


@numba.jit(nopython=True)
def kernel(r, h):
    d = np.sqrt(np.sum(r**2, axis=-1))
    q = d/h
    val = 7 * (1-q/2)**4 * (2*q+1) / (4*np.pi*h**2)
    return val


@numba.jit(nopython=True)
def gradkernel(r, h):
    d = np.sqrt(np.sum(r**2))
    q = d/h
    val = -35/(4*np.pi*h**3) * q * (1-q/2)**3
    val /= d
    return val


# 连续密度法，使用公式为p119-4.34
@numba.jit(nopython=True)
def change_rho(particles, idx):
    num = particles['rho'].shape[0]
    position = particles["position"]
    velocity = particles["velocity"]
    mass = dx*dy*particles['rho']
    result = np.zeros(num)
    for i in range(num):
        for j in idx[i]:
            if i != j:  # 排除自己
                rij = position[i] - position[j]
                gk = gradkernel(rij, H) * rij
                vij = velocity[i] - velocity[j]
                result[i] += mass[j]*np.dot(gk, vij)
        particles['rho'][i] += dt * result[i]


@numba.jit(nopython=True)
def change_position(particles, idx):
    num = particles['rho'].shape[0]
    position = particles["position"]
    velocity = particles["velocity"]
    rho = particles["rho"]
    mass = dx*dy*rho
    result = np.zeros((num, 2))
    for i in range(num):
        for j in idx[i]:
            rhoij = (rho[i] + rho[j])/2
            vij = velocity[j] - velocity[i]
            rij = position[i] - position[j]
            ke = kernel(rij, H)
            result[i] += mass[j]*vij*ke/rhoij  # 此处使用了XSPH公式，见公众号
        result[i] = velocity[i] + 0.5*result[i]

    tag = particles['isBd']  # tag表示实粒子为false，虚粒子为true，原因见上面代码初始化
    # ~tag与tag相反，当为true时显示，false去掉，故只对实粒子更新位置
    particles['position'][~tag] += dt * result[~tag]


def change_p(particles, i):
    B = c0**2*rho0/gamma
    particles['pressure'] = B * ((particles['rho']/rho0)**gamma - 1)
    # particles['sound']是声速，是压力对密度的偏导数开方，见公众号描述，求导后刚好是下式形式
    particles['sound'] = (
        B*gamma/rho0 * (particles['rho']/rho0)**(gamma-1))**0.5


@numba.jit(nopython=True)
def change_v(particles, idx):
    num = particles['rho'].shape[0]
    rho = particles['rho']
    mass = dx*dy*rho  # 用哪一步密度计算质量
    position = particles["position"]
    velocity = particles["velocity"]
    sound = particles["sound"]
    pressure = particles["pressure"]
    result = np.zeros((num, 2))
    for i in range(num):
        for j in idx[i]:
            if i != j:  # 排除自己
                val = pressure[i]/rho[i]**2 + pressure[j]/rho[j]**2
                rij = position[i] - position[j]
                gk = gradkernel(rij, H) * rij
                vij = velocity[i] - velocity[j]
                pij = 0
                # 此处在计算人工粘性项
                if np.dot(rij, vij) < 0:
                    pij = -alpha * (sound[i] + sound[j])/2
                    pij *= H*np.dot(rij, vij)/(np.dot(rij, rij)+0.01*H*H)
                    pij /= (rho[i] + rho[j])/2
                result[i] += mass[j]*(val+pij)*gk
    result = -result + g  # 考虑重力
    tag = particles['isBd']
    particles['velocity'][~tag] += dt * result[~tag]  # 仍然只更新实粒子的速度

# 密度重置
# @numba.jit(nopython=True)


def rein_rho(particles, idx):
    num = particles['rho'].shape[0]
    rho = particles['rho']
    mass = dx*dy*rho  # 用哪一步密度计算质量
    position = particles["position"]
    vol = mass/rho
    A = np.zeros((num, 3, 3))
    for i in range(num):
        for j in idx[i]:
            rij = position[i] - position[j]
            wij = kernel(rij, H)
            Abar = np.zeros((3, 3))
            Abar[0, 1] = rij[0]
            Abar[0, 2] = rij[1]
            Abar[1, 2] = rij[0]*rij[1]
            Abar += Abar.T
            Abar[0, 0] = 1
            Abar[1, 1] = rij[0]**2
            Abar[2, 2] = rij[1]**2
            A[i] += Abar*wij*vol[j]
    for i in range(num):
        particles['rho'][i] = 0
        condA = np.linalg.cond(A[i])  # 计算矩阵条件数
        if condA < 1e15:
            invA = np.linalg.inv(A[i])  # 矩阵求逆
            for j in idx[i]:
                rij = position[i] - position[j]
                wij = kernel(rij, H)
                wmls = invA[0, 0] + invA[1, 0]*rij[0] + invA[2, 0]*rij[1]
                particles['rho'][i] += wij*wmls*mass[j]
        else:
            # 当逆矩阵不存在时
            sum_numer = 0
            sum_denom = 0
            for j in idx[i]:
                rij = position[i] - position[j]
                wij = kernel(rij, H)
                mb = mass[j]
                rho_b = particles['rho'][j]
                sum_numer += mb*wij
                sum_denom += (mb*wij)/rho_b
            if sum_denom != 0:
                particles['rho'][i] = sum_numer/sum_denom


def draw(particles, i):
    plt.clf()
    tag = np.where(particles['isBd'])
    c = particles['pressure']
    c[tag] = 0
    plt.scatter(particles['position'][:, 0],
                particles['position'][:, 1], c=c, cmap='jet', s=5)
    plt.colorbar(cmap='jet')
    plt.clim(0, 7)
    plt.title(f"Time Step: {i}")
    fname = './' + 'test_' + str(i+1).zfill(10) + '.png'
    plt.savefig(fname)
    plt.pause(0.005)


for i in range(maxstep):
    print("i:", i)
    idx = find_neighbors_within_distance(particles["position"], 2*H)
    idx = List([np.array(neighbors) for neighbors in idx])
    change_rho(particles, idx)
    change_p(particles, i)
    change_v(particles, idx)
    change_position(particles, idx)
    # if i % 30 == 0 and i != 0:
    #     rein_rho(particles, idx)
    draw(particles, i)

tag = np.where(particles['isBd'])
c = particles['velocity'][:, 0]
plt.scatter(particles['position'][:, 0],
            particles['position'][:, 1], c=c, cmap='jet', s=5)
plt.colorbar(cmap='jet')
plt.clim(0, 7)
plt.grid(True)
plt.show()
