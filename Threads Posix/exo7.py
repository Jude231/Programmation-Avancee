import threading
import random
import time
import math
import sys

# Variables globales
u = 1.0
compteur = 0
verrou = threading.Lock()

def f1(x):
    return (1.0 / 4.0) * math.pow(x - 1.0, 2)

def f2(x):
    return (1.0 / 6.0) * math.pow(x - 2.0, 2)

def thread_fonction(thread_id):
    global u, compteur
    
    while True:
        with verrou:
            compteur += 1
            
            if thread_id == 1:
                u = f1(u)
            else:
                u = f2(u)
                
            print(f"[Thread {thread_id}] Itération {compteur} : u = {u:.6f}")
            
        # Simulation d'un délai aléatoire (1 à 5 secondes)
        time.sleep(random.randint(1, 5))

def main():
    random.seed(time.time())

    # Création des threads
    # On passe l'ID via l'argument 'args' (doit être un tuple)
    t1 = threading.Thread(target=thread_fonction, args=(1,), daemon=True)
    t2 = threading.Thread(target=thread_fonction, args=(2,), daemon=True)

    t1.start()
    t2.start()

    # Puisque les threads sont en boucle infinie, on attend une interruption (Ctrl+C)
    try:
        t1.join()
        t2.join()
    except KeyboardInterrupt:
        print("\nArrêt du programme.")

if __name__ == "__main__":
    main()