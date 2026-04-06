import os
import sys

def main():
    while True:
        f = input("Fichier à ouvrir (ou 'quitter') : ")

        if f == "quitter":
            break

        pid = os.fork()

        if pid == 0:
            # Processus enfant
            os.execl("/usr/bin/emacs", "emacs", f)
            os._exit(0)
        
       

if __name__ == "__main__":
    main()