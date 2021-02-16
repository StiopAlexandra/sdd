#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
enum { stanga, dreapta };
typedef struct _nodAVL {
	int cheie, contor, ech;
	_nodAVL* f[2];//cei doi fii: *f[0] = fiul stang, *f[1] = fiul drept
}nodAVL;
nodAVL* rad;
int na, nra, ns, nrs,ok;
int h;/*va indica:
 - la insertie: daca inaltimea subarborelui in care s-a inserat a crescut
 - la suprimare: daca inaltimea subarborelui din care s-a suprimat a scazut */
int echMareP[2] = { -1, 1 }, echilibrat = 0;//echilibrele posibile pt. un nod AVL
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
			nrs++;
			cout << "\n!!!ARBORELE A FOST REECHILIBRAT!!!\n";
			if ((*p)->f[1 - parte]->ech == echMareP[1 - parte]) {//pt b, hP >hPO
				RotSimpla(1 - parte, p);//rot. simpla in partea opusa suprimarii
				(*p)->ech = 0;//acum va fi echilibrat
			}
			else//pt b, hP <= hPO
				if ((*p)->f[1 - parte]->ech == echilibrat) {//pt b, hP==hPO (exceptia)
					h = 2;
					RotSimpla(1 - parte, p);
					h = 0;//de aici nu se mai propaga posibilitatea reechilibrarii reechilibrat nu va fi perfect echilibrata
				}
				else {//pt b, hP < hPO
					RotDubla(1 - parte, p);//rot. dubla in partea opusa suprimarii
					(*p)->ech = echilibrat;//acum va fi echilibrat
				}
		}
}
void AdaugNod(nodAVL** p, int x);
void InsNod(int parte, nodAVL** p, int x) {//inserarea intr-o parte si, eventual, reech.
	AdaugNod(&(*p)->f[parte], x);
	if (h)//a crescut subarborele in care am adaugat
		if ((*p)->ech == echMareP[1 - parte]) {//pt a, aveam hP < hPO
			(*p)->ech = echilibrat;//pt a vom avea hP = hPO
			h = 0;//imbunatatirea echilibrului, h nu a crescut
		}
		else//pt a, aveam hP >= hPO
			if ((*p)->ech == echilibrat)//pt a, aveam hP = hPO
				(*p)->ech = echMareP[parte];//si vom avea hP > hPO
			else {//(*p)->ech==echMareP[parte] <=> pt a aveam hP > hPO
				if (ok == 1) {
					nra++;
					cout << "\n!!!ARBORELE A FOST REECHILIBRAT!!!\n";
				}
				if ((*p)->f[parte]->ech == echMareP[parte])
					RotSimpla(parte, p);
				else RotDubla(parte, p);
				(*p)->ech = echilibrat;//dupa reech., pt a, vom avea hP =hPO
				h = 0;//si inaltimea nu este mai mare decat inainte de insertie
			}
}
void AdaugNod(nodAVL** p, int x) {
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
//afisarea subarborelui cu radacina p
void Afis(nodAVL* p, int niv) {
	int i;
	if (p) {
		Afis(p->f[1], niv + 1);
		for (i = 0; i < niv; i++) cout << " ";
		cout << "\n" << p->cheie << " " << p->ech;
		Afis(p->f[0], niv + 1);
	}
}
//stergerea subarborelui cu radacina p
void StergAVL(nodAVL* p) {//traversare in postordine
	if (p) {
		StergAVL(p->f[0]);
		StergAVL(p->f[1]);
		delete p;
	}
}
void Afisare(nodAVL* p, int niv) {
	int i;
	if (p) {
		Afisare(p->f[1], niv + 1);
		for (i = 0; i < niv; i++) cout << "\t";
		cout << p->cheie << endl;
		Afisare(p->f[0], niv + 1);
	}
}
int main() {
	int i, nr;
	char optiune;
	rad = NULL;
	//crearea cu nr. aleatoare
	cout << "Cate elemente sa se insereze initial in arborele AVL: ";
	cin >> nr;
	srand(time(NULL));
	for (i = 0; i < nr; i++) {
		h = 0;
		AdaugNod(&rad, rand() % 100);
	}
	ok = 1;
	cout << "Arborele AVL este:";
	Afis(rad, 0);
	cout << endl;
	Afisare(rad, 0);
	do {
		h = 0;
		cout << "\n\n 1.Adaugare 2.Suprimare 0.Iesire\n\n";
		optiune = _getch();
		if (optiune != '0') {
			if (optiune == '1') {
				cout << "Cheia nodului de adaugat: ";
				cin >> i;
				na++;
				AdaugNod(&rad, i);
				Afis(rad, 0);
				cout << endl;
				Afisare(rad, 0);
			}
			else if (optiune == '2') {
				cout << "Cheia nodului de suprimat: ";
				cin >> i;
				ns++;
				StergNod(&rad, i);
				Afis(rad, 0);
				cout << endl;
				Afisare(rad, 0);
			}
		}
	} while (optiune != '0');
	cout << "In arbore au fost adaugate " << na << " noduri si a fost nevoie de " << nra << " reechilibrari"<<endl;
	cout << "Din arbore au fost sterse " << ns << " noduri si a fost nevoie de " << nrs << " reechilibrari"<<endl;
	StergAVL(rad);
	return 0;
}
