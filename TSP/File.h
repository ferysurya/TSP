#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Matriks.h"
#include "Simpul.h"
using namespace std;

class File{
private:
	string filename;	// Nama file yg akandibaca

public:
	File();
	File(string namafile);
	~File();
	void bacaMatriks();

};
