#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif


#ifndef OPERATII_DE_BAZA_H_INCLUDED
#include "operatii_de_baza.h"
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Calculam cati bani obtine curierul de la o statie
int suma_statie(statie st)
{
	p_client client = st.graf_clienti->clienti;
	int i, suma = 0;
	for(i = 0; i < st.nr_clienti; i++)
	{
		suma += client[i].de_platit;
	}

	return suma;

}

// Afisam statiile de la care curierul obtine o suma de bani,
// mai mare decat parametrul suma
void comanda_statie(FILE *f, p_graf_statie graf, int suma)
{
	p_statie st = graf->stati;
	int i;
	for(i = 0; i < graf->nr_stati; i++)
	{
		
		if(suma_statie(st[i]) >= suma)
			fprintf(f, "%s ", st[i].nume);
		
	}
	fprintf(f, "\n");

}

// folosesc pointer la graf pentru ca IUBESC sageata aia :))) ->^_^<-

//Afisam toate statiile adiacente statiei cu numele *char
void legatura(FILE *f, p_graf_statie graf, char *statie)
{
	int i, nr_st;
	nr_st = numar_statie(statie);
	//printf("%d\n", nr_st);
	for(i = 0; i < graf->nr_stati; i++)
	{
		if(graf->statie_adj[i][nr_st] != 0 && graf->statie_adj[i][nr_st] != MAX)
			fprintf(f, "%s ", graf->stati[i].nume);
	}
	//printf(f, "\b");
	fprintf(f, "\n");
}


// Blocam un tunel de metrou prin modificare distantei in MAX
void blocaj_tunel(p_graf_statie graf, char *st1, char *st2)
{
	int nr_st1, nr_st2;
	nr_st1 = numar_statie(st1);
	nr_st2 = numar_statie(st2);
	if(graf->statie_adj[nr_st2][nr_st1] != 0)
		graf->statie_adj[nr_st1][nr_st2] = graf->statie_adj[nr_st2][nr_st1] = MAX;

}


// Adaugam o ruta intre doua stati de metrou, distanta fiind
// egala cu valoarea parametrului valoare
void adauga_ruta(p_graf_statie graf, char *st1, char *st2, int valoare)
{
	int nr_st1, nr_st2;
	nr_st1 = numar_statie(st1);
	nr_st2 = numar_statie(st2);
	int **adj = graf->statie_adj;
	if(adj[nr_st1][nr_st2] == 0 )
		adj[nr_st1][nr_st2] = adj[nr_st2][nr_st1] = valoare;
	else return;
}


// Stergem o ruta, prin setarea in matricea drumurilor a valorii
// corespunzatoare legaturii dintre cele doua cu 0
void sterge_ruta(p_graf_statie graf, char *st1, char *st2)
{
	int nr_st1, nr_st2;
	nr_st1 = numar_statie(st1);
	nr_st2 = numar_statie(st2);
	int **adj = graf->statie_adj;
	if(adj[nr_st1][nr_st2] != 0 )
		adj[nr_st1][nr_st2] = adj[nr_st2][nr_st1] = 0;
	else
		return;
}



// Afisam timpul cel mai scurt in care curierul poate sa livreze,
// comenzile tuturor clientilor de la o statie, cu mentiunea ca,
// se presupune ca plecam de la un client si nu ne intoarcem,
// adica fiecare client este vizitat o singura data

void timp_statie(FILE *f, p_graf_statie graf, char *st)
{
	int nr_st = numar_statie(st);
	int sursa, min = MAX;
	int i, n, j;
	int **a = graf->stati[nr_st].graf_clienti->clienti_adj;
	n = graf->stati[nr_st].nr_clienti;
	for(i = 0; i < n; i++)
	{
		if(min > a[i][i])
		{
			sursa = i;
			min = a[i][i];
		}	 
	}
	int timp = min;
		
	int *sps = set_visited(n);
	for( i = 0; i < n - 1; i++)
	{
		sps[sursa] = 1;
		j = min_matrice(sps, a[sursa], n);
		timp = timp + a[j][sursa];
		sursa = j;
	}


	int ultimul_client = -1;

	for(i = 0; i < n; i++)
		if(sps[i] == 0) 
			ultimul_client = i;

	timp += a[ultimul_client][ultimul_client];
	fprintf(f, "%d\n", timp);
	free(sps);


}


// Afisam drumul cel mai scrut parcurs de curier pentru 
// a ajunge de la o statie la alta
void drum_metrou(FILE *f, p_graf_statie graf, char *st1, char *st2)
{
	int nr_st1 ,nr_st2;
	nr_st1 = numar_statie(st1);
	nr_st2 = numar_statie(st2);
	p_dij data = dijkstra(graf->statie_adj, graf->nr_stati, nr_st1);
	afisare_cale(f, data, "Statie", nr_st1, nr_st2);
	fprintf(f, "\n");
	sterge_date_dijkstra(data);
}

