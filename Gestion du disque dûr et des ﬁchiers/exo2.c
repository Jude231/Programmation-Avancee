#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    struct dirent *entry;
    struct stat st;
    char path[1024];

    for (int i = 1; i < argc; i++) 
    {
        DIR *dir = opendir(argv[i]);
        if (!dir) 
        {
            continue;
        }
        while ((entry = readdir(dir)) != NULL) 
        {
            
            snprintf(path, sizeof(path), "%s/%s", argv[i], entry->d_name);
            
            if (stat(path, &st) == 0 && S_ISREG(st.st_mode)) 
            {
                // 1 Mo = 1024 * 1024 octets
                if (st.st_size > 1048576) 
                {
                    printf("Fichier: %s | Taille: %ld octets | UID: %u\n", entry->d_name, st.st_size, st.st_uid);
                }
            }
        }
        closedir(dir);
    }
    return 0;
}