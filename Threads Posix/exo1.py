import threading

def afficher_tableau(tab):
    print("Contenu du tableau dans le thread : ", end="")
    for val in tab:
        print(f"{val} ", end="")
    print()

def main():
    mon_tableau = [10, 20, 30, 40, 50]

    thread = threading.Thread(target=afficher_tableau, args=(mon_tableau,))
    
    thread.start()
    thread.join()

if __name__ == "__main__":
    main()