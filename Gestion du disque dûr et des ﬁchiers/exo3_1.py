import os
import struct

taille_fichier = os.path.getsize("data.bin")
nb_elements = taille_fichier // 4 

with open("data.bin", "rb") as f:
    donnees = f.read()
    tab = list(struct.unpack(f'{nb_elements}i', donnees))

print(f"Tableau chargé : {tab}")
