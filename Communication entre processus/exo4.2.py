import os
import sys

def main():
    fd_str = os.environ.get("MON_TUBE")
    if fd_str is None:
        sys.exit(1)
        
    fd_lecture = int(fd_str)
    
    tampon = os.read(fd_lecture, 100)
    print(f"Fils (env) a reçu : {tampon.decode().strip(chr(0))}")

    os.close(fd_lecture)

if __name__ == "__main__":
    main()