#include "Matriks.h"

// CTOR
Matriks::Matriks()
{}

// CTOR w/ PARAM
Matriks::Matriks(vector<vector<int>> M)
{
	this->M = M;
}

// CCTOR
Matriks::Matriks(const Matriks &R)
{
	M = R.M;
}

// OPREQ
Matriks& Matriks::operator=(const Matriks &R)
{
	M = R.M;

	return *this;
}

// DTOR
Matriks::~Matriks() {}

void Matriks::Print()
{
	for (auto it = M.begin(); it != M.end(); ++it)
	{
		for (auto itcol = it->begin(); itcol != it->end(); ++itcol)
		{
			// Jika 1 digit
			if (*itcol<10 && *itcol!=-99)
				cout << "  " << *itcol << " ";
			else
			if (*itcol<100 && *itcol != -99)	// Jika 2 digit
				cout << " " << *itcol << " ";
			else
				cout << *itcol << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Matriks::Reduksi()
{
	// Reduksi baris
	for (int row = 0; row < M.size(); ++row)
	{
		// Jika tidak ada nol pada baris -> reduksi baris
		if (!isNolExistAtRow(row))
		{
			int Pengurang = getSmallestRowValue(row);
			reduksiBaris(row, Pengurang);
		}
	}

	//Reduksi kolom
	for (int column = 0; column < M.size(); ++column)
	{
		// Jika tidak ada nol pada kolom -> reduksi kolom
		if (!isNolExistAtColumn(column))
		{
			int Pengurang = getSmallestColumnValue(column);
			reduksiKolom(column, Pengurang);
		}
	}
}

// Mendapatkan r
int Matriks::getPengurang()
{
	int totalPengurang=0;

	// Reduksi baris
	for (int row = 0; row < M.size(); ++row)
	{
		// Jika tidak ada nol pada baris -> reduksi baris
		if (!isNolExistAtRow(row))
		{
			int Pengurang = getSmallestRowValue(row);
			reduksiBaris(row, Pengurang);
			totalPengurang += Pengurang;
		}
	}

	//Reduksi kolom
	for (int column = 0; column < M.size(); ++column)
	{
		// Jika tidak ada nol pada kolom -> reduksi kolom
		if (!isNolExistAtColumn(column))
		{
			int Pengurang = getSmallestColumnValue(column);
			reduksiKolom(column, Pengurang);
			totalPengurang += Pengurang;
		}
	}

	return totalPengurang;
}

void Matriks::setMatriks(vector<vector<int>> MM)
{
	M = MM;
}

int Matriks::getElmt(int i, int j)
{
	return M[i][j];
}

int Matriks::Size()
{
	return M.size();
}

// Fungsi reduksi matriks
bool Matriks::isNolExistAtRow(int row)
{
	int column = 0;
	while (column < M.size() && M[row][column]!=0)
	{
		++column;
	}

	if (column >= M.size())
		return false;
	else
		return true;
}

bool Matriks::isNolExistAtColumn(int column)
{
	int row = 0;
	while (row < M.size() && M[row][column] != 0)
	{
		++row;
	}

	if (row >= M.size())
		return false;
	else
		return true;
}

int Matriks::getSmallestRowValue(int row)
{
	int Smallest = 9999; // Set angka yg besar sembarang
	for (int column = 1; column < M.size(); ++column)
	{
		if (M[row][column] < Smallest && M[row][column]!=-99)
			Smallest = M[row][column];
	}

	return Smallest;
}

int Matriks::getSmallestColumnValue(int column)
{
	int Smallest = 9999; // Set angka yg besar sembarang
	for (int row = 1; row < M.size(); ++row)
	{
		if (M[row][column] < Smallest && M[row][column] != -99)
			Smallest = M[row][column];
	}
	
	return Smallest;
}

void Matriks::reduksiBaris(int row, int Pengurang)
{
	for (int column = 0; column < M.size(); ++column)
	{
		// Jika nilai elemen != -99, kurangkan dengan pengurang
		if (M[row][column] != -99)
			M[row][column] -= Pengurang;
	}
}

void Matriks::reduksiKolom(int column, int Pengurang)
{
	for (int row = 0; row < M.size(); ++row)
	{
		// Jika nilai elemen != -99, kurangkan dengan pengurang
		if (M[row][column] != -99)
			M[row][column] -= Pengurang;
	}
}