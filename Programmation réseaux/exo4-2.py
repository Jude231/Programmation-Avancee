import socket
import os

serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv.bind(('0.0.0.0', 8080))
serv.listen(5)

while True:
    cli, addr = serv.accept()
    
    with open("/tmp/recu.tgz", "wb") as f:
        while True:
            data = cli.recv(1024)
            if not data: break
            f.write(data)
    
    cli.close()
    
    # 3. Décompression
    os.makedirs("/tmp/save", exist_ok=True)
    os.system("tar -zxvf /tmp/recu.tgz -C /tmp/save/")
    os.remove("/tmp/recu.tgz")
    print(f"Archive reçue de {addr[0]} et extraite.")