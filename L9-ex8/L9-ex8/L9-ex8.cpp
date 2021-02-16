/*Se dă un graf neorientat care se citeşte dintr-un fişier. Să se afişeze pentru
fiecare nod gradul său. Să se verifice dacă graful este un graf regulat: un graf regulat este un
graf pentru care toate nodurile au acelaşi grad. În cazul unui răspuns afirmativ, să se afişeze
gradul acestui graf. In cazul unui răspuns negativ, să se determine care este numărul minim de
muchii care ar trebui adăugate pentru ca acesta să devină un graf regulat. */

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
	int grad;
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
		p->grad = nr;
		p = p->urmG;
	}
}
void AfisGrad(void) {
	nodG* p;
	p = incG;
	while (p) {
		cout << p->cheie << " - "<<p->grad<<endl;
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
	if (maxi == mini)
	{
		cout << "\nGraful este regulat";
		cout << "\nToate nodurile au gradul " << maxi;
	}
	else
	{
		cout << "\nGraful nu este regulat";
		cout << "\nGradurile nodurilor sunt: \n(nod - grad)\n";
		AfisGrad();
	}
	
}