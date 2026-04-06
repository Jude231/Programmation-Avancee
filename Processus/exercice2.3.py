import os
import sys

def main():
    for i in range(5):
        try:
            pid = os.fork()
        except OSError:
            print("Erreur lors de la création du processus")
            sys.exit(1)

        if pid == 0:
            print(f"Je suis le fils {i + 1}")
            break

if __name__ == "__main__":
    main()