/*Se consideră un arbore (în implementarea cu structuri de adiacenţă) care reprezintă
structura arborescentă a directoarelor şi fişierelor de pe o partiţie a unui disc (arborele este
doar o simulare în memorie a structurii de directoare). Să se realizeze mutarea conţinutului
unui director din ierarhie într-un alt director. */
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
char s[100], v[10][100], n1[100], n2[100], x[100];
int i, nrMax = 0, nr = 0, k = 0;
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
		for (int i = 0; i < niv; i++) cout << "   ";
		cout << p->cheie << endl;
		lf = p->lf; //ne pozitionam pe inceputul listei de fii
		while (lf) { //afisam toti fii din lista
			AfisArb(lf->fiu, niv + 1);
			lf = lf->urm;
		}
	}
}
void Adaugare(nodArb** nod)
{
	listaPFii** p;
	*nod = new nodArb; //crearea noului nod
	(*nod)->cheie = new char[strlen(v[0]) + 1];
	strcpy((*nod)->cheie, v[0]);
	p = &(*nod)->lf;
	*p = NULL; //initial nu are fii
	/*
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
	} while (nodNou != NULL);*/
}
void Mutare(nodArb* p, int niv) {
	listaPFii* lf;
	if (p) {
		lf = p->lf;
		while (lf) {
			if (!strcmp(lf->fiu->cheie, n1))
				strcpy(v[k++], lf->fiu->cheie);
			if (!strcmp(p->cheie, n1))
				strcpy(v[k++], lf->fiu->cheie);
			Mutare(lf->fiu, niv + 1);
			lf = lf->urm;
		}
	}
}
void StergArb(nodArb* p)
{
	listaPFii* q;
	if (p)
	{ //postordine
		while (p->lf)
		{ //cat timp lista de fii nu e vida
			q = p->lf; //ne pozitionam pe inceputul ei
			StergArb(q->fiu);
			//stergem subarborele cu radacina fiul curent
			p->lf = p->lf->urm;
			//mutam inceputul listei pe urmatorul nod al ei
			delete q; //stergem nodul din lista coresp. fiului curent
		}
		delete p->cheie;
		delete p; //stergem nodul
	}
}
nodArb* Cauta(nodArb* nod) {
	nodArb* p;
	p = NULL;
	listaPFii* lf;
	if (nod) {
		lf = nod->lf;
		while (lf) {
			if (!strcmp(nod->cheie, n1)) {
				p = nod;
			}
			Cauta(lf->fiu);
			lf = lf->urm;
		}
	}
	return p;
}
int main()
{
	int grN = 0, ad = 0, niv1 = 0, niv2 = 0, r = 1;
	rad = NULL;
	nodArb* p;
	cout << "Radacina arborelui: ";
	AdgNod(&rad, 0);
	AfisArb(rad, 0);
	cout << "Dati cheia nodului pe care doriti sa-l mutati: ";
	fflush(stdin); gets_s(n1);
	cout << "Dati cheia nodului unde doriti sa puneti nodul introdus mai sus: ";
	fflush(stdin); gets_s(n2);
	Mutare(rad, 0);
	for (i = 0; i < k; i++)
		cout << v[i] << " ";
	cout << endl;
	//Adaugare(Nod(rad));
	p = Cauta(rad);
	if (p)
		StergArb(p);
	AfisArb(rad, 0);
}