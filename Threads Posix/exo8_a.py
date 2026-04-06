import threading
import time
import random
import sys

# Initialisation du sémaphore (équivalent de sem_init avec valeur 0)
rendez_vous = threading.Semaphore(0)

def thread_T1():
    for i in range(10):
        time.sleep(2)
        print(f"T1 (it {i+1}) attend T2...")
        
        # sem_wait(&rendez_vous)
        rendez_vous.acquire()
        
        print("T1 repart !")

def thread_T2():
    for i in range(10):
        # Sommeil entre 4 et 9 secondes
        time.sleep(random.randint(4, 9))
        print(f"T2 (it {i+1}) arrive au rendez-vous.")
        
        # sem_post(&rendez_vous)
        rendez_vous.release()

def main():
    random.seed(time.time())

    # Création des threads
    t1 = threading.Thread(target=thread_T1)
    t2 = threading.Thread(target=thread_T2)

    # Lancement
    t1.start()
    t2.start()

    # Attente de la fin (équivalent de pthread_join)
    t1.join()
    t2.join()

    print("Fin du programme.")

if __name__ == "__main__":
    main()