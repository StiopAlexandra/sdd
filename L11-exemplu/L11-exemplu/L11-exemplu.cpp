#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#pragma warning (disable : 4996)
using namespace std;
typedef struct _nodG {
	int cheie;
	struct _nodL* incL, * sfL;
	struct _nodG* urmG, * urmCP;//urm. in graf, resp. in coada cu priorit.
	struct _nodG* par;//parintele in arbore
	int marc;
	int prt;
}nodG;
typedef struct _nodL {
	struct _nodG* nod;
	int cost;
	struct _nodL* urmL;
}nodL;
enum { nemarcat, marcat };
nodG* incG, * sfG, * incCP, * sfCP;//inc. si sf. pentru graf, resp. pentru coada
int n, m[3], i, j, costTotal;
FILE* f;
nodG* AdaugNod(int k) {
	nodG* p;
	p = new nodG;
	p->cheie = k;
	p->incL = p->sfL = NULL;
	p->urmG = NULL;
	p->marc = nemarcat;
	if (sfG) {
		sfG->urmG = p; sfG = p;
	}
	else
		incG = sfG = p;
	return p;
}
void AdaugMuchie(nodG* s, nodG* d, int cost) {//adauga muchie de la s la d
	nodL* l;
	//crearea si initializarea noului nod de adiacenta
	l = new nodL;
	l->nod = d;//care va indica spre d
	l->cost = cost;
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
	cout << "Graful dat este:";
	p = incG;
	while (p) {//pentru fiecare nod al grafului
		cout << "\n" << p->cheie << " - ";//il afisam
		l = p->incL;
		while (l) {//pentru fiecare nod adiacent lui
			cout << l->nod->cheie << " (" << l->cost << ") " << "\t";//il afisam
			l = l->urmL;
		}
		p = p->urmG;
	}
}
void adaugaCP(nodG* na, nodG* par, int cost) {
	nodG* p1, * p2;
	//p1 va fi pozitia cu prt.=cost (cu una inainte), p2 e poz unde mai exista, daca mai exista
		p1 = incCP;
	sfCP->prt = cost + 1;
	sfCP->cheie = na->cheie;
	while (cost >= p1->urmCP->prt && na != p1)
		p1 = p1->urmCP;//pozitia lui cost
	if (p1 != na) {//nu l-am gasit mai prioritar => aici va fi inserat
	 //verificam dc se afla mai departe
		p2 = p1;
		while (na->cheie != p2->urmCP->cheie) p2 = p2->urmCP;
		if (p2->urmCP != sfCP)//l-am gasit mai departe => il scoatem
			p2->urmCP = p2->urmCP->urmCP;
		//inserarea dupa p1
		na->urmCP = p1->urmCP;
		p1->urmCP = na;
		na->prt = cost; na->par = par;
	}
}
void CautPr(nodG* p) {
	int nrCC;
	nodL* l;
	nodG* q;
	costTotal = 0;
	nrCC = 0;//nr. de componente conexe
	p = incG;
	while (p) {//parcurgem nodurile grafului
	 //initializarea cozii cu primul element nevizitat din graf
		if (p->marc == nemarcat) {
			cout << "\n - pentru componenta conexa " << ++nrCC << ":\n ";
			adaugaCP(p, NULL, 0);
			while (incCP->urmCP != sfCP) {//prelucrarea cozii
				q = incCP->urmCP;//'scoaterea' primului din coada, retinerea in q
					incCP->urmCP = q->urmCP;
				if (q->par) {//afisarea arcului si actualizarea costului total
						cout << " (" << q->par->cheie << "," << q->cheie << ")"<<"\t";//afis. arc
						costTotal += q->prt;
				}
				q->marc = marcat;
				l = q->incL;//pozitionarea pe inceputul listei de adiacente
				while (l) {//parcurgerea listei de adiacente
					if (l->nod->marc == nemarcat)//neinclus inca in arbore
						adaugaCP(l->nod, q, l->cost);
					l = l->urmL;
				}//while(l)
			}//sf. prelucrarii cozii
		}//sf. if p->marc==nemarcat
		p = p->urmG;//trecerea la urmatorul nod al grafului
	}//sf. while(p)
}
void StergGraf() {
	while (incG) {
		sfG = incG->urmG;
		while (incG->incL) {
			incG->sfL = incG->incL->urmL;
			delete incG->incL;
			incG->incL = incG->sfL;
		}
		delete incG;
		incG = sfG;
	}
}
int main() {
	nodG* p[2];
	incG = sfG = NULL;//crearea grafului
	//crearea cozii cu prioritate
	sfCP = new nodG;//incCP si sfCP sunt noduri fara inf. utila
	sfCP->urmCP = NULL;//sfCP va fi folosit si pe post de fanion
	incCP = new nodG;
	incCP->urmCP = sfCP;
	if ((f = fopen("graf.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 0;
	}
	//crearea grafului din fisier
	fscanf(f, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(f, "%d%d%d", &m[0], &m[1], &m[2]);
		for (j = 0; j < 2; j++) {
			p[j] = CautaNod(m[j]);
			if (!p[j])
				p[j] = AdaugNod(m[j]);
		}
		if (p[0] != p[1]) {
			AdaugMuchie(p[0], p[1], m[2]);
			AdaugMuchie(p[1], p[0], m[2]);
		}
	}
	fclose(f);
	AfisImplGraf();
	cout << "\n\nMuchiile arborelui de acoperire minim : \n";
	CautPr(incG);
	cout << endl;
	cout << "\n Costul total este: " << costTotal;
	_getch();
	delete incCP;
	delete sfCP;
	StergGraf();
}