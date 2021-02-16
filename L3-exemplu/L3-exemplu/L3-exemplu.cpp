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
	char* nume;
	struct _listaPFii* lf;
}nodArb;
nodArb* rad;
char nume[100], nume1[100], nume2[100];
char s[100];
int nivel[3], i;
//adauga un nod in arbore
void AdgNod(nodArb** nod, int niv)
{
	listaPFii** p;
	nodArb* nodNou;
	int nrFii;
	gets_s(s);
	if (s[0] != '\0') {
		//numele citit nu e vid => cream un nod in arbore
		*nod = new nodArb; //crearea noului nod
		(*nod)->nume = new char[strlen(s) + 1];
		strcpy((*nod)->nume, s);
		p = &(*nod)->lf;
		//p = incep. listei de fii ai noului nod
		*p = NULL; //initial nu are fii
		nrFii = 0;
		do { //adaug fii
			for (i = 0; i <= niv; i++) cout << " ";
			cout << "Fiul " << nrFii + 1 << " al lui " << (*nod)->nume << " este ";
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
		cout << p->nume << endl;
		lf = p->lf; //ne pozitionam pe inceputul listei de fii
		while (lf) { //afisam toti fii din lista
			AfisArb(lf->fiu, niv + 1);
			lf = lf->urm;
		}
	}
}
//stergerea arborelui
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
		delete p->nume;
		delete p; //stergem nodul
	}
}
//determinarea nivelurilor celor 2 rude si al stramosului comun
int DetNiv(nodArb* p, int niv)
{
	//parcurgere in preordine
	listaPFii* lf;
	int gasiti = 0;//vom numara cate rude contine subarborele curent
	if (p) {
		if (!nivel[1] && !strcmp(p->nume, nume1))
		{
			nivel[1] = niv;
			gasiti++; //aceasta este prima ruda
		}
		else
			if (!nivel[2] && !strcmp(p->nume, nume2))
			{
				nivel[2] = niv;
				gasiti++; //acesta este a doua ruda
			}
		lf = p->lf; //ne pozitionam pe inceputul listei de fii
		while ((!nivel[1] || !nivel[2]) && lf)
		{ //cat timp mai e vreo ruda negasita si mai sunt fii de parcurs
			if (DetNiv(lf->fiu, niv + 1)) gasiti++;
			lf = lf->urm;
		}
		if (gasiti == 2)
		{ //acesta este stramosul
			nivel[0] = niv; strcpy(nume, p->nume);
		}
	}
	return gasiti;
}
int main()
{
	rad = NULL;
	cout << "Dati stramosul tuturor: ";
	AdgNod(&rad, 0); //crearea arborelui
	do {
		cout << "\nArborele descendentilor:\n";
		AfisArb(rad, 0);//afisarea arborelui
		cout << "\nDati numele unei rude (sau Enter): ";
		fflush(stdin); gets_s(nume1);
		if (nume1[0] != '\0') {
			cout << "Dati numele celeilalte rude: ";
			cin >> nume2;
			nivel[0] = 0; nivel[1] = 0; nivel[2] = 0;
			DetNiv(rad, 1);
			// determinam cele trei niveluri
			//(ale celor 2 rude si al stramosului comun)
			if (!nivel[1] || !nivel[2])
			{
				if (!nivel[1])
					cout << "\nPersoana " << nume1 << " nu a fost gasita.";
				if (!nivel[2])
					cout << "\nPersoana " << nume2 << " nu a fost gasita.";
			}
			else
			{
				cout << "\nAceste rude sunt de gradul " << (nivel[1] - nivel[0]) +
					(nivel[2] - nivel[0]);
				cout << "\nCel mai apropiat stramos comun al lor este " << nume;
			}
			_getch();
		}
	} while (nume1[0] != '\0');
	StergArb(rad); //stergerea arborelui
}
