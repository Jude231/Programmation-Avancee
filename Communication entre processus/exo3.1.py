import os
import sys

def main():
  
    r, w = os.pipe()

    pid = os.fork()

    if pid == 0:
     
        os.close(w) #
        
     
        fd_str = str(r)
        
        # Chemin vers l'interpréteur python et le script fils
        path_to_python = sys.executable
        script_fils = "./fils_exec.py"
        
   
        os.execv(path_to_python, [path_to_python, script_fils, fd_str])
        
      
        os._exit(1)

    else:
        # --- PROCESSUS PARENT ---
        os.close(r)
        
        msg = "Message secret du pere"
        os.write(w, (msg + '\0').encode())
        
        os.close(w)
        os.wait()

if __name__ == "__main__":
    main()