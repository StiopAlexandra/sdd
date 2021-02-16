/*Să se determine pentru un graf dat, dacă există drum între două noduri
specificate. Pentru aceasta veti utiliza implementarea cu matrici de adiacență. */

#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#define nrMax 20 
#pragma warning (disable : 4996)
using namespace std;
typedef struct _nodG {//definirea tipului unui nod
	int cheie;
}nodG;
int nrarc, nrnod, i, j, k, k1, k2, val, n1, n2;
nodG nod[nrMax];//tabloul de noduri
int arc[nrMax][nrMax];//matricea de adiacenta, nrN este numarul maxim de noduri
FILE* f;
void main() {
	if ((f = fopen("graf.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); return;
	}
	fscanf(f, "%d", &nrnod);
	fscanf(f, "%d", &nrarc);
	for (i = 0; i < nrnod; i++)
	{
		fscanf(f,"%d", &val);
		nod[i].cheie = val;
	}
	for (j = 1; j <= nrarc; j++)
	{
		fscanf(f, "%d%d", &k1, &k2);
		arc[k1][k2] = 1;
		arc[k2][k1] = 1;
	}
	fclose(f);
	cout << "Nodurile grafului sunt: ";
	for (i = 0; i < nrnod; i++)
		cout << nod[i].cheie << " ";
	cout << "\nMatricea de adiacenta este: \n";
	for (i = 1; i <= nrnod; i++) {
		for(j=1;j<=nrnod;j++)
			cout<<arc[i][j] << " ";
		cout << endl;
	}
	cout << "Introduceti un nod: ";
	cin >> n1;
	cout << "Introduceti alt nod: ";
	cin >> n2;
	for (k = 1; k <= nrnod; k++)
		for (i = 1; i <= nrnod; i++)
			for (j = 1; j <= nrnod; j++)
				if (i != j && arc[i][j] == 0 && arc[i][k] == 1 && arc[k][j] == 1)
					arc[i][j] = 1;
	if (arc[n1][n2] == 1)
		cout << "Exista drum intre nodul " << n1 << " si nodul " << n2;
	else
		cout << "Nu exista drum intre nodul " << n1 << " si nodul " << n2;
}
