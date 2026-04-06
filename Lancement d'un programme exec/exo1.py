import sys

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <entier> <entier>")
        sys.exit(1)

    num1 = int(sys.argv[1])
    num2 = int(sys.argv[2])
    somme = num1 + num2
    
    print(f"La somme de {num1} et {num2} est : {somme}")

if __name__ == "__main__":
    main()