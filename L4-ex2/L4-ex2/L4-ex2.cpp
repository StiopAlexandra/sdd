/*Se consideră un arbore binar care reprezintă o expresie aritmetică. Nodurile terminale
sunt numere, iar cele interne sunt operatorii aritmetici binari: +, –, * şi /, precum şi operatorii unari: +
şi –. Aceştia din urmă vor avea operandul ca fiu drept.
Dacă expresia este corectă, să se afişeze şi să se evalueze. */

#define use_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
using namespace std;
typedef struct _nodAB {
	char* info;
	_nodAB* stanga;
	_nodAB* dreapta;
}nodAB;

nodAB* rad;
char info[100],ec[100];
int i;
void AdaugNod(nodAB** p, int niv) {
	gets_s(info);
	if (info[0] != '\0') {
		*p = new nodAB;
		(*p)->info = new char[strlen(info) + 1];
		strcpy((*p)->info, info);
		for (i = 0; i <= niv; i++) cout << " ";
		cout << "Fiul stang al lui " << (*p)->info << " este: ";
		AdaugNod(&(*p)->stanga, niv + 1);
		for (i = 0; i <= niv; i++) cout << " ";
		cout << "Fiul drept al lui " << (*p)->info << " este: ";
		AdaugNod(&(*p)->dreapta, niv + 1);
	}
	else *p = NULL;
}
int eval(nodAB* nod) {
	if (!nod)
		return 0;
	if (!nod->stanga && !nod->dreapta)
		return atoi(nod->info);
	int l_val = eval(nod->stanga);
	int r_val = eval(nod->dreapta);
	if (!strcmp(nod->info,"+"))
		return l_val + r_val;
	if (!strcmp(nod->info,"-"))
		return l_val - r_val;
	if (!strcmp(nod->info, "*"))
		return l_val * r_val;
	return l_val / r_val;
}
void inordine(nodAB* p)
{
	if (p)
	{	
		if (p->stanga) {
			strcat(ec, "(");
			inordine(p->stanga);
		}
		strcat(ec,p->info);
		if (p->dreapta) {
			inordine(p->dreapta);
			strcat(ec, ")");
		}
	}
}

int main() {

	rad = NULL;
	cout << "Radacina arborelui: ";
	AdaugNod(&rad, 0);
	cout << endl;
	cout << "Expresia este:\t";
	inordine(rad);
	ec[strlen(ec) - 1]='\0';
	cout << ec << endl;
	cout << "Rezultatul expresie este:\t";
	cout << eval(rad) << endl;
}


