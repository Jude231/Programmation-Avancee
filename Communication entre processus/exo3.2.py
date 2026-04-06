import os
import sys

def main():
    if len(sys.argv) < 2:
        sys.exit(1)

    fd_lecture = int(sys.argv[1])
    
    tampon = os.read(fd_lecture, 100)
    print(f"Fils (execv) a reçu : {tampon.decode().strip()}")

    os.close(fd_lecture)

if __name__ == "__main__":
    main()