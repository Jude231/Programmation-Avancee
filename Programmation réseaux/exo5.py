import socket

def serve_chat():
    serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serv.bind(('0.0.0.0', 8080))
    serv.listen(2)

    print("En attente des clients...")
    c1, _ = serv.accept()
    print("Client 1 ok...")
    c2, _ = serv.accept()
    print("Client 2 ok. Relay actif.")

    c1.send(b"Connecte ! A vous l'honneur.\n")
    c2.send(b"Connecte ! Attendez le message...\n")

    try:
        while True:
            # Tour du Client 1
            c1.send(b"Saisissez la reponse : ")
            msg = c1.recv(1024)
            if not msg: break
            c2.send(b"L'autre client dit : " + msg)

            # Tour du Client 2
            c2.send(b"Saisissez la reponse : ")
            msg = c2.recv(1024)
            if not msg: break
            c1.send(b"L'autre client dit : " + msg)
    except:
        pass
    finally:
        c1.close()
        c2.close()

if __name__ == "__main__":
    serve_chat()