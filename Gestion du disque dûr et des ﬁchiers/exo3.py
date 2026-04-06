import os

tab = [int(x) for x in input("Entrez les entiers séparés par un espace : ").split()]
with open("data.bin", "wb") as f:
    f.write(bytearray(tab)) 
os.chmod("data.bin", 0o664)
