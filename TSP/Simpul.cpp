#include "Simpul.h"

// Static variable
Matriks Simpul::matriksBobot;

// CTOR
Simpul::Simpul() {}

// CTOR w/ PARAM
Simpul::Simpul(int noSimpul, Simpul simpulParent)
{
	this->noSimpul = noSimpul;
	MT = simpulParent.getMatriksTereduksi();
	MT.Reduksi();	// Reduksi matriks parent-nya
	Cost = hitungCost(simpulParent);
}

// DTOR
Simpul::~Simpul() {}

int Simpul::hitungCost(Simpul simpulParent) 
{
	int totalCost;
	int i = simpulParent.getNoSimpul();
	int j = noSimpul;
	totalCost = simpulParent.getCost() + Simpul::matriksBobot.getElmt(i,j) + MT.getPengurang();

	return totalCost;
}

bool Simpul::isSolusi()
{
	// Iterasi baris matriks
	int i=0;
	bool Found = false;
	while(!Found && i<MT.Size())
	{
		int j=0;
		// Iterasi kolom matriks
		while(!Found && j<MT.Size())
		{
			if(MT.getElmt(i,j) != -99)
				Found = true;
			else
				++j;
		}
		++i;
	}

	// Jika ditemukan angka selain -99(infiniti), maka bukan solusi
	return !Found;
}

int Simpul::getCost()
{
	return Cost;
}

int Simpul::getNoSimpul()
{
	return noSimpul;
}

Matriks Simpul::getMatriksTereduksi()
{
	return MT;

}