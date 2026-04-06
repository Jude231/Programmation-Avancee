import os
import signal
import time
import sys

pid = os.fork()

if pid == 0:
    # Le fils : boucle infinie
    while True:
        print("Fils travaille...")
        time.sleep(1)
else:
    # Le père : menu
    try:
        while True:
            choix = input("\nMenu : [s]toper, [r]edémarrer, [q]uitter : ").lower()
            
            if choix == 's':
                os.kill(pid, signal.SIGSTOP)
                print("Fils suspendu.")
            elif choix == 'r':
                os.kill(pid, signal.SIGCONT)
                print("Fils repris.")
            elif choix == 'q':
                os.kill(pid, signal.SIGKILL)
                print("Fils terminé.")
                os.wait() # Attend la fin du fils
                break
    except EOFError:
        os.kill(pid, signal.SIGKILL)