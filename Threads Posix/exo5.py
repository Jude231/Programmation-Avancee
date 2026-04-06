import threading
import random
import time
import sys

# Variables globales
compt = 0
limite = 0
verrou = threading.Lock()

def incrementer():
    global compt
    while True:
        with verrou:
            if compt >= limite:
                break
            compt += 1
            print(f"[Thread 1] Compteur incrémenté : {compt}")
        
        # Simulation d'un traitement avec sleep
        time.sleep(random.randint(1, 5))

def afficher():
    global compt
    while True:
        time.sleep(2)
        
        with verrou:
            print(f"[Thread 2] Valeur actuelle : {compt}")
            if compt >= limite:
                break

def main():
    global limite
    
    if len(sys.argv) < 2:
        return

    try:
        limite = int(sys.argv[1])
    except ValueError:
        return

    random.seed(time.time())

    # Création des threads
    t1 = threading.Thread(target=incrementer)
    t2 = threading.Thread(target=afficher)

    # Lancement des threads
    t1.start()
    t2.start()

    # Attente de la fin des threads
    t1.join()
    t2.join()

    print(f"Fin du programme. Valeur finale : {compt}")

if __name__ == "__main__":
    main()