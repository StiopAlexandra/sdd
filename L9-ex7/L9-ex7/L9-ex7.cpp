/* Să se determine pentru un graf dat, dacă acesta conţine bucle.  */

#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#define nMAX 50 
#pragma warning (disable : 4996)
using namespace std;
typedef struct _nodG {
	int cheie;
	struct _nodL* incL, * sfL;
	struct _nodG* urmG, * urmC;//urm. in graf, resp. in coada la trav. cupr.
	int marc;
}nodG;
typedef struct _nodL {
	struct _nodG* nod;
	struct _nodL* urmL;
}nodL;
enum { nemarcat, marcatAdancime, marcatCuprindere };
nodG* incG, * sfG, * incC, * sfC;//inc. si sf. pentru graf, resp. pentru coada
int n, m[2], i, j, b, nr,v[nMAX];
FILE* f;
nodG* AdaugNod(int k) {
	nodG* p;
	p = new nodG;
	p->cheie = k;
	p->incL = p->sfL = NULL;
	p->urmG = NULL;
	p->urmC = NULL;
	p->marc = nemarcat;
	if (sfG) {//mai sunt noduri in graf
		sfG->urmG = p; sfG = p;
	}
	else//nu mai sunt; acesta este primul nod
		incG = sfG = p;
	return p;
}
void AdaugMuchie(nodG* s, nodG* d) {//adauga muchie de la s la d
	nodL* l;
	//crearea si initializarea noului nod de adiacenta
	l = new nodL;
	l->nod = d;//care va indica spre d
	l->urmL = NULL;
	//adaugarea nodului la sfarsitul listei de adiacente a lui s
	if (s->sfL) {//lista de adiacente nu este vida
		s->sfL->urmL = l; s->sfL = l;
	}
	else//lista de adiacente este vida
		s->incL = s->sfL = l;
}
nodG* CautaNod(int k) {
	nodG* p;
	p = incG;
	while (p && k != p->cheie)
		p = p->urmG;
	return p;
}
void AfisImplGraf(void) {
	nodG* p;
	nodL* l;
	cout << "Structura de adiacenta a grafului orientat este:";
	p = incG;
	while (p) {//pentru fiecare nod al grafului
		cout << "\n" << p->cheie << " - ";//il afisam
		b = p->cheie;
		l = p->incL;
		while (l) {//pentru fiecare nod adiacent lui
			cout << " " << l->nod->cheie;//il afisam
			if (b == l->nod->cheie)
				v[nr++] = b;
			l = l->urmL;
		}
		p = p->urmG;
	}
}
void main() {
	nodG* p[2];
	incG = sfG = NULL;
	if ((f = fopen("graf.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return;
	}
	fscanf(f, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(f, "%d%d", &m[0], &m[1]);
		for (j = 0; j < 2; j++) {
			p[j] = CautaNod(m[j]);
			if (!p[j]) p[j] = AdaugNod(m[j]);
		}
		AdaugMuchie(p[0], p[1]);
	}
	fclose(f);
	AfisImplGraf();
	if (nr != 0)
	{
		cout << "\nGraful dat contine bucle";
		cout << "\nNodurile care au bucle sunt: ";
		for (i = 0; i < nr; i++)
			cout << v[i]<<" ";
	}
	else
		cout << "\nGraful dat nu contine bucle";
}
