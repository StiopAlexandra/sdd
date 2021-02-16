/*Pentru cuprinsul unei cărţi memorat sub formă de arbore generalizat, în implementarea
indicator spre părinte, să se realizeze următoarele operaţii interactive:
a). adăugarea unui capitol sau a unui subcapitol într-un (sub)capitol dat.
b). ştergerea unui (sub)capitol (cu toate subcapitolele lui).
c). mutarea unui subcapitol (cu toate subcapitolele lui) într-un alt (sub)capitol dat.*/

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
int aux[nrMaxN];
void Citire(int idxPar, int cheie, int niv) {
	int i, j, idx, nrFii;
	//adaugarea nodului
	idx = nrEl; //retinem indicele noului nod
	A[nrEl].cheie = cheie;
	A[nrEl].parinte = idxPar;
	nrEl++;
	nrFii = 0; //inca nu are fii
	do { //adaugarea fiilor
		for (i = 0; i < niv; i++) cout << " ";
		if (cheie == 1)
			cout << "Capitolul " << ++nrFii << " al cartii este ";
		else
			cout << "Subcapitolul " << ++nrFii << " al capitolului " << cheie << " este ";
		cin >> j;
		if (j) Citire(idx, j, niv + 1);
	} while (j);
}
void AdaugSubcapitol(int index, int el) {

	for (int i = nrEl; i > index; i--)
	{
		A[i].cheie = A[i - 1].cheie;
		if (A[i - 1].parinte >= index)
			A[i].parinte = A[i - 1].parinte + 1;
		else
			A[i].parinte = A[i - 1].parinte;
	}
	nrEl++;
	A[index].cheie = el;
	A[index].parinte = index - 1;

}
void StergereCapitol(int index) {
	int nr = 1;
	for (int i = index + 1; i < nrEl - 1; i++) {
		if (A[i].parinte >= index)
		{
			for (int j = i; j < nrEl; j++) {
				A[j].cheie = A[j + 1].cheie;
				A[j].parinte = A[j + 1].parinte;
			}
			nr++;
			nrEl--;
			i--;
		}
		else
			break;
	}
	for (int i = index; i < nrEl; i++) {
		A[i].cheie = A[i + 1].cheie;
		if (A[i + 1].parinte > nr)
			A[i].parinte = A[i + 1].parinte - nr;
		else
			A[i].parinte = A[i + 1].parinte;
	}
	nrEl--;

}
void MutareSubcapitol(int cap_m, int index_m, int index) {

	for (int i =index_m; i < nrEl; i++) {
			A[i].cheie = A[i + 1].cheie;
			A[i].parinte = A[i + 1].parinte - 1;
	}
	nrEl--;
	AdaugSubcapitol(index + 1, cap_m);
}
void CreareAG() {
	int i;
	nrEl = 0;
	cout << "Cartea=radacina arborelui: ";
	cin >> i;
	if (i) Citire(-1, i, 1);
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
	int cap_ad, cap_st, cap_m, cap;
	cout << "\nAfisarea ca tablou:\n";
	Afisare();
	_getch();
	cout << "\n\nAfisarea ca arbore:";
	AfisareAG(0, 0);
	_getch();
	cout << "\n\nIntrodu cheia capitolului caruia doresti sa-i adaugi un subcapitol:\t";
	cin >> cap_ad;
	for (int i = 0; i < nrEl; i++)
		if(A[i].cheie==cap_ad)
		{
			AdaugSubcapitol(i+1,nrEl);
			cout << "\nAm adaugat subcapitolul cu cheia " << nrEl << " capitolului cu cheia " << cap_ad;
		}
	cout << "\nAfisarea ca tablou:\n";
	Afisare();
	_getch();
	cout << "\n\nAfisarea ca arbore:";
	AfisareAG(0, 0);
	_getch();
	cout << "\n\nIntrodu cheia capitolului pe care doresti sa-l stergi:\t";
	cin >> cap_st;
	for (int i = 0; i < nrEl; i++)
		if (A[i].cheie == cap_st)
		{
			StergereCapitol(i);
			cout << "\nAm sters capitolul cu cheia " << cap_st;
		}
	cout << "\nAfisarea ca tablou:\n";
	Afisare();
	_getch();
	cout << "\n\nAfisarea ca arbore:";
	AfisareAG(0, 0);
	_getch();
	cout << "\n\nIntrodu cheia subcapitolului pe care doresti sa-l muti:\t";
	cin >> cap_m;
	cout << "\nIntrodu cheia capitolului unde doresti sa atasezi subcapitolul " << cap_m << ":\t";
	cin >> cap;
	for (int i = 0; i < nrEl; i++)
		if (A[i].cheie == cap_m)
		{
			for (int j = 0; j < nrEl; j++)
				if (A[j].cheie == cap) {
					MutareSubcapitol(cap_m, i, j);
				}
		}
	cout << "\nAfisarea ca tablou:\n";
	Afisare();
	_getch();
	cout << "\n\nAfisarea ca arbore:";
	AfisareAG(0, 0);
	_getch();
}

