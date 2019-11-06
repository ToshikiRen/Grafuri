#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Extragem numarul clientului, si returnam indicele corespunzator
// liniei sale din matricea de adiacenta
int numar_client(char *nume)
{
	int i, numar = 0, p = 1;
	i = strlen(nume) - 1;
	while(nume[i] != '.')
	{
		numar = ( nume[i] - 48 ) * p + numar;
		p = p * 10;
		i--;
	}
	////printf("%s\n", nume);
	return numar - 1;
}

// Extragem din numele clientului numarul statiei ce se afla
// in legatura directa cu acesta
int numar_statie_client(char *nume)
{
	int i = strlen(nume) - 1;
	while(nume[i] != '.')
		i--;
	i--;

	int numar = 0, p = 1;
	while(nume[i] >= '0' && nume[i] <= '9')
	{
		numar += (nume[i] - 48) * p;
		p = p * 10;
		i--;
	}
	return numar - 1;

}


// Extragem numarul statiei, si returnam indicele corespunzator
// liniei sale din matricea de adiacenta
int numar_statie(char *nume)
{

	int i, numar, p = 1;
	numar = 0;
	i = strlen(nume) - 1;
	while(nume[i] >= '0' && nume[i] <= '9')
	{
		numar += (nume[i] - 48) * p;
		p = p * 10;
		i--;
	}
	return numar - 1;
}



// Verificam daca un pointer este NULL, in cazul in care este NULL,
// oprim executia programului
void isNULL(void *ptr)
{
	if(ptr == NULL)
	{
		fprintf(stderr, "Eroare la initializarea adresei de memorie\n");
		exit(1);
	}
}

// Deschidem fisierul cu numele dat de parametrul filename in modul
// specificat de parametrul mod
FILE* deschide_fisier(char *filename, char *mod)
{
	FILE *f = fopen(filename, mod);
	if(f == NULL)
	{
		printf("Fisierul nu a fost deschis\n");
		exit(1);
	}
}

// Stergem \n de la final si \t de la inceput dintr-un sir
void sterge_sfarsit_si_spatii(char *nume)
{
	if(nume[strlen(nume) - 1] == '\n') 
		nume[strlen(nume) - 1] = '\0';
	if(nume[0] == '\t')
		strcpy(nume, nume + 1);
}

// Convertim un sir la un intreg
int sir_la_numar(char *sir)
{
	int i, numar = 0, p = 1;
	i = strlen(sir) - 1;
	while(i >= 0)
	{
		numar += (sir[i] - 48) * p;
		p = p * 10;
		i--;
	}
	return numar;
}

// Alocam memorie pentru matricea de adiacenta
int** initializare_matrice_adiacenta(int n)
{
	int i;
	int **adj = (int**)malloc(n * sizeof(int*));
	isNULL((int**)adj);
	for(i = 0; i < n; i++)
	{
		adj[i] = calloc( n , sizeof(int));
		isNULL((int*)adj[i]);
	}
	return adj;
}

// Citim informatia stocata in graful clientului si returnam adresa,
// de memorie la care am stocat aceste date
p_graf_client citire_graf_clienti(FILE *f,  int nr_clienti )
{
	p_graf_client graf = (p_graf_client)malloc(nr_clienti * sizeof(graf_client));
	isNULL((p_graf_client)graf);
	graf->clienti = (p_client)malloc(nr_clienti * sizeof(client));
	isNULL((p_client)graf->clienti);
	graf->clienti_adj = initializare_matrice_adiacenta(nr_clienti);

	char buffer[100];
	int i;
	int nr_leg, l, m;
	for(i = 0; i < nr_clienti; i++)
	{
		
		fgets(buffer, 99, f);
		sterge_sfarsit_si_spatii(buffer);
		graf->clienti[i].nume = malloc( (strlen(buffer) +1 ) * sizeof(char));
		strcpy(graf->clienti[i].nume, buffer);
		fscanf(f, "%d\n", &graf->clienti_adj[i][i] );
		fscanf(f, "%d\n", &graf->clienti[i].de_platit);
	}

	fscanf(f, "%d\n", &nr_leg);
	for(i = 0; i < nr_leg; i++)
	{
		fscanf(f, "%s", buffer);
		l = numar_client(buffer);

		fscanf(f, "%s", buffer);
		m = numar_client(buffer);
		
		fscanf(f, "%d\n", &graf->clienti_adj[l][m]);
		graf->clienti_adj[m][l] = graf->clienti_adj[l][m];

		
	}

	return graf;

}

// Citim informatiile referitoare la magistrala de metrou si returnam,
// adresa de inceput a blocului de memorie in care am stocat aceste
// date
p_graf_statie citire_date_graf(FILE *f)
{
	p_graf_statie graf;
	int i, m, l;
	graf = (p_graf_statie)malloc(sizeof(graf_statie));
	isNULL((p_graf_statie)graf);
	fscanf(f, "%d\n", &graf->nr_stati);	
	graf->stati = (p_statie)malloc(graf->nr_stati * sizeof(statie));
	isNULL((p_statie)graf->stati);
	char buffer[100];
	graf->statie_adj = initializare_matrice_adiacenta(graf->nr_stati);
	for(i = 0; i < graf->nr_stati; i++)
	{
		fgets(buffer, 99, f);
		sterge_sfarsit_si_spatii(buffer);
		graf->stati[i].nume = malloc((strlen(buffer) + 1 ) * sizeof(char));
		strcpy(graf->stati[i].nume, buffer);
		isNULL((char*)graf->stati[i].nume);
		fscanf(f, "%d\n", &graf->stati[i].nr_clienti);
		graf->stati[i].graf_clienti = citire_graf_clienti(f, graf->stati[i].nr_clienti);
	}

	fscanf(f, "%d\n", &graf->nr_leg);
	for(i = 0; i < graf->nr_leg; i++)
	{
		fscanf(f, "%s", buffer);
		l = numar_statie(buffer);

		fscanf(f, "%s", buffer);
		m = numar_statie(buffer);

		fscanf(f, "%d\n", &graf->statie_adj[l][m]);
		graf->statie_adj[m][l] = graf->statie_adj[l][m];
		
	}

	return graf;

}

// Alocam memorie pentru un vector cu n elemente folosind
// calloc pentru a initializa cu 0 zona de memorie
int* set_visited(int n)
{
	int *v = calloc(n , sizeof(int));
	isNULL((int*)v );
	return v;
}

// Initializam un vector deja alocat cu valoarea value
void reset_visited(int *v, int n, int value)
{
	int i;
	for(i = 0; i < n; i++)
	{
		v[i] = value;
	}
}

// Returnam indexul elementului cel mai mic din vectorul de
// de distanta ce nu se afla in vectorul sps
int minValue(int *sps, int *dist, int N)
{

	int i;
	int min = MAX, index;
	for(i = 0; i < N; i++)
	{
		if(sps[i] == 0 && dist[i] < min)
		{
			min = dist[i];
			index = i;
		}
	}

	return index;

}


// Algoritmul de gasire al drumului celui mai scurt de la nodul
// sursa la orice alt nod
p_dij dijkstra(int **a, int n , int source)
{

	p_dij data = (p_dij)malloc(sizeof(dij));
	isNULL((p_dij)data);
	data->sps = set_visited(n);
	data->dist = set_visited(n);
	data->prev = set_visited(n);

	reset_visited(data->prev, n, -1);
	reset_visited(data->sps, n, 0);
	reset_visited(data->dist, n, MAX);
	
	int i, j, u;
	data->dist[source] = 0;
	data->prev[source] = -1;
	for(j = 0; j < n - 1; j++)
	{
		u = minValue(data->sps, data->dist, n);
		data->sps[u] = 1;
		for(i = 0; i < n; i++)
		{
			if(data->sps[i] == 0 && data->dist[u] != MAX &&
				a[u][i] && data->dist[u] + a[u][i] < data->dist[i])
			{
				data->dist[i] = data->dist[u] + a[u][i];
				data->prev[i] = u;
			}		
		}
	}
	return data;
}
/*
void afisare_linie(int *v, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%d ", v[i]);
}*/



/*p_dij dijkstra_cu_modificarea_sursei(int **a, int n, int source)
{

	p_dij data = (p_dij)malloc(sizeof(dij));
	isNULL((p_dij)data);
	data->sps = set_visited(n);
	data->dist = set_visited(n);
	data->prev = set_visited(n);

	reset_visited(data->prev, n, -1);
	reset_visited(data->sps, n, 0);
	reset_visited(data->dist, n, MAX);
	
	int i, j, u;
	data->dist[source] = 0;
	data->prev[source] = -1;
	for(j = 0; j < n - 1; j++)
	{
		u = minValue(data->sps, data->dist, n);
		data->sps[u] = 1;
		for(i = 0; i < n; i++)
		{
			if(data->sps[i] == 0 && data->dist[u] != MAX &&
				a[u][i] && a[u][i] < data->dist[i])
			{
				data->dist[i] = a[u][i];
				data->prev[i] = u;
			}		
		}
	}
	afisare_linie(data->sps, n);
	return data;
}
*/

// Elibereaza memoria ocupata de structura returnata de algoritmul
// lui Dijkstra
void sterge_date_dijkstra(p_dij data)
{
	free(data->sps);
	free(data->prev);
	free(data->dist);
	free(data);
}

// Returneaza indexul celui mai mic element de pe linia unei matrice
// ce nu se afla in sps si este diferit de 0
int min_matrice(int *sps, int *linie, int N)
{

	int i;
	int min = MAX, index;
	for(i = 0; i < N; i++)
	{
		if(sps[i] == 0 && linie[i] < min && linie[i] != 0)
		{
			min = linie[i];
			index = i;
		}
	}

	return index;

}

// Afiseaza calea de la un nod la alt nod
void afisare_cale(FILE *f, p_dij data, char *tag, int n1, int n2)
{
	if(n1 == n2)
	{
		fprintf(f, "%s%d ",tag, n1 + 1);
		return;
	}
	afisare_cale(f, data, tag, n1, data->prev[n2]);
	fprintf(f, "%s%d ",tag, n2 + 1);

}


// Elibereaza memoria ocupata de o matrice
void eliberare_matrice(int **a, int n)
{
	int i;
	for(i = 0; i < n; i++)
		free(a[i]);
	free(a);
}
// Elibereaza memoria ocupata de graful ce simuleaza magistrala
void eliberare_memorie_graf(p_graf_statie graf)
{
	int i, j;
	for(i = 0; i < graf->nr_stati; i++)
	{

		for(j = 0; j < graf->stati[i].nr_clienti; j++)
			free(graf->stati[i].graf_clienti->clienti[j].nume);
		free(graf->stati[i].graf_clienti->clienti);
		eliberare_matrice(graf->stati[i].graf_clienti->clienti_adj, graf->stati[i].nr_clienti);
		free(graf->stati[i].graf_clienti);
		free(graf->stati[i].nume);
	}
	free(graf->stati);
	eliberare_matrice(graf->statie_adj, graf->nr_stati);
	free(graf);
}

// Extrage operatiile ce trebuie efectuate dintr-un sir linie
void extrage_operatii(char *linie, char s[4][50])
{
	int  k = -1, j;
	unsigned int i;
	i = 0;
	sterge_sfarsit_si_spatii(linie);
	while(i < strlen(linie))
	{
		k++;
		j = 0;
		while(linie[i] != ' ' && linie[i] != '\0')
			s[k][j++] = linie[i++];
		i++;
		s[k][j] = '\0';
		
	}
}

// Returneaza minimul a doua numere
int minim(int a, int b)
{
	if(a < b) return a;
	return b;
}

// Afiseaza lungimea drumului cel mai scrut din coltul dreapta jos
// al unei matrice la coltul din stanga sus
// Rezolvarea foloseste un procedeu de programare dinamica,
// matricea creata contine in fiecare "casuta" lungimea celui mai scrut
// drum de la acea "casuta" la coltul din stanga sus
void bonus(FILE *f, FILE *f1, int n)
{
	int **a;
	a = initializare_matrice_adiacenta(n);
	int i, j, k;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
		{

			fscanf(f1, "%d", &k);
			if(i == 0 && j == 0)
				a[i][j] = k;
			else if(i == 0)
				a[i][j] = a[i][j-1] + k;
			else if(j == 0)
				a[i][j] = a[i-1][j] + k;
			else
				a[i][j] = k + minim(a[i-1][j], a[i][j-1]);
		}
	fprintf(f, "%d", a[n-1][n-1]);
	eliberare_matrice(a, n);

}

