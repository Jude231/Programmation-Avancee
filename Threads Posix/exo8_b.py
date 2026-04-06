import threading
import random
import time
import sys

# La barrière sera initialisée dans le main
barriere = None

def travail_thread(thread_id):
    # Simulation d'un travail de durée aléatoire
    time.sleep(random.randint(1, 5))
    print(f"Thread {thread_id} arrivé au rendez-vous.")
    
    try:
        # Équivalent de pthread_barrier_wait
        barriere.wait()
        
        print(f"Thread {thread_id} franchit la barrière !")
    except threading.BrokenBarrierError:
        # Gère le cas où la barrière est réinitialisée ou brisée
        print(f"Thread {thread_id} : La barrière a été brisée.")

def main():
    global barriere
    
    if len(sys.argv) < 2:
        return

    try:
        n = int(sys.argv[1])
    except ValueError:
        return

    # Initialisation de la barrière pour n threads
    # Équivalent de pthread_barrier_init(&barriere, NULL, n)
    barriere = threading.Barrier(n)

    threads = []
    
    # Création et lancement des threads
    for i in range(n):
        t = threading.Thread(target=travail_thread, args=(i,))
        threads.append(t)
        t.start()

    # Attente de la fin de tous les threads (pthread_join)
    for t in threads:
        t.join()

    print("Tous les threads ont terminé.")

if __name__ == "__main__":
    main()