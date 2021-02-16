/*Să se construiască un arbore binar ordonat şi unul AVL, pornind de la aceeaşi
secvenţă de chei (generate aleator sau citite dintr-un fişier). Să se compare înălţimile celor doi
arbori şi să se afişeze diferenţa raportată la numărul de chei, precum şi raportul celor două
înălţimi. 
*/
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
int havl,hao;
int h;/*va indica:
 - la insertie: daca inaltimea subarborelui in care s-a inserat a crescut
 - la suprimare: daca inaltimea subarborelui din care s-a suprimat a scazut */
int echMareP[2] = { -1, 1 }, echilibrat = 0;//echilibrele posibile pt. un nod AVL
typedef struct _nodABO {
	int cheie;
	_nodABO* st, * dr;
}nodABO;
nodABO* radAO;
FILE* f;
int cheie, n;
void AdaugNodAO(nodABO** p) {
	if (*p) {
		if (cheie < (*p)->cheie)
			AdaugNodAO(&(*p)->st);
		else AdaugNodAO(&(*p)->dr);
	}
	else {
		*p = new nodABO;
		(*p)->cheie = cheie;
		(*p)->st = (*p)->dr = NULL;
	}
}
void AfisareAO(nodABO* p, int niv) {
	int i;
	if (p) {
		AfisareAO(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "\t";
		cout << p->cheie << endl;
		AfisareAO(p->st, niv + 1);
	}
}
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
				if ((*p)->f[parte]->ech == echMareP[parte])
					RotSimpla(parte, p);
				else RotDubla(parte, p);
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
void AfisareAVL(nodAVL* p, int niv) {
	int i;
	if (p) {
		AfisareAVL(p->f[1], niv + 1);
		for (i = 0; i < niv; i++) cout << "\t";
		cout << p->cheie << endl;
		AfisareAVL(p->f[0], niv + 1);
	}
}
void NivelAO(nodABO* p, int niv) {
	if (p) {
		if (niv > hao)
			hao = niv;
		NivelAO(p->st, niv + 1);
		NivelAO(p->dr, niv + 1);
	}
}
void NivelAVL(nodAVL* p, int niv) {
	if (p) {
		if (niv > havl)
			havl = niv;
		NivelAVL(p->f[1], niv + 1);
		NivelAVL(p->f[0], niv + 1);
	}
}
int main() {
	int i, nr;
	radAO = NULL;
	radAVL = NULL;
	if ((f = fopen("arbori.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		h = 0;
		fscanf(f, "%d", &cheie);
		AdaugNodAO(&radAO);
		AdaugNodAVL(&radAVL,cheie);
	}
	fclose(f);
	cout << "Arborele binar ordonat este: \n";
	AfisareAO(radAO, 0);
	cout << "\nArborele AVL este:\n";
	AfisareAVL(radAVL, 0);
	NivelAO(radAO, 0);
	NivelAVL(radAVL, 0);
	hao++;
	havl++;
	cout << "\nInaltimea arborelui binar ordonat este: " << hao;
	cout << "\nInaltimea arborelui AVL este: " << havl;
	if (hao > havl)
		cout << "\nArborele binar ordonat este mai inalt decat arborele AVL.";
	else
		if (hao < havl)
			cout << "\nArborele AVL este mai inalt decat arborele binar ordonat.";
		else
			cout << "\nArborele binar ordonat are aceeasi inaltime cu arborele AVL => arborele binar ordonat este echilibrat.";
	cout << "\nFiecare arbore contine " << nr <<" noduri.";
	cout << "\nArborele binar ordonat are "<<nr<<" noduri pe "<<hao<< " nivele.";
	cout << "\nArborele AVL are " << nr << " noduri pe " << havl << " nivele.";
	return 0;
}
