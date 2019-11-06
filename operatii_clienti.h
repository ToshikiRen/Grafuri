#ifndef OPERATII_CLIENTI_H_INCLUDED
#define OPERATII_CLIENTI_H_INCLUDED

#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif



void extrage_tag_client(char *nume);
void conexiune(FILE *f, p_graf_statie graf, char *client1, char *client2);
void blocaj_strada(p_graf_statie graf, char *clt1, char *clt2);
void adauga_strada(p_graf_statie graf, char *clt1, char *clt2, int valoare);
void sterge_strada(p_graf_statie graf, char *clt1, char *clt2);
void drum_strada(FILE *f, p_graf_statie graf, char *clt1, char *clt2);

#endif
