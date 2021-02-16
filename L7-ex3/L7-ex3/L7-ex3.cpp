//Să se scrie un program care verifică dacă un arbore binar ordonat este AVL.

#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#pragma warning (disable : 4996)
using namespace std;
typedef struct _nodABO {
	int cheie;
	int ech;
	_nodABO* st, * dr;
}nodABO;
nodABO* rad, ** pp;
FILE* f;
int cheie, n, ok;
void AdaugNod(nodABO** p) {
	if (*p) {
		if (cheie < (*p)->cheie)
			AdaugNod(&(*p)->st);
		else AdaugNod(&(*p)->dr);
	}
	else {
		*p = new nodABO;
		(*p)->cheie = cheie;
		(*p)->st = (*p)->dr = NULL;
	}
}
void AfisAB(nodABO* p, int niv) {
	int i;
	if (p) {
		AfisAB(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "\t";
		cout << p->cheie <<" "<< p->ech <<"\n";
		if (p->ech < -1 || p->ech>1)
			ok = 1;
		AfisAB(p->st, niv + 1);
	}
}
void drum_maxim(nodABO* p, int& max, int lung) {
	if (p != NULL) {
		drum_maxim(p->dr, max, lung + 1);
		if ((p->st == NULL) && (p->dr == NULL) && (max < lung))
			max = lung;
		drum_maxim(p->st, max, lung + 1);
	}
}
void calcul_factor_echilibru(nodABO* p) {
	int h_st = 1, h_dr = 1;
	if (p->st != NULL)
		drum_maxim(p->st, h_st, 1);
	else
		h_st = 0;
	if (p->dr != NULL)
		drum_maxim(p->dr, h_dr, 1);
	else
		h_dr = 0;
	p->ech = h_dr - h_st;
}
void Preordine(nodABO* p) {
	if (p) {
		calcul_factor_echilibru(p);
		Preordine(p->st);
		Preordine(p->dr);
	}
}
int main()
{
	int nr, i;
	rad = NULL;
	if ((f = fopen("abo.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%d", &cheie);
		AdaugNod(&rad);
	}
	fclose(f);
	Preordine(rad);
	cout << "Arborele binar ordonat este: \n";
	AfisAB(rad, 0);
	if (ok == 1)
		cout << "Arborele nu este AVL";
	else
		cout << "Arborele este AVL";
	return 0;
}