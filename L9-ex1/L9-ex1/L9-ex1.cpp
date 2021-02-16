/*Scrieţi un program care, pentru un graf neorientat dat, afişează nodurile cu gradul
maxim respectiv minim. Să se determine apoi care este numărul minim de muchii care ar
trebui adăugat astfel încît graful să nu conţină noduri terminale. */

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
	int muchii;
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
int n, m[2], i, j, nr, maxi, mini, adM, ok, sM;
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
	mini = n;
	cout << "Structura de adiacenta a grafului este:";
	p = incG;
	while (p) {//pentru fiecare nod al grafului
		nr = 0;
		cout << "\n" << p->cheie << " - ";//il afisam
		l = p->incL;
		while (l) {//pentru fiecare nod adiacent lui
			nr++;
			cout << " " << l->nod->cheie;//il afisam
			l = l->urmL;
		}
		if (nr > maxi)
			maxi = nr;
		if (nr < mini)
			mini = nr;
		p->muchii = nr;
		p = p->urmG;
	}
}
void GradMaxim(void) {
	nodG* p;
	p = incG;
	while (p) {
		if(p->muchii==maxi)
			cout <<p->cheie<<" ";
		p = p->urmG;
	}
}
void GradMinim(void) {
	nodG* p;
	p = incG;
	while (p) {
		if (p->muchii == mini)
			cout << p->cheie << " ";
		p = p->urmG;
	}
}
void Muchii(int ch, int& ok) {
	nodG* p;
	nodL* l;
	p = incG;
	while (p) {
		if (p->muchii <= 1) {
			l = p->incL;
			while (l) {
				if (l->nod->cheie == ch)
					ok=1;
				l = l->urmL;
			}
		}
		p = p->urmG;
	}
}
void nodTerminal(void) {
	nodG* p;
	p = incG;
	while (p) {
		if (p->muchii == 1) {
			adM++;
			Muchii(p->cheie, ok);//verificam daca nodul terminal are legatura cu alt nod terminal
			if (ok == 0)//daca ad=0 nodul terminal nu are legatura cu alt nod terminal
				sM++;//sM va memora nr de noduri terminale care nu au legatura cu alte noduri terminale
			//se va aduga o muchie intre 2 nodurile terminale care nu au legatura intre ele
			//daca 2 nodurile terminale au legatura intre ele se va adauga cate o muchie pt fiecare nod		
		}
		if (p->muchii == 0)
			adM = adM + 2;//daca nodul este izolat e nevoie sa adaugam 2 muchii
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
		if (p[0] != p[1]) {
			AdaugMuchie(p[0], p[1]);
			AdaugMuchie(p[1], p[0]);
		}
	}
	fclose(f);
	AfisImplGraf();
	cout << "\nGradul maxim este " << maxi;
	cout << "\nNodurile cu gradul maxim sunt: ";
	GradMaxim();
	cout << "\nGradul minim este " << mini;
	cout << "\nNodurile cu gradul minim sunt: ";
	GradMinim();
	nodTerminal();
	cout << "\nIn graf ar trebui adaugate " << adM-(sM/2) << " muchii ca acesta sa nu mai contina noduri terminale\n";
}
