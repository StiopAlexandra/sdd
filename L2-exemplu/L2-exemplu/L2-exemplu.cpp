// L2-exemplu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#define nrMaxN 20
using namespace std;
typedef struct _nod {
	int cheie, parinte;
}nod;
nod A[nrMaxN];
int nrEl; //numarul de elemente
void AdaugFii(int idxPar, int cheie, int niv) {
	int i, j, idx, nrFii;
	//adaugarea nodului
	idx = nrEl; //retinem indicele noului nod
	A[nrEl].cheie = cheie;
	A[nrEl].parinte = idxPar;
	nrEl++;
	nrFii = 0; //inca nu are fii
	do { //adaugarea fiilor
		for (i = 0; i < niv; i++) cout << " ";
			cout << "Fiul " << ++nrFii << " al lui " << cheie << " este ";
			cin >> j;
		if (j) AdaugFii(idx, j, niv + 1);
	} while (j);
}
void CreareAG() {
	int i;
	nrEl = 0;
	cout << "Radacina arborelui: ";
	cin >> i;
	if (i) AdaugFii(-1, i, 1);
}
void Afisare() {
	int i;
	cout << "\nIndice: ";
	for (i = 0; i < nrEl; i++)
		cout << setw(4) << i;//se foloseste in locul printf("%3d", i)
	cout << "\nCheie:  ";
		for (i = 0; i < nrEl; i++) cout << setw(4) << A[i].cheie;
	cout << "\nParinte:";
	for (i = 0; i < nrEl; i++)
		cout << setw(4) << A[i].parinte;
}
//parcurgere in preordine
void AfisareAG(int idx, int niv) {
	int i;
	//prelucrarea nodului
	cout << "\n";
	for (i = 0; i < niv; i++) cout << " ";
		cout << A[idx].cheie;
	//parcurgerea fiilor
	for (i = idx + 1; i < nrEl; i++) //fiii au indici mai mari
		if (A[i].parinte == idx) AfisareAG(i, niv + 1);
}
int main() {
	CreareAG();
	cout << "Afisarea ca tablou:\n";
	Afisare();
	_getch();
	cout << "\n\nAfisarea ca arbore:";
	AfisareAG(0, 0);
	_getch();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
