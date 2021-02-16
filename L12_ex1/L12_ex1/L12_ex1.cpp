/*.Se dă o hartă care conţine localizarea mai multor magazine din cadrul unui centru
comercial, împreună cu strazile care leagă reţeaua de magazine. Pentru fiecare stradă se
specifică lungimea acesteia, precum şi dacă este sau nu cu sens unic.
- dîndu-se două magazine, să se determine şi să se afişeze drumul cel mai scurt între ele.
Analizaţi rezultatul obţinut cu cel care se obţine pentru cazul în care s-ar permite circulaţia
în ambele sensuri pentru toate drumurile
- să se determine şi să se afişeze care este magazinul cel mai apropiat de toate celelalte
(suma distanţelor este minimă)
*/
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
int arc[nrMaxN][nrMaxN], arc2[nrMaxN][nrMaxN], nrN, nrA, drum[nrMaxN][nrMaxN], drum2[nrMaxN][nrMaxN],sum[nrMaxN];
int m[4], i, j, k,m1,m2,mini;
FILE* f;
int CautaNod(int k) {//da pozitia la care se afla sau -1 dc nu se afla
	int i;
	for (i = 0; i < nrN; i++)
		if (k == nod[i].cheie) return i;
	return -1;
}
void AfisImplGraf(void) {
	cout << "Graful strazilor intre magazine este:";
	cout << "\n\nMagazinele: \n";
	for (i = 0; i < nrN; i++) cout << setw(3) << nod[i].cheie;
	cout << "\n\nLungimea strazilor: \n";
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++) {
			if (arc[i][j] == mare) cout << setw(3) << "X";
			else cout << setw(3) << arc[i][j];
		}
		cout << " - " << nod[i].cheie << "\n";
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
void Floyd2() {
	for (i = 0; i < nrN; i++)//initializarea matricii de drum
		for (j = 0; j < nrN; j++)
			drum2[i][j] = -1;//memoram pozitia din matrice, nu cheia
	for (k = 0; k < nrN; k++) {//incercam actualizarea drumurilor prin nodul k
		for (i = 0; i < nrN; i++)//de la fiecare nod
			for (j = 0; j < nrN; j++)//la toate celelalte
				if (arc2[i][j] > arc2[i][k] + arc2[k][j]) {//este mai ieftin prin k
					arc2[i][j]=arc2[j][i] = arc2[i][k] + arc2[k][j];//actualizam cost
					drum2[i][j]= drum2[j][i] = k;//actualizam drum
				}
	}
}
void AfisDrum2(int i, int j) {
	if (drum2[i][j] != -1) {
		AfisDrum2(i, drum2[i][j]);
		cout << " " << nod[drum2[i][j]].cheie;
		AfisDrum2(drum2[i][j], j);
	}
}
int main() {
	int p[2],x;

	if ((f = fopen("graf.txt", "r")) == NULL) {
		cout << "Eroare la deschiderea fisierului.";
		_getch(); exit(1);
	}
	fscanf(f, "%d", &nrA);
	nrN = 0;//nr. de noduri
	for (i = 0; i < nrA; i++) {
		fscanf(f, "%d%d%d%d", &m[0], &m[1], &m[2],&m[3]);
		for (j = 0; j < 2; j++) {
			p[j] = CautaNod(m[j]);
			if (p[j] == -1) {//nu s-a gasit => il adaug
				p[j] = nrN;
				nod[nrN].cheie = m[j];
				for (k = 0; k < nrN; k++)//init. cu 'mare' a tuturor conexiunilor lui
				{
					arc[nrN][k] = arc[k][nrN] = mare;
					arc2[nrN][k] = arc[k][nrN] = mare;
				}
				arc[nrN][nrN] = 0;//diagonala e minima
				arc2[nrN][nrN] = 0;
				nrN++;
			}
		}
		//adaug muchia
		if(m[3]==0)
			arc[p[0]][p[1]] = m[2];
		else
			arc[p[0]][p[1]]= arc[p[1]][p[0]] = m[2];
		arc2[p[0]][p[1]] = arc2[p[1]][p[0]] = m[2];
	}
	fclose(f);
	AfisImplGraf();
	Floyd();
	mini = mare;
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++) {
			sum[i]=sum[i]+ arc[i][j];
		}
	}
	for (i = 0; i < nrN; i++)
	{
		if (sum[i] < mini)
		{
			mini = sum[i];
			x = nod[i].cheie;
		}
	}
	cout << "\nMagazinul cel mai apropiat de toate celelalte este " << x<<endl;
	cout << "\nIntroduceti cheia unui magazin: ";
	cin >> m1;
	cout << "\nIntroduceti cheia altui magazin: ";
	cin >> m2;
	cout << "\nDrumul cel mai scurt";
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++)
			if (i != j && arc[i][j] != mare && nod[i].cheie==m1 && nod[j].cheie==m2) {
				cout << " de la " << nod[i].cheie << " la " <<nod[j].cheie << " (cost " << arc[i][j] << ") este prin nodurile: ";
				AfisDrum(i, j);
			}
	}
	Floyd2();
	cout << "\nDaca toate drumurile ar fi cu sens dublu, cel mai scurt drum ";
	for (i = 0; i < nrN; i++) {
		for (j = 0; j < nrN; j++)
			if (i != j && arc2[i][j] != mare && nod[i].cheie == m1 && nod[j].cheie == m2) {
				cout << " de la " << nod[i].cheie << " la " << nod[j].cheie << " (cost " << arc2[i][j] << ") ar fi prin nodurile: ";
				AfisDrum2(i, j);
			}
	}
	cout << endl;
	_getch();
	return 0;
}