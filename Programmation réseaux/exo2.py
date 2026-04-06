import socket

def charger_autorisations():
    auths = {}
    try:
        with open("add_autoris.txt", "r") as f:
            for ligne in f:
                parts = ligne.split()
                if len(parts) >= 2:
                    auths[parts[0]] = parts[1]
    except FileNotFoundError:
        print("Erreur : add_autoris.txt introuvable.")
    return auths

def serveur():
    serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serv.bind(('0.0.0.0', 8080))
    serv.listen(5)
    
    print("Serveur Python en attente sur le port 8080...")
    
    while True:
        cli, (ip, port) = serv.accept()
        autorisations = charger_autorisations()
        
        if ip in autorisations:
            nom = autorisations[ip]
            cli.send(f"Bienvenue {nom} ! (IP reconnue : {ip})\n".encode())
            print(f"Accès accordé à {nom} ({ip})")
        else:
            cli.send(f"Accès refusé pour l'IP {ip}.\n".encode())
            print(f"Refus pour {ip}")
            
        cli.close()

if __name__ == "__main__":
    serveur()