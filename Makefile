build :
	gcc -g -Wextra tema.c operatii_de_baza.c operatii_clienti.c operatii_stati.c -o curier
clean :
	rm -f .*o
	rm -f curier
