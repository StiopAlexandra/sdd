#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
using namespace std;
#pragma warning (disable : 4996) 
typedef struct _nodAB {
	char* nume;
	_nodAB* tata;
	_nodAB* mama;
}nodAB;
typedef struct _coada {
	nodAB* nod;
	_coada* urm;
}coada;
nodAB* rad;//radacina arborelui
coada* inc, * sf;//inceputul, respectiv sfarsitul cozii
char nume[100];
int i;
//adauga recursiv cate un nod in arbore
void AdaugNod(nodAB** p, int niv) {
	gets_s(nume);
	if (nume[0] != '\0') {
		*p = new nodAB;
		(*p)->nume = new char[strlen(nume) + 1];
		strcpy((*p)->nume, nume);
		for (i = 0; i <= niv; i++) cout << " ";
		cout << "Tatal pentru " << (*p)->nume << " este: ";
		AdaugNod(&(*p)->tata, niv + 1);
		for (i = 0; i <= niv; i++) cout << " ";
		cout << "Mama pentru " << (*p)->nume << " este: ";
		AdaugNod(&(*p)->mama, niv + 1);
	}
	else *p = NULL;
}
//afis. arb. rotit cu 90 de grade in sens trigonometric(dr=tata, st=mama)
void AfisAB(nodAB* p, int niv) {
	if (p) {
		AfisAB(p->tata, niv + 1);
		for (i = 0; i < niv; i++) cout << " ";
		cout << p->nume << endl;
		AfisAB(p->mama, niv + 1);
	}
}
void StergAB(nodAB* p) {
	if (p) {//traversare in postordine
		StergAB(p->tata);
		StergAB(p->mama);
		delete p->nume;
		delete p;
	}
}
//cauta un nod in arbore, traversandu-l in preordine
nodAB* Cauta(nodAB* nod) {
	nodAB* p;
	p = NULL;
	if (nod) {
		if (!strcmp(nod->nume, nume))//s-a gasit
			p = nod;
		else {//daca nu este acesta
			p = Cauta(nod->tata);//caut pe ramura tatalui
			if (!p)//nu s-a gasit nici pe ramura tatalui
				p = Cauta(nod->mama);//caut pe ramura mamei
		}
	}
	return p;
}
//adauga un nod in coada (la sfarsitul cozii)
int AdaugInCoada(nodAB * p) {
	coada* q;
	if (p) {
		q = new coada;
		q->nod = p;
		q->urm = NULL;
		sf->urm = q;
		sf = q;
		return 1;//am adaugat 1 nod
	}
	return 0;//nu am avut ce adauga(am adaugat 0 noduri)
}
//afisarea arborelui binar pe generatii
void AfisABGen() {
	coada* p;
	int cati, catiNou, grad;
	cati = 1;//initial avem un singur nod in coada
	grad = 0;//si suntem la gradul 0 (generatia formata de acest nod)
	while (inc) {//cat timp coada nu e vida
		catiNou = 0;//inca nu avem in coada noduri din generatia urmatoare
		cout << "\nGradul " << grad << ": ";
		for (i = 0; i < cati; i++) {//pentru toti din generatia curenta
			p = inc;//ne pozitionam pe inceputul cozii
			cout << "\n" << p->nod->nume;
			//inseram si numaram cati introducem din gen. urmatoare
			catiNou += AdaugInCoada(p->nod->tata);
			catiNou += AdaugInCoada(p->nod->mama);
			inc = inc->urm;//scoatem din coada nodul prelucrat (primul)
			delete p;//si il stergem
		}
		//pregatirea pentru generatia urmatoare
		cati = catiNou;
		grad++;
	}
}
int main() {
	nodAB* p;
	rad = NULL;
	cout << "Persoana pentru care se construieste arborele genealogic: ";
	AdaugNod(&rad, 0);//crearea arborelui
	do {
		cout << "Arborele este:\n";
		AfisAB(rad, 0);
		cout << "\nArborele pe generatii pentru: ";
		fflush(stdin);
		gets_s(nume);
		if (nume[0] != '\0') {
			p = Cauta(rad);//cautarea nodului cu cheia data
			if (p) {//s-a gasit => il introducem ca singurul nod in coada
				inc = new coada;
				inc->nod = p;
				inc->urm = NULL;
				sf = inc;
				AfisABGen();//afis. arb. pe generatii
			}
			else cout << "Persoana " << nume << " nu se gaseste in arbore.";
			_getch();
		}
	} while (nume[0] != '\0');
	StergAB(rad);//stergerea arborelui
}