import os
import signal
import time
import sys

def fils_handler(signum, frame):
    print(f"\n[Fils {os.getpid()}] Reçu signal de fin. Je m'arrête.")
    sys.exit(0)

def pere_handler(signum, frame):
    print("\n[Père] Le processus principal s'arrête.")
    sys.exit(0)

signal.signal(signal.SIGINT, pere_handler)

pids = []
for i in range(5):
    pid = os.fork()
    if pid == 0:
        signal.signal(signal.SIGTERM, fils_handler)
        while True:
            time.sleep(1)
    pids.append(pid)

try:
    while True:
        print("\nActions: 1:Stop, 2:Cont, 3:Term")
        s = input("Entrez 'Indice Action' (ex: 0 3) : ").split()
        if len(s) < 2: continue
        
        idx, act = int(s[0]), int(s[1])
        target = pids[idx]

        if act == 1: os.kill(target, signal.SIGSTOP)
        elif act == 2: os.kill(target, signal.SIGCONT)
        elif act == 3: os.kill(target, signal.SIGTERM)
except (EOFError, KeyboardInterrupt, IndexError, ValueError):
    pass