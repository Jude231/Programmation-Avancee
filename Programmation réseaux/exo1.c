#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>

typedef struct Produit
{
    char nom[50];
    float prix;
} Produit;

Produit catalogue[100];
int nb_produits = 0;

// b) Chargement depuis un fichier "bdd.txt" (format: nom prix)
void charger_bdd() 
{
    FILE *f = fopen("bdd.txt", "r");
    if (!f) 
    {
        return;
    }
    while (fscanf(f, "%s %f", catalogue[nb_produits].nom, &catalogue[nb_produits].prix) == 2) 
    {
        nb_produits++;
    }
    fclose(f);
}

// c) Recherche
Produit* trouver_produit(char *nom) 
{
    for (int i = 0; i < nb_produits; i++) 
    {
        if (strcmp(catalogue[i].nom, nom) == 0) 
        {
            return &catalogue[i];
        }
    }
    return NULL;
}


void gerer_serveur() 
{
    int s_ecoute = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {AF_INET, htons(8080), INADDR_ANY};
    bind(s_ecoute, (struct sockaddr*)&adr, sizeof(adr));
    listen(s_ecoute, 5);

    while (1) 
    {
        int s_client = accept(s_ecoute, NULL, NULL);
        char buffer[1024], nom_prod[50], nom_client[50];
        int qte;
        float total = 0;

        dprintf(s_client, "Nom du client : ");
        read(s_client, nom_client, 50);

        // Boucle pour plusieurs produits (e)
        while (1) 
        {
            dprintf(s_client, "Produit (ou 'fin') : ");
            if (read(s_client, nom_prod, 50) <= 0 || strncmp(nom_prod, "fin", 3) == 0) 
            {
                break;
            }
            strtok(nom_prod, "\r\n"); // Nettoyage Telnet

            dprintf(s_client, "Quantité : ");
            read(s_client, buffer, 1024);
            qte = atoi(buffer);

            Produit *p = trouver_produit(nom_prod);
            if (p) 
            {
                total += p->prix * qte;
            }
        }

        dprintf(s_client, "Total commande : %.2f\n", total);

        // f) Enregistrement fichier unique
        char filename[100];
        sprintf(filename, "cmd_%ld.txt", time(NULL));
        FILE *f = fopen(filename, "w");
        fprintf(f, "Client: %s\nTotal: %.2f\n", nom_client, total);
        fclose(f);

        close(s_client);
    }
}