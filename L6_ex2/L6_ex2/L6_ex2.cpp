/* Se dă un arbore binar ordonat cu chei întregi. Să se scrie un program care
determină şi suprima toate nodurile arborelui care se află iniţial de pe un nivel i dat, unde i nu
este nivelul maxim. Ilustraţi structura arborelui înainte şi după suprimarea nodurilor.  */

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
	_nodABO* st, * dr;
}nodABO;
nodABO* rad, ** pp;
FILE* f;
int cheie,n;
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
void AfisCaLista(nodABO* p) {
	if (p) {
		AfisCaLista(p->st);
		cout << p->cheie<< "   ";
		AfisCaLista(p->dr);
	}
}
void AfisAB(nodABO* p, int niv) {
	int i;
	if (p) {
		AfisAB(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "\t";
		cout << p->cheie << endl;
		AfisAB(p->st, niv + 1);
	}
}
void CopStergPred(struct _nodABO** p, struct _nodABO* q) {
	while ((*p)->dr) p = &(*p)->dr;
	q->cheie = (*p)->cheie;
	q = *p;
	*p = (*p)->st;
	delete q;
}
void Stergere(nodABO** p,int niv) {
	nodABO* q;
	if ((*p)) {
		if (n==niv) {
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
			Stergere(&(*p)->st,niv+1);
			Stergere(&(*p)->dr, niv + 1);
		}
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
	cout << "Arborele binar ordonat este: \n";
	AfisAB(rad, 0);
	cout << "\nArborele binar ordonat sub forma de lista este: ";
	AfisCaLista(rad);
	cout << "\n\nIntroduceti un nivel: ";
	cin >> n;
	cout << "Nodurile de pe nivelul " << n << " au fost sterse\n";
	Stergere(&rad,0);
	cout << "\nArborele binar ordonat dupa stergere este: \n";
	AfisAB(rad, 0);
	cout << "\nArborele binar ordonat sub forma de lista dupa stergere este: ";
	AfisCaLista(rad);
	return 0;
}
