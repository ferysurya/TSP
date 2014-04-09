#include <iostream>
#include "Matriks.h"
#include "Simpul.h"
#include "File.h"
using namespace std;

#define Nil 0

int main() {

	// Set nama file
	File F("Filematriks.txt");

	// Baca file
	F.bacaMatriks();

	// Tampilkan matriksBobot
	Simpul::matriksBobot.Print();

	// Reduksi matriksBobot
	Simpul::matriksBobot.Reduksi();

	// Tampilkan matriksBobot tereduksi
	Simpul::matriksBobot.Print();

	// Buat simpul Start
	//Simpul Start(0, 
	


	int X;
	cin >> X;

	return 0;
}