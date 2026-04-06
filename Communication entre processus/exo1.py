import os
import sys

def main():
    
    r, w = os.pipe()

    pid = os.fork()

    if pid == 0:
        
        mot = input("Saisir un mot : ")
        
      
        data_to_send = mot.ljust(50).encode()
        os.write(w, data_to_send)
        
        
        res_bytes = os.read(r, 4)
        resultat = int.from_bytes(res_bytes, byteorder=sys.byteorder)
        
        print(f"Résultat : {resultat}")
        os._exit(0)

    else:
     
        data_received = os.read(r, 50).decode().strip()
        
        trouve = 0
        try:
            with open("texte.txt", "r") as f:
                contenu = f.read().split()
                if data_received in contenu:
                    trouve = 1
        except FileNotFoundError:
            print("Erreur : Le fichier 'texte.txt' n'existe pas.")

       
        os.write(w, trouve.to_bytes(4, byteorder=sys.byteorder))
        
        
        os.wait()

if __name__ == "__main__":
    main()