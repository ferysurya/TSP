#include <iostream>
#include <deque>
#include "Matriks.h"
#include "Simpul.h"
#include "File.h"
using namespace std;

#define Nil 0

int main() {

	// Handle file input
	File F("Filematriks.txt");
	F.bacaMatriks();

	// Tampilkan matriksBobot
	Simpul::matriksBobot.Print();

	// Reduksi matriksBobot
	Simpul::matriksBobot.Reduksi();		// Reduksi matriks Start
	Simpul::matriksBobot.Print();		// Tampilkan matriksBobot tereduksi
	
	// Buat simpul bestSolution
	Simpul bestSolution;
	bestSolution.setCost(9999); // Set sgt tinggi supaya pasti ditukar klo ada solusi pertama

	// Buat Queue Simpul
	vector<Simpul> Q;

	// Buat simpul Start & push ke Q
	Simpul Start;
	Start.setNoSimpul(1);
	Start.setMT(Simpul::matriksBobot);
	Start.setCost(Simpul::matriksBobot.getPengurang());
	Start.insertPassedNode(1);
	Simpul::simpulGenerated++;
	Q.push_back(Start);

	// Selama Q tidak kosong, expand simpul terdepan
	while(Q.size() != 0)
	{
		Simpul X = Q.front();	// Ambil simpul terdepan
		Q.erase(Q.begin());	// Pop depan
		if(!X.isSolusi())
		{
			X.Expand(Q);
		}
		else
		{
			if(X.getCost()<bestSolution.getCost())	// Jika X merupakan solusi terbaik
				bestSolution = X;			// Masukkan ke bestSolution
			
			if(bestSolution.isCostSmallest(Q))		// Jika tidak ada lg Cost(simpul) pd Q < Cost(bestSolutiono) 
			{
				Q.erase(Q.begin(),Q.end());		// Hapus semua isi Q
			}
		}
	}
	
	bestSolution.PrintPassedNode();
	cout << "Jumlah simpul dibangkitkan : " << Simpul::simpulGenerated << endl;

	int X;
	cin >> X;

	return 0;
}