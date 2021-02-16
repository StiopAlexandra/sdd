//arbore binar ordonat
///*
#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
using namespace std;
typedef struct _nodABO {
	char* nume;
	_nodABO* st, * dr;
}nodABO;
nodABO* rad;
FILE* f;
char s[100];
int nivel[100], n = 0, nmax = 0;
void AdaugNod(nodABO** p) {
	if (*p) {
		if (strcmp(s, (*p)->nume) < 0)
			AdaugNod(&(*p)->st);
		else AdaugNod(&(*p)->dr);
	}
	else {
		*p = new nodABO;
		(*p)->nume = new char[strlen(s) + 1];
		strcpy((*p)->nume, s);
		(*p)->st = (*p)->dr = NULL;
	}
}
void CreareABO(void) {
	int nr, i;
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%s", s);
		AdaugNod(&rad);
	}
}
void AfisAB(nodABO* p, int niv) {
	int i;
	if (p) {
		AfisAB(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "   ";
		cout << p->nume << endl;
		AfisAB(p->st, niv + 1);
	}
}
void Preordine(nodABO* p) {
	if (p) {
		cout << p->nume << " ";
		Preordine(p->st);
		Preordine(p->dr);
	}
}
void Inordine(nodABO* p) {
	if (p) {
		Inordine(p->st);
		cout << p->nume << " ";
		Inordine(p->dr);
	}
}
void Postordine(nodABO* p) {
	if (p) {
		Postordine(p->st);
		Postordine(p->dr);
		cout << p->nume << " ";
	}
}
int main() {
	rad = NULL;
	if ((f = fopen("abo.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	CreareABO();
	fclose(f);
	cout << "Arborele binar ordonat este: " << endl;
	AfisAB(rad, 0);
	cout << "\nPreordine: " << endl;
	Preordine(rad);
	cout << "\nInordine: " << endl;
	Inordine(rad);
	cout << "\nPostordine: " << endl;
	Postordine(rad);
	return 0;
}
//*/

//arbore binar
/*
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
	_nodAB* st;
	_nodAB* dr;
}nodAB;
nodAB* rad;//radacina arborelui
char s[100];
int i;
FILE* f;
//adauga recursiv cate un nod in arbore
void AdaugNod(nodAB** p, int niv) {
	fscanf(f, "%s", s);
	if (strcmp(s,"0")!=0) {
		*p = new nodAB;
		(*p)->nume = new char[strlen(s) + 1];
		strcpy((*p)->nume, s);
		AdaugNod(&(*p)->st, niv + 1);
		AdaugNod(&(*p)->dr, niv + 1);
	}
	else *p = NULL;
}
//afis. arb. rotit cu 90 de grade in sens trigonometric(dr=st, st=dr)
void AfisAB(nodAB* p, int niv) {
	if (p) {
		AfisAB(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "   ";
		cout << p->nume << endl;
		AfisAB(p->st, niv + 1);
	}
}
void Preordine(nodAB* p) {
	if (p) {
		cout << p->nume << " ";
		Preordine(p->st);
		Preordine(p->dr);
	}
}
void Inordine(nodAB* p) {
	if (p) {
		Inordine(p->st);
		cout << p->nume << " ";
		Inordine(p->dr);
	}
}
void Postordine(nodAB* p) {
	if (p) {
		Postordine(p->st);
		Postordine(p->dr);
		cout << p->nume << " ";
	}
}
int main() {
	rad = NULL;
	if ((f = fopen("ab.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	AdaugNod(&rad, 0);//crearea arborelui
	cout << "Arborele binar este:\n";
	AfisAB(rad, 0);
	cout << "\nPreordine: " << endl;
	Preordine(rad);
	cout << "\nInordine: " << endl;
	Inordine(rad);
	cout << "\nPostordine: " << endl;
	Postordine(rad);
}
*/

//arbore general
/*
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
FILE* f;
char s[100];
int  i;
//adauga un nod in arbore
void AdgNod(nodArb** nod, int niv)
{
	listaPFii** p;
	nodArb* nodNou;
	int nrFii;
	fscanf(f, "%s", s);
	if (strcmp(s, "0") != 0) {
		//numele citit nu e vid => cream un nod in arbore
		*nod = new nodArb; //crearea noului nod
		(*nod)->nume = new char[strlen(s) + 1];
		strcpy((*nod)->nume, s);
		p = &(*nod)->lf;
		//p = incep. listei de fii ai noului nod
		*p = NULL; //initial nu are fii
		nrFii = 0;
		do { //adaug fii
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
		cout << p->nume << endl;
		lf = p->lf; //ne pozitionam pe inceputul listei de fii
		while (lf) { //afisam toti fii din lista
			AfisArb(lf->fiu, niv + 1);
			lf = lf->urm;
		}
	}
}
void Preordine(nodArb* p) {
	listaPFii* lf;
	if (p) {
		cout << p->nume << " ";
		lf = p->lf;
		while (lf) {
			Preordine(lf->fiu);
			lf = lf->urm;
		}
	}
}
void Inordine(nodArb* p) {
	listaPFii* lf;
	if (p) {
		if (p->lf) Inordine(p->lf->fiu);
		cout << p->nume << " ";
		if (p->lf) {
			lf = p->lf->urm;
			while (lf) {
				Inordine(lf->fiu);
				lf = lf->urm;
			}
		}
	}
}
void Postordine(nodArb* p) {
	listaPFii* lf;
	if (p) {
		lf = p->lf;
		while (lf) {
			Postordine(lf->fiu);
			lf = lf->urm;
		}
		cout << p->nume << " ";
	}
}
int main()
{
	rad = NULL;
	if ((f = fopen("ag.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	AdgNod(&rad, 0); //crearea arborelui
	cout << "Arborele general este:\n";
	AfisArb(rad, 0);//afisarea arborelui
	cout << "\nPreordine: " << endl;
	Preordine(rad);
	cout << "\nInordine: " << endl;
	Inordine(rad);
	cout << "\nPostordine: " << endl;
	Postordine(rad);
}
*/
/*
#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable : 4996)
using namespace std;
enum { stanga, dreapta };
typedef struct _nodAVL {
	int cheie, contor, ech;
	_nodAVL* f[2];//cei doi fii: *f[0] = fiul stang, *f[1] = fiul drept
}nodAVL;
nodAVL* radAVL;
int havl, hao;
int h;
//va indica:
// - la insertie: daca inaltimea subarborelui in care s-a inserat a crescut
// - la suprimare: daca inaltimea subarborelui din care s-a suprimat a scazut 
int echMareP[2] = { -1, 1 }, echilibrat = 0;//echilibrele posibile pt. un nod AVL
FILE* f;
int cheie, n, ok;
void RotSimpla(int parte, nodAVL** p) {//rotatia simpla in partea specificata
	nodAVL* p1;
	int st, dr;
	if (parte == stanga) { st = 0; dr = 1; }//rotatie simpla stanga
	else { st = 1; dr = 0; }//rotatie simpla dreapta
	 //initial, **p este nodul a din figuri
	p1 = (*p)->f[st];//initial, *p1 este nodul b
	//cazul exceptie la suprimare => a nu va fi perfect echilibrat(hP > hPO)
	if (h == 2) (*p)->ech = echMareP[parte];
	else (*p)->ech = echilibrat;//altfel, a va fi perfect echilibrat (ech = 0)
	 //reasignarea pointerilor
	(*p)->f[st] = p1->f[dr];//e va fi fiu al lui a
	p1->f[dr] = *p;//a va fi fiu al lui b
	*p = p1;//b va fi radacina subarborelui
}
void RotDubla(int parte, nodAVL** p) {//rotatia dubla in partea specificata
	nodAVL* p1, * p2;
	int st, dr;
	if (parte == stanga) { st = 0; dr = 1; }//rotatie dubla stanga
	else { st = 1; dr = 0; }//rotatie dubla dreapta
	 //initial, **p este nodul a din figuri
	p1 = (*p)->f[st];//*p1 este initial nodul b
	p2 = p1->f[dr];//*p2 este initial nodul e
	//ajustarea factorilor de echilibru
	if (p2->ech == echMareP[parte]) {//daca pentru e, hP > hPO, vom avea:
		p1->ech = echilibrat;//b va fi echilibrat (ech = 0)
		(*p)->ech = echMareP[1 - parte];//pentru a, hP < hPO
	}
	else
		if (p2->ech == echMareP[1 - parte]) {//daca pentru e, hP < hPO, vom avea:
			p1->ech = echMareP[parte];//pentru b, hP > hPO
			(*p)->ech = echilibrat;//a va fi echilibrat (ech = 0)
		}
		else {//p2->ech == ech; la adaugare acest lucru <=> e este terminal (h=0; e este noul inserat)
			(*p)->ech = echilibrat;
			p1->ech = echilibrat;
		}
	//reasignarea pointerilor
	(*p)->f[st] = p2->f[dr];//un fiu al lui e va fi al lui a
	p1->f[dr] = p2->f[st];//celalalt fiu al lui e va fi al lui b
	p2->f[st] = p1;//b va fi fiu al lui e
	p2->f[dr] = *p;//a va fi fiu al lui e
	*p = p2;//e va fi radacina subarborelui
}
//la revenirea dintr-o parte, la stergere
void RevSterg(int parte, nodAVL** p) {
	//s-a micsorat subarborele de unde am revenit <=> a avut loc o suprimare
	if ((*p)->ech == echMareP[parte])//a fost mai inalt in aceasta parte
		(*p)->ech = echilibrat;//imbunatatirea echilibrului, h a scazut
	else
		if ((*p)->ech == echilibrat) {//a fost echilibrat
			(*p)->ech = echMareP[1 - parte];
			h = 0;//h nu a scazut
		}
		else {//(*p)->ech==echMarePO[parte] <=> a fost mai inalt in partea opusa supr = > reech.
				if ((*p)->f[1 - parte]->ech == echMareP[1 - parte]) {//pt b, hP > hPO
					RotSimpla(1 - parte, p);//rot. simpla in partea opusa suprimarii
					cout << "\nROTATIE SIMPLA\n\n";
					(*p)->ech = 0;//acum va fi echilibrat
				}
				else//pt b, hP <= hPO
					if ((*p)->f[1 - parte]->ech == echilibrat) {//pt b, hP==hPO (exceptia)
							h = 2;
						RotSimpla(1 - parte, p);
						cout << "\nROTATIE SIMPLA\n\n";
						h = 0;//de aici nu se mai propaga posibilitatea reechilibrarii
						(*p)->ech = echMareP[parte];//radacina arborelui reechilibrat nu va fi perfect echilibrata
					}
					else {//pt b, hP < hPO
						RotDubla(1 - parte, p);//rot. dubla in partea opusa suprimarii
						cout << "\nROTATIE DUBLA\n\n";
						(*p)->ech = echilibrat;//acum va fi echilibrat
					}
		}
}
void AdaugNodAVL(nodAVL** p, int x);
void InsNod(int parte, nodAVL** p, int x) {//inserarea intr-o parte si, eventual, reech.
	AdaugNodAVL(&(*p)->f[parte], x);
	if (h)//a crescut subarborele in care am adaugat
		if ((*p)->ech == echMareP[1 - parte]) {//pt a, aveam hP < hPO
			(*p)->ech = echilibrat;//pt a vom avea hP = hPO
			h = 0;//imbunatatirea echilibrului, h nu a crescut
		}
		else//pt a, aveam hP >= hPO
			if ((*p)->ech == echilibrat)//pt a, aveam hP = hPO
				(*p)->ech = echMareP[parte];//si vom avea hP > hPO
			else {//(*p)->ech==echMareP[parte] <=> pt a aveam hP > hPO
				if ((*p)->f[parte]->ech == echMareP[parte]) {
					RotSimpla(parte, p);
					if (ok == 1)
						cout << "\nROTATIE SIMPLA\n\n";
				}	
				else {
					RotDubla(parte, p);
					if (ok == 1)
						cout << "\nROTATIE DUBLA\n\n";
				} 
				(*p)->ech = echilibrat;//dupa reech., pt a, vom avea hP =hPO
				h = 0;//si inaltimea nu este mai mare decat inainte de insertie
			}
}
void AdaugNodAVL(nodAVL** p, int x) {
	if (*p)
		if (x < (*p)->cheie)//il cautam in stanga
			InsNod(stanga, p, x);
		else
			if (x > (*p)->cheie)//il cautam in dreapta
				InsNod(dreapta, p, x);
			else (*p)->contor++;
	else {//nodul nu se afla in arbore => adaugarea propriu-zisa
		*p = new nodAVL;
		(*p)->cheie = x;
		(*p)->f[0] = (*p)->f[1] = NULL;
		(*p)->ech = echilibrat;
		(*p)->contor = 1;
		h = 1;//semnalam pentru stramosi ca arborele a crescut
	}
}
void StergNod1(nodAVL** p, nodAVL* nS) {//copiaza inf. pred. peste nS (de sters)
	nodAVL* q; //si sterge predecesorul; initial, p = fiul stg al lui nS
		if ((*p)->f[1]) {//deplasari in dreapta cat se poate
			StergNod1(&(*p)->f[1], nS);
			if (h) RevSterg(dreapta, p);
		}
		else {//p este predecesorul lui nS
			q = *p;//il retinem in q
			nS->cheie = q->cheie;//copiem inf. predecesorului in nodul de sters
			nS->contor = q->contor;
			*p = q->f[0];//scoatem pred. din arbore
			delete q;//stergem predecesorul
			h = 1;//semnalam stramosilor ca a scazut inaltimea arborelui (s-ar putea sa fie nevoie de reechilibrare)
		}
}
void StergNod(nodAVL** p, int x) {
	nodAVL* q;
	if (!(*p)) {
		cout << "Nod negasit\n";
		_getch();
	}
	else {
		if (x < (*p)->cheie) {//il stergem din stanga
			StergNod(&(*p)->f[0], x);
			if (h) RevSterg(stanga, p);
		}
		else
			if (x > (*p)->cheie) {//il stergem din dreapta
				StergNod(&(*p)->f[1], x);
				if (h) RevSterg(dreapta, p);
			}
			else {//suntem la nodul de sters
				q = (*p);//retinem adresa nodului de sters
				//scoatem din arbore nodul de sters
				if ((*p)->f[0] == NULL) {//are cel mult fiu drept
					*p = (*p)->f[1]; delete q; h = 1;
				}
				else
					if ((*p)->f[1] == NULL) {//are cel mult fiu stang
						*p = (*p)->f[0]; delete q; h = 1;
					}
					else {//are 2 fii => inlocuirea cu pred. si stergerea acestuia
							StergNod1(&(*p)->f[0], q);
						if (h) RevSterg(stanga, p);
					}
			}
	}
}
void AfisareAVL(nodAVL* p, int niv) {
	int i;
	if (p) {
		AfisareAVL(p->f[1], niv + 1);
		for (i = 0; i < niv; i++) cout << "\t";
		cout << p->cheie << endl;
		AfisareAVL(p->f[0], niv + 1);
	}
}
int main() {
	int i, nr;
	radAVL = NULL;
	if ((f = fopen("avl.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		h = 0;
		fscanf(f, "%d", &cheie);
		AdaugNodAVL(&radAVL, cheie);
	}
	fclose(f);
	ok = 1;
	cout << "Arborele AVL este:\n";
	AfisareAVL(radAVL, 0);
	char optiune;
	do {
		cout << "\n 1.Adaugare 2.Suprimare 0.Iesire\n";
		optiune = _getch();
		if (optiune != '0') {
			if (optiune == '1') {
				cout << "Cheia nodului de adaugat: ";
				cin >> i;
				AdaugNodAVL(&radAVL, i);
				AfisareAVL(radAVL, 0);
			}
			else if (optiune == '2') {
				cout << "Cheia nodului de suprimat: ";
				cin >> i;
				StergNod(&radAVL, i);
				AfisareAVL(radAVL, 0);
			}
		}
	} while (optiune != '0');

	return 0;
}
*/