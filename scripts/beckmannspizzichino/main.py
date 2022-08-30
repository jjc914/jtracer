import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

xvalues = []
yvalues = []
zvalues = []
with open("input.txt") as file:
    lines = file.readlines()
    for line in lines:
        line = line.strip()
        x, y, z = line.split(', ')
        x = float(x[5:])
        y = float(y)
        z = float(z[:-1])
        xvalues.append(x)
        yvalues.append(y)
        zvalues.append(z)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

X,Y = np.meshgrid(np.arange(-1,1,0.1), np.arange(-1,1,0.1))
Z = np.asarray([[0]*20]*20)

ax.set_xlim([-1, 1])
ax.set_ylim([-1, 1])
ax.set_zlim([-1, 1])

#ax.plot_surface(X, Y, Z, alpha=1)

ax.quiver(0, 0, 0, xvalues, zvalues, yvalues, color='r')
ax.quiver(0.5, 1, 1, -0.5, -1, -1, color='b')
# ax.quiver(0.1, 0.2, 2, -0.1, -0.2, -2, color='b')
ax.quiver(0, 0, 0, 0, 0, 1, color='g')
ax.quiver(0, 0, 0, 0.534522, -0.267261, 0, color='purple')

plt.show()
