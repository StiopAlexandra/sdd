#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#define nrEx 3
using namespace std;
typedef struct _nodABO {
	char* nume;
	int note[nrEx];
	float media;
	_nodABO* st, * dr;
}nodABO;
nodABO* radN, * radM;
FILE* f;
char s[100];
float vMin, vMax;
int note[nrEx];
//adaugarea in arbore alfabetic
void AdaugNodNume(nodABO** p) {
	int i;
	if (*p) {//nu am ajuns la locul noului nod
		if (strcmp(s, (*p)->nume) < 0)
			AdaugNodNume(&(*p)->st);
		else AdaugNodNume(&(*p)->dr);
	}
	else {//am ajuns => adaugarea lui
		*p = new nodABO;
		//initializarea campurilor de date
		(*p)->nume = new char[strlen(s) + 1];
		strcpy((*p)->nume, s);
		for (i = 0; i < nrEx; i++) (*p)->note[i] = note[i];
		//initializarea campurilor de legatura
		(*p)->st = (*p)->dr = NULL;
	}
}
//adaugare in arbore dupa medii
void AdaugNodMedii(nodABO** p, nodABO* q) {
	if (*p) {//nu am ajuns la locul noului nod
		if (q->media < (*p)->media)
			AdaugNodMedii(&(*p)->st, q);
		else AdaugNodMedii(&(*p)->dr, q);
	}
	else {//am ajuns
		*p = new nodABO;
		(*p)->nume = new char[strlen(q->nume) + 1];
		**p = *q;
		(*p)->st = (*p)->dr = NULL;
	}
}
//crearea arborelui binar ordonat dupa nume din fisier
void CreareABONumeFis(void) {
	int nr, i, j;
	fscanf(f, "%d", &nr);
	for (i = 0; i < nr; i++) {
		fscanf(f, "%s", s);
		for (j = 0; j < nrEx; j++) fscanf(f, "%d", &note[j]);
		AdaugNodNume(&radN);//adaugarea nodului in arborele initial
	}
}
//calcularea mediei si construirea arborelui ordonat dupa medii
void ParcurgereABONume(nodABO* p) {//inordine, pentru adaugarea alfabetica
	int i;
	if (p) {
		ParcurgereABONume(p->st);
		//prelucrarea nodului
		p->media = 0;//calculul mediei
		for (i = 0; i < nrEx; i++) p->media += p->note[i];
		p->media /= nrEx;
		AdaugNodMedii(&radM, p);//si adaugarea unui nou nod in noul arbore
		ParcurgereABONume(p->dr);
	}
}
//cauta si afiseaza alfabetic pe cei cu mediile intre cele doua valori
void CautaAB(nodABO* p) {//parcurgere in inordine
	if (p) {
		CautaAB(p->st);
		if (p->media >= vMin && p->media <= vMax)
			cout << "\n" << p->nume << " " << p->media;
		CautaAB(p->dr);
	}
}
//cauta si afiseaza in ordinea mediilor pe cei cu mediile intre cele doua valori
void CautaABO(nodABO* p) {//parcurgere in inordine
	if (p) {
		if (p->media >= vMin) CautaABO(p->st);
		if (p->media >= vMin && p->media <= vMax)
			cout << "\n" << p->nume << " " << p->media;
		if (p->media <= vMax) CautaABO(p->dr);
	}
}
//afisarea unui arbore
void Afisare(nodABO* p, int niv) {//parcurgere in inordine inversa (D, R, S)
	int i;
	if (p) {
		Afisare(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << " ";
		cout << "\n" << p->nume << " " << p->media;
		Afisare(p->st, niv + 1);
	}
}
//stergerea subarborelui cu radacina indicata de p
void StergABO(nodABO* p) {
	if (p) {//traversare in postordine
		StergABO(p->st);
		StergABO(p->dr);
		delete p->nume;
		delete p;
	}
}
int main() {
	radN = radM = NULL;
	if ((f = fopen("Medii.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		 return 1;
	}
	CreareABONumeFis();
	fclose(f);
	ParcurgereABONume(radN);
	cout << "ARBORELE ORDONAT ALFABETIC:\n";
	Afisare(radN, 0);
	cout << "\n\nARBORELE ORDONAT DUPA MEDII:\n";
	Afisare(radM, 0);
	cout << "\n\nValoarea minima: "; cin >> vMin;
	cout << "Valoarea maxima: "; cin >> vMax;
	cout << "\nLista din arborele alfabetic: "; CautaAB(radN);
	cout << "\n\nLista din arborele pe medii: "; CautaABO(radM);
	StergABO(radN); //stergerea arborelui ordonat dupa nume
	StergABO(radM); //stergerea arborelui ordonat dupa medii
	return 0;
}