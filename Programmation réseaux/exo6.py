import socket
import threading

clients = []
mutex_parole = threading.Lock()
mutex_liste = threading.Lock()

def gerer_client(cli, ip):
    global clients
    try:
        while True:
            cli.send(b"Tapez 1 pour demander la parole : ")
            data = cli.recv(1024).decode().strip()
            
            if data == '1':
                cli.send(b"Attente du tour...\n")
                with mutex_parole: # Acquisition du droit de parole
                    cli.send(b"Vous avez la parole. Votre message : ")
                    msg = cli.recv(1024).decode().strip()
                    
                    # Diffusion
                    with mutex_liste:
                        for c in clients:
                            if c != cli:
                                c.send(f"\n[{ip}] dit : {msg}\n".encode())
    except:
        pass
    finally:
        with mutex_liste:
            clients.remove(cli)
        cli.close()

def serveur():
    serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serv.bind(('0.0.0.0', 8080))
    serv.listen(10)
    
    while True:
        cli, (ip, port) = serv.accept()
        with mutex_liste:
            clients.append(cli)
        threading.Thread(target=gerer_client, args=(cli, ip)).start()

if __name__ == "__main__":
    serveur()