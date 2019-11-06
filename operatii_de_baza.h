#ifndef OPERATII_DE_BAZA_H_INCLUDED
#define OPERATII_DE_BAZA_H_INCLUDED

#include <stdio.h>

int numar_client(char *nume);
int numar_statie_client(char *nume);
int numar_statie(char *nume);
void isNULL(void *ptr);
FILE* deschide_fisier(char *filename, char *mod);
void sterge_sfarsit_si_spatii(char *nume);
int sir_la_numar(char *sir);
int** initializare_matrice_adiacenta(int n);
p_graf_client citire_graf_clienti(FILE *f,  int nr_clienti );
p_graf_statie citire_date_graf(FILE *f);
int* set_visited(int n);
void reset_visited(int *v, int n, int value);
int minValue(int *sps, int *dist, int N);
p_dij dijkstra(int **a, int n , int source);
//void afisare_linie(int *v, int n);
void sterge_date_dijkstra(p_dij data);
int min_matrice(int *sps, int *linie, int N);
void afisare_cale(FILE *f, p_dij data, char *tag, int n1, int n2);
void eliberare_matrice(int **a, int n);
void eliberare_memorie_graf(p_graf_statie graf);
void extrage_operatii(char *linie, char s[4][50]);
int minim(int a, int b);
void bonus(FILE *f, FILE *f1, int n);


#endif
