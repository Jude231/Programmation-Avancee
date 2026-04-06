import os

tab = [int(x) for x in input("Entrez les entiers séparés par un espace : ").split()]
with open("data.bin", "wb") as f:
    f.write(bytearray(tab)) # Python gère différemment les types d'octets
    
# Réglage des permissions : 0o664
os.chmod("data.bin", 0o664)