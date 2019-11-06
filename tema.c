#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "structuri.h"
#include "operatii_de_baza.h"
#include "operatii_clienti.h"
#include "operatii_stati.h"


// Rezolvarea a fost gandita in urma unei analize atente a fisierelor de output,
// de aceea, rezolvarea este buna, doar daca se pastreaza aceleasi denumiri
// ca si in fisierele de input
// Spre exemplu numele statiilor sa fie de forma StatieNumar_statie,
// iar numele clientilor de forma ClientNumar_statie.Numar_client



int main(int argc, char *args[])
{
	FILE *f = deschide_fisier(args[1], "rt");
	

	FILE *f1 = deschide_fisier(args[2], "wt");
		
	p_graf_statie graf = citire_date_graf(f);
	int n, i;
	char linie[100], s[4][50];
	fscanf(f, "%d\n", &n);
	for(i = 0; i < n; i++)
	{
		fgets(linie, 99, f);
		extrage_operatii(linie, s);
		if(!strcmp("legatura", s[0]))
			legatura(f1 ,graf, s[1]);
		else if(!strcmp("sterge_ruta", s[0]))
			sterge_ruta(graf, s[1], s[2]);
		else if(!strcmp("adauga_ruta", s[0]))
			adauga_ruta(graf, s[1], s[2], sir_la_numar(s[3]));
		else if(!strcmp("timp_statie", s[0]))
			timp_statie(f1, graf, s[1]);
		else if(!strcmp("comanda_statie", s[0]))
			comanda_statie(f1, graf, sir_la_numar(s[1]));
		else if(!strcmp("conexiune", s[0]))
			conexiune(f1 , graf, s[1], s[2]);
		else if(!strcmp("blocaj_tunel", s[0]))
			blocaj_tunel(graf, s[1], s[2]);
		else if(!strcmp("blocaj_strada", s[0]))
			blocaj_strada(graf, s[1], s[2]);
		else if(!strcmp("sterge_strada", s[0]))
			sterge_strada(graf, s[1], s[2]);
		else if(!strcmp("adauga_strada", s[0]))
			adauga_strada(graf, s[1], s[2], sir_la_numar(s[3]));
		else if(!strcmp("drum_metrou", s[0]))
			drum_metrou(f1, graf, s[1], s[2]);
		else if(!strcmp("drum_strada", s[0]))
			drum_strada(f1, graf, s[1], s[2]);
	}
	i = -1;
	fscanf(f, "%d", &i);
	if(i != -1)
		bonus(f1, f, i);

	eliberare_memorie_graf(graf);
	fclose(f);
	fclose(f1);
	return 0;
}