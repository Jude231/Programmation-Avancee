import socket
import sys
import os

if len(sys.argv) < 2:
    sys.exit("Usage: python client.py <chemin_repertoire>")

# 1. Archivage
os.system(f"tar -zcvf /tmp/rep.tgz {sys.argv[1]}")

# 2. Envoi
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('127.0.0.1', 8080))

with open("/tmp/rep.tgz", "rb") as f:
    sock.sendall(f.read())

sock.close()
print("Archive envoyée.")