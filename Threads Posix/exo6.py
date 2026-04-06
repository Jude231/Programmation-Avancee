import threading
import random
import time
import sys

# Configuration et variables globales
N = 100
tableau = [0.0] * N
mutex = threading.Lock()

def lissage():
    global tableau
    while True:
        with mutex:
            # On crée une copie ou on travaille prudemment pour le lissage
            for i in range(1, N - 1):
                tableau[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0
        
        time.sleep(random.randint(1, 3))

def affichage():
    while True:
        time.sleep(4)
        with mutex:
            print("\n--- État du tableau ---")
            for i in range(N):
                print(f"{tableau[i]:.2f} ", end="")
                if (i + 1) % 10 == 0:
                    print()
            print()

def main():
    random.seed(time.time())

    # Initialisation du tableau
    tableau[0] = 0.0
    tableau[N-1] = 0.0
    for i in range(1, N - 1):
        tableau[i] = float(random.randint(0, 100))

    # Création des threads
    t1 = threading.Thread(target=lissage, daemon=True)
    t2 = threading.Thread(target=affichage, daemon=True)

    # Lancement
    t1.start()
    t2.start()

    # Dans ce cas précis, on attend indéfiniment puisque les threads sont en while(1)
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nArrêt du programme.")

if __name__ == "__main__":
    main()