/*Să se particularizeze algoritmul căutării cu prioritate pentru grafuri neponderate. Cum
trebuie să considerăm prioritatea nodurilor astfel încît să obţinem traversarea în adîncime
respectiv prin cuprindere utilizînd acest algoritm? */

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
	struct _nodG* urmG, * urmCP,*urmC;//urm. in graf, resp. in coada cu priorit.
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
nodG* incG, * sfG, * incCP, * sfCP, * incC, * sfC;//inc. si sf. pentru graf, resp. pentru coada
int n, m[3], i, j, nr;
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
	cout << "Graful neponderat dat este:";
	p = incG;
	while (p) {//pentru fiecare nod al grafului
		cout << "\n" << p->cheie << " - ";//il afisam
		l = p->incL;
		while (l) {//pentru fiecare nod adiacent lui
			cout << l->nod->cheie << "  ";//il afisam
			l = l->urmL;
		}
		p = p->urmG;
	}
}
void adaugaCP1(nodG* na, nodG* par, int cost) {
	nodG* p1, * p2;
	//p1 va fi pozitia cu prt.=cost (cu una inainte), p2 e poz unde mai exista, daca mai exista
	p1 = incCP;
	sfCP->prt = cost+1 ;
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
		na->prt = cost; 
		na->par = par;
	}
}
void adaugaCP2(nodG* na, nodG* par, int cost) {
	nodG* p1, * p2;
	//p1 va fi pozitia cu prt.=cost (cu una inainte), p2 e poz unde mai exista, daca mai exista
	p1 = incCP;
	sfCP->prt = cost+1;
	sfCP->cheie = na->cheie;
	while (cost-1>= p1->urmCP->prt && na != p1)
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
		na->prt = cost;
		na->par = par;
	}
}
void CautPr1(nodG* p) {
	int nrCC;
	nodL* l;
	nodG* q;
	nrCC = 0;//nr. de componente conexe
	p = incG;
	while (p) {//parcurgem nodurile grafului
	 //initializarea cozii cu primul element nevizitat din graf
		if (p->marc == nemarcat) {
			cout << "\n\tComponenta conexa " << ++nrCC << ": ";
			adaugaCP1(p, NULL, 0);
			while (incCP->urmCP != sfCP) {//prelucrarea cozii
				q = incCP->urmCP;//'scoaterea' primului din coada, retinerea in q
				incCP->urmCP = q->urmCP;
				if (q->par) {
					cout << "(" << q->par->cheie << "," << q->cheie << ") ";//afis. arc
				}
				q->marc = marcat;
				l = q->incL;//pozitionarea pe inceputul listei de adiacente
				while (l) {//parcurgerea listei de adiacente
					if (l->nod->marc == nemarcat)//neinclus inca in arbore
						adaugaCP1(l->nod, q, l->cost);
					l = l->urmL;
				}
			}//sf. prelucrarii cozii
		}//sf. if p->marc==nemarcat
		p = p->urmG;//trecerea la urmatorul nod al grafului
	}
}
void CautPr2(nodG* p) {
	int nrCC;
	nodL* l;
	nodG* q;
	nrCC = 0;//nr. de componente conexe
	p = incG;
	while (p) {//parcurgem nodurile grafului
	 //initializarea cozii cu primul element nevizitat din graf
		if (p->marc == nemarcat) {
			cout << "\n\tComponenta conexa " << ++nrCC << ": ";
			adaugaCP2(p, NULL,0);
			while (incCP->urmCP != sfCP) {//prelucrarea cozii
				q = incCP->urmCP;//'scoaterea' primului din coada, retinerea in q
				incCP->urmCP = q->urmCP;
				if (q->par) {
					cout << "(" << q->par->cheie << "," << q->cheie << ") ";//afis. arc
				}
				q->marc = marcat;
				l = q->incL;//pozitionarea pe inceputul listei de adiacente
				nr = 0;
				while (l) {//parcurgerea listei de adiacente
					if (l->nod->marc == nemarcat)//neinclus inca in arbore
					{						
						adaugaCP2(l->nod, q, l->cost+nr);
						nr++;
					}
					l = l->urmL;
				}
			}//sf. prelucrarii cozii
		}//sf. if p->marc==nemarcat
		p = p->urmG;//trecerea la urmatorul nod al grafului
	}
}
void CautAdanc(nodG* p) { //traversarea nodului indicat de p
	nodL* l;
	p->marc = marcat; //marcam nodul ca vizitat
	l = p->incL;//ne pozitionam pe inceputul listei de adiacente
	while (l) {//pentru fiecare nod adiacent lui
		if (l->nod->marc == nemarcat) {//daca n-a fost vizitat
			cout << "(" << p->cheie << "," << l->nod->cheie << ") ";
			CautAdanc(l->nod);//il traversam
		}
		l = l->urmL;//trecem la urmatorul nod adiacent
	}
}
void CautAdancGraf(nodG* p) { //functia de traversare in adancime pentru tot graful
	int nrCC;
	nrCC = 1; //initializarea numarului de componente conexe
	while (p) {//parcurgerea listei de noduri
		if (p->marc== nemarcat) { //daca nodul curent nu a fost parcurs => o noua comp. conexa
			cout << "\n Componenta conexa " << nrCC << ": ";
			CautAdanc(p); //traversare pentru noua comp. conexa
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
		if (p->marc == nemarcat) {
			incC = sfC = p;
			p->marc = marcat;
			cout << "\n Componenta conexa " << ++nrCC << ": ";
		}
		while (incC) {//prelucrarea cozii
			l = incC->incL;//pozitionarea pe inceputul listei de adiacente
			while (l) {//parcurgerea listei de adiacente
				if (l->nod->marc == nemarcat) {//nevizitat
					sfC->urmC = l->nod;//adaugare la sf. cozii
					sfC = l->nod;
					l->nod->marc = marcat;//marcare ca vizitat
					cout << "("<<incC->cheie<<","<<l->nod-> cheie << ") ";//afis. arc
				}
				l = l->urmL;
			}
			incC = incC->urmC;//scoaterea din coada
		}
		p = p->urmG;
	}
}
void ReinitializarelGraf(void) {
	nodG* p;
	nodL* l;
	p = incG;
	while (p) {
		p->marc = nemarcat;
		l = p->incL;
		while (l) {
			l->nod->marc = nemarcat;
			l = l->urmL;
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
		fscanf(f, "%d%d", &m[0], &m[1]);
		for (j = 0; j < 2; j++) {
			p[j] = CautaNod(m[j]);
			if (!p[j])
				p[j] = AdaugNod(m[j]);
		}
		//un graf cu aceeasi pondere pentru toate muchiile poate fi considerat un graf neponderat
		if (p[0] != p[1]) {
			AdaugMuchie(p[0], p[1], 1);
			AdaugMuchie(p[1], p[0], 1);
		}
	}
	fclose(f);
	AfisImplGraf();
	cout << "\n\nAlgoritmul de cautare cu prioritate pentru un graf neponderat va afisa acelasi rezultat \nca si algoritmul de traversare prin cuprindere, deoarece nodurile care se introduc in \ncoada au intodeauna prioritatea cea mai mica fata de toate nodurile care sunt deja in coada";
	cout << "\n\n\tMuchiile arborelui de acoperire minim:";
	CautPr1(incG);
	cout << "\n\nAm modificat algoritmul de cautare cu prioritate pentru un graf neponderat astfel incat \nsa afiseze acelasi rezultat ca si algoritmul de traversare prin adancime";
	ReinitializarelGraf();
	cout << "\n\n\tMuchiile arborelui de acoperire minim:";
	CautPr2(incG);
	ReinitializarelGraf();
	cout << "\n\n\nTraversarea prin adancime:";
	CautAdancGraf(incG);
	ReinitializarelGraf();
	cout << "\n\nTraversarea prin cuprindere:";
	CautCuprGraf(incG);
	StergGraf();
}
