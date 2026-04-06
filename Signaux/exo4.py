import sys

try:
    n = int(input("Taille du tableau n : "))
    tab = []
    for j in range(n):
        tab.append(int(input(f"tab[{j}] = ")))

    while True:
        try:
            i = int(input(f"\nQuel index i voulez-vous afficher (0 à {n-1}) ? "))
            print(f"Valeur lue : {tab[i]}")
        except IndexError:
            print("Erreur : Index hors limites. Recommencez.")
        except ValueError:
            print("Veuillez entrer un nombre entier.")

except EOFError:
    print("\nFin du programme.")