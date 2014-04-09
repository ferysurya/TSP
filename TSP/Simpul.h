#pragma once

#include <iostream>
#include <vector>
#include "Matriks.h"
using namespace std;

class Simpul{
private:
	int noSimpul;	// Kota/Simpul
	int Cost;		// Cost simpul
	Matriks MT;		// Matriks tereduksi-nya
	vector<int> PassedNode;		// Daftar simpul yang telah dilewati
	int hitungCost(Simpul simpulParent); 

public:
	static Matriks matriksBobot;		// matriks bobot graf (A)

	Simpul();
	Simpul(int noSimpul, Simpul simpulParent);
	~Simpul();	
	bool isSolusi();
	int getCost();
	int getNoSimpul();
	Matriks getMatriksTereduksi();
};
