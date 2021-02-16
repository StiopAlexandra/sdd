/* Să se scrie un program care creează un arbore generalizat cu noduri identificate prin chei.
Pentru arborele construit, să se determine următoarele:
a). pentru un anumit nod dat, afişează cheia tatălui, cheile fiilor, gradul şi adâncimea nodului.
b). gradul arborelui.
c). verifică dacă două noduri date sunt în relaţia strămoş-descendent.
d). realizează transformarea arborelui dat într-un arbore simetric (în oglindă). */
#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
using namespace std;
#pragma warning (disable : 4996)
typedef struct _listaPFii {
	struct _nodArb* fiu;
	_listaPFii* urm;
}listaPFii;
typedef struct _nodArb {
	char* cheie;
	struct _listaPFii* lf;
}nodArb;
nodArb* rad;
char s[100], x[100],n1[100],n2[100];
int i, nrMax = 0, nr = 0;
//adauga un nod in arbore
void AdgNod(nodArb** nod, int niv)
{
	listaPFii** p;
	nodArb* nodNou;
	int nrFii;
	gets_s(s);
	if (s[0] != '\0') {
		*nod = new nodArb; //crearea noului nod
		(*nod)->cheie = new char[strlen(s) + 1];
		strcpy((*nod)->cheie, s);
		p = &(*nod)->lf;
		//p = incep. listei de fii ai noului nod
		*p = NULL; //initial nu are fii
		nrFii = 0;
		do { //adaug fii
			for (i = 0; i <= niv; i++) cout << " ";
			cout << "Fiul " << nrFii + 1 << " al lui " << (*nod)->cheie << " este ";
			AdgNod(&nodNou, niv + 1); //incerc sa creez un nou fiu
			if (nodNou != NULL)
			{//s-a creat => il adaug la lista de fii
				*p = new listaPFii; //creez un nou nod de tipul listei
				(*p)->fiu = nodNou; //care va indica spre fiul nou creat
				(*p)->urm = NULL; //va fi ultimul din lista
				p = &(*p)->urm; //pregatire pentru un nou fiu
				nrFii++;
			}
		} while (nodNou != NULL);
	}
	else //nu am creat un nod
		*nod = NULL;
}
//afisarea arborelui
void AfisArb(nodArb* p, int niv) {
	listaPFii* lf;
	if (p) { //daca avem ce afisa
		for (int i = 0; i < niv; i++) cout << " ";
		cout << p->cheie << endl;
		lf = p->lf; //ne pozitionam pe inceputul listei de fii
		while (lf) { //afisam toti fii din lista
			AfisArb(lf->fiu, niv + 1);
			lf = lf->urm;
		}
	}
}
int GrArbore(nodArb* p, int niv) {
	listaPFii* lf;
	if (p) {
		lf = p->lf;
		if (nr > nrMax)
			nrMax = nr;
		nr = 0;
		while (lf) {
			GrArbore(lf->fiu, niv + 1);
			nr++;
			lf = lf->urm;
		}
	}
	return nrMax;
}
void DetNod(nodArb* p, int niv, int& grN, int& ad, int& r ) {
	listaPFii* lf;
	if (p) {
		lf = p->lf;
		while (lf) {
			if (!strcmp(lf->fiu->cheie, x))
			{
				cout << "Cheia tatalui lui " << x << " este egala cu " << p->cheie << endl;
				ad = niv;
				r = 0;
			}
			if (!strcmp(p->cheie, x)) {
				if (grN == 0)
					cout << "Cheile fiilor lui " << x << " sunt: " << endl;
				cout << lf->fiu->cheie << endl;
				grN++;
			}
			DetNod(lf->fiu, niv + 1, grN, ad, r);
			lf = lf->urm;
		}
	}
}
void Nod1(nodArb* p, int niv, int& niv1 ) {
	listaPFii* lf;
	if (p) { 
		if (!strcmp(p->cheie, n1))
			niv1= niv;
		lf = p->lf; 
		while (lf) { 
			Nod1(lf->fiu, niv + 1,niv1);
			lf = lf->urm;
		}
	}
}
void Nod2(nodArb* p, int niv, int& niv2) {
	listaPFii* lf;
	if (p) {
		if (!strcmp(p->cheie, n2))
			niv2= niv;
		lf = p->lf;
		while (lf) {
			Nod2(lf->fiu, niv + 1,niv2);
			lf = lf->urm;
		}
	}
}
int main()
{
	int grN = 0, ad = 0,niv1=0,niv2=0,r=1;
	rad = NULL;
	cout << "Radacina arborelui: ";
	AdgNod(&rad, 0); 
	AfisArb(rad, 0);
	cout << "a)" << endl;
	cout << "Introduceti cheia nodului pentru care doriti detalii: ";
	fflush(stdin);
	gets_s(x);
	DetNod(rad, 0, grN, ad,r);
	if (grN==0)
		cout << "Nodul " << x << " nu are fii" << endl;
	cout << "Gradul nodului " << x << " este egal cu " << grN << endl;
	if (r == 1) {
		cout << "Nodul " << x << " este radacina" << endl;
		cout << "Adancimea nodului " << x << " este egal cu " << 0 << endl;
	}
	else
		cout << "Adancimea nodului " << x << " este egal cu " << ad+1 << endl;
	cout << "b)" << endl;
	cout << "Gradul arborelui este egal cu " << GrArbore(rad, 0) << endl;
	cout << "c)" << endl;
	cout << "Dati cheia unui nod: ";
	fflush(stdin); gets_s(n1);
	cout << "Dati cheia altui nod: ";
	fflush(stdin); gets_s(n2);
	Nod1(rad, 0,niv1);
	Nod2(rad, 0,niv2);
	if (niv1 - niv2 != 0)
		cout << "Nodul cu cheia " << n1 << " este in relatie stramos-descendent cu nodul cu cheia " << n2;
	else
		cout << "Nodul cu cheia " << n1 << " este frate sau verisor cu nodul cu cheia " << n2;
}