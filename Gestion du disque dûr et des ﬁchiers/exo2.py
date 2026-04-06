import os
import sys

def lister_gros_fichiers(repertoires):
    for repo in repertoires:
        if not os.path.isdir(repo):
            continue
            
        for fichier in os.listdir(repo):
            chemin = os.path.join(repo, fichier)
            
           
            if os.path.isfile(chemin):
                infos = os.stat(chemin)
               
                if infos.st_size > 1_000_000:
                    print(f"Fichier: {fichier} | Taille: {infos.st_size} | UID: {infos.st_uid}")

if __name__ == "__main__":
    lister_gros_fichiers(sys.argv[1:])