/*Să se realizeze ştergerea unui nod dintr-un arbore binar, astfel:
 - dacă a fost fiu stâng sau rădăcina arborelui, în locul lui trece fiul său stâng, iar fiul său drept
devine fiu drept al celui mai din dreapta nod al fiului stâng al nodului de şters.
 - dacă a fost fiu drept, în locul lui trece fiul său drept, iar fiul său stâng devine fiu stâng al
celui mai din stânga nod al fiului drept al nodului de şters. */
#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
using namespace std;
typedef struct _nodAB {
	char* nume;
	_nodAB* stanga;
	_nodAB* dreapta;
}nodAB;
nodAB* rad;
char nume[100], inf[100];
int i,ok=0;
void AdaugNod(nodAB** p, int niv) {
	gets_s(nume);
	if (nume[0] != '\0') {
		*p = new nodAB;
		(*p)->nume = new char[strlen(nume) + 1];
		strcpy((*p)->nume, nume);
		for (i = 0; i <= niv; i++) cout << " ";
		cout << "Fiul stang al lui " << (*p)->nume << " este: ";
		AdaugNod(&(*p)->stanga, niv + 1);
		for (i = 0; i <= niv; i++) cout << " ";
		cout << "Fiul drept al lui " << (*p)->nume << " este: ";
		AdaugNod(&(*p)->dreapta, niv + 1);
	}
	else *p = NULL;
}
void AfisAB(nodAB* p, int niv) {
	if (p) {
		AfisAB(p->stanga, niv + 1);
		for (i = 0; i < niv; i++) cout << "  ";
		cout <<p->nume<<endl;
		AfisAB(p->dreapta, niv + 1);
	}
}
void CopStergPred(nodAB** p, nodAB* q) {
	while ((*p)->dreapta) p = &(*p)->dreapta; //deplasari in dreapta
	q->nume = (*p)->nume;
	//copierea din predecesor a celorlalte date 
	q = *p; //retinem adresa predecesorului
	*p = (*p)->stanga; //scoaterea predecesorului
	delete q; //stergerea lui
}
void StergNod(struct _nodAB** p) {
	nodAB* q;
	if ((*p))
	{
			if (strcmp(inf, (*p)->nume) == 0) {//l-am gasit
				ok = 1;
				q = (*p);
				if ((*p)->stanga == NULL) {//are cel mult fiu drept
					*p = (*p)->dreapta;
					delete q;
				}
				else
					if ((*p)->dreapta == NULL) {//are cel mult fiu stang
						*p = (*p)->stanga;
						delete q;
					}
					else //are 2 fii
						CopStergPred(&(*p)->stanga, q);
			}
			else
			{
				StergNod(&(*p)->stanga);
				if (ok==0)
					StergNod(&(*p)->dreapta);
			}	
	}
}
int main() {
	rad = NULL;
	cout << "Radacina arborelui: ";
	AdaugNod(&rad, 0);
	cout << "\nArborele este:\n";
	AfisAB(rad, 0);
	cout << "\nDati nodul pe care doriti sa-l stergeti: ";
	fflush(stdin);
	gets_s(inf);
	StergNod(&rad);
	if (ok == 0)
		cout << "Nodul nu se gaseste in arbore";
	else
	{
		cout << "Nodul a fost gasit";
		cout << "Arborele este:\n";
		AfisAB(rad, 0);
	}	
}
