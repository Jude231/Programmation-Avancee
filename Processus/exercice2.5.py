import os
import sys
import time
import random

def main():
    debut = time.time()

    pid1 = os.fork()

    if pid1 < 0:
        print("Erreur lors de la creation du processus fils 1")
        sys.exit(1)

    if pid1 == 0:
        random.seed(os.getpid())
        d1 = random.randint(1, 10)
        print(f"Fils 1 (PID {os.getpid()}) : je vais dormir {d1} secondes.")
        time.sleep(d1)
        print("Fils 1 terminé.")
        os._exit(0)
    else:
        pid2 = os.fork()

        if pid2 < 0:
            print("Erreur lors de la creation du processus fils 2")
            sys.exit(1)

        if pid2 == 0:
            random.seed(os.getpid() + 1)
            d2 = random.randint(1, 10)
            print(f"Fils 2 (PID {os.getpid()}) : je vais dormir {d2} secondes.")
            time.sleep(d2)
            print("Fils 2 terminé.")
            os._exit(0)

    print("Parent : j'attends la fin des fils...")

    os.wait()
    os.wait()

    fin = time.time()

    print(f"Duree totale ecoulee : {int(fin - debut)} secondes.")

if __name__ == "__main__":
    main()