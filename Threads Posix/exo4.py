import threading
import random
import time
import sys
import os

class Tableau:
    def __init__(self, n):
        self.tab = []
        self.n = n

class Paquet:
    def __init__(self, t1, t2):
        self.t1 = t1
        self.t2 = t2

def generer(tableau):
    tableau.tab = [random.randint(0, 99) for _ in range(tableau.n)]

def verifier_inclusion(paquet):
    inclus = True
    for x in paquet.t1.tab:
        if x not in paquet.t2.tab:
            inclus = False
            break
    
    resultat = "inclus" if inclus else "NON inclus"
    print(f"\nRésultat : T1 est {resultat} dans T2")

def guetter_annulation():
    if sys.stdin.read(1) == 'A':
        print("\nProgramme annulé par l'utilisateur.")
        os._exit(0)

def main():
    random.seed(time.time())
    
    t1 = Tableau(5)
    t2 = Tableau(10)
    p = Paquet(t1, t2)

    th_abort = threading.Thread(target=guetter_annulation, daemon=True)
    th_abort.start()

    th1 = threading.Thread(target=generer, args=(t1,))
    th2 = threading.Thread(target=generer, args=(t2,))

    th1.start()
    th2.start()

    th1.join()
    th2.join()

    th3 = threading.Thread(target=verifier_inclusion, args=(p,))
    th3.start()
    th3.join()

if __name__ == "__main__":
    main()