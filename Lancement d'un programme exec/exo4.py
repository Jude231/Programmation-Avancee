import os
import sys

def main():
    while True:
        dest = input("Répertoire destination (ou 'quitter') : ")

        if dest == "quitter":
            break

        cmd = f"cp -r . {dest}"
        os.system(cmd)

if __name__ == "__main__":
    main()