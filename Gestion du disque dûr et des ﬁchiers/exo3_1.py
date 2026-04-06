import os
import struct

taille_fichier = os.path.getsize("data.bin")
nb_elements = taille_fichier // 4 # Un int fait généralement 4 octets

with open("data.bin", "rb") as f:
    # On lit tout et on convertit le binaire en entiers
    donnees = f.read()
    tab = list(struct.unpack(f'{nb_elements}i', donnees))

print(f"Tableau chargé : {tab}")