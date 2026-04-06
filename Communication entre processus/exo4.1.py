import os
import sys

def main():
    r, w = os.pipe()

    pid = os.fork()

    if pid == 0:
        os.close(w)
        
        os.environ["MON_TUBE"] = str(r)
        
        path_to_python = sys.executable
        script_fils = "./fils_env.py"
        
        os.execv(path_to_python, [path_to_python, script_fils])
        os._exit(1)

    else:
        os.close(r)
        
        msg = "Message via environnement"
        os.write(w, (msg + '\0').encode())
        
        os.close(w)
        os.wait()

if __name__ == "__main__":
    main()