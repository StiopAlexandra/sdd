/*Un graf este complet dacă fiecare nod este conectat în mod direct cu toate
celelalte noduri. Dîndu-se un graf neorientat şi ponderat şi complet cu N>5 noduri, generat
aleator, să se determine:
- arborele de acoperire minim pentru graful dat, utilizînd algoritmul lui Prim
- care sunt arcele prin suprimarea cărora arborele de acoperire minim rezultat pentru noul
graf se modifică faţă de cel determinat iniţial?
- să se realizeze o statistică despre cum variază costul total al arborilor de acoperire minimi
în funcţie de costul arcului care se suprimă */

#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define nrMaxN 20
#define mare 2000 
#define inf 20000
using namespace std;
typedef struct _nodG {
	int cheie;
}nodG;
nodG nod[nrMaxN];
int arc[nrMaxN][nrMaxN], nrN, nrA, costMin[nrMaxN], apropiat[nrMaxN],copieArc[nrMaxN][nrMaxN],modCost;
int i, j, k, mini, idxMin, costTotal,costInitial;
void AfisImplGraf() {
	cout << "\n--Graful conectarilor intre noduri--";
	cout << "\n\nNoduri: ";
	for (i = 0; i < nrN; i++) cout << " " << nod[i].cheie;
	cout << "\n\nConectarile: \n";
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++) {
			if (arc[i][j] == mare) 
				cout << " 0 ";
			else 
				cout << " " << arc[i][j] << " ";
		}
		cout  << "\n";
	}
}
void Prim1() {
	costTotal = 0;
	/*initializam multimea nodurilor incluse in arbore cu primul nod
	si actualizam costmin si apropiat*/
	for (i = 0; i < nrN; i++) {
		apropiat[i] = 0;//cel mai apropiat nod dintre cele incluse este 0
		costMin[i] = arc[0][i];//costul minim este fata de acesta
	}
	for (j = 0; j < nrN - 1; j++) {//mai sunt nrN-1 noduri de adaugat
	//determinam arcul de cost minim dintre un nod neales inca si unul ales
			idxMin = 1; mini = costMin[1];
		for (k = 2; k < nrN; k++)
			if (costMin[k] < mini) {
				mini = costMin[k];
				idxMin = k;
			}
		if (mini != mare) {
			cout << " (" << nod[apropiat[idxMin]].cheie << " -> " << nod[idxMin].cheie << ") cu costul "<< mini<<"\n";
				costTotal += mini;
		}
		costMin[idxMin] = inf;//marcam nodul ca inclus
		for (k = 1; k < nrN; k++) {//actualizam apropiat si costMin
			if (arc[idxMin][k] < costMin[k] && costMin[k] < inf) {
				apropiat[k] = idxMin;
				costMin[k] = arc[idxMin][k];
			}
		}
	}
}
void Prim2() {
	costTotal = 0;
	costMin[nrMaxN] = { 0 };
	apropiat[nrMaxN] = { 0 };
	/*initializam multimea nodurilor incluse in arbore cu primul nod
	si actualizam costmin si apropiat*/
	for (i = 0; i < nrN; i++) {
		apropiat[i] = 0;//cel mai apropiat nod dintre cele incluse este 0
		costMin[i] = copieArc[0][i];//costul minim este fata de acesta
	}
	for (j = 0; j < nrN - 1; j++) {//mai sunt nrN-1 noduri de adaugat
	//determinam arcul de cost minim dintre un nod neales inca si unul ales
		idxMin = 1; mini = costMin[1];
		for (k = 2; k < nrN; k++)
			if (costMin[k] < mini) {
				mini = costMin[k];
				idxMin = k;
			}
		if (mini != mare) {
			costTotal += mini;
		}
		costMin[idxMin] = inf;//marcam nodul ca inclus
		for (k = 1; k < nrN; k++) {//actualizam apropiat si costMin
			if (copieArc[idxMin][k] < costMin[k] && costMin[k] < inf) {
				apropiat[k] = idxMin;
				costMin[k] = copieArc[idxMin][k];
			}
		}
	}
}
void CopieGraf() {
	int i, j;
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++) {
			copieArc[i][j] = arc[i][j];
		}
	}
}
void determArce() {
	int i, j;
	for (i = 0; i < nrN; i++) {
		for (j = i + 1; j < nrN; j++) {
			CopieGraf();
			copieArc[i][j] = copieArc[j][i] = mare;
			Prim2();
			if (costInitial != costTotal)
			{				
				if(modCost<arc[i][j])
					modCost = arc[i][j];
				cout << "\n\nIn urma stergerii muchiei " << i + 1 << "->" << j + 1 <<" cu costul "<<arc[i][j]<<" costul noului graf s-a modificat";
				cout <<"\nCostul noului graf este "<< costTotal;
			}
		}
	}
}
int main() {
	cout << "Introduceti nr de noduri: ";
	cin >> nrN;
	nrA = nrN * (nrN - 1) / 2;
	for (i = 0; i < nrN; i++) {
		nod[i].cheie = i + 1;
		for (j = i+1; j < nrN; j++) {
			arc[i][j] = arc[j][i] = rand() % 9 + 1;
		}
	}
	AfisImplGraf();
	cout << "\nConectarile alese sunt:\n";
	Prim1();
	costInitial = costTotal;
	cout << "\nCostul conectarii in acest mod este " << costTotal<<endl;
	determArce(); 
	cout << "\n\nLa stergerea muchiilor cu cost mai mic sau egal cu " << modCost << " costul noului graf se modifica\n";
	return 0;
}
