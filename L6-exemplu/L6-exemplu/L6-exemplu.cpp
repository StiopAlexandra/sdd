#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#pragma warning (disable : 4996)
using namespace std;
typedef struct _nodABO {
	char* nume;
	float media;
	_nodABO* st, * dr;
}nodABO;
nodABO * rad, * radN, ** pp;
FILE* f;
char s[100];
float medie;
//adaugarea in arbore alfabetic
void AdaugNod(nodABO** p) {
	if (*p) {//nu am ajuns la locul noului nod
		if (strcmp(s, (*p)->nume) < 0)
			AdaugNod(&(*p)->st);
		else AdaugNod(&(*p)->dr);
	}
	else {//am ajuns => adaugarea lui
		*p = new nodABO;
		//initializarea campurilor de date
		(*p)->nume = new char[strlen(s) + 1];
		strcpy((*p)->nume, s);
		(*p)->media = medie;
		//initializarea campurilor de legatura
		(*p)->st = (*p)->dr = NULL;
	}
}
//afisare arbore ca lista
void AfisCaLista(nodABO* p) {
	if (p) { //parcurgere in inordine
		AfisCaLista(p->st);
		cout << "\n" << p->nume << " " << p->media;
		AfisCaLista(p->dr);
	}
}
//cauta nod cu cheia s in arbore alfabetic
nodABO** Cauta(nodABO** p) {
	if (*p) {
		if (strcmp(s, (*p)->nume) < 0)
			return Cauta(&(*p)->st);
		if (strcmp(s, (*p)->nume) > 0)
			return Cauta(&(*p)->dr);
	}
	return p;
}
//insertie nod in arbore descrescator dupa medii
void InsertieNod(nodABO** p, nodABO* q) {
	if (*p) {//nu am ajuns la locul noului nod
		if (q->media <= (*p)->media)
			InsertieNod(&(*p)->dr, q);
		else InsertieNod(&(*p)->st, q);
	}
	else {//am ajuns
		*p = q;
		q->st = q->dr = NULL;
	}
}
//intoarce adresa predecesorului, dupa ce-l scoate din arbore
nodABO* Predecesor(nodABO** p) {
	nodABO* q;
	//deplasari in dreapta cat se poate
	while ((*p)->dr) p = &(*p)->dr;
	q = *p;//retinem adresa predecesorului
	*p = (*p)->st;//il scoatem din arbore
	return q;
}
//muta nodul primit ca parametru din arborele initial in celalalt
void Imparte(nodABO** p) {
	nodABO* q, * t;
	q = (*p);//retinem adresa nodului de mutat
	//scoatem din arbore nodul de mutat
	if ((*p)->st == NULL)//are cel mult fiu drept
		*p = (*p)->dr;
	else
		if ((*p)->dr == NULL)//are cel mult fiu stang
			*p = (*p)->st;
		else {//are 2 fii => mutam predecesorul sau in locul sau
			t = Predecesor(&(*p)->st);
			t->st = (*p)->st;
			t->dr = (*p)->dr;
			*p = t;
		}
	//inseram in noul arbore nodul de mutat
	InsertieNod(&radN, q);
}
void StergABO(nodABO* p) {
	if (p) {//traversare in postordine
		StergABO(p->st);
		StergABO(p->dr);
		delete p->nume;
		delete p;
	}
}
int main()
{
	int nr, i;
	rad = radN = NULL;
	//crearea arborelui din fisier
	if ((f = fopen("medii.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return 1;
	}
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%s", s);
		fscanf(f, "%f", &medie);
		AdaugNod(&rad);//adaugarea nodului in arborele initial
	}
	fclose(f);
	do {
		cout << "Cei fara cerere (alfabetic): " << endl;
		AfisCaLista(rad);
		cout << "\n Lista doritorilor (descrescator, dupa medii): " << endl;
		AfisCaLista(radN);
		cout << "\nCine mai doreste bilet: ";
		fflush(stdin); gets_s(s);
		if (s[0] != '\0') {
			pp = Cauta(&rad); //cautam nodul in arborele initial
			if (*pp) Imparte(pp);//gasit => il mutam
			else {//negasit
				cout << "Studentul " << s << " nu a fost gasit printre cei fara cerere.";
				_getch();
			}
		}
	} while (s[0] != '\0');
	StergABO(rad); //stergere arbore initial
	StergABO(radN); //stergere arbore cu doritori
	return 0;
}