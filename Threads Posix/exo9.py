import threading
import time
import random


tampon = 0
sem_vide = threading.Semaphore(1)
sem_plein = threading.Semaphore(0)

def emetteur():
    global tampon
    for i in range(10):
        # Simulation d'un délai de préparation
        time.sleep(random.randint(1, 3))
        octet = random.randint(0, 255)

        sem_vide.acquire()      
        tampon = octet          
        print(f"[Émetteur] Octet déposé : {octet:02X}")
        sem_plein.release()   

def recepteur():
    global tampon
    for i in range(10):
       
        time.sleep(random.randint(1, 3))

        sem_plein.acquire()     
        octet = tampon          # Lit l'octet
        print(f"[Récepteur] Octet lu : {octet:02X}")
        sem_vide.release()      # sem_post(&sem_vide)

def main():
    random.seed(time.time())

    
    t1 = threading.Thread(target=emetteur)
    t2 = threading.Thread(target=recepteur)

 
    t1.start()
    t2.start()

    t1.join()
    t2.join()

if __name__ == "__main__":
    main()