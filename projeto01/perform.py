import subprocess
import matplotlib.pyplot as plt
import os

def roda_com_entrada(ex, in_f):
    proc = subprocess.run([ex, in_f], text=True, capture_output=True)

    return proc.stdout

arq = 1
input = []
output = []

os.chdir("./inputs")
for file in os.listdir():
    if file.endswith(".txt"):
        input.append(file.split('.')[0])

os.chdir("..")
for k in input:
    out = roda_com_entrada("./projetoGuloso", k)
    outputTuple = tuple(out.strip().split(' '))
    output.append(outputTuple)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

for nFilme, nCat, t, total in output:
     ax.scatter(nFilme, nCat, t)

ax.set_xlabel('n Filme')
ax.set_ylabel('tempo(ns)')
ax.set_zlabel('n Categoria')

plt.savefig('my_plot.png')
