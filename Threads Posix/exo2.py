import threading
import random
import time

def generer_tableau():
    tab = [random.randint(0, 99) for _ in range(10)]
    return tab

class ThreadAvecRetour(threading.Thread):
    def __init__(self, target):
        super().__init__()
        self.target = target
        self.resultat = None

    def run(self):
        self.resultat = self.target()

def main():
    thread = ThreadAvecRetour(target=generer_tableau)
    
    thread.start()
    thread.join()

    resultat = thread.resultat
    
    print("Tableau reçu du thread : ", end="")
    for val in resultat:
        print(f"{val} ", end="")
    print()

if __name__ == "__main__":
    main()