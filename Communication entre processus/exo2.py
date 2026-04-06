import os
import sys

def main():
    # p1: Enfant -> Parent | p2: Parent -> Enfant
    p1_read, p1_write = os.pipe()
    p2_read, p2_write = os.pipe()

    pid = os.fork()

    if pid == 0:

        os.close(p1_read)
        os.close(p2_write)

        mot = input("Saisir un mot : ")
        
        # Envoie au père via p1
        os.write(p1_write, mot.ljust(50).encode())
        
        # Reçoit du père via p2
        res_bytes = os.read(p2_read, 4)
    
        try:
            res = int(res_bytes.decode().strip())
            print(f"Résultat : {res}")
        except ValueError:
            print("Erreur de réception")
            
        os._exit(0)

    else:

        os.close(p1_write)
        os.close(p2_read)

        os.dup2(p1_read, sys.stdin.fileno())
     
        os.dup2(p2_write, sys.stdout.fileno())

     
        mot_cherche = sys.stdin.read(50).strip()

        trouve = 0
        try:
            with open("texte.txt", "r") as f:
                mots_fichier = f.read().split()
                if mot_cherche in mots_fichier:
                    trouve = 1
        except FileNotFoundError:
            pass

     
        sys.stdout.write(str(trouve))
        sys.stdout.flush() 
        os.wait()

if __name__ == "__main__":
    main()