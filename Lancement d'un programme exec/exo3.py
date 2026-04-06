import os
import sys

def main():
    fichier = input("Nom du fichier : ")
    
    os.execl("/usr/bin/emacs", "emacs", fichier)

if __name__ == "__main__":
    main()