import os
import sys

def main():
    pid = os.fork()

    if pid == -1:
        print("Erreur lors de la création du processus")
        sys.exit(1)

    for i in range(5):
        if pid == 0:
            print(f"Je suis le fils {i + 1}")
            break

    print("Je suis le père")
    
    for j in range(5):
        try:
            os.wait()
        except ChildProcessError:
            break

if __name__ == "__main__":
    main()