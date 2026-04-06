import socket
import time

def charger_bdd():
    bdd = {}
    try:
        with open("bdd.txt", "r") as f:
            for ligne in f:
                nom, prix = ligne.split()
                bdd[nom] = float(prix)
    except FileNotFoundError: pass
    return bdd

def serveur():
    catalogue = charger_bdd()
    serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serv.bind(('0.0.0.0', 8080))
    serv.listen(5)

    while True:
        cli, _ = serv.accept()
        cli.send(b"Nom client: ")
        nom_cli = cli.recv(1024).decode().strip()
        
        total = 0.0
        while True:
            cli.send(b"Produit (ou 'fin'): ")
            prod = cli.recv(1024).decode().strip()
            if prod == "fin": break
            
            cli.send(b"Quantite: ")
            qte = int(cli.recv(1024).decode().strip())
            
            if prod in catalogue:
                total += catalogue[prod] * qte

        cli.send(f"Total: {total}\n".encode())
        
        # Sauvegarde
        with open(f"cmd_{int(time.time())}.txt", "w") as f:
            f.write(f"Client: {nom_cli}\nTotal: {total}")
        cli.close()

if __name__ == "__main__":
    serveur()