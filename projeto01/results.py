import matplotlib.pyplot as plt
import numpy as np
import os

path = "./outputs/aleatorio"
output = []
trend = []

os.chdir(path)
for file in os.listdir():
    if file.endswith(".txt"):
        with open(file, 'r') as f:
            outputTuple = tuple(map(int, f.read().strip().split(' ')))
            if (outputTuple[0] <= 30000):
                output.append(outputTuple)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

# for nFilme, nCat, t, total in output:
#     ax.scatter(nFilme, nCat, t)
zip(*output)
ax.scatter(*zip(*output))

ax.set_xlabel('n Filme')
ax.set_ylabel('n Categoria')
ax.set_zlabel('tempo(ms)')


plt.savefig('img1.png')
plt.show()

fig2 = plt.figure()
n_t = [(t[0], t[2]) for t in output]
ax2 = fig2.add_subplot()
ax2.scatter(*zip(*n_t))
ax2.set_xlabel('n filme')
ax2.set_ylabel('tempo(ms)')

plt.savefig('img2.png')
plt.show()





