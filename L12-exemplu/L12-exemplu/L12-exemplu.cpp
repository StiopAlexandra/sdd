#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#define nrMaxN 20
#define mare 2000
#pragma warning (disable : 4996)
using namespace std;
typedef struct _nodG {
	int cheie;
}nodG;
nodG nod[nrMaxN];
int arc[nrMaxN][nrMaxN], nrN, nrA, drum[nrMaxN][nrMaxN];
int m[3], i, j, k;
FILE* f;
int CautaNod(int k) {//da pozitia la care se afla sau -1 dc nu se afla
	int i;
	for (i = 0; i < nrN; i++)
		if (k == nod[i].cheie) return i;
	return -1;
}
void AfisImplGraf(void) {
	cout << "Graful curselor intre orase este:";
	cout << "\nOrasele: ";
	for (i = 0; i < nrN; i++) cout << setw(4) << nod[i].cheie;
	cout << "\nCursele: \n";
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++) {
			if (arc[i][j] == mare) cout << setw(3) << "X";
			else cout << setw(3) << arc[i][j];
		}
		cout << "- " << nod[i].cheie << "\n";
	}
}
void Floyd() {
	for (i = 0; i < nrN; i++)//initializarea matricii de drum
		for (j = 0; j < nrN; j++)
			drum[i][j] = -1;//memoram pozitia din matrice, nu cheia
	for (k = 0; k < nrN; k++) {//incercam actualizarea drumurilor prin nodul k
		for (i = 0; i < nrN; i++)//de la fiecare nod
			for (j = 0; j < nrN; j++)//la toate celelalte
				if (arc[i][j] > arc[i][k] + arc[k][j]) {//este mai ieftin prin k
						arc[i][j] = arc[i][k] + arc[k][j];//actualizam cost
					drum[i][j] = k;//actualizam drum
				}
	}
}
void AfisDrum(int i, int j) {
	if (drum[i][j] != -1) {
		AfisDrum(i, drum[i][j]);
		cout << " " << nod[drum[i][j]].cheie;
		AfisDrum(drum[i][j], j);
	}
}
int main() {
	int p[2];

	if ((f = fopen("graf.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); exit(1);
	}
	fscanf(f, "%d", &nrA);
	nrN = 0;//nr. de noduri
	for (i = 0; i < nrA; i++) {
		fscanf(f, "%d%d%d", &m[0], &m[1], &m[2]);
		for (j = 0; j < 2; j++) {
			p[j] = CautaNod(m[j]);
			if (p[j] == -1) {//nu s-a gasit => il adaug
				p[j] = nrN;
				nod[nrN].cheie = m[j];
				for (k = 0; k < nrN; k++)//init. cu 'mare' a tuturor conexiunilor lui
					arc[nrN][k] = arc[k][nrN] = mare;
				arc[nrN][nrN] = 0;//diagonala e minima
				nrN++;
			}
		}
		arc[p[0]][p[1]] = m[2];//adaug muchia
	}
	fclose(f);
	AfisImplGraf();
	Floyd();
	cout << "\nCalatoriile cele mai ieftine:";
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++)
			if (i != j && arc[i][j] != mare) {
				cout << "\n de la " << nod[i].cheie << " la " <<
					nod[j].cheie << ": cost " << arc[i][j] << ", escale: ";
				AfisDrum(i, j);
			}
	}
	_getch();
	return 0;
}