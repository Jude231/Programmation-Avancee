import os
import sys

def main():
    pid1 = os.fork()

    if pid1 < 0:
        print("Erreur lors de la création du processus")
        sys.exit(1)
    elif pid1 == 0:
        print("Je suis le fils 1")
    else:
        pid2 = os.fork()
        if pid2 < 0:
            print("Erreur lors de la création du processus")
            sys.exit(1)
        elif pid2 == 0:
            print("Je suis le fils 2")
        else:
            print("Je suis le père")

if __name__ == "__main__":
    main()