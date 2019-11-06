#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif


#ifndef OPERATII_DE_BAZA_H_INCLUDED
#include "operatii_de_baza.h"
#endif



#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// Extragem din numele clientului bucata ce se afla
// pana la punct
void extrage_tag_client(char *nume)
{
	int i = strlen(nume) - 1;
	while(nume[i] != '.')
		i--;
	nume[i+1] = '\0';
}


// Verificam daca exista legatura intre 2 clienti
void conexiune(FILE *f, p_graf_statie graf, char *client1, char *client2)
{

	int st_aferenta;
	int nr_clt1, nr_clt2;
	st_aferenta = numar_statie_client(client1);
	nr_clt1 = numar_client(client1);
	nr_clt2 = numar_client(client2);
	int **adj = graf->stati[st_aferenta].graf_clienti->clienti_adj;
	if(nr_clt1 != nr_clt2 && adj[nr_clt1][nr_clt2] != 0 && adj[nr_clt1][nr_clt2] != MAX)
		fprintf(f, "%s\n", "OK");
	else 
		fprintf(f, "%s\n", "NO");

}

// Blocam o strada prin setarea timpului MAX
void blocaj_strada(p_graf_statie graf, char *clt1, char *clt2)
{
	int nr_clt1, nr_clt2;
	int nr_st = numar_statie_client(clt1);
	nr_clt1 = numar_client(clt1);
	nr_clt2 = numar_client(clt2);

	int **adj = graf->stati[nr_st].graf_clienti->clienti_adj;
	if(adj[nr_clt2][nr_clt1] != 0)
		adj[nr_clt1][nr_clt2] = adj[nr_clt2][nr_clt1] = MAX;

}

// Adaugam o strada intre doi clienti daca nu exista deja o strada intre cei doi
void adauga_strada(p_graf_statie graf, char *clt1, char *clt2, int valoare)
{
	int nr_st = numar_statie_client(clt1);
	int nr_clt1, nr_clt2;
	nr_clt1 = numar_client(clt1);
	nr_clt2 = numar_client(clt2);

	int **adj = graf->stati[nr_st].graf_clienti->clienti_adj;
	if(adj[nr_clt2][nr_clt1] == 0 )
		adj[nr_clt1][nr_clt2] = adj[nr_clt2][nr_clt1] = valoare; 
	else
		return;
}
// Stergem, daca exista strada dintre doi clienti
void sterge_strada(p_graf_statie graf, char *clt1, char *clt2)
{
	int nr_st = numar_statie_client(clt1);
	int nr_clt1, nr_clt2;
	nr_clt1 = numar_client(clt1);
	nr_clt2 = numar_client(clt2);

	int **adj = graf->stati[nr_st].graf_clienti->clienti_adj;
	if(adj[nr_clt2][nr_clt1] != 0 )
		adj[nr_clt1][nr_clt2] = adj[nr_clt2][nr_clt1] = 0; 
	else
		return;
}

// Afisam drumul cel mai scurt de la un client la alt client
void drum_strada(FILE *f, p_graf_statie graf, char *clt1, char *clt2)
{
	int nr_st = numar_statie_client(clt1);
	int nr_clt1, nr_clt2;
	nr_clt1 = numar_client(clt1);
	nr_clt2 = numar_client(clt2);
	statie statia = graf->stati[nr_st];
	p_dij data = dijkstra(statia.graf_clienti->clienti_adj, statia.nr_clienti, nr_clt1);
	extrage_tag_client(clt1);
	afisare_cale(f, data, clt1, nr_clt1, nr_clt2);
	fprintf(f, "\n");
	sterge_date_dijkstra(data);
}




