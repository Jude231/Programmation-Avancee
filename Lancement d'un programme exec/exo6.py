import os
import sys

def main():
    # Récupération des arguments n et k
    n = int(sys.argv[1])
    k = int(sys.argv[2])

    # Cas de base
    if k == 0 or k == n:
        # En Python, on utilise sys.exit() pour renvoyer un code de retour
        sys.exit(1)

    # Préparation des arguments pour les appels récursifs
    n1 = str(n - 1)
    k1 = str(k - 1)
    k2 = str(k)

    # Premier fils : calcul de C(n-1, k-1)
    pid1 = os.fork()
    if pid1 == 0:
        os.execl(sys.executable, sys.executable, sys.argv[0], n1, k1)
        os._exit(0)

    # Deuxième fils : calcul de C(n-1, k)
    pid2 = os.fork()
    if pid2 == 0:
        os.execl(sys.executable, sys.executable, sys.argv[0], n1, k2)
        os._exit(0)


    _, s1 = os.wait()
    _, s2 = os.wait()


    res1 = os.waitstatus_to_exitcode(s1)
    res2 = os.waitstatus_to_exitcode(s2)

    resultat = res1 + res2

    
    if len(sys.argv) == 3:
        print(f"Resultat C({n}, {k}) = {resultat}")

    sys.exit(resultat)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit(1)
    main()