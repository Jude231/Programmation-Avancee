import threading
import time
import random

TAILLE = 10
pile = [0] * TAILLE
top = 0

sem_libres = threading.Semaphore(TAILLE)
sem_prets = threading.Semaphore(0)
mutex = threading.Lock()

def producteur(id_prod):
    global top
    while True:
        objet = random.randint(0, 255)
        time.sleep(random.randint(1, 3))

        sem_libres.acquire()
        with mutex:
            pile[top] = objet
            top += 1
            print(f"[Prod {id_prod}] + Déposé: {objet:02X} (Stock: {top}/{TAILLE})")
        sem_prets.release()

def consommateur(id_cons):
    global top
    while True:
        time.sleep(random.randint(1, 3))

        sem_prets.acquire()
        with mutex:
            top -= 1
            objet = pile[top]
            print(f"[Cons {id_cons}] - Retiré: {objet:02X} (Stock: {top}/{TAILLE})")
        sem_libres.release()

def main():
    line = input("Nombre de producteurs (N) et consommateurs (M) : ")
    params = line.split()
    if len(params) < 2: return
    n, m = int(params[0]), int(params[1])

    for i in range(n):
        threading.Thread(target=producteur, args=(i,), daemon=True).start()
    
    for i in range(m):
        threading.Thread(target=consommateur, args=(i,), daemon=True).start()

    try:
        while True: time.sleep(1)
    except KeyboardInterrupt:
        pass

if __name__ == "__main__":
    main()