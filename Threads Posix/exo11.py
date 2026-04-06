import threading
import time
import random
import sys

base = [0] * 15
nb_lecteurs = 0

sem_base = threading.Semaphore(1)
mutex_lecteurs = threading.Lock()

def lecteur(id_l):
    global nb_lecteurs
    while True:
        time.sleep(random.randint(1, 3))

        with mutex_lecteurs:
            nb_lecteurs += 1
            if nb_lecteurs == 1:
                sem_base.acquire()

        pos = random.randint(0, 14)
        print(f"[Lecteur {id_l}] Lit base[{pos}] = {base[pos]} (Lecteurs actifs: {nb_lecteurs})")

        with mutex_lecteurs:
            nb_lecteurs -= 1
            if nb_lecteurs == 0:
                sem_base.release()

def ecrivain(id_e):
    while True:
        time.sleep(random.randint(1, 10))

        sem_base.acquire()
        
        pos = random.randint(0, 14)
        base[pos] = random.randint(0, 255)
        print(f"[Écrivain {id_e}] !!! MODIFIE base[{pos}] = {base[pos]} !!!")
        
        sem_base.release()

def main():
    try:
        entree = input("Nombre de lecteurs (N) et écrivains (M) : ")
        n, m = map(int, entree.split())
    except ValueError:
        return

    for i in range(n):
        threading.Thread(target=lecteur, args=(i,), daemon=True).start()

    for i in range(m):
        threading.Thread(target=ecrivain, args=(i,), daemon=True).start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        pass

if __name__ == "__main__":
    main()