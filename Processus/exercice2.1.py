import os
import sys

def main():
    try:
        pid = os.fork()
    except OSError:
        print("Erreur lors de la création du processus")
        sys.exit(1)

    if pid == 0:
        print("Je suis fils")
    else:
        print("Je suis le père")

if __name__ == "__main__":
    main()