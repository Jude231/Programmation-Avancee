import os
import signal
import time

def reception(signum, frame):
    with open("/tmp/entier.txt", "r") as f:
        print(f"\n[Affiche] Valeur lue : {f.read()}")

# Sauvegarde du PID
with open("/tmp/affiche.pid", "w") as f:
    f.write(str(os.getpid()))

signal.signal(signal.SIGUSR1, reception)
print(f"En attente (PID: {os.getpid()})...")

while True:
    time.sleep(1)