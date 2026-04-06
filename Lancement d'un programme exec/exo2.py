import sys
import os

def main():
    if len(sys.argv) != 2:
        sys.exit(1)

    destination = sys.argv[1]
    commande = f"cp -r . {destination}"

    status = os.system(commande)
    
    sys.exit(status)

if __name__ == "__main__":
    main()