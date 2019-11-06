#ifndef OPERATII_STATI_H_INCLUDED
#define OPERATII_STATI_H_INCLUDED



#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif


int suma_statie(statie st);
void comanda_statie(FILE *f, p_graf_statie graf, int suma);
void legatura(FILE *f, p_graf_statie graf, char *statie);
void blocaj_tunel(p_graf_statie graf, char *st1, char *st2);
void adauga_ruta(p_graf_statie graf, char *st1, char *st2, int valoare);
void sterge_ruta(p_graf_statie graf, char *st1, char *st2);
void timp_statie(FILE *f, p_graf_statie graf, char *st);
void drum_metrou(FILE *f, p_graf_statie graf, char *st1, char *st2);


#endif
