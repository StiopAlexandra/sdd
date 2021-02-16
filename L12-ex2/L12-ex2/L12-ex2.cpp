/* Să se scrie un program care determină dacă un graf dat este arbore. În caz
afirmativ, desemnaţi drept rădăcină un nod pentru care arborele astfel obţinut să aibă înălţime
minimă.  */

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
int arc[nrMaxN][nrMaxN], nrN, nrA, D[nrMaxN][nrMaxN], aux[nrMaxN][nrMaxN], m[2],p[2],ok, i, j, k, mini,sum[100];
FILE* f;
int CautaNod(int k) {
	int i;
	for (i = 0; i < nrN; i++)
		if (k == nod[i].cheie) return i;
	return -1;
}
void AfisImplGraf(void) {
	cout << "Graful dat este:";
	cout << "\n\nNodurile: \n";
	for (i = 0; i < nrN; i++) cout << setw(3) << nod[i].cheie;
	cout << "\n\nMatricea de adiacenta: \n";
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++) {
			cout << setw(3) << arc[i][j];
		}
		cout << " - " << nod[i].cheie << "\n";
	}
}
void Conex()
{
	for (k = 0; k < nrN; k++)
		for (i = 0; i < nrN; i++)
			for (j = 0; j < nrN; j++)
				if (i != j)
					if (aux[i][j] == 0)
						aux[i][j] = aux[i][k] * aux[k][j];
}
void Drumuri(int s)
{
	int C[nrMaxN] = { 0 };
	int d[nrMaxN] = { 0 };
	int st, dr,i;
	C[0] = s;
	d[s] = 1;
	st = dr = 0;
	while (st <= dr)
	{
		for (i = 0; i < nrN; i++)
			if (arc[C[st]][i] && d[i] == 0)
			{
				dr++;
				C[dr] = i;
				d[i] = d[C[st]] + 1;
			}
		st++;
	}
	for (i = 0; i < nrN; i++) D[s][C[i]] = d[C[i]] - 1;
}

int main() {
	if ((f = fopen("graf.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); exit(1);
	}
	fscanf(f, "%d", &nrA);
	nrN = 0;
	for (i = 0; i < nrA; i++) {
		fscanf(f, "%d%d", &m[0], &m[1]);
		for (j = 0; j < 2; j++) {
			p[j] = CautaNod(m[j]);
			if (p[j] == -1) {
				p[j] = nrN;
				nod[nrN].cheie = m[j];
				nrN++;
			}
		}
		if (p[0] != p[1]) {
			arc[p[0]][p[1]] = arc[p[1]][p[0]] = 1;
			aux[p[0]][p[1]] = aux[p[1]][p[0]] = 1;
		}	
	}
	fclose(f);
	AfisImplGraf();
	Conex();
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++) {
			if (i != j && aux[i][j] == 0)// aux[i][j] va fi 0 daca nu exista drum de la i la j
				ok = 1;
		}
	}
	mini = mare;
	if (ok == 0 && nrN - 1 == nrA)//verificam daca graful nu are cicluri si este conex 
	{
		cout << "\nGraful dat este arbore\n";
		for (i = 0; i < nrN; i++) 
			Drumuri(i);//calculam nr de muchii dintre 2 noduri
		for (i = 0; i < nrN; i++)
			for (j = 0; j < nrN; j++)
				sum[i] = sum[i] + D[i][j];
		for (i = 0; i < nrN; i++)
			if (sum[i] < mini)
			{
				mini = sum[i];
				k = nod[i].cheie;//alegem ca radacina nodul pentru care suma nr de muchii (dintre el si restul nodurilor) este minima
			}
		cout << "Daca radacina arborelui este "<<k<<" atunci inaltimea acestuia va fi minima\n";
	}
	else
		cout << "\nGraful dat nu este arbore\n";
	return 0;
}

