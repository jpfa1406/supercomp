import subprocess
import matplotlib.pyplot as plt
import os
import os.path

def roda_com_entrada(ex, in_f):
    proc = subprocess.run([ex, in_f], text=True, capture_output=True)

    return proc.stdout

input = []

os.chdir("./inputs")
for file in os.listdir():
    if file.endswith(".txt"):
        if (os.path.isfile("./inputs" + file) == False):
            input.append(file.split('.')[0])

os.chdir("..")
count = 0 
for k in input:
    if (int(k.split('_')[1]) < 100000):
        out = roda_com_entrada("./projetoAleatorio", k)
        count += 1
        print("Arquivo ", k, " lido (", count, "/", len(input),")")

