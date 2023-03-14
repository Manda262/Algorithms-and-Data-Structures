#ifndef GRAF
#define GRAF
#include <iostream>
#include <vector>
#include<queue>
#include<set>
#include<stack>
#include <limits>
#include <iterator>
const int MAX = 100;
using namespace std;
struct Elem {
	int w;    // tezina
	int cvi;  // cvor iz indices
	int cve;  // cvor iz edges
	Elem(int we, int cvij, int cvet) {
		w = we;
		cvi = cvij;
		cve = cvet;
	}
};

struct Cmp {
	bool operator()(const Elem& e1, const Elem& e2) const {
		return e1.w > e2.w;
	}
};
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
		g->ind.erase(g->ind.begin() + b - 1);  // brisanje cvora iz indices
		for (int i = 0; i < g->edg.size(); i++) { // uklanjanje svakog elemnta edges kome je cvor koji se uklanja bio sused i namestanje indices
			if (g->edg[i] == b) {
				g->edg.erase(g->edg.begin() + i);
				for (int j = 0; j < g->ind.size(); j++) {
					if (g->ind[j] - 1 > i) g->ind[j]--;
				}
			}
		}
		g->n--;
	}
	friend void dodajGranu(Graf* g, int k, int k1) { // int koji kontrolise da li je unet tezinski ili netezinski graf//
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
		cout << "Tezine: ";
		for (int i = 0; i < g->tez.size(); i++)
			cout << g->tez[i] << " ";
		cout << endl;
		cout << "Izgradjen: ";
		for (int i = 0; i < g->tez.size(); i++)
			cout << g->izgr[i] << " ";
		cout << endl;
	}
	friend void minCena(Graf* g) {
		priority_queue<Elem, vector<Elem>, Cmp > pq;
		vector<set<int, greater<int>>> se;
		int cena = 0;
		for (int i = 0; i < g->ind.size() - 1; i++) {  // provera da li se moze oformiti minimalno obuhvatno stablo//
			if (g->ind[i] == g->ind[i + 1]) {
				cout << "Minimalna cena ne moze da se nadje jer nisu svi cvorovi povezani" << endl;
				return;
			}
		}
		for (int i = 0; i < g->ind.size() - 1; i++) {
			for (int j = g->ind[i] - 1; j < g->ind[i + 1] - 1; j++) {
				pq.push(Elem(g->tez[j], i + 1, g->edg[j]));
			}
		}
		for (int i = 0; i < g->ind.size() - 1; i++) {
			set<int, greater<int>> s;
			s.insert(i + 1);
			se.push_back(s);
			s.clear();
		}
		int br1 = 0;
		int brisi1 = 0;
		int brisi2 = 0;
		for (int num = 0; num < g->ind.size() - 2;) {
			set<int, greater<int>> s;
			for (int i = 0; i < se.size(); i++) {
				if (((se[i].count(pq.top().cve))) && (!(se[i].count(pq.top().cvi)))) {   //ako se oba cvora ne nalaze u skupu dodaj cenu grane u ukupnu cenu
					for (auto it = se[i].begin(); it != se[i].end(); ++it)
						s.insert(*it);
					brisi1 = i;
					br1++;
				}
				if (!(se[i].count(pq.top().cve)) && (se[i].count(pq.top().cvi))) {
					for (auto it = se[i].begin(); it != se[i].end(); ++it)
						s.insert(*it);
					brisi2 = i;
					br1++;
				}
			}


			if (br1 == 2) {
				se.push_back(s);
				num++;
				if (brisi1 > brisi2) {
					se.erase(se.begin() + brisi2);
					se.erase(se.begin() + brisi1 - 1);
				}
				else {
					se.erase(se.begin() + brisi1);
					se.erase(se.begin() + brisi2 - 1);
				}
				cena += pq.top().w;
				s.clear();
				br1 = 0;
			}
			pq.pop();
		}
		cout << endl;
		cout << "Najmanja cena izgradje metroa je " << cena << endl;
	}
	friend void najbrziPut(Graf* g) {
		vector<int> pr1; // pr1 i pr2 sluze za nalazenje prethodnika kod Dijkstrinog algoritma //
		vector<int> pr2;
		vector<int> duz1; // duz1 i duz2 sluze za nalazenje najkraceg rastojanja do nekog cvora // 
		vector<int> duz2;
		set<int> skup;
		stack<int> stek;
		int v;
		cout << "Unesite cvor na kom se vatrogasci parkiraju: " << endl;
		cin >> v;
		int a = numeric_limits<int>::max();  // a je beskonacno // 
		int nastavak1 = 0;
		for (int i = g->ind[v - 1] - 1, j = 1; i < g->ind[v] - 1; j++) {
			nastavak1 = j;
			if (g->edg[i] == j) {
				pr1.push_back(v);
				duz1.push_back(g->tez[i]);
				i++;
			}
			else {
				pr1.push_back(0);
				duz1.push_back(a);
			}
		}
		for (int i = nastavak1; i < g->ind.size() - 1; i++) {
			pr1.push_back(0);
			duz1.push_back(a);

		}


		for (int k = 0; k < pr1.size() - 1; k++) {   // prolazak kroz elemente n-1 puta, gde je n roj cvorova
			int min = a;
			int minind = a;
			for (int i = 0; i < pr1.size(); i++) {   // trazenje minimuma za svaki prolazak // 
				if ((duz1[i] < min) && (!(skup.count(i + 1)))) {
					min = duz1[i];
					minind = i;
				}
			}
			skup.insert(minind + 1); // stavljanje cvorova kroz koje sam prosao u skup //
			int nastavak = 0;
			if (minind == a) {
				nastavak = 0;
			}
			else {
				for (int i = g->ind[minind] - 1, j = 1; i < g->ind[minind + 1] - 1; j++) {
					if (g->edg[i] == j) {
						if ((g->edg[i] != v) && (g->tez[i] + duz1[minind] < duz1[j - 1])) {
							duz2.push_back(g->tez[i] + duz1[minind]);
							pr2.push_back(minind + 1);
						}
						if ((g->edg[i] == v) || (g->tez[i] + duz1[minind] >= duz1[j - 1])) {
							duz2.push_back(duz1[j - 1]);
							pr2.push_back(pr1[j - 1]);
						}
						i++;
					}
					else {
						duz2.push_back(duz1[j - 1]);
						pr2.push_back(pr1[j - 1]);
					}
					if (minind != a) nastavak = j;;

				}
			}
			for (int i = nastavak; i < pr1.size(); i++) {
				duz2.push_back(duz1[i]);
				pr2.push_back(pr1[i]);
			}
			duz1.swap(duz2);
			pr1.swap(pr2);
			duz2.clear();
			pr2.clear();

		}

		for (int i = 0; i < duz1.size(); i++) {
			if (pr1[i] == 0 && (i != v - 1)) {
				cout << endl << "Ne postoji put do cvora " << i + 1;
			}
			if (pr1[i] == v) {
				cout << endl << "Postoji direktan put do cvora " << i + 1 << " V-" << i + 1 << " (duzina " << duz1[i] << ")";
				for (int j = g->ind[v - 1] - 1; j < g->ind[v] - 1; j++) {
					if ((g->edg[j] == (i + 1)) && g->izgr[j]) {
						cout << " sa neizgradjenim putem";
						break;
					}
				}
			}
			if (pr1[i] != 0 && pr1[i] != v) {
				for (int prosli = pr1[i]; prosli != v; prosli = pr1[prosli - 1]) {
					stek.push(prosli);
				}
				cout << endl << "Postoji put do cvora " << i + 1 << " i to V";
				int izz = 0;
				for (int i = g->ind[v - 1] - 1; i < g->ind[v] - 1; i++) {
					if (g->edg[i] == stek.top()) izz += g->izgr[i];
				}
				while (!stek.empty())
				{
					int t = stek.top();
					cout << "-" << t;
					stek.pop();
					for (int j = g->ind[t - 1] - 1; j < g->ind[t] - 1; j++) {
						if ((stek.empty()) && (g->edg[j] == i + 1)) {
							izz += g->izgr[j];
						}
						if (!(stek.empty()) && (g->edg[j] == stek.top())) {
							izz += g->izgr[j];
						}
					}
				}
				cout << "-" << i + 1;
				cout << " (duzine " << duz1[i] << ")";
				cout << " sa " << izz << " neizgradjenih puteva";
			}
		}
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
	int t1;
	bool tacno1 = true;
	while (tacno1) {
		cout << "Da li su svi putevi u vasem zadatku izgradjeni? " << endl;
		cout << "Unesite 1 ako nisu, a 0 ako jesu" << endl;
		cin >> t1;
		if (t1 != 0 && t1 != 1) {
			cout << "Uneli ste broj koji nije bio opcija, molim unesite broj opet " << endl;
		}
		else {
			tacno1 = false;
		}

	}

	Graf* g1 = new Graf;
	while (true) {
		cout << "Unesite redni broj operacije koju zelite da izvrsite" << endl;
		cout << "1. Dodavanje grane izmedju 2 cvora iz grafa" << endl;
		cout << "2. Ispis cene " << endl;
		cout << "3. Trazenje najblizeg cvora " << endl;
		cout << "0. Kraj rada" << endl << endl;

		int op;
		cin >> op;

		switch (op) {
		case 1:
			dodajGranu(g1, 1, t1);
			break;
		case 2:
			minCena(g1);
			break;
		case 3:
			najbrziPut(g1);
			break;
		case 0:
			cout << endl << endl << "Dovidjenja! " << endl;
			exit(-1);
			break;
		default:
			cout << "Broj koji ste uneli ne predstavlja ni jednu operaciju, " << endl;
			cout << "unesite novi redni broj" << endl;
		}

	}

}