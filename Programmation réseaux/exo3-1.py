import socket
import datetime
import os

# Assurez-vous que le répertoire existe
os.makedirs("/home/save/", exist_ok=True)

serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv.bind(('0.0.0.0', 8080))
serv.listen(5)

while True:
    cli, (ip, port) = serv.accept()
    
    # Génération du nom de fichier
    date_str = datetime.datetime.now().strftime("%Y_%m_%d")
    nom_fich = f"/home/save/{ip}_{date_str}.txt"
    
    with open(nom_fich, "wb") as f:
        while True:
            data = cli.recv(1024)
            if not data: break
            f.write(data)
            
    print(f"Fichier copié pour {ip} -> {nom_fich}")
    cli.close()