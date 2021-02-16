/* Să se creeze un arbore binar odonat şi să se implementeze ca şi funcţii
următoarele operaţii:
a) stabilirea faptului că două chei date sunt în relaţie strămoş-descendent sau nu.
b) afişarea nodurilor de pe un nivel dat.
c) afişarea subarborelui a cărui rădăcină este un nod dat.
d) crearea unui alt arbore binar ordonat care să conţină numai nodurile cu chei mai
mari decât o valoare dată. 
*/

#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
using namespace std;
typedef struct _nodABO {
	int cheie;
	_nodABO* st, * dr;
}nodABO;
nodABO* rad;
nodABO* r;
FILE* f;
int cheie,nod1,nod2,nivel,val,n;
void AdaugNod(nodABO** p) {
	if (*p) {
		if (cheie<(*p)->cheie)
			AdaugNod(&(*p)->st);
		else AdaugNod(&(*p)->dr);
	}
	else {
		*p = new nodABO;
		(*p)->cheie = cheie;
		(*p)->st = (*p)->dr = NULL;
	}
}
void CreareABO1(void) {
	int nr, i;
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%d", &cheie);
		AdaugNod(&rad);
	}
}
void CreareABO2(void) {
	int nr, i;
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%d", &cheie);
		if(cheie>val)
			AdaugNod(&r);
	}
}
void CautaABO(nodABO* p, int niv, int& gasit, int nod) {
	if (p) {
		if (nod == p->cheie)
			gasit = niv;
		else
			if (nod<p->cheie) 
				CautaABO(p->st, niv + 1, gasit, nod);
			else
				CautaABO(p->dr, niv + 1, gasit, nod);
	}
}
void Afisare(nodABO* p, int niv) {
	if (p) {
		Afisare(p->st, niv + 1);
		if(niv==nivel)
			cout << p->cheie<<" ";
		Afisare(p->dr, niv + 1);
	}
}
void AfisAB(nodABO* p, int niv) {
	int i;
	if (p) {
		AfisAB(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "\t";
		cout << p->cheie << endl;
		AfisAB(p->st, niv + 1);
	}
}
void Cauta(nodABO* p, int niv) {
	if (p) {
		if (n == p->cheie)
			AfisAB(p, niv);
		else
			if (n < p->cheie)
				Cauta(p->st, niv + 1);
			else
				Cauta(p->dr, niv + 1);
	}
}
int main() {
	int niv1=0, niv2=0;
	rad=r=NULL;
	if ((f = fopen("abo.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	CreareABO1();
	fclose(f);
	cout << "Arborele binar ordonat este: " << endl;
	AfisAB(rad, 0);
	cout << "\n\na)" << endl;
	cout << "Dati cheia unui nod: ";
	cin >> nod1;
	cout << "Dati cheia altui nod: ";
	cin >> nod2;
	CautaABO(rad, 0, niv1, nod1);
	CautaABO(rad, 0, niv2, nod2);
	if(niv1==0)
		cout << "Nodul cu cheia " << nod1 << " nu se gaseste in arbore "<< endl;
	if (niv2 == 0)
		cout << "Nodul cu cheia " << nod2 << " nu se gaseste in arbore " << endl;
	if (niv1 != 0 && niv2 != 0) {
		if (niv1 - niv2 != 0 )
			cout << "Nodul cu cheia " << nod1 << " este in relatie stramos-descendent cu nodul cu cheia " << nod2<<endl;
		else
			cout << "Nodul cu cheia " << nod1 << " nu este in relatie stramos-descendent cu nodul cu cheia " << nod2<<endl;
	}
	cout << "\n\nb)" << endl;
	cout << "Introduceti un nivel: ";
	cin >> nivel;
	cout << "Cheile de pe nivelul " << nivel << " sunt:  ";
	Afisare(rad, 0);
	cout << "\n\nc)" << endl;
	cout << "Introduceti cheia unui nod: ";
	cin >> n;
	cout << "Subarborele care are radacina " << n << " este:" << endl;
	Cauta(rad, 0);
	cout << "\n\nd)" << endl;
	cout << "Introduceti o valoare: ";
	cin >> val;
	if ((f = fopen("abo.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	CreareABO2();
	fclose(f);
	cout << "Arborele binar ordonat cu chei mai mari decat " <<val<<" este: "<<endl;
	AfisAB(r, 0);
	return 0;
}
