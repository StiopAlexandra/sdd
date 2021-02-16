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
	struct _nodG* urmG, * urmC;//urm. in graf, resp. in coada la trav. cupr.
	int marc;
}nodG;
typedef struct _nodL {
	struct _nodG* nod;
	struct _nodL* urmL;
}nodL;
enum { nemarcat, marcatAdancime, marcatCuprindere };
nodG* incG, * sfG, * incC, * sfC;//inc. si sf. pentru graf, resp. pentru coada
int n, m[2], i, j;
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
	cout << "Graful cunostintelor este:";
	p = incG;
	while (p) {//pentru fiecare nod al grafului
		cout << "\n" << p->cheie << " - ";//il afisam
		l = p->incL;
		while (l) {//pentru fiecare nod adiacent lui
			cout << " " << l->nod->cheie;//il afisam
			l = l->urmL;
		}
		p = p->urmG;
	}
}
void CautAdanc(nodG* p) { //traversarea nodului indicat de p
	nodL* l;
	cout << " " << p->cheie;//afisarea la semnare
	p->marc = marcatAdancime; //marcam nodul ca vizitat
	l = p->incL;//ne pozitionam pe inceputul listei de adiacente
	while (l) {//pentru fiecare nod adiacent lui
		if (l->nod->marc != marcatAdancime) {//daca n-a fost vizitat
			CautAdanc(l->nod);//il traversam
			cout << " " << p->cheie;//afisarea la revenire
		}
		l = l->urmL;//trecem la urmatorul nod adiacent
	}
}
void CautAdancGraf(nodG* p) {//functia de traversare in adancime pentru tot graful
	int nrCC;
	nrCC = 1;//initializarea numarului de componente conexe
	while (p) {//parcurgerea listei de noduri
		if (p->marc != marcatAdancime) {//daca nodul curent nu a fost parcurs => o noua comp.conexa
				cout << "\n Grupul " << nrCC << ":\n";
			CautAdanc(p);//traversare pentru noua comp. conexa
			nrCC++;//numararea componentelor conexe
		}
		p = p->urmG;
	}
}
void CautCuprGraf(nodG* p) {
	int nrCC;
	nodL* l;
	nrCC = 0;//initial nu avem nici o componenta conexa
	while (p) {
		//initializarea cozii cu primul element nevizitat din graf
		if (p->marc != marcatCuprindere) {
			incC = sfC = p;
			p->marc = marcatCuprindere;
			cout << "\n Grupul" << ++nrCC << ", pentru persoana " << p->cheie << ": \n "; 
		}
		while (incC) {//prelucrarea cozii
			l = incC->incL;//pozitionarea pe inceputul listei de adiacente
			while (l) {//parcurgerea listei de adiacente
				if (l->nod->marc != marcatCuprindere) {//nevizitat
					sfC->urmC = l->nod;//adaugare la sf cozii
					sfC = l->nod;
					l->nod->marc = marcatCuprindere;//marcare ca vizitat
					cout << "( " << incC->cheie << " -> " << l->nod->cheie << ")";//afis. arc
				}
				l = l->urmL;
			}
			incC = incC->urmC;//'scoaterea' din coada
		}
		p = p->urmG;
	}
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
		if (p[0] != p[1]) {
			AdaugMuchie(p[0], p[1]);
			AdaugMuchie(p[1], p[0]);
		}
	}
	fclose(f);
	AfisImplGraf();
	cout << "\n\nDrumul documentului:"; CautAdancGraf(incG);
	cout << "\n\nPerechile de cunostinte pentru legaturile minime la fiecare persoana:";
	CautCuprGraf(incG);
	StergGraf();
	_getch();
}
