/*  Se consideră un arbore binar ordonat cu chei şiruri de caractere, dat iniţial. Să se
scrie programul prin care să se determine nivelul (nivelurile) cu numărul maxim de noduri. 
*/

#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
using namespace std;
typedef struct _nodABO {
	char* nume;
	_nodABO* st, * dr;
}nodABO;
nodABO* rad;
FILE* f;
char s[100];
int nivel[100],n=0,nmax=0;
void AdaugNod(nodABO** p) {
	if (*p) {
		if (strcmp(s, (*p)->nume) < 0)
			AdaugNod(&(*p)->st);
		else AdaugNod(&(*p)->dr);
	}
	else {
		*p = new nodABO;
		(*p)->nume = new char[strlen(s) + 1];
		strcpy((*p)->nume, s);
		(*p)->st = (*p)->dr = NULL;
	}
}
void CreareABO(void) {
	int nr, i;
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%s", s);
		AdaugNod(&rad);
	}
}
void Nivel(nodABO* p, int niv) {
	if (p) {
		nivel[niv]++;
		if(niv>n)
			n=niv;
		Nivel(p->st, niv + 1);
		Nivel(p->dr, niv + 1);
	}
}
void AfisAB(nodABO* p, int niv) {
	int i;
	if (p) {
		AfisAB(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "\t";
		cout << p->nume << endl;
		AfisAB(p->st, niv + 1);
	}
}
int main() {
	int i;
	rad = NULL;
	if ((f = fopen("abo.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	CreareABO();
	fclose(f);
	cout << "Arborele binar ordonat este: " << endl;
	AfisAB(rad, 0);
	cout << endl;
	Nivel(rad, 0);
	for (i = 0; i < n + 1; i++) {
		if (nivel[i] >= nmax) {
			nmax = nivel[i];
		}	
	}
	cout << "Nivelurile cu numar maxim de noduri ("<<nmax<<") sunt: ";
	for (i = 0; i < n + 1; i++) {
		if (nivel[i] == nmax)
			cout <<"\n\tnivelul "<< i;
	}
	cout << endl;
	return 0;
}
