/* Catalogul unei biblioteci de fişiere este organizat ca şi o structură de arbore binar
ordonat (funcţie de numele fişierului). Fiecare nod se referă la un fişier şi conţine numele
fişierului, data creării, dimensiunea fişierului precum şi alte informaţii. Să se redacteze un
program care şterge din structura de arbore toate fişierele a căror dimensiune este mai mică
decât o dimensiune dată. */

#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#pragma warning (disable : 4996)
using namespace std;
typedef struct _nodABO {
	char* nume;
	char* data;
	int dim;
	_nodABO* st, * dr;
}nodABO;
nodABO* rad, * radD, ** pp;
FILE* f;
char s[100], d[100];
int dim, dmin, n;
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
		(*p)->data = new char[strlen(d) + 1];
		strcpy((*p)->data, d);
		(*p)->dim = dim;
		(*p)->st = (*p)->dr = NULL;
	}
}
void AdaugNodDim(nodABO** p, nodABO* q) {
	if (*p) {
		if (q->dim < (*p)->dim)
			AdaugNodDim(&(*p)->st, q);
		else AdaugNodDim(&(*p)->dr, q);
	}
	else {
		*p = new nodABO;
		**p = *q;
		(*p)->st = (*p)->dr = NULL;
	}
}
void ParcurgereABO(nodABO* p) {
	if (p) {
		ParcurgereABO(p->st);
		AdaugNodDim(&radD, p);
		ParcurgereABO(p->dr);
	}
}
void AfisCaLista(nodABO* p) {
	if (p) { 
		AfisCaLista(p->st);
		cout << "\n" << p->nume << " -> " << p->data << " -> " << p->dim;
		AfisCaLista(p->dr);
	}
}
void AfisAB(nodABO* p, int niv) {
	int i;
	if (p) {
		AfisAB(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "\t\t";
		cout << p->nume << endl;
		AfisAB(p->st, niv + 1);
	}
}
void Numarare(nodABO* p) {
	if (p) {
		Numarare(p->dr);
		if (p->dim < dmin)
			n++;
		Numarare(p->st);
	}
}
void CopStergPred(struct _nodABO** p, struct _nodABO* q) {
	while ((*p)->dr) p = &(*p)->dr; 
	q->dim = (*p)->dim;
	q = *p; 
	*p = (*p)->st;
	delete q; 
}
void Stergere(nodABO** p) {
	nodABO* q;
	if ((*p)) {
		if ((*p)->dim < dmin) {
			q = (*p);
			if ((*p)->st == NULL) {
				*p = (*p)->dr;
				delete q;
			}
			else
				if ((*p)->dr == NULL) {
					*p = (*p)->st;
					delete q;
				}
				else 
					CopStergPred(&(*p)->st, q);
		}
		else
		{
			Stergere(&(*p)->st);
			Stergere(&(*p)->dr);
		}
	}
}
int main()
{
	int nr, i;
	rad = radD = NULL;
	if ((f = fopen("abo.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%s", s);
		fscanf(f, "%s", d);
		fscanf(f, "%d", &dim);
		AdaugNod(&rad);
	}
	fclose(f);
	ParcurgereABO(rad);
	cout << "Arborele binar ordonat dupa nume este: \n";
	AfisAB(rad, 0);
	cout << "\nArborele binar ordonat sub forma de lista este: ";
	cout << "\nNume -> Data -> Dimensiune";
	AfisCaLista(rad);
	cout << "\n\nIntroduceti o dimensiune: ";
	cin >> dmin;
	cout << "Nodurile cu dimensiune mai mica decat " << dmin << " au fost sterse\n";
	Numarare(rad);
	while (n) {
		Stergere(&rad);
		n--;
	}
	cout << "\nArborele binar ordonat sub forma de lista dupa stergere este: ";
	cout << "\nNume -> Data -> Dimensiune";
	AfisCaLista(rad);
	return 0;
}
