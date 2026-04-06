import threading
import random
import time
import sys

class TypeTableau:
    def __init__(self):
        self.tab = []
        self.n = 0
        self.x = 0

def initialiser(tt):
    random.seed(time.time())
    tt.tab = [random.randint(0, 99) for _ in range(tt.n)]
    for val in tt.tab:
        print(f"{val} ", end="")
    print()

def chercher(tt, result_container):
    trouve = 0
    for val in tt.tab:
        if val == tt.x:
            trouve = 1
            break
    result_container[0] = trouve

def main():
    tt = TypeTableau()

    tt.n = int(input("Nombre d'éléments : "))

    t1 = threading.Thread(target=initialiser, args=(tt,))
    t1.start()

    tt.x = int(input("Entrez x à chercher : "))

    t1.join()

    resultat = [0]
    t2 = threading.Thread(target=chercher, args=(tt, resultat))
    t2.start()
    t2.join()

    print(f"Présent ? {resultat[0]}")

if __name__ == "__main__":
    main()