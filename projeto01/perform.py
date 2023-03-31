import subprocess
import matplotlib.pyplot as plt

def roda_com_entrada(ex, in_f):
    proc = subprocess.run([ex, in_f], text=True, capture_output=True)

    return proc.stdout

nFilme = 10
tipo = "Guloso"
nCategoria = 1
arq = 1
input = []
output = []

for i in range(5):
        for j in range(6):
            input.append("in" + "_" + str(nFilme) + "_" + str(nCategoria))
            nCategoria += 1
            arq += 1
        nCategoria = 1
        nFilme = nFilme * 10

for k in input:
    out = roda_com_entrada('./projetoGuloso', k)
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
