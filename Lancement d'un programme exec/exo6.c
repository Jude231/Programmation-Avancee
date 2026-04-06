#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
   
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    
    if (k == 0 || k == n) 
    {
        printf("1\n");
        return 1; 
    }
    char n1[10], k1[10], k2[10], fname[50];
    sprintf(n1, "%d", n - 1);
    sprintf(k1, "%d", k - 1);
    sprintf(k2, "%d", k);
    sprintf(fname, "/tmp/cnk_%d_%d", n, k);

    
    if (fork() == 0) 
    {
        execl(argv[0], argv[0], n1, k1, NULL);
    }
    if (fork() == 0) 
    {
        execl(argv[0], argv[0], n1, k2, NULL);
    }
    int s1, s2;
    wait(&s1);
    wait(&s2);

    
    int resultat = WEXITSTATUS(s1) + WEXITSTATUS(s2); 
    
    if (argc == 3) 
    {
        printf("Resultat C(%d, %d) = %d\n", n, k, resultat);
    }
    return resultat;
}