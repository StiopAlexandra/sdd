/*   Se consideră doi arbori binari ordonaţi, daţi iniţial, cu chei de tip şir de caractere.
Să se scrie programul prin care se verifică dacă cel de-al doilea arbore este un sub-arbore al
primului arbore. 
*/

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
nodABO* rad1;
nodABO* rad2;
FILE* f;
char s[100],pre1[100],pre2[100];
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
void CreareABO1(void) {
	int nr, i;
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%s", s);
		AdaugNod(&rad1);
	}
}
void CreareABO2(void) {
	int nr, i;
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%s", s);
		AdaugNod(&rad2);
	}
}
void AfisAB(nodABO* p, int niv) {
	int i;
	if (p) {
		AfisAB(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "\t";
		cout << p->nume << endl;
		AfisAB(p->st, niv + 1);
	}
}
void Preordine1(nodABO* p) {
	if (p) {
		strcat(pre1, p->nume);
		Preordine1(p->st);
		Preordine1(p->dr);
	}
}
void Preordine2(nodABO* p) {
	if (p) {
		strcat(pre2, p->nume);
		Preordine2(p->st);
		Preordine2(p->dr);
	}
}
int main() {
	rad1 = rad2 = NULL;
	if ((f = fopen("abo1.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	CreareABO1();
	fclose(f);
	cout << "Primul arbore este: " << endl;
	AfisAB(rad1, 0);
	cout << endl;
	if ((f = fopen("abo2.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	CreareABO2();
	fclose(f);
	cout << "Al doilea arbore este: " << endl;
	AfisAB(rad2, 0);
	Preordine1(rad1);
	Preordine2(rad2);
	cout << endl;
	if (strstr(pre1, pre2))
		cout << "Al doilea arbore este subarborele primului arbore"<<endl;
	else
		cout << "Al doilea arbore nu este subarborele primului arbore"<<endl;
	return 0;
}
