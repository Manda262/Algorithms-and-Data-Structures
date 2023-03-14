#ifndef GRAF
#define GRAF
#include <iostream>
#include <vector>
const int MAX = 100;
using namespace std;
class Graf
{
private:
	vector<int> ind;
	vector<int> edg;
	vector<int> tez;
	vector<bool> izgr;
	int n;
public:
	Graf() {
		cout << "Unesite broj cvorova: ";
		int b;
		cin >> b;
		n = b;
		cout << "Pocetni cvorovi su: " << endl;
		for (int i = 1; i <= n + 1; i++) {
			ind.push_back(1);
			if (i < n + 1) cout << i << " ";
		}
		cout << endl;
		edg.push_back(0);
		tez.push_back(0);
		izgr.push_back(0);
		cout << endl;
	}
	~Graf() {
		ind.clear();
		edg.clear();
		tez.clear();
		izgr.clear();
		n = 0;
	}
	friend void dodajCvor(Graf* g) {
		if (g->n == 0) {
			cout << "Graf je obrisan" << endl;
			return;
		}
		g->ind.push_back(g->ind[g->n]);
		g->n++;
		cout << "Uspesno dodat cvor" << endl;
	}
	friend void ukloniCvor(Graf* g) {
		if (g->n == 0) {
			cout << "Graf je obrisan" << endl;
			return;
		}
		cout << endl << "Unesite cvor koji zelite da uklonite: " << endl;
		int b;
		cin >> b;
		if (b <= 0 || b > g->ind.size() - 1) {
			cout << "Uneli ste cvor koji ne postoji" << endl;
			return;
		}
		int tmp = g->ind[b - 1];
		for (int i = g->ind[b] - 2; i >= g->ind[b - 1] - 1; i--) {  // brisanje dela edges koji odgovara susedima cvora koji se brise
			g->edg.erase(g->edg.begin() + i);
		}
		int pos = g->ind[b] - g->ind[b - 1];
		for (int i = b; i < (g->ind.size()); i++) { // namestanje indices nakon promene
			g->ind[i] -= pos;
		}
		int m = g->edg.size();
		g->ind.erase(g->ind.begin() + b - 1);  // brisanje cvora iz indices
		for (int i = 0; i < m; i++) { // uklanjanje svakog elemnta edges kome je cvor koji se uklanja bio sused i namestanje indices
			if (g->edg.size() <= i) {
				if (g->edg[0] == b) {
					g->edg.erase(g->edg.begin());
					for (int j = 0; j < g->ind.size(); j++) {
						if (g->ind[j] - 1 > i) g->ind[j]--;
					}
				}
			}
			else {
				if (g->edg[i] == b) {
					g->edg.erase(g->edg.begin() + i);
					for (int j = 0; j < g->ind.size(); j++) {
						if (g->ind[j] - 1 > i) g->ind[j]--;
					}
				}
			}
		}
		g->n--;
	}
	friend void dodajGranu(Graf* g, int k, int k1) {
		if (g->n == 0) {
			cout << "Graf je obrisan" << endl;
			return;
		}
		cout << "Unesite cvorove izmedju kojih zelite da dodate granu" << endl;
		int c1, c2, veci, manji;
		cin >> c1 >> c2;
		if (c1 == c2) {
			cout << "Ne moze da se formira grana koja ide iz nekog cvora u taj isti cvor " << endl;
			return;
		}
		if (c1 > c2) {
			veci = c1;
			manji = c2;
		}
		if (c1 < c2) {
			manji = c1;
			veci = c2;
		}
		if (veci > g->ind.size() - 1 || manji <= 0) {
			cout << "Uneli ste cvorove koji ne postoje" << endl;
			return;
		}
		int br = 0;
		for (int i = g->ind[veci - 1] - 1; i < g->ind[veci] - 1; i++) { // provera ispravnosti podataka
			if (g->edg[i] == manji) {
				br++;
				break;
			}
		}
		for (int i = g->ind[manji - 1] - 1; i < g->ind[manji] - 1; i++) {
			if (g->edg[i] == veci) {
				br++;
				break;
			}
		}
		if (br == 2) {
			cout << "Uneli ste granu koja vec postoji " << endl;
			return;
		}

		int t = 0;
		if (k == 1) {
			cout << "Zeljena grana moze da se formira, unesite tezinu unete grane" << endl;
			cin >> t;
		}
		bool tacno2 = true;
		int info = 1;
		if (k1 == 1) {
			while (tacno2) {
				cout << "Tezine su unete, mozete uneti informaciju da li je put izgradjen ili nije (1 - nije, 0 - jeste) ";
				cin >> info;
				if (info != 1 && info != 0) {
					cout << "Niste uneli korektnu vrednost, molim unesite opet " << endl;
				}
				else {
					tacno2 = false;
				}
			}
			cout << "Informacija je uspesno dodata! " << endl;
		}

		if (g->edg.size() == 1) {
			g->edg.insert(g->edg.begin(), manji);
			g->edg.pop_back();
			g->tez.insert(g->tez.begin(), t);
			g->tez.pop_back();
			g->izgr.insert(g->izgr.begin(), info);
			g->izgr.pop_back();
		}
		else {
			for (int i = g->edg.size() - 1; i >= g->ind[veci - 1] - 2; i--) { // nalazenje manjeg cvora u delu edges koji odgovara susedima veceg cvora
				if (i == -1 && g->edg[0] < manji && g->ind[veci] != 1) {
					g->edg.insert(g->edg.begin() + 1, manji);
					g->tez.insert(g->tez.begin() + 1, t);
					g->izgr.insert(g->izgr.begin() + 1, info);
					break;
				}
				if (i == -1 && g->edg[0] >= manji && g->ind[veci] != 1) {
					g->edg.insert(g->edg.begin(), manji);
					g->tez.insert(g->tez.begin(), t);
					g->izgr.insert(g->izgr.begin(), info);
					break;
				}
				if (i == -1 && g->ind[veci] == 1) {
					g->edg.insert(g->edg.begin(), manji);
					g->tez.insert(g->tez.begin(), t);
					g->izgr.insert(g->izgr.begin(), info);
					break;
				}
				if (i == g->ind[veci - 1] - 2) {
					g->edg.insert(g->edg.begin() + i + 1, manji);
					g->tez.insert(g->tez.begin() + i + 1, t);
					g->izgr.insert(g->izgr.begin() + i + 1, info);
					break;
				}
				if (i <= g->ind[veci] - 2 && (g->edg[i] < manji)) {
					g->edg.insert(g->edg.begin() + i + 1, manji);
					g->tez.insert(g->tez.begin() + i + 1, t);
					g->izgr.insert(g->izgr.begin() + i + 1, info);
					break;
				}
			}
		}
		if (g->edg.size() == 1) {
			g->edg.insert(g->edg.begin(), veci);
			g->tez.insert(g->tez.begin(), t);
			g->izgr.insert(g->izgr.begin(), info);
		}


		else {
			for (int i = g->ind[veci - 1] - 2; i >= g->ind[manji - 1] - 2; i--) { // nalazenje veceg cvora u delu edges koji odgovara susedima manjeg cvora
				if (i == -1 && g->edg[0] < veci && g->ind[manji] != 1) {
					g->edg.insert(g->edg.begin() + 1, veci);
					g->tez.insert(g->tez.begin() + 1, t);
					g->izgr.insert(g->izgr.begin() + 1, info);
					break;
				}
				if (i == -1 && g->edg[0] >= veci && g->ind[manji] != 1) {
					g->edg.insert(g->edg.begin(), veci);
					g->tez.insert(g->tez.begin(), t);
					g->izgr.insert(g->izgr.begin(), info);
					break;
				}
				if (i == -1 && g->ind[manji] == 1) {
					g->edg.insert(g->edg.begin(), veci);
					g->tez.insert(g->tez.begin(), t);
					g->izgr.insert(g->izgr.begin(), info);
					break;
				}
				if (i == g->ind[manji - 1] - 2) {
					g->edg.insert(g->edg.begin() + i + 1, veci);
					g->tez.insert(g->tez.begin() + i + 1, t);
					g->izgr.insert(g->izgr.begin() + i + 1, info);
					break;
				}
				if (i <= g->ind[manji] - 2 && g->edg[i] < veci) {
					g->edg.insert(g->edg.begin() + i + 1, veci);
					g->tez.insert(g->tez.begin() + i + 1, t);
					g->izgr.insert(g->izgr.begin() + i + 1, info);
					break;
				}
			}
		}
		for (int i = g->ind.size() - 1; i >= 0; i--) { // namestanje indices
			if (i > veci - 1) {
				g->ind[i] += 2;
			}
			if (i > manji - 1 && i <= veci - 1) {
				g->ind[i]++;
			}
		}
	}
	friend void ukloniGranu(Graf* g) {
		if (g->n == 0) {
			cout << "Graf je obrisan" << endl;
			return;
		}
		cout << "Unesite cvorove izmedju kojih se brise grana" << endl;
		int c1, c2, veci, manji;
		cin >> c1 >> c2;
		if (c1 > c2) {
			veci = c1;
			manji = c2;
		}
		else {
			manji = c1;
			veci = c2;
		}
		int br = 0;
		if (veci > g->ind.size() - 1 || manji <= 0) {
			cout << "Uneli ste cvor koji ne postoji!" << endl;
			return;
		}
		for (int i = g->ind[veci - 1] - 1; i < g->ind[veci] - 1; i++) { // provera ispravnosti podataka
			if (g->edg[i] == manji) {
				br++;
				break;
			}
		}
		for (int i = g->ind[manji - 1] - 1; i < g->ind[manji] - 1; i++) {
			if (g->edg[i] == veci) {
				br++;
				break;
			}
		}
		if (br == 2) {
			for (int i = g->ind[veci - 1] - 1; i < g->ind[veci] - 1; i++) { // brisanje manjeg cvora iz edges
				if (g->edg[i] == manji) {
					g->edg.erase(g->edg.begin() + i);
					g->tez.erase(g->tez.begin() + i);
					g->izgr.erase(g->izgr.begin() + i);
					break;
				}
			}
			for (int i = g->ind[manji - 1] - 1; i < g->ind[manji] - 1; i++) { // brisanje veceg cvora iz edges
				if (g->edg[i] == veci) {
					g->edg.erase(g->edg.begin() + i);
					g->tez.erase(g->tez.begin() + i);
					g->izgr.erase(g->izgr.begin() + i);
					break;
				}
			}
		}
		else {
			cout << "Niste uneli granu koja postoji " << endl;
			return;
		}

		for (int i = g->ind.size() - 1; i >= 0; i--) { // namestanje indices
			if (i > veci - 1) {
				g->ind[i] -= 2;
			}
			if (i > manji - 1 && i <= veci - 1) {
				g->ind[i]--;
			}
		}
	}
	friend void brisiGraf(Graf* g) {
		if (g->n == 0) {
			cout << "Graf je obrisan" << endl;
			return;
		}
		g->ind.clear();
		g->edg.clear();
		g->tez.clear();
		g->izgr.clear();
		g->n = 0;
		cout << "Uspesno ste obrisali graf" << endl;
	}
	friend void pisi(Graf* g) {
		cout << "Elementi niza indices: ";
		for (int i = 0; i < g->ind.size(); i++)
			cout << g->ind[i] << " ";
		cout << endl;
		cout << "Elementi niza edges: ";
		for (int i = 0; i < g->edg.size(); i++)
			cout << g->edg[i] << " ";
		cout << endl;
	}

};

#endif








#include "graf.h"
#include <iostream>
using namespace std;

int main() {
	cout << "Dobrodosli u program koji vrsi operacije nad neusmerenim grafom. " << endl;
	cout << "U okviru ovog programa se upotrebljava sekvencijalna reprezentacija " << endl;
	cout << "koriscenjem linearizovanih lista susednosti" << endl << endl;

	Graf* g1 = new Graf;
	while (true) {
		cout << "Unesite redni broj operacije koju zelite da izvrsite" << endl;
		cout << "1. Dodavanje cvora u graf" << endl;
		cout << "2. Uklanjanje zeljenog cvora iz grafa" << endl;
		cout << "3. Dodavanje grane izmedju 2 cvora iz grafa" << endl;
		cout << "4. Uklanjanje postojecih grana iz grafa" << endl;
		cout << "5. Ispisivanje grafa u datoj reprezentaciji" << endl;
		cout << "6. Brisanje grafa iz memorije" << endl;
		cout << "0. Kraj rada" << endl << endl;

		int op;
		cin >> op;

		switch (op) {
		case 1:
			dodajCvor(g1);
			break;
		case 2:
			ukloniCvor(g1);
			break;
		case 3:
			dodajGranu(g1, 0, 0);
			break;
		case 4:
			ukloniGranu(g1);
			break;
		case 5:
			pisi(g1);
			break;
		case 6:
			brisiGraf(g1);
			break;
		case 0:
			exit(-1);
			cout << endl << endl << "Dovidjenja! " << endl;
			break;
		default:
			cout << "Broj koji ste uneli ne predstavlja ni jednu operaciju, " << endl;
			cout << "unesite novi redni broj" << endl;
		}

	}


}