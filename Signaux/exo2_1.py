import os
import signal

n = input("Entrez un entier : ")

with open("/tmp/entier.txt", "w") as f:
    f.write(n)

try:
    with open("/tmp/affiche.pid", "r") as f:
        pid_dest = int(f.read())
    os.kill(pid_dest, signal.SIGUSR1)
except FileNotFoundError:
    print("Erreur : Le programme affiche.py n'est pas lancé.")